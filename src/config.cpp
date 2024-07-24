#include "config.h"
#include "ini.h"

Config::Config(const std::string& filename) {
    // Use the static function to parse the INI file
    ini_parse(filename.c_str(), handle_ini, this);
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

// Static function definition
int Config::handle_ini(void* user, const char* section, const char* name, const char* value) {
    Config* config = static_cast<Config*>(user);
    config->data[section][name] = value;
    return 1; // Continue parsing
}
