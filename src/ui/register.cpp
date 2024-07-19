#include <raylib.h>
#include <string.h>
void DrawRegisterScreen(Rectangle,Rectangle,char*,char*);
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
int main(){

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Monkeytype Clone");
    SetTargetFPS(60);
  Rectangle loginTextBox = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 25, 200, 50};
  char loginInputText[256] = {0};

    Rectangle regTextBox1 = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 60, 200, 50};
    Rectangle regTextBox2 = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 10, 200, 50};
    char regInputText1[256] = {0};
    char regInputText2[256] = {0};
  while(!WindowShouldClose()){
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawRegisterScreen(regTextBox1,regTextBox2,regInputText1,regInputText2);
}
}

void DrawRegisterScreen(
    Rectangle textBox1, 
    Rectangle textBox2, 
    char *inputText1, 
    char *inputText2)
{
    DrawText("Register", SCREEN_WIDTH/2 - MeasureText("Register", 40)/2, 100, 40, BLACK);
    DrawRectangleRec(textBox1, LIGHTGRAY);
    DrawRectangleRec(textBox2, LIGHTGRAY);
    DrawText(inputText1, textBox1.x + 5, textBox1.y + 8, 40, MAROON);
    DrawText(inputText2, textBox2.x + 5, textBox2.y + 8, 40, MAROON);
    DrawText("ENTER to submit", SCREEN_WIDTH/2 - MeasureText("ENTER to submit", 20)/2, SCREEN_HEIGHT - 50, 20, DARKGRAY);
  
}


