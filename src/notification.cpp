#include "notification.h"
#include <iostream>


void Notification::sendEmail(const std::string& recipient, const std::string& subject, const std::string& message) {
    // Реалізуйте надсилання електронних листів
    std::cout << "Sending email to " << recipient << ": " << subject << " - " << message << std::endl;
}

void Notification::sendSMS(const std::string& phoneNumber, const std::string& message) {
    // Реалізуйте надсилання SMS
    std::cout << "Sending SMS to " << phoneNumber << ": " << message << std::endl;
}
