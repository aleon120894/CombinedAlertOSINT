#ifndef OSINT_SYSTEM_H
#define OSINT_SYSTEM_H

#include <string>
#include <vector>

class OSINTSystem {
    
public:

    OSINTSystem();
    void gatherData(const std::string &source);
    std::vector<std::string> analyzeData();
};

void fetchOSINTData(const std::string &url, std::string &osintData);
void parseOSINTJSON(const std::string &osintData);
void saveOSINTToDatabase(const std::string &osintData);

#endif // OSINT_SYSTEM_H
