#pragma once
#include<cstring>
#include "./login_example.hpp"
#include "./register_example.hpp"
#include"../db/database.hpp"
#include "./graph.hpp"
#include "./../globals.hpp"
#define MAX_INPUT_CHAR_UP 18
#define MARGIN 20
#define ELEMENT_SPACING 40
#define INPUT_BOX_WIDTH 200
#define INPUT_BOX_HEIGHT 30
#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 45
#define DEFAULT_FONT_SIZE 20
#define DEFAULT_HEADER_FONT_SIZE 30
using namespace std;




class LoginScene : public Scene {
public:
    Graph testGraph; 
    char username[MAX_INPUT_CHAR_UP + 1] = "\0";
    char password[MAX_INPUT_CHAR_UP + 1] = "\0";

    bool typingUsername = true;
    bool typingPassword = false;

    int usernameLength = 0;
    int passwordLength = 0;
    Rectangle mainRec;
    Rectangle loginButton;
    Rectangle switchToRegistration;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    Session* session; 

    LoginScene(SceneManager* scenemanager,Session* session) : db("credentials.db"), scenemanager(nullptr),session(session){
        db.query_data("", 1);
        db.InitializeLeaderboard();
        this->scenemanager = scenemanager;
        Rectangle mainRec;
        Rectangle loginButton;
        Rectangle switchToRegistration;
    }

 void on_entry() override{
    Database db("credentials.db");
    
    
    loginButton = { 
      GetScreenWidth() / 2 - BUTTON_WIDTH,
      GetScreenHeight() / 2 + ELEMENT_SPACING,
      120,
      45 };
    switchToRegistration = {
     GetScreenWidth()/2  - INPUT_BOX_WIDTH -MARGIN*4,
      GetScreenHeight() / 2 + ELEMENT_SPACING*1 ,
      120,45
    };

    mainRec = {
      GetScreenWidth()/ 2 -300,
      GetScreenHeight()/ 2 -200,
      450,
      300};

    }

    void on_event() override {

    if (IsKeyPressed(KEY_TAB)){
               typingUsername = !typingUsername;
               typingPassword = !typingPassword;
           }

            if (IsKeyPressed(KEY_BACKSPACE)) {
               if (typingUsername && usernameLength > 0) {
                   username[--usernameLength] = '\0';
               } else if (typingPassword && passwordLength > 0) {
                   password[--passwordLength] = '\0';
               }
           }
           int key = GetCharPressed();
               if(key >0 && key != KEY_SPACE){
                   if(typingUsername && usernameLength < MAX_INPUT_CHAR_UP){
                       username[usernameLength]= (char)key;
                       username[usernameLength + 1] = '\0';
                       usernameLength++;
                   } else if (typingPassword && passwordLength < MAX_INPUT_CHAR_UP){
                       password[passwordLength] = (char)key;
                       password[passwordLength + 1] = '\0';
                       passwordLength++;
                   }
               }

           
            std::string strp(password);
            std::string stru(username);
           
            if (IsButtonClicked(loginButton) && checkLoginInfo()){ 
              if(db.checkCredentialsLogin(stru,strp)) {

                  session->switchStatus();
                  session->setSessionUsername(string(username));
                  session->setSessionScene("cgamemode");
                  scenemanager->switch_to("cgamemode");
              }
            }
           else if(IsButtonClicked(loginButton)){

                drawTempText=true;        
                dt=GetFrameTime();
           }
           if(IsButtonClicked(switchToRegistration)){
             session->setSessionScene("registerpage");
             scenemanager->switch_to("registerpage");
           }
    }

    bool IsButtonClicked(Rectangle button) {
        return (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
    }
    void on_update() override {

      ClearBackground(Color{46,26,71});
            
            testGraph.Draw(); 
            DrawRectangleRounded(mainRec, 0.3, 1, RAYWHITE); 
            DrawText("Not Registered Yet?",
                GetScreenWidth()/2  - INPUT_BOX_WIDTH -MARGIN*4,
                GetScreenHeight() / 2 + ELEMENT_SPACING*1 ,
                15,
                BLACK);
            
            DrawText(
                "User Login Page",
                GetScreenWidth()/2 - INPUT_BOX_WIDTH ,
                GetScreenHeight()/2 -MARGIN*8,
                DEFAULT_HEADER_FONT_SIZE,
                BLACK);

            DrawText(
                "Username:", 
                GetScreenWidth()/2  - INPUT_BOX_WIDTH / 2 -MARGIN*3-MeasureText("Username:",DEFAULT_FONT_SIZE),
                GetScreenHeight() / 2 - ELEMENT_SPACING*2,
                DEFAULT_FONT_SIZE,
                BLACK);
            DrawText(
                username,
                GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN*3,
                GetScreenHeight()/ 2 - ELEMENT_SPACING*2,
                DEFAULT_FONT_SIZE,
                BLACK);
        
            if (typingUsername) DrawRectangleLines( 
                GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN*3,
                GetScreenHeight()/ 2  - ELEMENT_SPACING*2,
                INPUT_BOX_WIDTH,
                INPUT_BOX_HEIGHT,
                RED);
            else DrawRectangleLines(
                GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN*3,
                GetScreenHeight() / 2  - ELEMENT_SPACING*2,
                INPUT_BOX_WIDTH,
                INPUT_BOX_HEIGHT,
                LIGHTGRAY);
        
            DrawText(
                "Password:",
                GetScreenWidth()/2  - INPUT_BOX_WIDTH / 2 -MARGIN*3-MeasureText("Password:",DEFAULT_FONT_SIZE),
                GetScreenHeight() / 2 - ELEMENT_SPACING,
                DEFAULT_FONT_SIZE,
                BLACK);
            for (int i = 0; i < passwordLength; i++) {
                DrawText(
                    "*", 
                    GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN*3 + i * 10,
                    GetScreenHeight() / 2 - ELEMENT_SPACING,
                    DEFAULT_FONT_SIZE,
                    BLACK);
            
            }

            if(drawTempText){
                renderTempText(
                "Please type username and password!",
                GetScreenWidth() / 2,
                GetScreenHeight()/ 2  - ELEMENT_SPACING*2,
                15,BLACK); 
            }

            //DrawText(password, GetScreenWidth()/2 - 210 + 20 + 100 + 20 , GetScreenHeight()/2 + 20 - 150 + 20 +20, 20, BLACK );
        
            if (typingPassword) 
              DrawRectangleLines(
                GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN*3,
                GetScreenHeight() / 2 - ELEMENT_SPACING, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT, RED);
            else DrawRectangleLines(GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN*3, GetScreenHeight() / 2 - ELEMENT_SPACING, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT, LIGHTGRAY);        
          
            DrawRectangleRounded(loginButton, 1, 6 , LIGHTGRAY);
            DrawText(
                "Login",
                loginButton.x + 30,
                loginButton.y + 13,
                DEFAULT_FONT_SIZE,
                BLACK);
            //DrawRectangleRoundedLines(loginButton, 1, 6 , BLACK);

           // DrawRectangleRoundedLines(guestButton, 1, 6 , BLACK);
          EndDrawing();
    }
    bool checkLoginInfo(){
      return(strlen(username) && strlen(password));
    } 
    void renderTempText(string tempText,int posX,int posY,int fontSize,Color color){
          //GetFrameTime()
            DrawText(tempText.c_str(),posX,posY,fontSize,color);
            dt+=GetFrameTime(); 
          if(dt>3){
              
            return;
          }
    }
    void on_exit() override {
      db.closeDB();
      return;
    }

private:
    SceneManager* scenemanager;
    bool drawTempText =false;
    int dt;  
    Database db;
};

