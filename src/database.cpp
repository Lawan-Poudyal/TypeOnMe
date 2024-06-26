#include <iostream>
#include <sqlite3.h>

// Callback function to handle each row of the result set
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << std::endl;
    return 0;
}

int main() {
    sqlite3* db;
    char* errMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("data.db", &db);

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    } else {
        std::cout << "Opened database successfully" << std::endl;
    }

    // Query to get the list of tables
    const char* listTablesQuery = "SELECT name FROM sqlite_master WHERE type='table';";
    rc = sqlite3_exec(db, listTablesQuery, callback, 0, &errMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Tables listed successfully" << std::endl;
    }

    // Query to get the contents of each table
    const char* getContentsQuery = "SELECT * FROM sqlite_master WHERE type='table';";
    sqlite3_stmt* stmt;
    rc = sqlite3_prepare_v2(db, getContentsQuery, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
    } else {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            std::string tableName(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));
            std::cout << "Contents of table: " << tableName << std::endl;

            std::string query = "SELECT * FROM " + tableName;
            rc = sqlite3_exec(db, query.c_str(), callback, 0, &errMsg);

            if (rc != SQLITE_OK) {
                std::cerr << "SQL error: " << errMsg << std::endl;
                sqlite3_free(errMsg);
            }
        }
    }
    sqlite3_finalize(stmt);

    // Close database
    sqlite3_close(db);
    return 0;
}
