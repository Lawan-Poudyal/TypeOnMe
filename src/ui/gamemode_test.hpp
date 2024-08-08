#include "raylib.h"
#include <vector>
#include <string>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <sstream>
#include<memory>
#include "./../scene_manager/scene_manager.hpp"
#include "../game_logic/accuracy.hpp"
#include "../globals.hpp"
#include "../db/database.hpp"

using namespace std;

#define MAX_INPUT_CHAR 500


static bool timer_initialized = false;
static double timer_start = 0.0;
int  init_width = 1440;
int  init_height = 760;
int CENTER_X = init_width / 2;
int CENTER_Y = init_height / 2;
int global_seed = time(NULL);
vector<string> dictionary = {"apple", "banana", "cat", "dog", "elephant", "forest", "giraffe", "honey", "ice", "jacket", "kangaroo", "lemon", "mountain", "notebook", "ocean", "pencil", "quartz", "river", "sand", "tiger", "umbrella", "violin", "whale", "xylophone", "yacht", "zebra", "ant", "balloon", "candle", "dolphin", "eagle", "fountain", "grape", "house", "igloo", "jungle", "kite", "lantern", "mirror", "nest", "owl", "peacock", "quilt", "rainbow", "sunflower", "turtle", "unicorn",  "vase", "windmill", "x-ray", "yarn"};
vector<string> sentences = {
    "Overcoming betrayal is a profound and challenging journey that requires resilience and self-compassion. It involves acknowledging the hurt and allowing oneself to grieve the loss of trust. Healing begins with introspection, understanding that the betrayal reflects more on the betrayer's character than on one's worth."
};


class Cursor {
public:

    Cursor( char* word, int letter_count, bool drawCursor, int c_height) {
        if (drawCursor && letter_count < MAX_INPUT_CHAR) {
            int wordWidth = MeasureText(word, 30);
            int cursorX = CENTER_X + wordWidth / 2;
            DrawLine(cursorX, CENTER_Y - c_height / 2,
                     cursorX, CENTER_Y + c_height / 2, RAYWHITE);
        }
    }
};

class SentenceGenerator {
private:
    vector<string> sentences;
    vector<string> unused_sentences;
    int seed;

public:
    SentenceGenerator(){}
    SentenceGenerator( vector<string>& sent, int s) : sentences(sent), seed(s) {
      std::cout << "SentenceGenerator constructor, sentences size: " << sentences.size() << std::endl;
    
      srand(seed);
        resetUnusedSentences();
    }

    void resetUnusedSentences(){
        unused_sentences = sentences;
        random_shuffle(unused_sentences.begin(), unused_sentences.end());
    }

    string getNextSentence() {
        if(unused_sentences.empty()){
            resetUnusedSentences();
        }
        string sentence = unused_sentences.back();
        unused_sentences.pop_back();
        
    std::cout << "Getting next sentence, unused_sentences size: " << unused_sentences.size() << std::endl;
        return sentence;   
    }
};

class WordGenerator {
private:
    vector<string> dictionary;
    vector<string> unused_words;
    int seed;

public:
    WordGenerator(){}
    WordGenerator( vector<string>& dict, int s) : dictionary(dict), seed(s) {
      
    std::cout << "WordGenerator constructor, dictionary size: " << dictionary.size() << std::endl;
      srand(seed);
        resetUnusedWords();
    }

    void resetUnusedWords(){
 
        unused_words = dictionary;
        random_shuffle(unused_words.begin(), unused_words.end());
    }

    string getNextWord() {
        if(unused_words.empty()){
            resetUnusedWords();
        }
        string word = unused_words.back();
        unused_words.pop_back();

    std::cout << "Getting next word, unused_words size: " << unused_words.size() << std::endl;
  
        return word;   
    }
};


class CGamemode : public Scene{
  private:
    Database db;
    int remaining_time;
    string prev_word;
    bool sentence_mode;
    bool animating;
    int init_width;
    int init_height;
    SentenceGenerator sentence_generator;
    double typing_start_time;
    double typing_end_time;
    bool typing_started;
    int total_characters_typed;
    WordGenerator word_generator;
    deque<string> word_queue;
    
    int button_width;
    int button_height;
    int spacing;
    int start_y;
    int letter_count;
    SceneManager* scenemanager;
    string current_sentence;

  
    
