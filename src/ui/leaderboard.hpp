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
    Session* session;

    Image first ;     
    Image second ;    
    Image third ;     

    LeaderboardScene(SceneManager* scenemanager,Session* session) : scenemanager(nullptr),db("credentials.db"),session(nullptr) {
        this->session = session;
        this->scenemanager = scenemanager;
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
    }
    Texture2D texture1;
    Texture2D texture2;
    Texture2D texture3;

    void on_entry() override {
     first = LoadImage("assets/first.png");     
     second = LoadImage("assets/second.png");    
     third = LoadImage("assets/third.png");     
    populateLeaderboardVector(); 

    texture1 = LoadTextureFromImage(first);
    texture2 = LoadTextureFromImage(second);
    texture3 = LoadTextureFromImage(third);
   if( (texture1.id)==0 || (texture2.id)==0 || (texture3.id)==0){
     std::cerr << "Error loading textures!" <<endl;
   } 
    }

    void on_event() override {
  
      if(IsKeyPressed(KEY_TAB)){
          scenemanager->switch_to(session->currSessionScene());
      }

    }

void on_update() override {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawText("Leaderboard", GetScreenWidth()/2 - MeasureText("Leaderboard",30)/2, screenHeight + 30*2, 30, BLACK);

    int i = 0;
    for (std::pair<string, int> entry : dbLeaderboard) {
        float yOffset = 100 + i * 100;
        float scale = 60.0f / texture1.width;
        
        DrawRectangleRec((Rectangle){150, yOffset, GetScreenWidth() * 0.75f - 20, 30}, LIGHTGRAY);
        DrawText(entry.first.c_str(), GetScreenWidth()/2 - 100, yOffset, 30, BLACK);
        DrawText(to_string(entry.second).c_str(), GetScreenWidth()/2 + 100, yOffset, 30, BLACK);

        if (i == 0) {
            DrawTextureEx(texture1, (Vector2){150,yOffset-20}, 0, scale, WHITE);
            DrawRectangleRec((Rectangle){150, yOffset, GetScreenWidth() * 0.75f - 20, 30}, Color{});
        } else if (i == 1) {
            DrawTextureEx(texture2, (Vector2){150, yOffset-20}, 0, scale, WHITE);
            DrawRectangleRec((Rectangle){150, yOffset, GetScreenWidth() * 0.75f - 20, 30}, Color{});
        } else if (i == 2) {
            DrawTextureEx(texture3, (Vector2){150, yOffset-20}, 0, scale, WHITE); 
            DrawRectangleRec((Rectangle){150, yOffset, GetScreenWidth() * 0.75f - 20, 30}, Color{});
        }
        i++;
    }

    DrawRectangleRec((Rectangle){100, 100, screenWidth - 20, 100}, RED);
    EndDrawing();
}

    void on_exit() override {    
   
    UnloadImage(first); 
    UnloadImage(second); 
    UnloadImage(third);

      UnloadTexture(texture1);
      UnloadTexture(texture2);
      UnloadTexture(texture3);

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

