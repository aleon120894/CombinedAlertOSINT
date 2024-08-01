#ifndef ALERT_SYSTEM_H
#define ALERT_SYSTEM_H

#include <string>

// Клас AlertSystem
class AlertSystem {
    
public:
    AlertSystem();
    void sendAlert(const std::string &message);
};

void fetchAlertData(const std::string &url, std::string &alertData);
void parseAlertJSON(const std::string &alertData);
void saveAlertToDatabase(const std::string &alertData);

#endif // ALERT_SYSTEM_H
