#pragma once
#include <raylib.h>
#include <string>
#include <iostream>
#include "../scene_manager/scene_manager.hpp"
#include "./login_example.hpp"
#include "./register_example.hpp"
#define MAX_INPUT_CHAR 16 

class RegistrationPage : public Scene {
public:  
 SceneManager* scenemanager;
 RegistrationPage(SceneManager* scenemanager){
    (this->scenemanager) = scenemanager;
  }  
  void on_entry() override {
            return;
    }

    void on_exit() override{
      return ;
    }
    void on_update() override{

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawRectangle(10, 10, 100, 50, BLUE);
            EndDrawing();
            return;
    }
    void on_event(){
       if(IsKeyPressed(KEY_TAB)){
          scenemanager->switch_to("login");
          return;
       }
    }
      private:
};
