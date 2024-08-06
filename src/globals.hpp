#pragma once
#include<string>
#define MAX_SIZE 256
typedef enum Status {
  LOGGEDIN,
  NOTLOGGEDIN
};

class Session{
  private:
    std::string username;
    std::string retrieveSessionUsername(){
      return this->username;
    }
  public:

    Status status;
    Session():status(NOTLOGGEDIN){
      
    }
   
    void switchStatus(){
        status =(status==LOGGEDIN)?NOTLOGGEDIN:LOGGEDIN;
    }
    std::string getUsername(){
        if(status==LOGGEDIN){
          return retrieveSessionUsername();
        }
        else{
          return string("Not Logged In!");
        }
    }
    void setSessionUsername(string username){
      if(status==LOGGEDIN){
        this->username = username;
      }
      else{
        this->username = string("NOT LOGGED IN!");
      }
    } 
};
