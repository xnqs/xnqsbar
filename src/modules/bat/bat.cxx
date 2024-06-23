#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <cstring>

std::string get_percentage(const std::string& path) {
	std::ifstream path_stream(path);
	if (!path_stream.good()) {
		return "-1";
	}
	std::string ret;
	path_stream >> ret;
	return ret;
}

extern "C" {
void get_info(char* dest) {
	std::filesystem::path psu("/sys/class/power_supply");
	std::filesystem::directory_iterator it(psu);

	std::vector<std::string> batteries;
	for (auto entry : it) {
		auto entry_path = entry.path();
		std::string device_str(entry_path);

		// trim out everything before device name and after "BAT"
		device_str = device_str.substr(24,3);

		// if the device is a battery, push it onto the vector
		if (device_str=="BAT") {
			batteries.emplace_back(entry_path);
		}
	}

	// forming the output
	std::string output(" ");
	for (auto battery_it = batteries.begin(); battery_it != batteries.end(); battery_it++) {
		output += "B" + std::to_string(battery_it-batteries.begin()) + ": " + get_percentage(*battery_it + "/capacity") + "%";
		if (battery_it+1!=batteries.end()) {
			output += ", ";
		}
		//std::cout << *battery_it << " " << get_percentage(*battery_it + "/capacity") << "\n";
	}

	strcpy(dest, output.c_str());
}
}

#if 0
int main() {
	char buff[256];
	get_info(buff);
	std::cout << buff << "\n";
}
#endif
