#include <cstdio>
#include <ctime>

// this one was actually very easy to implement, same for time, which is essentially just this, but the
// sprintf statement is slightly different.

extern "C" {
void get_info(char* dest) {
	std::time_t t = std::time(0);
	std::tm* now  = std::localtime(&t);

	sprintf(dest," %02d:%02d:%02d",
			now->tm_hour,now->tm_min,now->tm_sec);
}
}
