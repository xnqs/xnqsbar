// xnqsbar - a very minimal, but FIRE AF status bar for dwm.
//                                 ^^^  cringe
// You can customize almost every single aspect of xnqsbar in config.hxx.

#include <iostream>
#include <chrono>
#include <ctime>
#include <cstring>
#include <thread>
#include <vector>
#include <unistd.h>

#include "utils.hxx"
#include "enums.hxx"
#include "config.hxx"
#include "kernel.hxx"
#include "cpu.hxx"
#include "ram.hxx"
#include "swap.hxx"
#include "date.hxx"
#include "time.hxx"

void (*exec_func[])(char*) = {xnqs::get_kernel, 
                              xnqs::get_cpu, 
                              xnqs::get_ram, 
                              xnqs::get_swap, 
                              xnqs::get_date,
                              xnqs::get_time};

int main(int argc, char** argv) {
	if (argc>2) {
		std::cerr << "Usage: xnqsbar <flags>\n";
		std::cerr << "where <flags> is a number in decimal base.\n";
		std::cerr << "Kernel = 1\n";
		std::cerr << "CPU = 2\n";
		std::cerr << "RAM = 4\n";
		std::cerr << "Swap = 8\n";
		std::cerr << "Date = 16\n";
		std::cerr << "Time = 32\n";
		std::cerr << "\n";
		std::cerr << "Example: xnqsbar    - this launches xnqsbar with no flags, and defaults to enabling everything.\n";
		std::cerr << "         xnqsbar 15 - this launches xnqsbar with flags Kernel, CPU, RAM and Swap.\n";
		return 1;
	}

	if (argc==2&&!(argv[1][0]>='0'&&argv[1][0]<='9')) {
		std::cerr << "Usage: xnqsbar <flags>\n";
		std::cerr << "where <flags> is a number in decimal base.\n";
		std::cerr << "Kernel = 1\n";
		std::cerr << "CPU = 2\n";
		std::cerr << "RAM = 4\n";
		std::cerr << "Swap = 8\n";
		std::cerr << "Date = 16\n";
		std::cerr << "Time = 32\n";
		std::cerr << "\n";
		std::cerr << "Example: xnqsbar    - this launches xnqsbar with no flags, and defaults to enabling everything.\n";
		std::cerr << "         xnqsbar 15 - this launches xnqsbar with flags Kernel, CPU, RAM and Swap.\n";
		return 1;
	}

	int flag = argc==2 ? std::atoi(argv[1]) : 63;
	if (!(0<=flag&&flag<=63)) {
		std::cerr << "Error: flag is not in range [0, 63].\n";
		return 1;
	}

	int enum_order_size = sizeof(enum_order)/sizeof(enum_order[0]);
	while (1) {
		auto time_start = std::chrono::high_resolution_clock::now();
		char info[6][71];
		for (int i = 0; i < enum_order_size; i++) {
			int msb = xnqs::msb(enum_order[i]);
			if (flag&(1<<msb)) {
				exec_func[msb](info[i]);
			}
		}
	
		char final_status_msg[256] = {0};
		for (int i = 0; i < enum_order_size; i++) {
			int msb = xnqs::msb(enum_order[i]);
			if (flag&(1<<msb)) {
				strcat(final_status_msg,info[i]);
				strcat(final_status_msg," | ");
			}
		}
	
		std::cout << final_status_msg << "\n";

		// FIXME i have to stop using system() calls here to run commands
		// and set WM_NAME natively through c++ but i cba rn
		char cmd[300] = "xprop -root -set WM_NAME \"";
		strcat(cmd,final_status_msg);
		strcat(cmd,"\"");
		system(cmd);

		auto time_end = std::chrono::high_resolution_clock::now();

		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY-std::chrono::duration_cast<std::chrono::milliseconds>(time_end-time_start).count()));
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time_end-time_start).count() << "\n";
	}

	return 0;
}
