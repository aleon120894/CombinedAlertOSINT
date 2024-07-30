#include "alert_api.h"
#include "utils.h"
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>

AlertAPI::AlertAPI(const std::string& url) : apiUrl(url) {}

std::vector<Alert> AlertAPI::fetchAlerts() {

    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();

    if(curl) {

        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return {};
        }
    }

    std::vector<Alert> alerts;
    Json::Value jsonData;
    Json::Reader jsonReader;

    if (jsonReader.parse(readBuffer, jsonData)) {

        for (const auto& item : jsonData["alerts"]) {

            Alert alert;
            alert.id = item["id"].asString();
            alert.message = item["message"].asString();
            alert.region = item["region"].asString();

            alert.time = item["time"].asString();
            alerts.push_back(alert);
        }
    } else {
        std::cerr << "Failed to parse JSON data" << std::endl;
    }

    return alerts;
}
