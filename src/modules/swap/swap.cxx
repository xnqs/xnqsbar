#include <cstdio>

extern "C" {
void get_info(char* dest) {
	dest[0] = 0;

	FILE* fp = fopen("/proc/meminfo","r");
	if (!fp) {
		return;
	}

	int swap_total = 0, swap_free = 0;
	char buff[50] = {0};
	while (fgets(buff,50,fp)!=NULL) {
		sscanf(buff,"SwapTotal: %d",&swap_total);
		sscanf(buff,"SwapFree: %d",&swap_free);
	}

	int swap_used = swap_total - swap_free;
	sprintf(dest," %dMB/%dMB",swap_used/1024,swap_total/1024);

	fclose(fp);
}
}
