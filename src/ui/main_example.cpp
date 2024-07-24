#pragma once
#include "./register_example.hpp"
#include <string>
#include "./login_example.hpp"

int main(){
  SceneManager scenemanager;
  RegistrationPage registerpage(&scenemanager);
  LoginScene login(&scenemanager);
 //CGamemode cgamemode(&scenemanager);
  scenemanager.add("registerpage",&registerpage);
  scenemanager.add("login",&login);
  //scenemanager.add("cgamemode",&cgamemode);

  InitWindow(1440, 720, "TypeOnMe");
  
  SetTargetFPS(200);
  scenemanager.switch_to("login");
  
  while(!WindowShouldClose()){
    BeginDrawing();
    scenemanager.update();
    scenemanager.poll_event();
  }

  return 0;
}
