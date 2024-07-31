#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>

class Notification {
    
public:
    static void sendEmail(const std::string& recipient, const std::string& subject, const std::string& message);
    static void sendSMS(const std::string& phoneNumber, const std::string& message);
};

#endif // NOTIFICATION_H
