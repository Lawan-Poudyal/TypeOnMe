#include "./database.hpp"
#include "../main.hpp"
#include <iostream>
#include <cstring>
#include <unordered_map>
Database::Database(const std::string& db) {
    int rc = sqlite3_open(db.c_str(), &m_db);
    if (rc) {
        std::cerr << "Can't create database: " << sqlite3_errmsg(m_db) << std::endl;
    } else {
        std::cout << "Accessed Database!" << std::endl;
    }
}

Database::~Database() {

}

// Corrected callback function signature
int Database::db_callback(void* data, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << "=" << (argv[i] ? argv[i] : "NULL") << " ";
    }
    std::cout << std::endl;
    return 0;
}

int Database::query_data(const std::string& query, int create_t) {
    char* zErrMsg = nullptr;
    int rc;

    if (create_t) {
        const char* sql = "CREATE TABLE IF NOT EXISTS credentials("
                          "UID INTEGER PRIMARY KEY AUTOINCREMENT,"
                          "username TEXT,"
                          "password TEXT);";
        rc = sqlite3_exec(m_db, sql, db_callback, 0, &zErrMsg);
    } else {
        rc = sqlite3_exec(m_db, query.c_str(), db_callback, 0, &zErrMsg);
    }

    if (rc != SQLITE_OK) {
        std::cerr << "SQLITE-ERROR: " << sqlite3_errmsg(m_db) << std::endl;
        sqlite3_free(zErrMsg);
        return rc;
    } else {
        std::cout << "Database query successful" << std::endl;
    }
    return 0;
}

bool Database::AddEntry(const std::string& username, const std::string& password) {
    const char* sql = "INSERT INTO credentials (username, password) VALUES (?, ?)";
    sqlite3_stmt* stmt = nullptr;
    int result = sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
        std::cerr << "Error preparing insert statement: " << sqlite3_errmsg(m_db) << std::endl;
        return false;
    }

    if (sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK) {
        std::cerr << "Error binding parameters: " << sqlite3_errmsg(m_db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    result = sqlite3_step(stmt);
    if (result != SQLITE_DONE) {
        std::cerr << "Error inserting data: " << sqlite3_errmsg(m_db) << std::endl;
        sqlite3_finalize(stmt);
        return false;
    }

    sqlite3_finalize(stmt);
    return true;
}

bool Database::checkCredentialsLogin(const std::string& usrname, const std::string& passwd) {
    char* zErrMsg = nullptr;
    int rc;
    sqlite3_stmt* stmt;

    // SQL query with placeholders for username and password
    const char* sql = "SELECT * FROM credentials WHERE username = ? AND password = ?";

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "3.SQLITE Error: %s\n", sqlite3_errmsg(m_db));
        return false;
    }

    // Bind the username and password parameters to the prepared statement
    sqlite3_bind_text(stmt, 1, usrname.c_str(), usrname.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, passwd.c_str(), passwd.length(), SQLITE_TRANSIENT);

    // Execute the prepared statement
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_ROW) {
        std::cerr << "No matching credentials found.\n";
        sqlite3_finalize(stmt);
        return false;
    }

    // Finalize the statement after use
    sqlite3_finalize(stmt);

    return true;
}

bool Database::checkCredentialsRegister(const std::string& usrname, const std::string& passwd) {
    const char* sql = "SELECT * FROM credentials WHERE username = ?";
    sqlite3_stmt* stmt = nullptr;
    int rc = sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing select statement: " << sqlite3_errmsg(m_db) << std::endl; 
        return false;
    }
    sqlite3_bind_text(stmt, 1, usrname.c_str(), -1, SQLITE_TRANSIENT);

    rc = sqlite3_step(stmt);
    bool userExists = (rc == SQLITE_ROW);
    std::cout << userExists << endl;
    sqlite3_finalize(stmt);

    if (userExists) {
        std::cout << "Username already exists." << std::endl;
        return false;
    } else {
        return true;
    }
}

unordered_map<string,int> Database::getLeaderboard(){

  const char* sql = "SELECT * FROM leaderboard;";
  sqlite3_stmt* stmt = nullptr;
  unordered_map<string,int> leaderboardMap;

    if (rc != SQLITE_OK) {
        std::cerr << "Error preparing select statement: " << sqlite3_errmsg(m_db) << std::endl; 
        return false;
    }

    rc = sqlite3_step(stmt);
    bool userExists = (rc == SQLITE_ROW);
    std::cout << userExists << endl;
    sqlite3_finalize(stmt);
    return leaderboardMap;

}

bool Database::InitializeLeaderboard(){

    char* zErrMsg = nullptr;
    int rc;

    const char* sql = "CREATE TABLE IF NOT EXISTS leaderboard("
                      "username TEXT,"
                      "wpm INTEGER);";
   
    
    rc = sqlite3_exec(m_db, sql, db_callback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK) {
        std::cerr << "SQLITE-ERROR: " << sqlite3_errmsg(m_db) << std::endl;
        sqlite3_free(zErrMsg);
        return rc;
    }
    else {
        std::cout << "Database query successful" << std::endl;
    }

    return 0;
}

bool Database::closeDB() {
    if(sqlite3_close(m_db) == SQLITE_OK){
      return true;
    }
    else{
      std::cerr <<"Database exited abnormally!" << sqlite3_errmsg(m_db) << std::endl;
      return false;
    }
}

