#include "httplib.h"
#include "alert_api.h"
#include "config.h"

void start_server(const std::string& air_alert_url, const std::string& news_aggregator_url) {
    httplib::Server svr;

    svr.Get("/air_alerts", [&](const httplib::Request&, httplib::Response& res) {
        AlertAPI api("");
        api.processAirAlerts(air_alert_url);
        res.set_content("Air Alerts processed.", "text/plain");
    });

    svr.Get("/news_aggregator", [&](const httplib::Request&, httplib::Response& res) {
        AlertAPI api("");
        api.processNewsAggregator(news_aggregator_url);
        res.set_content("News Aggregator processed.", "text/plain");
    });

    svr.listen("0.0.0.0", 8080);
}
