#ifndef ALERT_API_H
#define ALERT_API_H

#include <string>
#include <vector>

// Consider using a forward declaration for JSON to avoid direct inclusion
class JsonValue;

struct Alert {
    std::string id;
    std::string message;
    std::string region;
    std::string time;
    // Add other fields as needed
};

class AlertAPI {
public:
    AlertAPI(const std::string& url);

    // Use a result type to indicate success or failure and provide additional information
    struct FetchResult {
        bool success;
        std::string error_message; // Optional
        std::vector<Alert> alerts;
    };

    FetchResult fetchAlerts();

    // Consider returning a future or promise for asynchronous operations
    // void processAirAlerts(const std::string& url);
    // void processNewsAggregator(const std::string& url);

private:
    std::string apiUrl;

    JsonValue fetchData(const std::string& url); // Assuming JsonValue is defined elsewhere
};

#endif // ALERT_API_H