    vector<string> typedWords;
    vector<string> all_displayed_words;

    float animation_progress;
    float ANIMATION_DURATION; // Animation duration in seconds
    Session* session; 
    int test_duration; // Default duration
    int NUM_TIME_BUTTONS;
    char time_options[4][4];



    std::unique_ptr<char[]> word;

    float cursorContent;
    bool drawCursor;

    bool game_over;
    // Struct definitions
    typedef struct Button {
        Rectangle rect;
        Color color;
    } Button;
    Button time_buttons[4];
    Button button_0 ; //the button 
    Button button_1;  //the button
    Button addToLeaderboard;
public:


   CGamemode(SceneManager* scenemanager,Session* session) :

    button_width(100),
    button_height(40),
    spacing(20),
    start_y(100),
    animating(false),
    typing_start_time(0.0),
    typing_end_time(0.0),
        typing_started(false),
        total_characters_typed(0),
        animation_progress(1.0f),
        ANIMATION_DURATION(0.3f),
        test_duration(30),
        NUM_TIME_BUTTONS(4),
        game_over(false),
     init_width(1440),
     init_height(760),
     scenemanager(scenemanager),
     session(session),
     db("credentials.db")
     {
    
        memcpy(time_options, (char[4][4]){"60s", "45s", "30s", "15s"}, sizeof(time_options));
        sentence_mode = (false);
        current_sentence = ("");
        prev_word = ("");
        sentence_generator = SentenceGenerator(sentences, global_seed);
        word_generator = WordGenerator(dictionary, global_seed);

    float cursorContent;
    bool drawCursor;

    word = std::make_unique<char[]>(MAX_INPUT_CHAR + 1);
    word[0] = '\0';
    letter_count = 0;
    
    std::cout << "Sentences size: " << sentences.size() << std::endl;
    std::cout << "Dictionary size: " << dictionary.size() << std::endl;
    
    Button button_0 = {0}; //the button
    Button button_1 = {0}; //the button
    Button addToLeaderboard = {0};
    for (int i = 0; i < 3; ++i) {
        word_queue.push_back(word_generator.getNextWord());
      }
    } 

   void on_entry() override{



    init_button(&button_0, (Rectangle){0, 15, 200, 30}, RED);
    init_button(&button_1, (Rectangle){210, 15, 200, 30}, RED);
    init_button(&addToLeaderboard,(Rectangle){init_width/2-50, init_height/2+100,200+100,30},RED); 

    for (int i = 0; i < NUM_TIME_BUTTONS; i++) {
        Rectangle rect = {
            (float)(init_width - button_width - 20),
            (float)(start_y + i * (button_height + spacing)),
            (float)button_width,
            (float)button_height
    
        };

      cout << "INIT WIDTH: "<<init_width<<endl;
        cout << "X:" <<(init_width - button_width - 20) << endl
             << "Y: " <<(start_y + i * (button_height + spacing)) << endl
             << "WIDTH: "<<(float)button_width <<endl
            << "HEIGHT: " << (float)button_height<<endl;
        init_button(&time_buttons[i], rect, DARKGRAY);
    }
  
   }
//Button Initialization


    float calculate_wpm() {
        if (!typing_started) return 0.0f;
        double end_time = typing_end_time > 0 ? typing_end_time : GetTime();
        float elapsed_time = (end_time - typing_start_time) / 60.0f; // convert seconds to minutes
        if (elapsed_time < 0.0001f) return 0.0f; // Avoid division by zero
        return (total_characters_typed / 5.0f) / elapsed_time; // Assuming 5 characters per word
    }


// Drawing functions:
    int DrawTime() {
        int seconds = test_duration;

        if (typing_started && !timer_initialized) {
            timer_start = GetTime();
            timer_initialized = true;
        }

        if (timer_initialized) {
            double elapsed = GetTime() - timer_start;
            seconds = test_duration - static_cast<int>(elapsed);
            if (seconds < 0) seconds = 0;
        }

        DrawText(TextFormat("Time: %i", seconds), init_width-200, 40, 20, WHITE);
        return seconds;
    }


