#pragma once
#include "./register_example.hpp"
#include <string>
#include "./login_example.hpp"
#include "./leaderboard.hpp"
#include "./gamemode_test.hpp"
#include "./../globals.hpp"
int main(){
  InitAudioDevice();
  Session session; 
  SceneManager scenemanager;
  RegistrationPage registerpage(&scenemanager,&session);
  LoginScene login(&scenemanager,&session);
  LeaderboardScene leaderboard(&scenemanager,&session);
  CGamemode cgamemode(&scenemanager,&session);
  scenemanager.add("registerpage",&registerpage);
  scenemanager.add("login",&login);
  scenemanager.add("leaderboard",&leaderboard);
  //scenemanager.add("gamemode",&gamemode);
  scenemanager.add("cgamemode",&cgamemode);

  InitWindow(1440, 768, "TypeOnMe");
  
  SetTargetFPS(200);
  session.setSessionScene("login");
  scenemanager.switch_to("login");
  
  while(!WindowShouldClose()){ 
    BeginDrawing();
    scenemanager.update();
    scenemanager.poll_event();
  }
  scenemanager.quit();
  return 0;
}
