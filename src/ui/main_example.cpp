#pragma once
#include "./register_example.hpp"
#include <string>
#include "./login_example.hpp"
//#include "./leaderboard.hpp"
#include "./gamemode_test.hpp"
int main(){
  SceneManager scenemanager;
  RegistrationPage registerpage(&scenemanager);
  LoginScene login(&scenemanager);
 //LeaderboardScene leaderboard(&scenemanager);
  CGamemode cgamemode;
  scenemanager.add("registerpage",&registerpage);
  scenemanager.add("login",&login);
  //scenemanager.add("leaderboard",&leaderboard);
  //scenemanager.add("gamemode",&gamemode);
  scenemanager.add("cgamemode",&cgamemode);

  InitWindow(1440, 720, "TypeOnMe");
  
  SetTargetFPS(200);
  scenemanager.switch_to("cgamemode");
  
  while(!WindowShouldClose()){
    BeginDrawing();
    scenemanager.update();
    scenemanager.poll_event();
  }
  scenemanager.quit();
  return 0;
}