    void DrawTextInBounds( string& prev_word, const string& current_word, const string& next_word, int start_x, int start_y, int max_width, int max_height) {
        Rectangle rect = {float(start_x), float(start_y), float(max_width), float(max_height)};

        //Rounded attributes
        float roundness = 0.3f;
        int segments = 10;
            
        DrawRectangleRounded(rect, roundness, segments, BLUE);

        //Restricts drawing operations to within the specified rectangle
        BeginScissorMode(start_x, start_y, max_width, max_height);
        
        int base_font_size = 32;
        int word_height = 40;
        int padding = 20;

        // Calculate positions
        int left_x = start_x + padding;
        int center_x = start_x + (max_width) / 2;
        int right_x = start_x + max_width - padding;
        int y = start_y + (max_height - word_height) / 2;

        // Calculate animated positions (right to left)
        float anim_left_x = left_x + (center_x - left_x) * (1 - animation_progress);
        float anim_center_x = center_x + (right_x - center_x) * (1 - animation_progress);
        float anim_right_x = right_x + (max_width) * (1 - animation_progress);

        // Calculate font size for the current word
        int current_word_font_size = base_font_size + int(10 * animation_progress);

        // Draw previous word (left)
        DrawText(prev_word.c_str(), anim_left_x, y, 30, LIGHTGRAY);

        // Draw current word (center)
        int current_word_width = MeasureText(current_word.c_str(), current_word_font_size);
        DrawText(current_word.c_str(), anim_center_x - current_word_width / 2, y - (current_word_font_size - base_font_size) / 2, current_word_font_size, WHITE);

        // Draw next word (right)
        int next_word_width = MeasureText(next_word.c_str(), 30);
        DrawText(next_word.c_str(), anim_right_x - next_word_width, y, 30, LIGHTGRAY);

        EndScissorMode();

    }

    void DrawSentenceInBounds( string& sentence, int start_x, int start_y, int max_width, int max_height) {
        Rectangle rect = {float(start_x), float(start_y), float(max_width), float(max_height)};

        float roundness = 0.3f;
        int segments = 10;
            
        DrawRectangleRounded(rect, roundness, segments, BLUE);

        BeginScissorMode(start_x, start_y, max_width, max_height);
        
        int font_size = 20;
        int padding = 20;
        int line_spacing = 5;

        int x = start_x + padding;
        int y = start_y + padding;

        vector<string> words;
        stringstream ss(sentence);
        string word;
        while (ss >> word) {
            words.push_back(word);
        }

        string line;
        for ( auto& word : words) {
            string test_line = line + (line.empty() ? "" : " ") + word;
            if (MeasureText(test_line.c_str(), font_size) <= max_width - 2 * padding) {
                line = test_line;
            } else {
                DrawText(line.c_str(), x, y, font_size, WHITE);
                y += font_size + line_spacing;
                line = word;
            }
        }
        if (!line.empty()) {
            DrawText(line.c_str(), x, y, font_size, WHITE);
        }

        EndScissorMode();

    }

    void DrawTypedWord( char* word, const char* correct_word, int x, int y, int fontSize) {
        int cursor_x = x;
        size_t word_len = strlen(word);

        size_t correct_len = strlen(correct_word);

        for (size_t i = 0; i < word_len; i++) {
            Color color = (i < correct_len && word[i] == correct_word[i]) ? RAYWHITE : RED;
            char temp[2] = {word[i], '\0'};
            DrawText(temp, cursor_x, y, fontSize, color);
            cursor_x += MeasureText(temp, fontSize) + 2;
        }

    }

    void on_event() override {

        int key = GetCharPressed();

        if (letter_count < MAX_INPUT_CHAR) {

            if ((key >= 32 && key <= 125) || key == ' ') {
                word[letter_count] = (char)key;
                letter_count++;
                total_characters_typed++;
                } 
            }
                if (!sentence_mode && letter_count > 0 && (key == 32 || word[letter_count - 1] == ' ')) {
                    if (word[letter_count - 1] == ' ') {
                        word[letter_count - 1] = '\0';  // Remove the space
                    } else {
                        word[letter_count] = '\0';  // Null-terminate the word
                    }
                      typedWords.push_back(std::string(word.get()));
                        
                        all_displayed_words.push_back(word_queue.front());
                        prev_word = word_queue.front();
                        word_queue.pop_front();
                        word_queue.push_back(word_generator.getNextWord());
                        
                        memset(word.get(), 0, sizeof(char) * (MAX_INPUT_CHAR + 1));
                        word[0] = '\0';
                        letter_count = 0;

                        animating = true;
                        animation_progress = 0.0f;
                }


        if ((IsKeyPressed(KEY_BACKSPACE) && letter_count > 0)) {
            total_characters_typed--;
            letter_count--;
            word[letter_count] = '\0';
        } 
        if(game_over && IsKeyPressed(KEY_ENTER)){
              on_exit();
        }
        if(game_over && IsButtonClicked(addToLeaderboard.rect)){
          std::pair <string,int> pairBuf(session->getUsername(),calculate_wpm());
          std::cout << "USERNAME: " << session->getUsername() << "WPM: "<< calculate_wpm() << endl;
          db.insertLeaderboard(pairBuf);
        }
        
        if(game_over && IsKeyPressed(KEY_TAB)){
          scenemanager->switch_to("leaderboard");
        }
    }


