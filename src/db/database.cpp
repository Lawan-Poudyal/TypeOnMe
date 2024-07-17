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
    char** azColName
    )
{
      for(int i=0;i<argc;i++){
        std::cout<< azColName[i]<< "="<<argv[i]?argv[i]:"NULL";
      }
}

int Database::query_data(
                          std::string query,
                          int create_t =0
                          )
{
   if(create_t){
    char *zErrMsg = 0;
    int rc;
    char* sql = "CREATE TABLE credentials("  \
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

