#include<raylib.h>
#include<iostream>
#include<string>
#include<vector>
#include<ctime>
#include<unistd.h>
#include<numeric>

#define MAX_INPUT_CHAR 500

using namespace std;
vector<string> RandomWord(vector<string>,int seed);

class Cursor{
  
  public:
    int pos1_x;
    int pos2_x;
    int pos1_y;
    int pos2_y;
   
    Cursor(char* name,int init_height_name,int letter_count,bool drawCursor){
      if(drawCursor && letter_count < MAX_INPUT_CHAR){
          DrawLine(MeasureText(name,30)+35,init_height_name/2 - 25,MeasureText(name,30)+35,init_height_name/2+25,BLACK);
      }
   }

}; 

class WordGenerator{

    public:
    vector<string> RandomWord(vector<string>dictionary,int seed,int n){

  srand(seed);
  vector<string> return_list;
  
  for(int i=0;i<n;i++){
    return_list.push_back(dictionary[rand()%10]);
  }
  return return_list;   
  }

};


int main(void){  
  
  const int init_width  = 1440;
  const int init_height = 768;

  char name[MAX_INPUT_CHAR + 1];
  name[MAX_INPUT_CHAR+1] = '\0';
  int letter_count = 0;
  float cursorContent = 0.0f;
  bool drawCursor = true;

  int spaces =0;
  float wpm;
  int count_for_closing_window_after_wpm=0;

  //initializers the raylib window and sets the targetfps to 200
  InitWindow(init_width,init_height,"TypeOnMe");
  SetTargetFPS(200);
  
  //a list of words to use {not the datatype}
  vector<string> dictionary = {
  "very",
  "cool",
  "looking",
  "guy",
  "is",
  "democrat",
  "nation",
  "signify",
  "netlify",
  "hey",
  "hello",
  "rather",
  "punctual",
  "philosophical",
  "romantic",
  "exquisite"
  };

  vector<int> wpm_list_vector;  

  int start_time;
  while(!WindowShouldClose())
    {
      
if(letter_count==1){
  start_time = GetTime();
} //Only starts the timer when the first character is pressed.


if(spaces==5){     

      //average nikalna sakxas,sab wpm ko sum garera,store all the wpms in a vector
      //and push_back to push to the very vector and finally final wpm vanera dekhauna sakiyo,damnn
        const int end_time = GetTime();
        wpm = (float)10/(end_time-start_time) * 60 ;    
        wpm_list_vector.push_back(wpm);
        
      int avg_wpm = accumulate(wpm_list_vector.begin(),wpm_list_vector.end(),0) / wpm_list_vector.size(); 
      DrawText(to_string(avg_wpm).c_str(),30,init_height/2 + 100,30,BLACK);  //c_str() method is used for string objects to convert into c-type strings,
      count_for_closing_window_after_wpm++;
  }
      
      if((IsKeyPressed(KEY_BACKSPACE) && letter_count > 0)){
        if(name[letter_count] == ' '){
          spaces--;
        }
        letter_count--;
        name[letter_count] = '\0';
      }

      else if(letter_count < MAX_INPUT_CHAR){
        int key = GetCharPressed();
      
      if((key >= 32 && key<= 125) || key== ' ' ){
         name[letter_count] = (char) key; //type caster to a character as key is a character pointer returned by GetCharPressed
        
         if(name[letter_count] == ' '){
          spaces++;
        }
          std::cout << name <<std::endl;
          letter_count++;
      }

      }

        cursorContent += GetFrameTime();
        if(cursorContent>=0.5f){
          cursorContent=0.0f;
          drawCursor = !drawCursor;
        }
         

        //To-be replenished with OOP

      BeginDrawing();
      
      ClearBackground(RAYWHITE);
      DrawText(name,30,init_height/2-10,30,BLACK);
 
      //Blinking Cursor Next to Text.
      Cursor cursor_1(name,init_height,letter_count,drawCursor); 

  

      WordGenerator random_word_gen;
      int word_width=0;
      vector<string> random_words = random_word_gen.RandomWord(dictionary,3,5);
      for(string random_word : random_words ){ 
        DrawText(random_word.c_str(),2.5*word_width+50,30,30,BLACK);
        word_width+=MeasureText(random_word.c_str(),20);
      
      }
        //Random Text Being Rendered
      
      EndDrawing();

     if(count_for_closing_window_after_wpm){
       sleep(2); 
       break;
     } 
     //To-be worked on with OOP
    }  
  
  CloseWindow();
  return 0;
}

