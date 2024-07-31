#include "alert_api.h"
#include "utils.h"
#include <iostream>
#include <curl/curl.h>
#include <json/json.h>


AlertAPI::AlertAPI(const std::string& url) : apiUrl(url) {}

Json::Value fetchData(const std::string& url) {
    CURL* curl;
    CURLcode res;
    MemoryStruct chunk;

    chunk.memory = (char*)malloc(1);
    chunk.size = 0;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&chunk);
        res = curl_easy_perform(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        } else {
            // Parse JSON data
            Json::CharReaderBuilder builder;
            Json::CharReader* reader = builder.newCharReader();
            Json::Value jsonData;
            std::string errors;

            bool parsingSuccessful = reader->parse(chunk.memory, chunk.memory + chunk.size, &jsonData, &errors);
            delete reader;

            if(!parsingSuccessful) {
                std::cerr << "Failed to parse the JSON data: " << errors << std::endl;
            }

            free(chunk.memory);
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return jsonData;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return Json::Value();
}

void processAirAlerts(std::string& url) {

    Json::Value data = fetchData(url);
    // Обробка даних з air_alerts
    std::cout << "Air Alerts Data: " << data.toStyledString() << std::endl;
}

void processNewsAggregator(std::string& url) {
    
    Json::Value data = fetchData(url);
    // Обробка даних з air_alerts
    std::cout << "Air Alerts Data: " << data.toStyledString() << std::endl;
}
