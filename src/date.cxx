#include <cstdio>
#include <ctime>

// this one was actually very easy to implement, same for time, which is essentially just this, but the
// sprintf statement is slightly different.

namespace xnqs {
void get_date(char* dest) {
	std::time_t t = std::time(0);
	std::tm* now  = std::localtime(&t);

	// by default this is the superior format i.e D/M/Y.
	sprintf(dest," %02d/%02d/%02d",
			now->tm_mday,now->tm_mon+1,now->tm_year+1900);
}
} // namespace xnqs

/*int main() {
	char str[256] = {0};
	xnqs::get_date(str);
	printf("%s\n",str);
}*/