    bool IsButtonClicked(Rectangle button) {
        return (CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
    }
    
    void on_update() override{
       
    int remaining_time = DrawTime();
      ClearBackground(BLACK);

        // Draw the text in the box
        int box_width = 740;
        int box_height = 150;
    
        DrawText(session->getUsername().c_str(),init_width/2,20, 30, WHITE);

        if(!game_over){
        // Handle animation
        if (animating && !sentence_mode) {
            animation_progress += GetFrameTime() / ANIMATION_DURATION;
            if (animation_progress >= 1.0f) {
                animation_progress = 1.0f;
                animating = false;
            }
        }

        cursorContent += GetFrameTime();
        if (cursorContent >= 0.5f) {
            cursorContent = 0.0f;
            drawCursor = !drawCursor;
        }

        if (remaining_time <= 0) {
            game_over = true;
            typing_end_time = GetTime();
        }


        if (!typing_started) {
            // Handle time button clicks
            for (int i = 0; i < NUM_TIME_BUTTONS; i++) {
                if (is_mouse_over_button(time_buttons[i])) {
                    time_buttons[i].color = GRAY;
                    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                        switch (i) {
                            case 0: test_duration = 60; break;
                            case 1: test_duration = 45; break;
                            case 2: test_duration = 30; break;
                            case 3: test_duration = 15;break;
                        }
                    }
                } else {
                    time_buttons[i].color = DARKGRAY;
                }
            }
        }

        // Handle mode selection buttons
        if (is_mouse_over_button(button_0)) {
            button_0.color = GRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !typing_started) {
                sentence_mode = true;
                current_sentence = sentence_generator.getNextSentence();
                memset(word.get(), 0, sizeof(char) * (MAX_INPUT_CHAR + 1));
                word[0] = '\0';
                letter_count = 0;
                total_characters_typed = 0;
                typedWords.clear();
                all_displayed_words.clear();
            }
        } else {
            button_0.color = RED;
        }

        if (is_mouse_over_button(button_1)) {
            button_1.color = GRAY;
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !typing_started) {
                sentence_mode = false;
                word_queue.clear();
                for (int i = 0; i < 3; ++i) {
                    word_queue.push_back(word_generator.getNextWord());
                }
                prev_word = "";
                memset(word.get(), 0, sizeof(char) * (MAX_INPUT_CHAR + 1));
                word[0] = '\0';
                letter_count = 0;
                total_characters_typed = 0;
                typedWords.clear();
                all_displayed_words.clear();
            }
        } else {
            button_1.color = RED;
        }

        if (!typing_started && letter_count > 0) {
            typing_started = true;
            typing_start_time = GetTime();
        }


