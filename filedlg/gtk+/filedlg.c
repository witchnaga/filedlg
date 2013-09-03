#include <gtk/gtk.h>

#include "../precomp.h"
#include "../filedlg.h"


typedef struct {
	unsigned int	filter;
	char*			name;
	char*			pattern;
	char*			mime_type;
} Filter;

static const Filter filters[] = {
	{ COMMAND_FILTER_ALL,	"All Files",	"*",	NULL			},
	{ COMMAND_FILTER_TXT,	"TXT",			NULL,	"text/plain"	},
	{ COMMAND_FILTER_BMP,	"BMP",			NULL,	"image/bmp"		},
	{ COMMAND_FILTER_JPEG,	"JPEG",			NULL,	"image/jpeg"	},
	{ COMMAND_FILTER_PNG,	"PNG",			NULL,	"image/png"		},
	{ COMMAND_FILTER_GIF,	"GIF",			NULL,	"image/gif"		},
};


typedef struct {
	unsigned short			action;
	GtkFileChooserAction	gtk_action;
} Action;

static const Action actions[] = {
	{ COMMAND_ACTION_OPEN,			GTK_FILE_CHOOSER_ACTION_OPEN			},
	{ COMMAND_ACTION_SAVE,			GTK_FILE_CHOOSER_ACTION_SAVE			},
	{ COMMAND_ACTION_SELECT_FOLDER,	GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER	},
	{ COMMAND_ACTION_CREATE_FOLDER,	GTK_FILE_CHOOSER_ACTION_CREATE_FOLDER	},
};


static GtkFileChooserAction file_dialog_get_action(Command* cmd_ptr)
{
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;

	if (cmd_ptr != NULL) {

		int i;
		for (i = 0; i < countof(actions); ++i) {
			
			if (cmd_ptr->action == actions[i].action) {
				action = actions[i].gtk_action;
				break;
			}
		}
	}
	
	return action;
}

static void file_dialog_set_filter(GtkWidget* dialog_ptr, Command* cmd_ptr)
{
	if (dialog_ptr != NULL && cmd_ptr != NULL) {

		int i;
		for (i = 0; i < countof(filters); ++i) {

			GtkFileFilter* filter = gtk_file_filter_new();
			if (filter != NULL) {

				if ((cmd_ptr->filter & filters[i].filter) != 0) {

					if (filters[i].name != NULL) {
						gtk_file_filter_set_name(filter, filters[i].name);
					}
					if (filters[i].pattern != NULL) {
						gtk_file_filter_add_pattern(filter, filters[i].pattern);
					}
					if (filters[i].mime_type != NULL) {
						gtk_file_filter_add_mime_type(filter, filters[i].mime_type);
					}
					gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog_ptr), filter);
				}
			}
		}
	}
}

void file_dialog_output_result(GtkWidget* dialog)
{
	if (dialog != NULL) {

		gchar* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
		gchar* folder   = gtk_file_chooser_get_current_folder(GTK_FILE_CHOOSER(dialog));

		g_print("%s=%s\n", RESULT_PATH, filename);
		g_print("%s=%s\n", RESULT_FOLDER, folder);

		g_free(folder);
		g_free(filename);
	}
}

int file_dialog_open(Command* cmd_ptr)
{
	int result = 0;

	if (cmd_ptr != NULL) {

		gtk_init(&cmd_ptr->argc, &cmd_ptr->argv);

		GtkWidget* dialog = gtk_file_chooser_dialog_new(cmd_ptr->title,
														NULL,
														file_dialog_get_action(cmd_ptr),
														GTK_STOCK_CANCEL,
														GTK_RESPONSE_CANCEL,
														(cmd_ptr->action == COMMAND_ACTION_SAVE) ? GTK_STOCK_SAVE : GTK_STOCK_OPEN,
														GTK_RESPONSE_ACCEPT,
														NULL);
		if (dialog != NULL) {

			gint response;

			file_dialog_set_filter(dialog, cmd_ptr);
			gtk_widget_show_all(dialog);

			response = gtk_dialog_run(GTK_DIALOG(dialog));

			if (response == GTK_RESPONSE_ACCEPT) {
				file_dialog_output_result(dialog);
			}
			else if(response == GTK_RESPONSE_CANCEL){
				g_print( "file_dialog : Cancel button was pressed.\n" );
			} else {
				g_print( "file_dialog : Another response was received.\n" );
			}

			gtk_widget_destroy(dialog);
		}
	} else {
		g_print( "file_dialog : arguement is invalid.\n" );
	}

	return result;
}

