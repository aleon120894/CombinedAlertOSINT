#include "config.h"
#include "ini.h"
#include <iostream>

Config::Config(const std::string& filename) {
    int result = ini_parse(filename.c_str(), [](void* user, const char* section, const char* name, const char* value) -> int {
        auto* config = static_cast<Config*>(user);
        std::cout << "Parsing - Section: " << section << ", Name: " << name << ", Value: " << value << std::endl;
        config->data[section][name] = value;
        return 1;
    }, this);

    if (result != 0) {
        std::cerr << "Error parsing INI file, error code: " << result << std::endl;
    }
}

std::string Config::get(const std::string& section, const std::string& name) const {
    auto it = data.find(section);
    if (it != data.end()) {
        auto jt = it->second.find(name);
        if (jt != it->second.end()) {
            return jt->second;
        }
    }
    return {};
}
