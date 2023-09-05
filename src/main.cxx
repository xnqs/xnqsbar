#include <iostream>
#include <chrono>
#include <ctime>
#include <cstring>
#include <thread>
#include <vector>
#include <map>
#include <filesystem>
#include <unistd.h>
#include <functional>

#include "config.hxx"
#include "enums.hxx"
#include "utils.hxx"
#include "module_loader.hxx"

int main(int argc, char** argv) {
	if (argc>1) {
		std::cerr << "xnqsbar does not take any command line arguments.\n";
		return 1;
	}
		
	while (1) {
		std::map<std::string,std::function<void(char*)>> map;
		std::vector<void*> dlhs;
		xnqs::load_modules(map,dlhs);

		auto time_start = std::chrono::high_resolution_clock::now();
		
		char final_status_msg[257] = {0};
		for (auto it = map.begin(); it != map.end(); it++) {
			std::cout << it->first << "\n";
			char buff[257] = {0};
			it->second(buff);
			std::cout << buff << "\n\n";
			
			strcat(final_status_msg,buff);
			if (it != map.end()) {
				strcat(final_status_msg," | ");
			}
		}
		
		char cmd[300] = "xprop -root -set WM_NAME \"";
		strcat(cmd,final_status_msg);
		strcat(cmd,"\"");
		system(cmd);

		for (const auto& i : dlhs) {
			dlclose(i);
		}

		auto time_end = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(DELAY-std::chrono::duration_cast<std::chrono::milliseconds>(time_end-time_start).count()));
	}
}
