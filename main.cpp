#include <iostream>
#include <string>
#include <sqlite3.h>
#include "alert_system.h"
#include "osint_system.h"


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
        std::cout << "ID: " << id << ", Data: " << data << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

int main() {
    testDatabase();

    std::string alertData;
    fetchAlertData("https://jsonplaceholder.typicode.com/todos/1", alertData);
    parseAlertJSON(alertData);
    saveAlertToDatabase(alertData);

    std::string osintData;
    fetchOSINTData("https://jsonplaceholder.typicode.com/todos/1", osintData);
    parseOSINTJSON(osintData);
    saveOSINTToDatabase(osintData);

    return 0;
}
