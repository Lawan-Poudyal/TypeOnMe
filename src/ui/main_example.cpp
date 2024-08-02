#pragma once
#include "./register_example.hpp"
#include <string>
#include "./login_example.hpp"
#include "./leaderboard.hpp"

int main(){
  SceneManager scenemanager;
  RegistrationPage registerpage(&scenemanager);
  LoginScene login(&scenemanager);
  LeaderboardScene leaderboard(&scenemanager);
 //CGamemode cgamemode(&scenemanager);
  scenemanager.add("registerpage",&registerpage);
  scenemanager.add("login",&login);
  scenemanager.add("leaderboard",&leaderboard);
  //scenemanager.add("cgamemode",&cgamemode);

  InitWindow(1440, 720, "TypeOnMe");
  
  SetTargetFPS(200);
  scenemanager.switch_to("leaderboard");
  
  while(!WindowShouldClose()){
    BeginDrawing();
    scenemanager.update();
    scenemanager.poll_event();
  }
  scenemanager.quit();
  return 0;
}
