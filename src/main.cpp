#include "raylib.h"
#include <string.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

typedef enum GameScreen { LOGO, LOGIN, REGISTER, GAMEPLAY } GameScreen;

typedef struct {
    char username[50];
    char password[50];
} User;

// Function prototypes
void DrawLoginScreen(Rectangle textBox, char *inputText);
void DrawRegisterScreen(Rectangle textBox1, Rectangle textBox2, char *inputText1, char *inputText2);
void DrawGameplayScreen(char *currentText, char *typedText, int charactersTyped, float accuracy, int wpm);

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Monkeytype Clone");
    SetTargetFPS(60);

    GameScreen currentScreen = GAMEPLAY;
    User currentUser = {0};
    
    Rectangle loginTextBox = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 25, 200, 50};
    char loginInputText[256] = {0};

    Rectangle regTextBox1 = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 60, 200, 50};
    Rectangle regTextBox2 = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 + 10, 200, 50};
    char regInputText1[256] = {0};
    char regInputText2[256] = {0};

    char gameText[] = "The quick brown fox jumps over the lazy dog.";
    char typedText[256] = {0};
    int charactersTyped = 0;
    float accuracy = 100.0f;
    int wpm = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);



        switch(currentScreen) {
            case LOGIN:
                DrawLoginScreen(loginTextBox, loginInputText);
                // Handle login logic here
                break;
            case REGISTER:
                DrawRegisterScreen(regTextBox1, regTextBox2, regInputText1, regInputText2);
                // Handle register logic here
                break;
            case GAMEPLAY:
                DrawGameplayScreen(gameText, typedText, charactersTyped, accuracy, wpm);
                // Handle gameplay logic here
                break;
            default: break;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void DrawLoginScreen(Rectangle textBox, char *inputText) {
    DrawText("Login", SCREEN_WIDTH/2 - MeasureText("Login", 40)/2, 100, 40, BLACK);
    DrawRectangleRec(textBox, LIGHTGRAY);
    DrawText(inputText, textBox.x + 5, textBox.y + 8, 40, MAROON);
    DrawText("ENTER to submit", SCREEN_WIDTH/2 - MeasureText("ENTER to submit", 20)/2, SCREEN_HEIGHT - 50, 20, DARKGRAY);
}

void DrawRegisterScreen(Rectangle textBox1, Rectangle textBox2, char *inputText1, char *inputText2) {
    DrawText("Register", SCREEN_WIDTH/2 - MeasureText("Register", 40)/2, 100, 40, BLACK);
    DrawRectangleRec(textBox1, LIGHTGRAY);
    DrawRectangleRec(textBox2, LIGHTGRAY);
    DrawText(inputText1, textBox1.x + 5, textBox1.y + 8, 40, MAROON);
    DrawText(inputText2, textBox2.x + 5, textBox2.y + 8, 40, MAROON);
    DrawText("ENTER to submit", SCREEN_WIDTH/2 - MeasureText("ENTER to submit", 20)/2, SCREEN_HEIGHT - 50, 20, DARKGRAY);
}

void DrawGameplayScreen(char *currentText, char *typedText, int charactersTyped, float accuracy, int wpm) {
    DrawText(currentText, 50, SCREEN_HEIGHT/2 - 50, 30, GRAY);
    DrawText(typedText, 50, SCREEN_HEIGHT/2, 30, BLACK);
    DrawText(TextFormat("Accuracy: %.2f%%", accuracy), 50, SCREEN_HEIGHT - 100, 20, BLACK);
    DrawText(TextFormat("WPM: %d", wpm), SCREEN_WIDTH - 150, SCREEN_HEIGHT - 100, 20, BLACK);
}
