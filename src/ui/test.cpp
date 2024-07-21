#pragma once
#include "./register.hpp"
#include <string>
#include "./_login.hpp"
int init_width = GetScreenWidth()/2;
int init_height = GetScreenHeight()/2;

int main(){
  SceneManager scenemanager;
  RegistrationPage registration;
  std::string registerText= "register";
  scenemanager.add(registerText,&registration);
  InitWindow(init_width*2 , init_height*2, "TypeOnMe");
  SetTargetFPS(200);

  scenemanager.switch_to(registerText); 
  while(!WindowShouldClose()){ 
      
    scenemanager.update();
    }

  return 0;
}
