#pragma once
#include <raylib.h>
#include <string>
#include <iostream>
#include "../scene_manager/scene_manager.hpp"
#include "./login_example.hpp"
#include "./register_example.hpp"
#include<cstdlib>
#include<cstring>

#define MAX_INPUT_CHAR_UP 10
#define MARGIN 20
#define ELEMENT_SPACING 40
#define INPUT_BOX_WIDTH 200
#define INPUT_BOX_HEIGHT 30
#define BUTTON_WIDTH 120
#define BUTTON_HEIGHT 45
#define DEFAULT_FONT_SIZE 20
#define DEFAULT_HEADER_FONT_SIZE 30


class RegistrationPage : public Scene {
public:  
 SceneManager* scenemanager;
 RegistrationPage(SceneManager* scenemanager){
    (this->scenemanager) = scenemanager;
     memset(username,0,sizeof(char)*MAX_INPUT_CHAR_UP);
     memset(password,0,sizeof(char)*MAX_INPUT_CHAR_UP);
     memset(rpassword,0,sizeof(char)*MAX_INPUT_CHAR_UP);
     usernameLength=0;
     passwordLength=0;
     rpasswordLength=0;
 }
 ~RegistrationPage(){
    delete username;
    delete password;
    delete rpassword;
 }
 
 void on_entry() override {
   
   inputFieldArray[0] = {
     .name="username",
     .posX=GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN * 3, 
     .posY=GetScreenHeight()/ 2 -ELEMENT_SPACING*2,
     .width=INPUT_BOX_WIDTH,
     .height=INPUT_BOX_HEIGHT,
     .active=true,
     .color=GRAY
   };

   inputFieldArray[1] = {
     .name="password",
     .posX=GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN * 3, 
     .posY=GetScreenHeight()/ 2 - ELEMENT_SPACING,
     .width=INPUT_BOX_WIDTH,
     .height=INPUT_BOX_HEIGHT,
     .active=false,
     .color=GRAY,
   };

   inputFieldArray[2] = {
     .name="repassword",
     .posX=GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN * 3, 
     .posY=GetScreenHeight()/ 2 ,
     .width=INPUT_BOX_WIDTH,
     .height=INPUT_BOX_HEIGHT,
     .active=false,
     .color=GRAY,
   };

   registerButton = { 
      .x=GetScreenWidth() / 2 - BUTTON_WIDTH,
      .y=GetScreenHeight() / 2 + ELEMENT_SPACING,
      .width=BUTTON_WIDTH,
      .height=BUTTON_HEIGHT 
    };



 }

void on_exit() override{
  return;
}

void on_event(){
  if(IsKeyPressed(KEY_ENTER)){
  scenemanager->switch_to("login");
  }

     int key = GetCharPressed();

      if (IsKeyPressed(KEY_BACKSPACE)) {
         if (inputFieldArray[0].active && usernameLength > 0) {
             username[--usernameLength] = '\0';
         }
         else if (inputFieldArray[1].active && passwordLength > 0) {
             password[--passwordLength] = '\0';
         }

          else if (inputFieldArray[2].active && rpasswordLength > 0) {
             rpassword[--rpasswordLength] = '\0';
         }
      }
     if(key >0 && key != KEY_SPACE){
         if(inputFieldArray[0].active && usernameLength < MAX_INPUT_CHAR_UP){
             username[usernameLength]= (char)key;
             username[usernameLength + 1] = '\0';
             usernameLength++;
         }
         else if (inputFieldArray[1].active && passwordLength < MAX_INPUT_CHAR_UP){
             password[passwordLength] = (char)key;
             password[passwordLength + 1] = '\0';
             passwordLength++;
         }

         else if (inputFieldArray[2].active && rpasswordLength < MAX_INPUT_CHAR_UP){
             rpassword[rpasswordLength] = (char)key;
             rpassword[rpasswordLength + 1] = '\0';
             rpasswordLength++;
         }
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

  ClearBackground(RAYWHITE);
  DrawText("User Registration Page",
            inputFieldArray[0].posX-MeasureText("Username:",DEFAULT_FONT_SIZE),
            GetScreenHeight()/2-MARGIN*8,
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

  drawButton(registerButton,
      "Register"
      );

      
  DrawText(
      username,
      GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN*3,
      GetScreenHeight()/ 2 - ELEMENT_SPACING*2,
      DEFAULT_FONT_SIZE,
      BLACK);


  for (int i = 0; i < passwordLength; i++) {
      DrawText(
          "*", 
          GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN*3 + i * 10,
          GetScreenHeight() / 2 - ELEMENT_SPACING,
          DEFAULT_FONT_SIZE,
          BLACK
          );
  
  }

  for (int i = 0; i < rpasswordLength; i++) {
      DrawText(
          "*", 
          GetScreenWidth() / 2 - INPUT_BOX_WIDTH / 2 - MARGIN*3 + i * 10,
          GetScreenHeight() / 2,
          DEFAULT_FONT_SIZE,
          BLACK
          );
  
  }



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

void drawButton(Rectangle recButton,string text="Button",Color color=LIGHTGRAY,int edgeRadius=1,int segments=6){
  //drawButton(Rectangle,ButtonText,ColorOfTheButton,edgeRadius,segments)

  DrawRectangleRounded(recButton, edgeRadius, segments , color);
  DrawText(
      text.c_str(),
      recButton.x +BUTTON_WIDTH/2 - MeasureText(text.c_str(),DEFAULT_FONT_SIZE)/2,
      recButton.y + BUTTON_HEIGHT/2-DEFAULT_FONT_SIZE/2,
      DEFAULT_FONT_SIZE,
      BLACK);
}
      private:

     char* username=static_cast<char*>(new char[MAX_INPUT_CHAR_UP]);
     char* password=static_cast<char*>(new char[MAX_INPUT_CHAR_UP]);
     char* rpassword=static_cast<char*>(new char[MAX_INPUT_CHAR_UP]);
     int usernameLength;
     int passwordLength;
     int rpasswordLength;
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
    Rectangle registerButton;
};
