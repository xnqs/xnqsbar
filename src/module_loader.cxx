#include <iostream>
#include <filesystem>
#include <dlfcn.h>
#include <unistd.h>
#include <cstring>
#include <map>
#include <functional>

namespace xnqs {
int load_modules(std::map<std::string,std::function<void(char*)>>& func_map, std::vector<void*>& dlhs) {
	char* linux_username = getlogin();
	
	std::filesystem::path config_dir(std::string("/home/") + linux_username + "/.config/xnqsbar");
	if (!std::filesystem::create_directories(config_dir/"modules")&&!std::filesystem::exists(config_dir/"modules")) {
		std::cerr << "Failed to create or access directory " << config_dir/"modules" << "\n";
		return 1;
	}

	using func_type = void(char*);
	
	std::filesystem::path modules_dir(config_dir/"modules");
	std::filesystem::directory_iterator modules_dir_it(modules_dir);
	for (auto& file : modules_dir_it) {
		void* dlh = dlopen(file.path().c_str(),RTLD_NOW);
		if (!dlh) {
			std::cerr << "Failed to open module " << file.path() << "\n";
			return 1;
		}

		auto func_ptr = dlsym(dlh,"get_info");
		char* module_name = (char*)(file.path().c_str())+strlen(file.path().c_str())-1;
		while (*module_name!='/') {
			--module_name;
		}

		++module_name;
		func_map[module_name] = reinterpret_cast<func_type*>(func_ptr);
		dlhs.emplace_back(dlh);
	}

	return 0;
}
} // namespace xnqs
