#include <QApplication>
#include <QFileDialog>
#include "../filedlg.h"
#include "../command.h"
#include "../precomp.h"

typedef struct {
	unsigned int	filter;
	const char*		extention;
	const char*		mime_type;
} Filter;

static const Filter filters[] = {
	{ COMMAND_FILTER_ALL,	"*.*",			"all"			},
	{ COMMAND_FILTER_TXT,	"*.txt",		"text/plain"	},
	{ COMMAND_FILTER_BMP,	"*.bmp",		"image/bmp"		},
	{ COMMAND_FILTER_JPEG,	"*.jpeg *.jpg",	"image/jpeg"	},
	{ COMMAND_FILTER_PNG,	"*.png",		"image/png"		},
	{ COMMAND_FILTER_GIF,	"*.gif",		"image/gif"		},
};


static QString createFilter(unsigned int filter)
{
	QString str = "";

	int c = 0;
	unsigned int i = 0;

	for (; i < countof(filters); ++i) {

		if ((filters[i].filter & filter) != 0) {

			if (c == 0) {
				str += ";;";
				++c;
			}

			str += filters[i].mime_type;
			str += " (";
			str += filters[i].extention;
			str += ")";
		}
	}

	return str;
}

int file_dialog_open(Command* cmd_ptr)
{
	int result = 0;

	if (cmd_ptr != 0) {

		QApplication app(cmd_ptr->argc, cmd_ptr->argv);

		QString filter = createFilter(cmd_ptr->filter);
		QString path = "";

		switch(cmd_ptr->action) {
			case COMMAND_ACTION_OPEN:
				path = QFileDialog::getOpenFileName(0,
													cmd_ptr->title ? cmd_ptr->title : "Open file",
													QDir::currentPath(),
													filter);
				break;

			case COMMAND_ACTION_SAVE:
				path = QFileDialog::getSaveFileName(0,
													cmd_ptr->title ? cmd_ptr->title : "Save file",
													QDir::currentPath(),
													filter);
				break;

			case COMMAND_ACTION_SELECT_FOLDER:
				/*not implemented yet*/
				break;

			case COMMAND_ACTION_CREATE_FOLDER:
				/*not implemented yet*/
				break;
		};

		if (path != "") {
			QByteArray path_char = path.toLocal8Bit();
			printf("%s=%s\n", RESULT_PATH, path_char.data());
			result = 1;
		}
	}
	return result;
}
