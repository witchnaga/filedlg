#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
	printf("program start\n");

	{
		FILE* fp = popen("../filedlg/gtk+/filedlg", "r");
		if (fp != NULL) {

			int in;
			char* p;
			char buffer[1024];
			memset(buffer, 0, sizeof(buffer));

			printf("filedlg program execute\n");

			in = 0;
			p = buffer;
			do {

				int c = fgetc(fp);
				if (c != EOF) {

					if (c == '@' && in == 0) {
						in = 1;
					}
					if (c == '\n' && in == 1) {
						in = 0;
					}
					if (in == 1) {
						*p++ = c;
					}
					if (in == 0) {
						if (strlen(buffer) > 0) {
							printf("filedlg program read : %s\n", buffer);
							memset(buffer, 0, sizeof(buffer));
							p = buffer;
						}
					}
				} else {
					break;
				}

			} while (1);

			pclose(fp);
		}
	}

	printf("program end\n");

	return 0;
}
