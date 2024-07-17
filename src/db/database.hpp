#pragma once
#include <stdio.h>
#include <sqlite3.h> 
#include "../main.hpp"
class Database{
  public:
    Database(const std::string&);
    int query_data(std::string,int);
    ~Database();
    static int db_callback(void*,int,char**,char**);  
    bool AddEntry(const std::string&, const std::string& );
  private:
    sqlite3 *m_db;

};
