#pragma once
#include <raylib.h>
#include <string>
#include <iostream>
#include "../scene_manager/scene_manager.hpp"
#include "./login_example.hpp"
#include "./register_example.hpp"
#define MAX_INPUT_CHAR 16 
#define DEFAULT_FONT_SIZE 20
#define DEFAULT_HEADER_FONT_SIZE 30
class RegistrationPage : public Scene {
public:  
 SceneManager* scenemanager;
 RegistrationPage(SceneManager* scenemanager){
    (this->scenemanager) = scenemanager;
  }
 char* username;
 char* password;
 int init_width;
 int init_height;
 int highlightButtonNum=1;
 typedef struct textfields{
    string name;
    int posX;
    int posY;
    int width;
    int height;
    bool active;
    Color color;
 }inputField;
inputField inputFieldArray[3];
 
 void on_entry() override {
   init_width=GetScreenWidth();
   init_height=GetScreenHeight();

   inputFieldArray[0] = {
     .name="username",
     .posX=init_width/ 2 - 20, 
     .posY=init_height/ 2 - 130,
     .width=200,
     .height=30,
     .active=true,
     .color=GRAY
   };

   inputFieldArray[1] = {
     .name="password",
     .posX=init_width/ 2 - 20, 
     .posY=init_height/ 2 - 90,
     .width=200,
     .height=30,
     .active=false,
     .color=GRAY,
   };

   inputFieldArray[2] = {
     .name="repassword",
     .posX=init_width/ 2 - 20, 
     .posY=init_height/ 2 - 50,
     .width=200,
     .height=30,
     .active=false,
     .color=GRAY,
   };

 }

    void on_exit() override{
      return ;
    }

    void on_event(){
       if(IsKeyPressed(KEY_ENTER)){
          scenemanager->switch_to("login");
          return;
       }
       int i;

      if(IsKeyPressed(KEY_TAB)){
        
      for(i= 0; i < sizeof(inputFieldArray)-1 ;i++){
        if(inputFieldArray[i].active && i<=3){
          
          if((i+1)>2){
              inputFieldArray[i].active=!inputFieldArray[i].active;
              inputFieldArray[(0)].active=!inputFieldArray[0].active;
              break;
          }
          else{
              inputFieldArray[i].active=!inputFieldArray[i].active;
              inputFieldArray[(i+1)].active=!inputFieldArray[i+1].active;
              break;  
        }
        }
          else{
          }
          }

        
        }
      }
    

    void on_update() override{

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("User Registration Page",
                      inputFieldArray[0].posX-MeasureText("Username:",DEFAULT_FONT_SIZE),
                      init_height/2-200,
                      DEFAULT_HEADER_FONT_SIZE,
                      BLACK);
            DrawText("Username:",
                      inputFieldArray[0].posX-MeasureText("Username:",DEFAULT_FONT_SIZE),
                      inputFieldArray[0].posY,
                      DEFAULT_FONT_SIZE,BLACK);
            DrawText("Password:",
                      inputFieldArray[1].posX-MeasureText("Password:",DEFAULT_FONT_SIZE),
                      inputFieldArray[1].posY,
                      DEFAULT_FONT_SIZE,BLACK);

            DrawText("Retype Password:",
                      inputFieldArray[2].posX-MeasureText("Retype Password:",DEFAULT_FONT_SIZE),
                      inputFieldArray[2].posY,
                      DEFAULT_FONT_SIZE,BLACK);
            drawInputBox(     
                inputFieldArray[0].posX, 
                inputFieldArray[0].posY,
                inputFieldArray[0].width,
                inputFieldArray[0].height,
                (inputFieldArray[0].active?RED:GRAY)
                );

            drawInputBox(     
                inputFieldArray[1].posX, 
                inputFieldArray[1].posY,
                inputFieldArray[1].width,
                inputFieldArray[1].height,
                (inputFieldArray[1].active?RED:GRAY)
                );
            drawInputBox(     
                inputFieldArray[2].posX, 
                inputFieldArray[2].posY,
                inputFieldArray[2].width,
                inputFieldArray[2].height,
                (inputFieldArray[2].active?RED:GRAY)
                );

            if(username){

            }

            if(password){

            }

            if(password){

            }

            EndDrawing();

            return;
    }
    void drawInputBox(int posX,int posY,int width,int height,Color color=RED){
            DrawRectangleLines(posX,posY,width,height,color);
    }
      private:
};
