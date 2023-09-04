#include <cstdio>
#include <ctime>

// this one was actually very easy to implement, same for time, which is essentially just this, but the
// sprintf statement is slightly different.

extern "C" {
void get_info(char* dest) {
	std::time_t t = std::time(0);
	std::tm* now  = std::localtime(&t);

	// by default this is the superior format i.e D/M/Y.
	sprintf(dest," %02d/%02d/%02d",
			now->tm_mday,now->tm_mon+1,now->tm_year+1900);
}
}
