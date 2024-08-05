#include "alert_api.h"
#include "utils.h"
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <optional>


AlertAPI::AlertAPI(const std::string& url) : apiUrl(url) {}

std::optional<Json::Value> AlertAPI::fetchData(const std::string& url) {
    CURL* curl = curl_easy_init();
    if (!curl) {
        std::cerr << "Failed to initialize curl" << std::endl;
        return std::nullopt;
    }

    MemoryStruct chunk;
    chunk.memory = (char*)malloc(1);
    if (!chunk.memory) {
        curl_easy_cleanup(curl);
        std::cerr << "Failed to allocate memory" << std::endl;
        return std::nullopt;
    }
    chunk.size = 0;

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        free(chunk.memory);
        curl_easy_cleanup(curl);
        return std::nullopt;
    }

    Json::Value jsonData;
    Json::CharReaderBuilder builder;
    Json::CharReader* reader = builder.newCharReader();
    std::string errors;

    bool parsingSuccessful = reader->parse(chunk.memory, chunk.memory + chunk.size, &jsonData, &errors);
    delete reader;

    if (!parsingSuccessful) {
        std::cerr << "Failed to parse JSON data: " << errors << std::endl;
        free(chunk.memory);
        curl_easy_cleanup(curl);
        return std::nullopt;
    }

    free(chunk.memory);
    curl_easy_cleanup(curl);
    return jsonData;
}

bool AlertAPI::processAirAlerts(const std::string& url) {
    std::optional<Json::Value> data = fetchData(url);
    if (!data) {
        return false;
    }

    // Process the data
    // ...

    return true;
}

bool AlertAPI::processNewsAggregator(const std::string& url) {
    std::optional<Json::Value> data = fetchData(url);
    if (!data) {
        return false;
    }

    // Process the data
    // ...

    return true;
}

