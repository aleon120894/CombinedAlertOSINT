#ifndef ALERT_API_H
#define ALERT_API_H

#include <string>
#include <vector>
#include <json/json.h>

struct Alert {
    std::string id;
    std::string message;
    std::string region;
    std::string time;
};

class AlertAPI {
public:
    AlertAPI(const std::string& url);
    std::vector<Alert> fetchAlerts();

    void processAirAlerts(const std::string& url);
    void processNewsAggregator(const std::string& url);

private:
    std::string apiUrl;

    Json::Value fetchData(const std::string& url);
};

struct MemoryStruct {
    char* memory;
    size_t size;
};

#endif // ALERT_API_H
