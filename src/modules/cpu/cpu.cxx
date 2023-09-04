#include <cstdio>
#include <cstring>

// for reference: we will be determining cpu usage percentage using /proc/stat. this file
// stores cpu usage information in "jiffies", and we will simply be converting this information into a percentage we can display.
// total jiffies are the total cpu usage across the board, including stuff like iowait, idle time, irq etc.
// work jiffies include only system, user and nice cpu usage.

extern "C" {
void get_info(char* dest) {
	static int last_total_jiffies = 0;
	static int last_work_jiffies  = 0;
	int        curr_total_jiffies = 0;
	int        curr_work_jiffies  = 0;
	
	dest[0] = 0;

	FILE* stat_file = fopen("/proc/stat","r");
	// FIXME do some debug shit here idk
	if (!stat_file) {
		return;
	}
	char buff[100] = {0};

	fgets(buff,100,stat_file);

	// we will be parsing the buffer using the index variable ptr.
	int ptr = 0;

	// we will just skip past the first token, which says "cpu".
	while (ptr>='a'&&ptr<='z') ++ptr;

	// and now we will be determining curr_total_jiffies and curr_work_jiffies
	int buff_len = std::strlen(buff), column = 0;
	while (ptr<buff_len) {
		// skip past the leading spaces
		while (ptr<buff_len&&!(buff[ptr]>='0'&&buff[ptr]<='9')) ++ptr;
		
		// determine the value of the current column and add it to curr_total_jiffies and curr_work_jiffies if it's the case.
		int add = 0;
		while (ptr<buff_len&&buff[ptr]>='0'&&buff[ptr]<='9') {
			add = add*10 + (buff[ptr]-'0');
			++ptr;
		}

		curr_total_jiffies += add;
		// if we are in system, user or nice columns (first 3) we add to the work jiffies
		if (column<3) {
			curr_work_jiffies += add;
		}

		// we have moved past the current column.
		++column;
	}

	// calculating the final percentage
	int    total_diff   = curr_total_jiffies - last_total_jiffies;
	int    work_diff    = curr_work_jiffies - last_work_jiffies;
	double cpu_usage    = (double)work_diff/total_diff*100;

	// printing the usage onto the desired string
	sprintf(dest," %.1f%%",cpu_usage);

	// before exiting out of the function, let's do some cleanup here and let's set last_* to curr_*
	fclose(stat_file);
	last_total_jiffies = curr_total_jiffies;
	last_work_jiffies  = curr_work_jiffies;
}
}
