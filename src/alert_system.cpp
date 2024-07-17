#include <iostream>
#include <string>
#include <curl/curl.h>
#include <sqlite3.h>
#include <json/json.h>
#include "alert_system.h"
#include "utils.h"  // Додайте цей рядок


void fetchAlertData(const std::string& url, std::string& readBuffer) {
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

void parseAlertJSON(const std::string& rawData) {
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

void saveAlertToDatabase(const std::string& data) {
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    rc = sqlite3_open("alerts.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    std::string sql = "INSERT INTO Alerts (Data) VALUES ('" + data + "');";

    rc = sqlite3_exec(db, sql.c_str(), 0, 0, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Data inserted successfully" << std::endl;
    }

    sqlite3_close(db);
}
