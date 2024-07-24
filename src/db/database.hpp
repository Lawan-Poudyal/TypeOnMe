#pragma once
#include <stdio.h>
#include <sqlite3.h> 
#include <string>
using namespace std;

class Database{
  public:
    Database(const std::string&);
    int query_data(std::string,int);
    ~Database();
    static int db_callback(void*,int,char**,char**);  
    bool AddEntry(const std::string&, const std::string& );
    bool checkCredentials(const std::string&,const std::string&);
  private:
    sqlite3 *m_db;

};

class SQL_query{
  public:
    SQL_query(string querr):querr(""){
       this->querr = querr.c_str();
    }
  private:
    const char* querr;
};

class SQL_result{
  public:

};
