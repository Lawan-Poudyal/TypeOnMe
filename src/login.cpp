#include <raylib.h>
#include <string.h>

#define MAX_INPUT_CHAR 50

typedef enum{
    LOGIN,
    GAMEMODE;
} gameState;

bool IsButtonClicked (Rectangle button ){
    return (CheckCollisionPointRec(GetMousePosition(), button ) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}

int main() {
   // Color black 
    
    char username[MAX_INPUT_CHAR + 1] = "\0";
    char password[MAX_INPUT_CHAR + 1] = "\0";

    bool typingUsername = true;
    bool typingPassword = false;

    int usernameLength = 0;
    int passwordLength = 0;

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    gameState = LOGIN;


    InitWindow(screenWidth , screenHeight, "TypeOnMe");
    SetTargetFPS(60);

    Rectangle mainRec ={GetScreenWidth()/2 - 210, GetScreenHeight()/2 - 150, 450 , 300};
    Rectangle loginButton = { GetScreenWidth() / 2 - 50 - 60 ,GetScreenHeight() / 2 , 120, 45 };
    Rectangle guestButton = { GetScreenWidth() / 2 + 80 - 60 ,GetScreenHeight() / 2 , 120, 45 };

    

    while(WindowShouldClose() == false){
        

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
        if(key > 0 && key != KEY_SPACE){
            if(typingUsername && usernameLength < MAX_INPUT_CHAR){
                username[usernameLength]= (char)key;
                username[usernameLength +1] = '\0';
                usernameLength++;
            } else if (typingPassword && passwordLength < MAX_INPUT_CHAR){
                password[passwordLength] = (char)key;
                password[passwordLength + 1] = '\0';
                passwordLength++;
            }
        }

        if(IsButtonClicked(loginButton)){
            TraceLog(LOG_INFO, "Login button clicke. \n Username: %s \n Password: %s", username, password);
            gameState = GAMEMODE;
        }

        if(IsButtonClicked(guestButton)){
            TraceLog(LOG_INFO, "Signed as Guest.");
            gameState = GAMEMODE;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangleRounded(mainRec, 0.3, 0, RAYWHITE);
        
        DrawText("Username:", GetScreenWidth()/2 - 210 + 20 + 50, GetScreenHeight()/2 + 20 - 150, 20, BLACK);
        DrawText(username, GetScreenWidth()/2 - 210 + 20 + 100 + 20 + 50 , GetScreenHeight()/2 + 20 - 150, 20, BLACK );
        if (typingUsername) DrawRectangleLines(GetScreenWidth()/2 - 210 + 20 + 100 + 20 + 50 , GetScreenHeight()/2 + 20 - 150, 200 , 30 , RED);
        else DrawRectangleLines(GetScreenWidth()/2 - 210 + 20 + 100 + 20 + 50, GetScreenHeight()/2 + 20 - 150, 200 , 30 , LIGHTGRAY);

        DrawText("Password:", GetScreenWidth()/2 - 210 + 20 + 50, GetScreenHeight()/2 + 20 - 150 + 20 + 20, 20, BLACK);
        for (int i = 0; i < passwordLength; i++) {
            DrawText("*",  GetScreenWidth()/2 - 210 + 20 + 100 + 20 + 50 + i * 10 , GetScreenHeight()/2 + 20 - 150 + 20 +20, 20, BLACK);
        }
        //DrawText(password, GetScreenWidth()/2 - 210 + 20 + 100 + 20 , GetScreenHeight()/2 + 20 - 150 + 20 +20, 20, BLACK );
        if (typingPassword) DrawRectangleLines(GetScreenWidth()/2 - 210 + 50 +20 + 100 + 20 , GetScreenHeight()/2 + 20 - 150 +20 + 20, 200 , 30 , RED);
        else DrawRectangleLines(GetScreenWidth()/2 - 210 + 20 + 100 + 20 + 50, GetScreenHeight()/2 + 20 - 150 + 20 + 20, 200 , 30 , LIGHTGRAY);
        
        
        DrawRectangleRounded(loginButton, 1, 6 , LIGHTGRAY);
        DrawText("Login", loginButton.x + 30, loginButton.y + 13, 20 , BLACK);

        DrawRectangleRounded(guestButton, 1, 6 , LIGHTGRAY);
        DrawText("Guest", guestButton.x + 30, guestButton.y + 13, 20 , BLACK);

        
        
        EndDrawing();

    }

    

}
