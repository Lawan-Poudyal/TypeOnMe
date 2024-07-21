#pragma once
#include <raylib.h>
#include <string>
#include <iostream>
#include "../scene_manager/scene_manager.hpp"

#define MAX_INPUT_CHAR 16 

class RegistrationPage : public Scene {
public:
    void on_entry() override {
    
            InitWindow(GetScreenWidth(),GetScreenHeight(), "TypeOnMe");
      return;
    }

    void on_exit() override{
      CloseWindow();
      return ;
    }
    void on_update() override{
            
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(10, 10, 100, 50, BLUE);
            EndDrawing();
            return;
    }
};
