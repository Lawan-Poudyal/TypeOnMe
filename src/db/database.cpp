#include "./database.hpp"
#include"../main.hpp"

Database::Database(const std::string& db){ 
     
   char *zErrMsg = 0;
   int rc;
   rc = sqlite3_open(db.c_str(), &m_db);

   if( rc ) {
      fprintf(stderr, "Can't create database: %s\n", sqlite3_errmsg(m_db));      
   } else {
      fprintf(stderr, "Created database successfully\n");
   }
  
}

Database::~Database(){
   sqlite3_close(m_db);
}

int Database::db_callback(
    void *data,
    int argc,
    char** argv,
    char** azColName){
      for(int i=0;i<argc;i++)std::cout<<azColName[i]<<"="<<argv[i]?argv[i]:"NULL";
    }

int Database::query_data(
    std::string query,
    int create_t =0
    ){

   if(create_t){
    char *zErrMsg = 0;
    int rc;
    char* sql = "CREATE TABLE credentials("  \
          "UID                INTEGER PRIMARY KEY AUTOINCREMENT," \
          "USERNAME           TEXT," \
          "PASSWORD           TEXT)";
    rc = sqlite3_exec(m_db,sql,db_callback,0,&zErrMsg);
    if(rc!= SQLITE_OK){
      fprintf(stdout,"SQLITE Error:%s\n",zErrMsg);
    }
    else{
      fprintf(stdout,"Table database query successful");
    }
  }
   
   else{

    char *zErrMsg = 0;
          int rc;
      char* sql ="SELECT * from CREDENTIALS";
      rc = sqlite3_exec(m_db,sql,db_callback,0,&zErrMsg);
      if(rc!= SQLITE_OK){
        fprintf(stdout,"SQLITE Error:%s\n",zErrMsg);
      }
      else{
        fprintf(stdout,"Table database query successful");
      }


     }
     return 0; 
   }

bool Database::AddEntry( const std::string& username, const std::string& password) {
    // Prepare SQL statement to insert data
    std::string sql = "INSERT INTO credentials (USERNAME, PASSWORD) VALUES (?, ?)";
    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(m_db, sql.c_str(), -1, &stmt, nullptr);
    if (result != SQLITE_OK) {
      std::cerr << "Error preparing statement: " << sqlite3_errmsg(m_db) << std::endl;
      return false;
    }

    // Bind values to the statement
    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, password.c_str(),-1,SQLITE_TRANSIENT);

    // Execute the statement
    result = sqlite3_step(stmt);
    sqlite3_finalize(stmt);  // Clean up the statement

    if (result != SQLITE_DONE) {
      std::cerr << "Error inserting data: " << sqlite3_errmsg(m_db) << std::endl;
      return false;
    }
    return true;
  }

bool Database::checkCredentials(const std::string& usrname,const std::string& passwd){
  
    char* zErrMsg = nullptr;
    int rc;
    sqlite3_stmt* stmt;

    // SQL query with placeholders for username and password
    const char* sql = "SELECT * FROM credentials WHERE USERNAME = ? AND PASSWORD = ?";

    // Prepare the SQL statement
    rc = sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQLITE Error: %s\n", sqlite3_errmsg(m_db));
        return false;
    }

    // Bind the username and password parameters to the prepared statement
    sqlite3_bind_text(stmt, 1, usrname.c_str(), usrname.length(), SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, passwd.c_str(), passwd.length(), SQLITE_TRANSIENT);

    // Execute the prepared statement and iterate over the result rows
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Retrieve column values (assuming username and password are at index 1 and 2)
        const char* username = (char*)sqlite3_column_text(stmt, 1);
        const char* password = (char*)sqlite3_column_text(stmt, 2);
   
        if((strcmp(username,usrname.c_str()))==0 && (strcmp(password,passwd.c_str()))==0){
          std::cout << "Successfully Logged in!"<<std::endl;
          return true;
        }

    }

    if (rc != SQLITE_DONE) {
        std::cerr << "SQLITE Error during query execution: " << sqlite3_errmsg(m_db) << std::endl;
    }
    sqlite3_finalize(stmt);
    return true;
}

