#include <iostream>
#include <string>
#include "alert_system.h"
#include "osint_system.h"

int main() {
    std::string alertData;
    fetchAlertData("https://example.com/alerts", alertData);
    parseAlertJSON(alertData);
    saveAlertToDatabase(alertData);

    std::string osintData;
    fetchOSINTData("https://api.example.com/osint", osintData);
    parseOSINTJSON(osintData);
    saveOSINTToDatabase(osintData);

    return 0;
}
