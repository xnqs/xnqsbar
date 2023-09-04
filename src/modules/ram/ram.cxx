#include <cstdio>

extern "C" {
void get_info(char* dest) {
	dest[0] = 0;
	FILE* fp = fopen("/proc/meminfo","r");
	if (!fp) {
		return;
	}

	int total        = 0;
	int shared       = 0;
	int free         = 0;
	int cached       = 0;
	int buffers      = 0;
	int sreclaimable = 0;

	char buff[50] = {0};
	while (fgets(buff,50,fp)!=NULL) {
		sscanf(buff,"MemTotal: %d",&total);
		sscanf(buff,"Shmem: %d",&shared);
		sscanf(buff,"MemFree: %d",&free);
		sscanf(buff,"Cached: %d",&cached);
		sscanf(buff,"Buffers: %d",&buffers);
		sscanf(buff,"SReclaimable: %d",&sreclaimable);
	}

	int mem_used_mb  = (total+shared-free-cached-buffers-sreclaimable)/1024;
	int mem_total_mb = total/1024;

	sprintf(dest," %dMB/%dMB",mem_used_mb,mem_total_mb);

	fclose(fp);
}
}
