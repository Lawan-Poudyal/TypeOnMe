#include <raylib.h>
#include <string>
#include <vector>

void DrawLeaderboardScreen(int screenWidth, int screenHeight) {
    ClearBackground(BLACK);

    // Draw title
    DrawText("Leaderboard", 20, 20, 30, WHITE);

    // Draw graph box
    DrawRectangleLines(20, 60, screenWidth - 40, 200, WHITE);
    DrawText("Graph", 30, 70, 20, WHITE);

    // Draw results box
    DrawRectangleLines(20, 280, (screenWidth - 60) / 2, 200, WHITE);
    DrawText("Your Results", 30, 290, 20, WHITE);
    DrawText("WPM: 78", 30, 320, 18, WHITE);
    DrawText("Correct Words: 156", 30, 350, 18, WHITE);
    DrawText("Accuracy: 95%", 30, 380, 18, WHITE);

    // Draw leaderboard box
    DrawRectangleLines(screenWidth / 2 + 10, 280, (screenWidth - 60) / 2, 200, WHITE);
    DrawText("Top Players", screenWidth / 2 + 20, 290, 20, WHITE);
    
    std::vector<std::string> topPlayers = {
        "1. Nerish    99",
        "2. Shri+Harsh 101",
        "3. Player3    95",
        "4. Player4    92",
        "5. Player5    90"
    };

    for (int i = 0; i < topPlayers.size(); i++) {
        DrawText(topPlayers[i].c_str(), screenWidth / 2 + 20, 320 + i * 30, 18, WHITE);
    }

  
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Typing Game Leaderboard");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        DrawLeaderboardScreen(screenWidth, screenHeight);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}