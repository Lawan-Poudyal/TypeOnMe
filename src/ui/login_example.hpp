#pragma once
#include "./login_example.hpp"
#include "./register_example.hpp"
#include"../db/database.hpp"
#define MAX_INPUT_CHAR 16 

using namespace std;

class LoginScene : public Scene {
public:
    char username[MAX_INPUT_CHAR + 1] = "\0";
    char password[MAX_INPUT_CHAR + 1] = "\0";
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
        loginButton = {screenWidth / 2 - 50 - 60, screenHeight / 2, 120, 45};
        guestButton = {screenWidth / 2 + 80 - 60, screenHeight / 2, 120, 45};
    }

    void on_entry() override{
        mainRec = {screenWidth / 2 - 210, screenHeight / 2 - 150, 450, 300};
        loginButton = {screenWidth / 2 - 50 - 60, screenHeight / 2, 120, 45};
        guestButton = {screenWidth / 2 + 80 - 60, screenHeight / 2, 120, 45};
    }

    void on_event() override {
        if (IsKeyPressed(KEY_TAB)) {
            typingUsername = !typingUsername;
            typingPassword = !typingPassword;
        }


        if (IsKeyPressed(KEY_ENTER)) {
          
          scenemanager->switch_to("registerpage");
  
        }


        if (IsKeyPressed(KEY_BACKSPACE)) {
            if (typingUsername && usernameLength > 0) {
                username[--usernameLength] = '\0';
            } else if (typingPassword && passwordLength > 0) {
                password[--passwordLength] = '\0';
            }
        }

        int key = GetCharPressed();
        if (key > 0 && key != KEY_SPACE) {
            if (typingUsername && usernameLength < MAX_INPUT_CHAR) {
                username[usernameLength] = (char)key;
                username[usernameLength + 1] = '\0';
                usernameLength++;
            } else if (typingPassword && passwordLength < MAX_INPUT_CHAR) {
                password[passwordLength] = (char)key;
                password[passwordLength + 1] = '\0';
                passwordLength++;
            }
        }
        
        if (IsButtonClicked(loginButton)) {
            string sUsername = username;
            string sPassword = password;
            db.AddEntry(sUsername, sPassword);
            cout << sUsername << "+" << sPassword;
        }

        if (IsButtonClicked(guestButton)) {
            TraceLog(LOG_INFO, "Signed as Guest.");
        }
    }
    bool IsButtonClicked(Rectangle button) {
        return (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
    }

    void on_update() override {

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangleRounded(mainRec, 0.3, 0, RAYWHITE);

        DrawText("Username:", GetScreenWidth() / 2 - 210 + 20 + 50, GetScreenHeight() / 2 + 20 - 150, 20, BLACK);
        DrawText(username, GetScreenWidth() / 2 - 210 + 20 + 100 + 20 + 50, GetScreenHeight() / 2 + 20 - 150, 20, BLACK);
        if (typingUsername) DrawRectangleLines(GetScreenWidth() / 2 - 210 + 20 + 100 + 20 + 50, GetScreenHeight() / 2 + 20 - 150, 200, 30, RED);
        else DrawRectangleLines(GetScreenWidth() / 2 - 210 + 20 + 100 + 20 + 50, GetScreenHeight() / 2 + 20 - 150, 200, 30, LIGHTGRAY);

        DrawText("Password:", GetScreenWidth() / 2 - 210 + 20 + 50, GetScreenHeight() / 2 + 20 - 150 + 20 + 20, 20, BLACK);
        for (int i = 0; i < passwordLength; i++) {
            DrawText("*", GetScreenWidth() / 2 - 210 + 20 + 100 + 20 + 50 + i * 10, GetScreenHeight() / 2 + 20 - 150 + 20 + 20, 20, BLACK);
        }
        if (typingPassword) DrawRectangleLines(GetScreenWidth() / 2 - 210 + 50 + 20 + 100 + 20, GetScreenHeight() / 2 + 20 - 150 + 20 + 20, 200, 30, RED);
        else DrawRectangleLines(GetScreenWidth() / 2 - 210 + 20 + 100 + 20 + 50, GetScreenHeight() / 2 + 20 - 150 + 20 + 20, 200, 30, LIGHTGRAY);

        DrawRectangleRounded(loginButton, 1, 6, LIGHTGRAY);
        DrawText("Login", loginButton.x + 30, loginButton.y + 13, 20, BLACK);

        DrawRectangleRounded(guestButton, 1, 6, LIGHTGRAY);
        DrawText("Guest", guestButton.x + 30, guestButton.y + 13, 20, BLACK);

        EndDrawing();
    }
    

    void on_exit() override {
      return;
    }
  private:
    SceneManager* scenemanager;
};

