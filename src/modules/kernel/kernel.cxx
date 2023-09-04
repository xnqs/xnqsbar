#include <cstdio>
#include <cctype>

// we will be getting the kernel version from the file /proc/version. nothing else to really add here.

extern "C" {
void get_info(char* dest) {
	dest[0] = 0;
	FILE* fp = fopen("/proc/version","r");
	if (!fp) {
		return;
	}

	int ver_len = 0;
	char ver[50] = {0}, ch, encountered_string = 0, over = 0;
	while (ch = fgetc(fp)) {
		if (ch>='0'&&ch<='9') {
			encountered_string = 1;
		}
		else if (!(ch>32&&ch<=127)&&encountered_string) over = 1;

		if (encountered_string) {
			if (!over) ver[ver_len++] = ch;
			else break;
		}
	}

	sprintf(dest," %s",ver);

	fclose(fp);
}
}
