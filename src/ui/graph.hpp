#pragma once
#include <raylib.h>
#include <string>
#include <iostream>
#include "../scene_manager/scene_manager.hpp"
#include "../db/database.hpp"
#include<cstdlib>
#include<cstring>
#include <vector>
using namespace std;

class Graph{
  public:
  void Init( vector<tuple<int,int>>pointPosition , Rectangle boxConfiguration,int maxTime){
    this->pointPosition = pointPosition;
    this->boxConfiguration = boxConfiguration;
  }

  void Draw(){

    //DrawRectangle(screenWidth/4*2 - 60, 100, 120, 60, RED);
    //void DrawCircle(int centerX, int centerY, float radius, Color color);                              // Draw a color-filled circle
    DrawRectangle(boxConfiguration.x,boxConfiguration.y,boxConfiguration.width,boxConfiguration.height,GRAY);
    for(tuple<int,int> pointBuf : pointPosition){
      DrawCircle(boxConfiguration.x + static_cast<float>(get<0>(pointBuf)/static_cast<float>(maxTime)) * boxConfiguration.width,
          boxConfiguration.y + boxConfiguration.height - (static_cast<float>(get<1>(pointBuf)/101.0f) * boxConfiguration.height),
          4,
          BLUE
          );                              // Draw a color-filled circle
    }
  } 
  void Update(){

  }

  private:
  vector<tuple<int,int>>pointPosition;
  Rectangle boxConfiguration;
  int maxTime;

};
