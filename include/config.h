#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <map>

class Config {
    
public:
    Config(const std::string& filename);
    std::string get(const std::string& section, const std::string& name) const;

private:
    std::map<std::string, std::map<std::string, std::string>> data;
};

#endif // CONFIG_H
