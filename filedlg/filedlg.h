
#ifndef _FILEDLG_H_
#define _FILEDLG_H_

#include "command.h"

/******************************************************************************
 value
******************************************************************************/
#define RESULT_KEYWORD	"@"
#define RESULT_PATH		RESULT_KEYWORD "path"
#define RESULT_FOLDER	RESULT_KEYWORD "folder"

/******************************************************************************
 structure
******************************************************************************/


/******************************************************************************
 function
******************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif

int file_dialog_open(Command* cmd_ptr);


#ifdef __cplusplus
}
#endif

#endif // _FILEDLG_H_

