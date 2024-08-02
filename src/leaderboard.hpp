#pragma once
#include "raylib.h"
#include <vector>

#define MARGIN 20
#define ELEMENT_SPACING 40
#define BOX_WIDTH 350
#define BOX_HEIGHT 180
#define GRAPH_WIDTH 700
#define GRAPH_HEIGHT 150
#define POINT_RADIUS 5
#define DEFAULT_FONT_SIZE 20
#define DEFAULT_HEADER_FONT_SIZE 30

using namespace std;

class LeaderboardScene : public Scene {
public:
    Rectangle mainRec;
    Rectangle graphArea;
    Rectangle wpmBox;
    Rectangle leaderboardBox;
    vector<Vector2> points;
    int screenWidth;
    int screenHeight;

    LeaderboardScene(SceneManager* scenemanager) : scenemanager(nullptr) {
        this->scenemanager = scenemanager;
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        setupLayout();
    }

    void setupLayout() {
        mainRec = { screenWidth / 2 - 350, screenHeight / 2 - 225, 700, 450 };
        graphArea = { 50, 50, GRAPH_WIDTH, GRAPH_HEIGHT };
        wpmBox = { 50, 220, BOX_WIDTH, BOX_HEIGHT };
        leaderboardBox = { 400, 220, BOX_WIDTH, BOX_HEIGHT };
        points = { {70, 180}, {150, 120}, {230, 100}, {310, 140}, {390, 130}, {470, 110}, {550, 140}, {630, 120} };
    }

    void on_entry() override {
        // Any setup needed when the scene is entered
    }

    void on_event() override {
        // Handle events such as mouse clicks or key presses
    }

    void on_update() override {
        ClearBackground(RAYWHITE);

        // Draw the main rectangle
        DrawRectangleRounded(mainRec, 0.3, 0, LIGHTGRAY);

        // Draw the graph area
        DrawRectangle(graphArea.x, graphArea.y, graphArea.width, graphArea.height, LIGHTGRAY);

        // Draw the points and lines on the graph
        for (int i = 0; i < points.size() - 1; i++) {
            DrawLineV(points[i], points[i + 1], RED);
            DrawCircleV(points[i], POINT_RADIUS, GREEN);
        }
        DrawCircleV(points.back(), POINT_RADIUS, GREEN);

        // Draw the WPM result box
        DrawRectangle(wpmBox.x, wpmBox.y, wpmBox.width, wpmBox.height, DARKGRAY);
        DrawText("WPM: 78", wpmBox.x + 20, wpmBox.y + 20, DEFAULT_FONT_SIZE, WHITE);
        DrawText("Other results", wpmBox.x + 20, wpmBox.y + 60, DEFAULT_FONT_SIZE, WHITE);

        // Draw the leaderboard box
        DrawRectangle(leaderboardBox.x, leaderboardBox.y, leaderboardBox.width, leaderboardBox.height, DARKGRAY);
        DrawText("Leaderboard", leaderboardBox.x + 20, leaderboardBox.y + 20, DEFAULT_FONT_SIZE, WHITE);
        DrawText("a) Nanish 89", leaderboardBox.x + 20, leaderboardBox.y + 60, DEFAULT_FONT_SIZE, WHITE);
        DrawText("b) Shritarsh lol", leaderboardBox.x + 20, leaderboardBox.y + 100, DEFAULT_FONT_SIZE, WHITE);

        EndDrawing();
    }

    void on_exit() override {
        // Any cleanup needed when the scene is exited
    }

private:
    SceneManager* scenemanager;
};

