#pragma once
#include <raylib.h>

#define MAX_INPUT_CHAR 10
#define MARGIN 20
#define ELEMENT_SPACING 40
#define INPUT_BOX_WIDTH 200
#define INPUT_BOX_HEIGHT 30
#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 45


void DrawGamePage(){
    

    while(!WindowShouldClose()){
        
        
        BeginDrawing();
        ClearBackground(BLACK);

        Rectangle mainRec = {GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 150, 450 , 300};
        Rectangle learnMode = { GetScreenWidth() / 2 - BUTTON_WIDTH  , GetScreenHeight() / 2 + ELEMENT_SPACING , 120, 45 };
        Rectangle compitetiveMode = { GetScreenWidth() / 2 + MARGIN , GetScreenHeight() / 2 + ELEMENT_SPACING , 120, 45 };

        DrawRectangleRounded(mainRec, 0.3, 0, RAYWHITE);

       
        DrawRectangleRounded(learnMode, 1, 6 , LIGHTGRAY);
        DrawText("Learn", learnMode.x + 30, learnMode.y + 13, 20 , BLACK);
        DrawRectangleRounded(compitetiveMode, 1, 6 , LIGHTGRAY);
        DrawText("Compitetive ", compitetiveMode.x + 30, compitetiveMode.y + 13, 20 , BLACK);

        
        EndDrawing();

    }   



    
}