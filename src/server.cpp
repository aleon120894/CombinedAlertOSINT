#include "httplib.h"
#include "alert_api.h"
#include "config.h"

void start_server(const std::string& air_alert_url, const std::string& news_aggregator_url) {
    httplib::Server svr;
    // AlertAPI api(""); // Create a single AlertAPI instance

    svr.Get("/air_alerts", [&](const httplib::Request&, httplib::Response& res) {
        // Handle potential errors from processAirAlerts
        // if (!api.processAirAlerts(air_alert_url)) {
        //     res.status(500);
        //     res.set_content("Error processing air alerts", "text/plain");
        //     return;
        // }
        res.set_content("Air Alerts processed.", "text/plain");
    });

    svr.Get("/news_aggregator", [&](const httplib::Request&, httplib::Response& res) {
        // Handle potential errors from processNewsAggregator
        // if (!api.processNewsAggregator(news_aggregator_url)) {
        //     res.status(500);
        //     res.set_content("Error processing news aggregator", "text/plain");
        //     return;
        // }
        res.set_content("News Aggregator processed.", "text/plain");
    });

    // Consider using a separate thread for the server to avoid blocking the main thread
    std::thread server_thread([&]() {
        svr.listen("0.0.0.0", 8080);
    });
    server_thread.detach(); // or join() if you want to wait for the server to stop
}
