#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sqlite3.h>
#include <json/json.h>
#include "osint_system.h"
#include "utils.h"  // Додайте цей рядок


void saveOSINTToDatabase(const std::string& data);

void fetchOSINTData(const std::string& url, std::string& readBuffer) {
    CURL* curl;
    CURLcode res;

    curl = curl_easy_init();

    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "Error fetching data: " << curl_easy_strerror(res) << std::endl;
        }
    }
}

void parseOSINTJSON(const std::string& rawData) {

    Json::CharReaderBuilder reader;
    Json::Value jsonData;
    std::string errs;

    std::istringstream s(rawData);
    std::string doc;
    doc.assign((std::istreambuf_iterator<char>(s)),
               (std::istreambuf_iterator<char>()));

    std::istringstream ss(doc);
    
    if (!Json::parseFromStream(reader, ss, &jsonData, &errs)) {
        std::cerr << "Error parsing JSON data: " << errs << std::endl;
        return;
    }

    std::cout << "Parsed JSON data: " << jsonData.toStyledString() << std::endl;
}
