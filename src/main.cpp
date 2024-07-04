#include"main.hpp"

int count_for_closing_window_after_wpm = 0;

typedef enum {
    LOGIN,
    GAMEMODE,
} gameState;
  

gameState currentState = GAMEMODE;

int main(){


  
  if(start_instance_cgamemode()==1){
    return 0;
  }

}
