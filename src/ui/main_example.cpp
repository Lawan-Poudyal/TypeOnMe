#pragma once
#include "./register_example.hpp"
#include <string>
#include "./login_example.hpp"
int init_width = 1440;
int init_height = 1080;

int main(){
  SceneManager scenemanager;
  RegistrationPage registerpage(&scenemanager);
  LoginScene login(&scenemanager); 
  scenemanager.add("registerpage",&registerpage);
 scenemanager.add("login",&login);
 
  InitWindow(init_width/2, init_height/2, "TypeOnMe");
  
  SetTargetFPS(200);
  scenemanager.switch_to("registerpage");
  
  while(!WindowShouldClose()){ 
    scenemanager.update();
    scenemanager.poll_event();
  }

  return 0;
}
