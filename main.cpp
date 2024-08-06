#include <iostream>
#include <string>
#include <cstdlib> // For std::getenv
#include <fstream> // For file reading
#include <unistd.h> // For getcwd
#include <sys/stat.h> // For struct stat and stat()

#include <sqlite3.h>
#include "alert_system.h"
#include "osint_system.h"
#include "config.h"
#include "notification.h"
// #include "alert_api.h"
#include "server.h"


// Declaration of function createTables
void createTables(sqlite3* db);

void testDatabase() {

    sqlite3* db;
    int rc = sqlite3_open("alerts.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    char* zErrMsg = 0;
    const char* sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='Alerts';";

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Alerts table exists." << std::endl;
    }

    sqlite3_close(db);
}

void printDatabaseContents(const std::string& dbName, const std::string& tableName) {
    sqlite3* db;
    char* zErrMsg = 0;
    int rc;

    sqlite3_stmt* stmt;
    std::string sql = "SELECT * FROM " + tableName;
    rc = sqlite3_open(dbName.c_str(), &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    std::cout << "Contents of " << tableName << " table:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* data = sqlite3_column_text(stmt, 1);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {

    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != nullptr) {
        std::cout << "Current working directory: " << cwd << std::endl;
    } else {
        std::cerr << "Error getting current working directory." << std::endl;
        return 1;
    }

    // Explicitly set the config file path to the project root directory
    std::string configFilePath = std::string(cwd) + "/../config.ini";

    // Debug: Print the path to the config file
    std::cout << "Config file path: " << configFilePath << std::endl;

    // Check if config.ini exists and is readable
    struct stat buffer;
    if (stat(configFilePath.c_str(), &buffer) != 0) {
        std::cerr << "Config file 'config.ini' does not exist or is not readable." << std::endl;
        return 1;
    } else {
        std::cout << "Config file 'config.ini' exists and is readable." << std::endl;

        // Print file contents for debugging
        std::ifstream configFile(configFilePath);
        
        if (configFile.is_open()) {
            std::string line;
            std::cout << "Contents of 'config.ini':" << std::endl;
            while (getline(configFile, line)) {
                std::cout << line << std::endl;
            }
            configFile.close();
        } else {
            std::cerr << "Error opening 'config.ini' for reading." << std::endl;
            return 1;
        }
    }

    // Load configuration from config.ini
    Config config(configFilePath);

    std::string alertURL = config.get("Settings", "alert_url");
    std::string osintURL = config.get("Settings", "osint_url");

    std::string air_alert_url = config.get("Settings", "air_alert_url");
    std::string news_aggregator_url = config.get("Settings", "news_aggregator_url");

    if (alertURL.empty() || osintURL.empty() || air_alert_url.empty() || news_aggregator_url.empty()) {
        std::cerr << "Configuration values for alert_url or osint_url, air_alert_url, or news_aggregator_url are not set." << std::endl;
        return 1;
    }

    sqlite3* db;
    int rc = sqlite3_open("alerts.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Create tables
    // createTables(db);
    // sqlite3_close(db);

    // Test if the database is set up correctly
    // testDatabase();

    // Fetch and save alert data
    // std::string alertData;
    // fetchAlertData(alertURL, alertData);
    // parseAlertJSON(alertData);
    // saveAlertToDatabase(alertData);

    // Fetch and save OSINT data
    // std::string osintData;
    // fetchOSINTData(osintURL, osintData);
    // parseOSINTJSON(osintData);
    // saveOSINTToDatabase(osintData);

    // Process alert api data
    // AlertAPI api("");

    // api.processAirAlerts(air_alert_url);
    // api.processNewsAggregator(news_aggregator_url);

    // Print contents of the database tables
    printDatabaseContents("alerts.db", "Alerts");
    printDatabaseContents("alerts.db", "OSINT");

    start_server(air_alert_url, news_aggregator_url);

    return 0;
}
