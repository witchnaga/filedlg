#include <string.h>
#include <stdio.h>

#include "precomp.h"
#include "command.h"


typedef struct {
	char*			command;
	unsigned int	value;
} UINTParameter;

typedef struct {
	char*			command;
	unsigned short	value;
} USHORTParameter;

static const USHORTParameter action_parameter[] = {
	{ "open", COMMAND_ACTION_OPEN },
	{ "OPEN", COMMAND_ACTION_OPEN },
	{ "save", COMMAND_ACTION_SAVE },
	{ "SAVE", COMMAND_ACTION_SAVE },
};
static const UINTParameter filter_parameter[] = {
	{ "ALL",	COMMAND_FILTER_ALL	},
	{ "all",	COMMAND_FILTER_ALL	},
	{ "TXT",	COMMAND_FILTER_TXT	},
	{ "txt",	COMMAND_FILTER_TXT	},
	{ "TEXT",	COMMAND_FILTER_TXT	},
	{ "text",	COMMAND_FILTER_TXT	},
	{ "BMP",	COMMAND_FILTER_BMP	},
	{ "bmp",	COMMAND_FILTER_BMP	},
	{ "BITMAP",	COMMAND_FILTER_BMP	},
	{ "bitmap",	COMMAND_FILTER_BMP	},
	{ "JPEG",	COMMAND_FILTER_JPEG	},
	{ "jpeg",	COMMAND_FILTER_JPEG	},
	{ "JPG",	COMMAND_FILTER_JPEG	},
	{ "jpg",	COMMAND_FILTER_JPEG	},
	{ "PNG",	COMMAND_FILTER_PNG	},
	{ "png",	COMMAND_FILTER_PNG	},
	{ "GIF",	COMMAND_FILTER_GIF	},
	{ "gif",	COMMAND_FILTER_GIF	},
	{ "TIFF",	COMMAND_FILTER_TIFF	},
	{ "tiff",	COMMAND_FILTER_TIFF	},
	{ "TIF",	COMMAND_FILTER_TIFF	},
	{ "tif",	COMMAND_FILTER_TIFF	},
};


static void command_init(int argc, char** argv, Command* data_ptr)
{
	if (data_ptr != NULL) {

		data_ptr->argc		= argc;
		data_ptr->argv		= argv;

		data_ptr->mode		= COMMAND_MODE_EXEC;
		data_ptr->filter	= COMMAND_FILTER_DEFAULT;
		data_ptr->action	= COMMAND_ACTION_DEFAULT;
		data_ptr->title		= NULL;
	}
}

static int command_parse_help(int argc, char** argv, Command* data_ptr, int pos)
{
	data_ptr->mode = COMMAND_MODE_HELP;

	return 0;
}

static int command_parse_title(int argc, char** argv, Command* data_ptr, int pos)
{
	int result = 0;

	if (pos < argc) {

//		printf("command_parse_title : title=%s\n", data_ptr->title);

		result = 1;
		data_ptr->title = argv[pos + 1];
	}

	return result;
}

static int command_parse_action(int argc, char** argv, Command* data_ptr, int pos)
{
	int result = 0;

	if (pos < argc) {

		if (*argv[pos + 1] != '-') {

			int i;
			result = 1;

			for (i = 0; i < countof(action_parameter); ++i) {

				if (strcmp(argv[pos + 1], action_parameter[i].command) == 0) {
					
					data_ptr->action = action_parameter[i].value;
					break;
				}
			}
		} else {
			printf("command_parse_action : action parameter is invalid.\n");
		}
	}

	return result;
}

static int command_parse_filter(int argc, char** argv, Command* data_ptr, int pos)
{
	int result = 0;

	if (pos < argc) {

		if (*argv[pos + 1] != '-') {

			int i, j;
			char buffer[16];
			unsigned int filter = 0;

			char* p_start = argv[pos + 1];
			int cch       = strlen(argv[pos + 1]);

//			printf("command_parse_filter : filter=%s\n", argv[pos + 1]);
//			printf("command_parse_filter : cch=%d\n", cch);

			result = 1;

			for (i = 0; i < cch; ++i) {

				char* p_temp = argv[pos + 1];
				char* p      = &p_temp[i];
				int len      = 0;

				if (*p == '+') {
					len = (p - p_start);
				} else if (cch == (i + 1)) {
					len = (p - p_start) + 1;
				}

				if (len > 0) {

//					printf("command_parse_filter : len=%d\n", len);
					if ((sizeof(buffer) / sizeof(char)) > len) {
						
						memset(buffer, 0, sizeof(buffer));
						strncpy(buffer, p_start, len);
						
//						printf("command_parse_filter : filter=%s\n", buffer);

						for (j = 0; j < countof(filter_parameter); ++j) {

							if (strcmp(buffer, filter_parameter[j].command) == 0) {
								filter |= filter_parameter[i].value;
								break;
							}
						}

						p_start = &p_temp[i + 1];
					}
				}
			}
			if (filter != 0) {
				data_ptr->filter = filter;
			}
			
		} else {
			printf("command_parse_filter : filter parameter is nothing.\n");
		}
	}

	return result;
}

int command_parse(int argc, char** argv, Command* data_ptr)
{
	int result = 0;

	if (data_ptr != NULL) {

		int i;

		command_init(argc, argv, data_ptr);

		result = 1;
		for (i = 0; i < argc; ++i) {

			char* p = argv[i];
			if (p != NULL) {

				if (strcmp(p, "--help") == 0) {
					i += command_parse_help(argc, argv, data_ptr, i);
				} else if (strcmp(p, "--title") == 0 || strcmp(p, "-t") == 0) {
					i += command_parse_title(argc, argv, data_ptr, i);
				} else if (strcmp(p, "--action") == 0 || strcmp(p, "-a") == 0) {
					i += command_parse_action(argc, argv, data_ptr, i);
				} else if (strcmp(p, "--filter") == 0 || strcmp(p, "-f") == 0) {
					i += command_parse_filter(argc, argv, data_ptr, i);
				} 
			}
		}
	}

	return result;
}

