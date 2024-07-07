#pragma once
#include <raylib.h>
#include "isButtonClicked.hpp"  
#include "gameModes.hpp"


void DrawGamePage(gameState currentState){
    

    while(!WindowShouldClose()){
        
        
        BeginDrawing();
        ClearBackground(BLACK);

        Rectangle mainRec = {GetScreenWidth() / 2 - 210, GetScreenHeight() / 2 - 150, 450 , 300};
        Rectangle learnMode = { GetScreenWidth() / 2 - 130 , GetScreenHeight() / 2 - 30 , 140, 45 };
        Rectangle competitiveMode = { GetScreenWidth() / 2 + 30 , GetScreenHeight() / 2 - 30 , 140, 45 };

        DrawRectangleRounded(mainRec, 0.3, 0, RAYWHITE);

        DrawText("Choose Game Mode.", GetScreenWidth() / 2 - 120 , GetScreenHeight() / 2 - 110 , 30 , BLACK);

       
        DrawRectangleRounded(learnMode, 1, 6 , LIGHTGRAY);
        DrawText("Learning", learnMode.x + 30, learnMode.y + 13, 20 , BLACK);
        DrawRectangleRoundedLines(learnMode, 1, 6, BLACK);

        DrawRectangleRounded(competitiveMode, 1, 6 , LIGHTGRAY);
        DrawText("Competitive ", competitiveMode.x + 15, competitiveMode.y + 13, 20 , BLACK);
        DrawRectangleRoundedLines(competitiveMode, 1, 6, BLACK);

            // Rectangle key = { GetScreenWidth() / 2 + 100 , GetScreenHeight() / 2 + 50 , 50, 49 };
            // DrawRectangleRounded(key, 0.3, 1, LIGHTGRAY);

        if(IsButtonClicked(learnMode)){
            currentState = LEARNMODE;
            // DrawLearnMode(LEARNMODE);

        }
        else if (IsButtonClicked(competitiveMode)){
            currentState = COMPETITIVEMODE;
            //DrawCompetitiveMode(COMPETITIVEMODE);
        }

        
        EndDrawing();

    }   



    
}