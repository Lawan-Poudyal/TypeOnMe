#pragma once
#include <stdio.h>
#include <sqlite3.h> 
#include <string>
using namespace std;


class Database{
  public:
    Database(const std::string&);
    Database(){}
    int query_data(const std::string& ,int);
    ~Database();
    static int db_callback(void*,int,char**,char**);  
    bool AddEntry(const std::string&, const std::string& );
    bool checkCredentialsLogin(const std::string&,const std::string&);
    bool checkCredentialsRegister(const std::string&,const std::string&);
    bool closeDB();
  private:
    sqlite3 *m_db;

};

class sqlTable{
  private:

};

class SQL_query{
  public:
    //SQL_query(string querr,string name):name(""),querr(""){}
 //   int SQL_query_exec(int):sqlTableRes(nullptr){}
  private:
    const char* querr;
    const string name;
};

class SQL_result{
  private:
    sqlTable* sqlTableRes;
    int sqlRows;
    int sqlCols;
    int rc;
    bool returnsOutput;
  public:
   // SQL_result(SQL_query* ,bool):SQL_query(nullptr){}
};