        if (sentence_mode) {
            DrawSentenceInBounds(current_sentence, 410, 65, box_width, box_height); 
            // Draw the typed word with wrapping
            int fontSize = 20;
            int textStartY = CENTER_Y + box_height / 2 + 20; // Position below the box
            int maxTypingWidth = box_width - 40; // Leave some padding
            int textStartX = 410; // Start from the left of the box with padding
            
            int currentLineWidth = 0;
            int currentLineY = textStartY;
            string currentLine;
            
            for (int i = 0; i < letter_count; i++) {
                char currentChar[2] = {word[i], '\0'};
                int charWidth = MeasureText(currentChar, fontSize);
                
                if (currentLineWidth + charWidth > maxTypingWidth) {
                    // Draw the current line and move to the next
                    DrawText(currentLine.c_str(), textStartX, currentLineY, fontSize, WHITE);
                    currentLineY += fontSize + 5; // Move to next line
                    currentLine.clear();
                    currentLineWidth = 0;
                }
                
                currentLine += word[i];
                currentLineWidth += charWidth;
            }
            
            // Draw the last line
            DrawText(currentLine.c_str(), textStartX, currentLineY, fontSize, WHITE);

            // Calculate cursor position
            int cursorX = textStartX + MeasureText(currentLine.c_str(), fontSize);
            int cursorY = currentLineY;

            // Draw the cursor
            if (drawCursor) {
                int cursorHeight = fontSize + 10;
                DrawLine(cursorX, cursorY - cursorHeight / 2, 
                        cursorX, cursorY + cursorHeight / 2, RAYWHITE);
            }
        }
    if (!sentence_mode) {
        DrawTextInBounds(prev_word, word_queue[0], word_queue[1], 410, 65, box_width, box_height);

        // Draw the typed word
        int wordWidth = MeasureText(word.get(), 30);
        int textStartX = CENTER_X - wordWidth / 2;
        DrawTypedWord(word.get(), word_queue[0].c_str(), textStartX, CENTER_Y, 30);
        // Draw the cursor
        if (drawCursor) {
            DrawLine(textStartX + wordWidth, CENTER_Y - 25, 
                     textStartX + wordWidth, CENTER_Y + 25, RAYWHITE);
        
        }
    }

        // Draw mode selection buttons
        DrawRectangleRec(button_0.rect, button_0.color);
        DrawText("Sentence", button_0.rect.x + button_0.rect.width/2 - MeasureText("Sentence", 10) - 10, button_0.rect.y + button_0.rect.height/2 - 20 / 2, 20, WHITE);
  
        DrawRectangleRec(button_1.rect, button_1.color);
        DrawText("Words", button_1.rect.x + button_1.rect.width/2 - MeasureText("Words", 10) - 10, button_1.rect.y + button_1.rect.height/2 - 20 / 2, 20, WHITE);


        // Draw time buttons
        if (!typing_started) {
            for (int i = 0; i < NUM_TIME_BUTTONS; i++) {

                DrawRectangleRec(time_buttons[i].rect, time_buttons[i].color);
                DrawText(time_options[i], 
                         time_buttons[i].rect.x + 10, 
                         time_buttons[i].rect.y + 10, 
                         20, WHITE);

            }
        }
        }
     else { 
        // Game over state
        ClearBackground(BLACK);
        float wpm = calculate_wpm();
        float acc = accuracy(typedWords, all_displayed_words);
        DrawText(TextFormat("Final WPM: %.2f", wpm), init_width / 2 - 100, init_height / 2, 30, RAYWHITE);
        DrawText(TextFormat("Accuracy: %.2f%%", acc), init_width / 2 - 100, init_height / 2 + 50, 30, RAYWHITE);
        DrawRectangleRec(addToLeaderboard.rect,addToLeaderboard.color);
        DrawText("Add To Leaderboard", addToLeaderboard.rect.x + addToLeaderboard.rect.width/2 - MeasureText("Add To Leaderboard", 10) - 10, addToLeaderboard.rect.y + addToLeaderboard.rect.height/2 - 20 / 2, 20, WHITE);

     }

        float current_wpm = calculate_wpm();
        DrawText(TextFormat("Current WPM: %.2f", current_wpm), 10, init_height - 40, 20, WHITE);
        EndDrawing(); 

    }

    void on_exit() override{
      game_over=false;  
      timer_initialized=false;
      timer_start=0;
      remaining_time=DrawTime();
      word_queue.clear();
      typing_started=false;
      for (int i = 0; i < 3; ++i) {
          word_queue.push_back(word_generator.getNextWord());
      }
      prev_word = "";
      memset(word.get(), 0, sizeof(char) * (MAX_INPUT_CHAR + 1));
      word[0] = '\0';
      letter_count = 0;
      total_characters_typed = 0;
      typedWords.clear();
      all_displayed_words.clear();
    
    }

    bool is_mouse_over_button(Button button){
        return CheckCollisionPointRec(GetMousePosition(), button.rect);
    }

    void init_button(Button *button, Rectangle rect, Color color){
        button->rect = rect;
        button->color = color;
    }

};
