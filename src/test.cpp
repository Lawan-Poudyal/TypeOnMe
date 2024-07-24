/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------
static void Button003();                // Button: Button003 logic

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main()
{
    // Initialization
    //---------------------------------------------------------------------------------------
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "layout_name");

    // layout_name: controls initialization
    //----------------------------------------------------------------------------------
    // Const text
    const char *GroupBox000Text = "LOGIN";    // GROUPBOX: GroupBox000
    const char *Button003Text = "CLICK";    // BUTTON: Button003
    
    // Define controls variables
    bool TextBox003EditMode = false;
    char TextBox003Text[128] = "Okay Daddy";            // TextBox: TextBox003

    // Define controls rectangles
    Rectangle layoutRecs[4] = {
        (Rectangle){ 712, 264, 392, 256 },    // GroupBox: GroupBox000
        (Rectangle){ 808, 352, 200, 16 },    // Line: Line001
        (Rectangle){ 848, 448, 120, 24 },    // Button: Button003
        (Rectangle){ 848, 304, 120, 24 },    // TextBox: TextBox003
    };
    //----------------------------------------------------------------------------------

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Implement required update logic
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 

            // raygui: controls drawing
            //----------------------------------------------------------------------------------
            // Draw controls
            GuiGroupBox(layoutRecs[0], GroupBox000Text);
            //GuiLine(layoutRecs[1], Line001Text);
            if (GuiButton(layoutRecs[2], Button003Text)) Button003(); 
            if (GuiTextBox(layoutRecs[3], TextBox003Text, 1024, TextBox003EditMode)) TextBox003EditMode = !TextBox003EditMode;
            //----------------------------------------------------------------------------------

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------
// Button: Button003 logic
static void Button003()
{
    // TODO: Implement control logic
}

