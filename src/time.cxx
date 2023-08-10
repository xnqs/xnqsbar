#include <cstdio>
#include <ctime>

// this one was actually very easy to implement, same for time, which is essentially just this, but the
// sprintf statement is slightly different.

namespace xnqs {
void get_time(char* dest) {
	std::time_t t = std::time(0);
	std::tm* now  = std::localtime(&t);

	sprintf(dest," %02d:%02d:%02d",
			now->tm_hour,now->tm_min,now->tm_sec);
}
} // namespace xnqs

/*int main() {
	char str[256] = {0};
	xnqs::get_time(str);
	printf("%s\n",str);
}*/
