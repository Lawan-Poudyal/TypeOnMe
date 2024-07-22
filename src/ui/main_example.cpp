#pragma once
#include "./register_example.hpp"
#include <string>
#include "./login_example.hpp"
int init_width = GetScreenWidth();
int init_height = GetScreenHeight();

int main(){
  SceneManager scenemanager;
  RegistrationPage registerpage(&scenemanager);
  LoginScene login(&scenemanager); 
  scenemanager.add("registerpage",&registerpage);
 scenemanager.add("login",&login);
 
  InitWindow(1440, 720, "TypeOnMe");
  
  SetTargetFPS(200);
  scenemanager.switch_to("registerpage");
  
  while(!WindowShouldClose()){
    BeginDrawing();
    scenemanager.update();
    scenemanager.poll_event();
  }

  return 0;
}
