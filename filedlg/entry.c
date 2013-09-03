#include <stdio.h>
#include <string.h>

#include "filedlg.h"
#include "command.h"


static int exec(Command* cmd_ptr)
{
	int result = 0;

//	printf("exec : start.\n");

	if (cmd_ptr != NULL) {

		file_dialog_open(cmd_ptr);
	}

//	printf("exec : end.\n");

	return result;
}

static int help(Command* cmd_ptr)
{
	int result = 0;

//	printf("help : start.\n");
//	printf("help : end.\n");

	return result;
}

int main(int argc, char** argv)
{
//	printf("program start.\n");

	{
		Command cmd;
		memset(&cmd, 0, sizeof(cmd));
		
		if (command_parse(argc, argv, &cmd) != 0) {

			switch (cmd.mode) {
				case COMMAND_MODE_EXEC:	exec(&cmd);				break;
				case COMMAND_MODE_HELP:	help(&cmd);				break;
				default:
					printf("main : cmd.mode is unexpected.\n");	break;
			}
		} else {
			printf("main : parse_command is failed.\n");
		}

	}

//	printf("program end.\n");

	return 0;
}

