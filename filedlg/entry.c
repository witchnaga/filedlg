#include <stdio.h>
#include <string.h>

#include "filedlg.h"
#include "command.h"


static int exec(Command* cmd_ptr)
{
	int result = 0;

	if (cmd_ptr != NULL) {

		file_dialog_open(cmd_ptr);
	}

	return result;
}

static int help(Command* cmd_ptr)
{
	int result = 0;

	printf("使用方法: filedlg [オプション]\n");
	printf("ファイルダイアログを起動し、選択されたファイルのパスを出力します。\n");
	printf("\n");
	printf(" -t, --title       ファイルダイアログのタイトル[省略可]\n");
	printf(" -a, --action      ファイルダイアログを起動するときの動作(open/save)[省略可]\n");
	printf(" -f, --filter      ファイルダイアログで選択可能なファイルの拡張子(txt/bmp/jpg/png[複数可])[省略可]\n");
	printf("\n");
	printf("使用例:\n");
	printf(" ./filedlg --title \"ファイルの選択\" --action open --filter bmp+jpg+png\n");
	printf(" ./filedlg -t Sample -a save -f txt\n");
	printf("\n");

	return result;
}

int main(int argc, char** argv)
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

	return 0;
}

