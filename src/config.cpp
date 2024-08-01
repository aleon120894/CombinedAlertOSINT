#include "config.h"
#include "ini.h"
#include <iostream>


Config::Config(const std::string& filename) {

    int error = ini_parse(filename.c_str(), [](void* user, const char* section, const char* name, const char* value) -> int {
        auto* config = static_cast<Config*>(user);
        config->data[section][name] = value;
        return 1;
    }, this);

    if (error != 0) {
        std::cerr << "Error parsing INI file, error code: " << error << std::endl;
        exit(EXIT_FAILURE);
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
