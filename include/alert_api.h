#ifndef ALERT_API_H
#define ALERT_API_H

#include <string>
#include <vector>

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
private:
    std::string apiUrl;
};

#endif // ALERT_API_H
