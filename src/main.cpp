#include "dependencies.h"
#include"wpm.hpp"
#include"accuracy.hpp"

//Declarations and definition of global variables
using namespace std;
vector<string> RandomWord(vector<string>,int seed);
const int init_width  = 1440;
const int init_height = 768;
void clearWindow();
int global_seed = time(NULL);
int gtotal_letter_count=0;
int in_positionY=init_height/2-10;
int in_positionX =init_width/2;
vector<string> typedWords;
vector<string> ext_random_words;
//Declarations ends here


//Class definiitions
class Cursor{
  
  public:
    int pos1_x;
    int pos2_x;
    int pos1_y;
    int pos2_y;
   
    Cursor(char* word,int letter_count,bool drawCursor,int c_height){
      if(drawCursor && letter_count < MAX_INPUT_CHAR){
          DrawLine(MeasureText(word,30)+in_positionX+10,in_positionY - c_height/2,in_positionX+MeasureText(word,30)+10,in_positionY+c_height/2,RAYWHITE);
// Auto positions the cursor/carat to the by displacing it by a hardco
      }
   }

}; 

class WordGenerator{

    public:
    vector<string> RandomWord(vector<string>dictionary,int seed,int n){
    
    srand(seed); //srand supplies the seed for rand() and call of rand() followed by srand corresponds to the seeded random_number being generated.
    vector<string> return_list;
  
    for(int i=0;i<n;i++){
    return_list.push_back(dictionary[rand()%10]);
    }

  return return_list;   
  }

};
//Class definitions ends here



int main(void){  
  

  int spaces=0;
  float wpm;
  int count_for_closing_window_after_wpm=0;
  char* word = (char *) malloc( sizeof(char)*MAX_INPUT_CHAR + 1); //Had to use memory allocation for updating the current buffer of the word inputted. 
  word[MAX_INPUT_CHAR+1] = '\0';
  char* gray_word = (char *) malloc(sizeof(char)*MAX_INPUT_CHAR +1 );
  int letter_count = 0;
  
  float cursorContent = 0.0f;
  bool drawCursor = true;


  bool truth_value = true;
   time_t start_time;
    

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
  "hello",
  "hey",
  "hello",
  "rather",
  "punctual",
  "philosophical",
  "romantic",
  "exquisite",
  "random",
  "slash",
  "govern",
  "mesh",
  "jeopardy",
  "utopia",
  "rant"
  };


  while(!WindowShouldClose())
    {
     
      if(gtotal_letter_count==1){

        if(truth_value){
        start_time = start_timer();
        truth_value = !truth_value;
        }
      }
if(spaces==4){     
  
        count_for_closing_window_after_wpm++;
        DrawText(to_string(calculate_wpm(start_time)).c_str(),init_width/2,init_height/2 + 100,30,RAYWHITE);  //c_str() method is used for string objects to convert into c-type strings, 
        DrawText(to_string(accuracy(typedWords,ext_random_words)).c_str(),init_width/2,init_height/2+150,30,RAYWHITE);
}
    if((IsKeyPressed(KEY_BACKSPACE) && letter_count > 0)){
        if(word[letter_count] == ' '){
          spaces--;
        }
        gtotal_letter_count--;
        letter_count--;
        word[letter_count] = '\0';
      }

      else if(letter_count < MAX_INPUT_CHAR){
        int key = GetCharPressed();
      
      if((key >= 32 && key<= 125) || key== ' ' ){

        word[letter_count] = (char) key; //type caster to a character as key is a character pointer returned by GetCharPressed
         
        if(key==' ' ||word[letter_count] == ' '){
          spaces++;
          word[letter_count] = '\0';
          typedWords.push_back(word);
          memset(gray_word,0,sizeof(char)*MAX_INPUT_CHAR +1 ); 
          memset(word, 0, sizeof(char) * MAX_INPUT_CHAR + 1);
          letter_count=0; 
        }
         else{
          cout << word <<endl;
          letter_count++;
          gtotal_letter_count++;
          in_positionX-=10;
        }
      
    }

      }

        cursorContent += GetFrameTime();
        if(cursorContent>=0.5f){
          cursorContent=0.0f;
          drawCursor = !drawCursor;
        }
         

      
      WordGenerator random_word_gen; //random_word generator,which is an instance of Word generator

      int word_width=0;
      vector<string> random_words = random_word_gen.RandomWord(dictionary,global_seed,4);
      ext_random_words = random_words;
      for(string random_word : random_words ){ 

        DrawText(random_word.c_str(),2.5*word_width+10,30,30,RAYWHITE);
        word_width+=MeasureText(random_word.c_str(),50);
      
      }

        gray_word = (char *)random_words[spaces].c_str(); 
        DrawText(gray_word,in_positionX,in_positionY,30,DARKGRAY);
        //Random Text Being Rendered


      DrawText(word,in_positionX,in_positionY,30,RAYWHITE);
      //Blinking Cursor Next to Text.
      Cursor cursor_1(word,letter_count,drawCursor,50); 

  ClearBackground(BLACK);
      EndDrawing();

     if(count_for_closing_window_after_wpm){
       sleep(2); 
       break;
     } 
     //To-be worked on with OOP
    }  
  free(gray_word);
  free(word);
  CloseWindow();
  return 0;
}
