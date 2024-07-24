#pragma once
#include "./login_example.hpp"
#include "./register_example.hpp"
#include"../db/database.hpp"

#define MAX_INPUT_CHAR_UP 10
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
    char username[MAX_INPUT_CHAR_UP + 1] = "\0";
    char password[MAX_INPUT_CHAR_UP + 1] = "\0";

    bool typingUsername = true;
    bool typingPassword = false;

    int usernameLength = 0;
    int passwordLength = 0;
    Rectangle mainRec;
    Rectangle loginButton;
    Rectangle guestButton;
    Database db;
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    LoginScene(SceneManager* scenemanager) : db("credentials.db"), scenemanager(nullptr){
        db.query_data("", 1);
        this->scenemanager = scenemanager;
        mainRec = {screenWidth / 2 - 210, screenHeight / 2 - 150, 450, 300};
        loginButton = {screenWidth / 2 - 110, screenHeight / 2, 120, 45};
        guestButton = {screenWidth / 2 + 20, screenHeight / 2, 120, 45};
    }

    void on_entry() override{
    
    Rectangle mainRec = {
      GetScreenWidth() / 2 -210,
      GetScreenHeight() / 2 - 150,
      450,
      300};
    Rectangle loginButton = { 
      GetScreenWidth() / 2 - BUTTON_WIDTH,
      GetScreenHeight() / 2 + ELEMENT_SPACING,
      120,
      45 };
    Rectangle guestButton = { GetScreenWidth() / 2 + MARGIN ,
      GetScreenHeight() / 2 + ELEMENT_SPACING ,
      120,
      45 }; 
    }

    void on_event() override {

    if(IsKeyPressed(KEY_ENTER)){
        scenemanager->switch_to("registerpage");
        return;
    }
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

           
           if (IsButtonClicked(loginButton)) {
               TraceLog(LOG_INFO, "Login button clicked. \n Username:%s\n Password:%s", username, password);
               //currentState = CHOOSEMODE;
               //DrawGamePage(CHOOSEMODE);

           }

           if (IsButtonClicked(guestButton)) {
               TraceLog(LOG_INFO, "Signed as Guest.");
               //currentState = CHOOSEMODE;
               //DrawGamePage(CHOOSEMODE);
           }
    }

    bool IsButtonClicked(Rectangle button) {
        return (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
    }
    void on_update() override {

            ClearBackground(RAYWHITE); 
            
            DrawRectangleRounded(mainRec, 0.3, 0, RAYWHITE); 

            DrawText(
                "User Login Page",
                GetScreenWidth()/2 - INPUT_BOX_WIDTH ,
                GetScreenHeight()/2- INPUT_BOX_HEIGHT*2-MARGIN*6,
                DEFAULT_HEADER_FONT_SIZE,
                BLACK);

            DrawText(
                "Username:", 
                GetScreenWidth()/2  - INPUT_BOX_WIDTH / 2 - MARGIN * 3,
                GetScreenHeight() / 2 - INPUT_BOX_HEIGHT - ELEMENT_SPACING*2,
                DEFAULT_FONT_SIZE,
                BLACK);
            DrawText(
                username,
                GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 + MARGIN * 3,
                GetScreenHeight()/ 2 - INPUT_BOX_HEIGHT - ELEMENT_SPACING*2,
                DEFAULT_FONT_SIZE,
                BLACK);
        
            if (typingUsername) DrawRectangleLines( 
                GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 + MARGIN * 3,
                GetScreenHeight()/ 2 - INPUT_BOX_HEIGHT - ELEMENT_SPACING*2,
                INPUT_BOX_WIDTH,
                INPUT_BOX_HEIGHT,
                RED);
            else DrawRectangleLines(
                GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 + MARGIN * 3,
                GetScreenHeight() / 2 - INPUT_BOX_HEIGHT - ELEMENT_SPACING*2,
                INPUT_BOX_WIDTH,
                INPUT_BOX_HEIGHT,
                LIGHTGRAY);
        
            DrawText(
                "Password:",
                GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN*3,
                GetScreenHeight() / 2 - ELEMENT_SPACING,
                DEFAULT_FONT_SIZE,
                BLACK);
            for (int i = 0; i < passwordLength; i++) {
                DrawText(
                    "*", 
                    GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 + MARGIN * 3 + i * 10,
                    GetScreenHeight() / 2 - ELEMENT_SPACING,
                    DEFAULT_FONT_SIZE,
                    BLACK);
            }
            //DrawText(password, GetScreenWidth()/2 - 210 + 20 + 100 + 20 , GetScreenHeight()/2 + 20 - 150 + 20 +20, 20, BLACK );
        
            if (typingPassword) DrawRectangleLines(
                GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 + MARGIN * 3,
                GetScreenHeight() / 2 - ELEMENT_SPACING, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT, RED);
            else DrawRectangleLines(GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 + MARGIN * 3, GetScreenHeight() / 2 - ELEMENT_SPACING, INPUT_BOX_WIDTH, INPUT_BOX_HEIGHT, LIGHTGRAY);        
          
            DrawRectangleRounded(loginButton, 1, 6 , LIGHTGRAY);
            DrawText(
                "Login",
                loginButton.x + 30,
                loginButton.y + 13,
                DEFAULT_FONT_SIZE,
                BLACK);
            //DrawRectangleRoundedLines(loginButton, 1, 6 , BLACK);

            DrawRectangleRounded(guestButton,
                1,
                6,
                LIGHTGRAY);
            DrawText("Guest",
                guestButton.x + 30,
                guestButton.y + 13,
                DEFAULT_FONT_SIZE,
                BLACK);
           // DrawRectangleRoundedLines(guestButton, 1, 6 , BLACK);
          EndDrawing();
    }
    

    void on_exit() override {
      return;
    }
  private:
    SceneManager* scenemanager;
};

