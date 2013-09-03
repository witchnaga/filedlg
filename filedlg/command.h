
#ifndef _COMMAND_H_
#define _COMMAND_H_

/******************************************************************************
 value
******************************************************************************/

// Command.mode
enum {
	COMMAND_MODE_EXEC,
	COMMAND_MODE_HELP,
};

// Command.filter
enum {
	COMMAND_FILTER_ALL		= 0x00000001,
	COMMAND_FILTER_TXT		= 0x00000002,
	COMMAND_FILTER_BMP		= 0x00000004,
	COMMAND_FILTER_JPEG		= 0x00000008,
	COMMAND_FILTER_PNG		= 0x00000020,
	COMMAND_FILTER_GIF		= 0x00000040,
	COMMAND_FILTER_TIFF		= 0x00000080,

	COMMAND_FILTER_DEFAULT = COMMAND_FILTER_ALL,
};

// Command.action
enum {
	COMMAND_ACTION_OPEN,
	COMMAND_ACTION_SAVE,
	COMMAND_ACTION_SELECT_FOLDER,
	COMMAND_ACTION_CREATE_FOLDER,

	COMMAND_ACTION_DEFAULT = COMMAND_ACTION_OPEN,
};


/******************************************************************************
 structure
******************************************************************************/
typedef struct {

	int				argc;
	char**			argv;

	unsigned short	mode;
	unsigned int	filter;
	unsigned short	action;
	char*			title;

} Command;

/******************************************************************************
 function
******************************************************************************/
int command_parse(int argc, char** argv, Command* data_ptr);

#endif // _COMMAND_H_

