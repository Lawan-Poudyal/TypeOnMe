#include <raylib.h>
#include "loginPage.hpp"


int main(){

    int screenHeight = GetScreenHeight();
    int screenWidth = GetScreenWidth();

    InitWindow(screenWidth, screenHeight, "TypeOnME");
    SetTargetFPS(60);
    
    // Rectangle loginButton = { GetScreenWidth() / 2 - BUTTON_WIDTH  , GetScreenHeight() / 2 + ELEMENT_SPACING , 120, 45 };
    // Rectangle guestButton = { GetScreenWidth() / 2 + MARGIN , GetScreenHeight() / 2 + ELEMENT_SPACING , 120, 45 };

    gameState currentState = LOGIN;

    while(WindowShouldClose() == false){

        

        if (currentState == LOGIN) {
            DrawLoginPage(LOGIN);

        }

        else if (currentState == GAMEMODE) {
        }
    
       
    
    }
    CloseWindow();

    return 0;
}

