#include <iostream>
#include <filesystem>
#include <dlfcn.h>
#include <unistd.h>
#include <cstring>
#include <map>
#include <functional>

namespace xnqs {
int load_modules(std::map<std::string,std::function<void(char*)>>& func_map, std::vector<void*>& dlhs);
} // namespace xnqs
