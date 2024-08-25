#pragma once
#include <raylib.h>
#include <string>

#define MARGIN 5

class Notification{
      public:
        void label(const std::string& notificationText,int notificationId,int timeDuration){
            this->notificationText = notificationText;
            this->notificationId = notificationId;
            this->timeDuration = timeDuration; 
            notificationRec = {MARGIN,MARGIN,MeasureText(notificationText.c_str(),20)+MARGIN*6,50};   
            firstCreation=true;
        }
        bool draw(){
            if(firstCreation){
            creationTime = GetTime(); 
            firstCreation=false;
            }
            currentTime = GetTime();
            if(currentTime-creationTime <=timeDuration){
            DrawRectangleRounded(notificationRec,50.0,1,Color{0,0,0,128});
            DrawText(notificationText.c_str(), notificationRec.x + MARGIN * 4, notificationRec.y + MARGIN * 3, 20, WHITE);
            }
            else{
              return false;
            }
            
              return true;
          }

        Rectangle notificationRec;
      private:
        double creationTime;
        int currentTime;
        std::string notificationText;
        int notificationId;
        int timeDuration;
        bool firstCreation;
        Sound errorSound;
};
