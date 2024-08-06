#pragma once
#include "raylib.h"
#include <vector>
#include "../db/database.hpp"
#include "../scene_manager/scene_manager.hpp"

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

typedef struct entrybox{
  Rectangle rect;
  Color color;
}entryBox;

class LeaderboardScene : public Scene {
public:
    Rectangle mainRec;
    Rectangle graphArea;
    Rectangle wpmBox;
    Rectangle leaderboardBox;
    vector<Vector2> points;
    int screenWidth;
    int screenHeight;
    int i;
    Database db;
    entryBox common_entryBox = {0}; 

    LeaderboardScene(SceneManager* scenemanager) : scenemanager(nullptr),db("credentials.db") {
        this->scenemanager = scenemanager;
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
    }

    void on_entry() override {
    
    populateLeaderboardVector();
     
    }

    void on_event() override {

    }

    void on_update() override {
    BeginDrawing();
      ClearBackground(RAYWHITE);
        int i=0;
        for(std::pair<string,int>entry: dbLeaderboard){
          DrawRectangleRec((Rectangle){50,i+50,GetScreenWidth()/2-20,30},LIGHTGRAY);
          DrawText(entry.first.c_str(),100,i+50,30,BLACK);
          DrawText(to_string(entry.second).c_str(),200,i+50,30,BLACK);
          i+=100;
        }

          DrawRectangleRec((Rectangle){100,100,screenWidth-20,100},RED);
        EndDrawing();

    }

    void on_exit() override {
    
    }

    void populateLeaderboardVector(){
      std::vector<std::pair<string,int>> bufVec;
      bufVec = db.getLeaderboard();
      dbLeaderboard = bufVec;
    }

private:
    SceneManager* scenemanager;
    std::vector<std::pair<string,int>> dbLeaderboard;
};

