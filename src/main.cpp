#include "raylib.h"
#include <vector>
#include <string>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

#define MAX_INPUT_CHAR 500

// Declarations and definition of global variables
using namespace std;
const int init_width = 1500;
const int init_height = 768;
const int CENTER_X = init_width / 2;
const int CENTER_Y = init_height / 2;
int global_seed = time(NULL);

double typing_start_time = 0.0;
double typing_end_time = 0.0;
bool typing_started = false;
int total_characters_typed = 0;

vector<string> typedWords;
vector<string> all_displayed_words;

float animation_progress = 1.0f;
const float ANIMATION_DURATION = 0.3f; // Animation duration in seconds

int test_duration = 30; // Default duration
const int NUM_TIME_BUTTONS = 3;
const char* time_options[] = {"60s", "45s", "30s"};

bool game_over = false;

// Struct definitions
typedef struct Button {
    Rectangle rect;
    Color color;
} Button;

Button button_0 = {0}; //the button
Button button_1 = {0}; //the button
Button time_buttons[NUM_TIME_BUTTONS];

// Function prototypes
float calculate_wpm();
float accuracy(const vector<string>& typedWords, const vector<string>& all_displayed_words);
void DrawTextInBounds(const string& prev_word, const string& current_word, const string& next_word, int start_x, int start_y, int max_width, int max_height);
void init_time_buttons();

// Class definitions
class Cursor {
public:
    Cursor(const char* word, int letter_count, bool drawCursor, int c_height) {
        if (drawCursor && letter_count < MAX_INPUT_CHAR) {
            int wordWidth = MeasureText(word, 30);
            int cursorX = CENTER_X + wordWidth / 2;
            DrawLine(cursorX, CENTER_Y - c_height / 2,
                     cursorX, CENTER_Y + c_height / 2, RAYWHITE);
        }
    }
};

class WordGenerator {
private:
    vector<string> dictionary;
    vector<string> unused_words;
    int seed;

public:
    WordGenerator(const vector<string>& dict, int s) : dictionary(dict), seed(s) {
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
        return word;   
    }
};

void init_button(Button *button, Rectangle rect, Color color){
    button->rect = rect;
    button->color = color;
}

bool is_mouse_over_button(Button button){
    return CheckCollisionPointRec(GetMousePosition(), button.rect);
}

void init_time_buttons() {
    int button_width = 100;
    int button_height = 40;
    int spacing = 20;
    int start_y = 100;

    for (int i = 0; i < NUM_TIME_BUTTONS; i++) {
        Rectangle rect = {
            (float)(init_width - button_width - 20),
            (float)(start_y + i * (button_height + spacing)),
            (float)button_width,
            (float)button_height
        };
        init_button(&time_buttons[i], rect, DARKGRAY);
    }
}

int DrawTime() {
    static bool timer_initialized = false;
    static double timer_start = 0.0;
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

float calculate_wpm() {
    if (!typing_started) return 0.0f;
    double end_time = typing_end_time > 0 ? typing_end_time : GetTime();
    float elapsed_time = (end_time - typing_start_time) / 60.0f; // convert seconds to minutes
    if (elapsed_time < 0.0001f) return 0.0f; // Avoid division by zero
    return (total_characters_typed / 5.0f) / elapsed_time; // Assuming 5 characters per word
}

float accuracy(const vector<string>& typedWords, const vector<string>& all_displayed_words) {
    int correct_words = 0;
    for (size_t i = 0; i < typedWords.size() && i < all_displayed_words.size(); ++i) {
        if (typedWords[i] == all_displayed_words[i]) {
            correct_words++;
        }
    }
    return (float)correct_words / all_displayed_words.size() * 100.0f; // percentage accuracy
}

void DrawTextInBounds(const string& prev_word, const string& current_word, const string& next_word, int start_x, int start_y, int max_width, int max_height) {
    Rectangle rect = {float(start_x), float(start_y), float(max_width), float(max_height)};

    //Rounded attributes
    float roundness = 0.3f;
    int segments = 10;
        
    DrawRectangleRounded(rect, roundness, segments, BLUE);

    //Restricts drawing operations to within the specified rectangle
    BeginScissorMode(start_x, start_y, max_width, max_height);

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

    // Draw previous word (left)
    DrawText(prev_word.c_str(), anim_left_x, y, 30, LIGHTGRAY);

    // Draw current word (center)
    int current_word_width = MeasureText(current_word.c_str(), 30);
    DrawText(current_word.c_str(), anim_center_x - current_word_width / 2, y, 30, WHITE);

    // Draw next word (right)
    int next_word_width = MeasureText(next_word.c_str(), 30);
    DrawText(next_word.c_str(), anim_right_x - next_word_width, y, 30, LIGHTGRAY);

    EndScissorMode();

}

void DrawTypedWord(const char* word, const char* correct_word, int x, int y, int fontSize) {
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

int main(void) {
    char* word = (char*)malloc(sizeof(char) * (MAX_INPUT_CHAR + 1));
    word[0] = '\0';
    int letter_count = 0;
    float cursorContent = 0.0f;
    bool drawCursor = true;

    InitWindow(init_width, init_height, "TypeOnMe");
    SetTargetFPS(200);

    init_button(&button_0, (Rectangle){0, 15, 200, 30}, RED);
    init_button(&button_1, (Rectangle){210, 15, 200, 30}, RED);
    init_time_buttons();

    vector<string> dictionary = {"apple", "banana", "cat", "dog", "elephant", "forest", "giraffe", "honey", "ice", "jacket", "kangaroo", "lemon", "mountain", "notebook", "ocean", "pencil", "quartz", "river", "sand", "tiger", "umbrella", "violin", "whale", "xylophone", "yacht", "zebra", "ant", "balloon", "candle", "dolphin", "eagle", "fountain", "grape", "house", "igloo", "jungle", "kite", "lantern", "mirror", "nest", "owl", "peacock", "quilt", "rainbow", "sunflower", "turtle", "unicorn", "vase", "windmill", "x-ray", "yarn"};

    WordGenerator word_generator(dictionary, global_seed);
    deque<string> word_queue;
    for (int i = 0; i < 3; ++i) {
        word_queue.push_back(word_generator.getNextWord());
    }
    string prev_word = "";

    bool animating = false;

    while (!WindowShouldClose()) {
        int remaining_time = DrawTime();

        if (!game_over) {
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
                            }
                        }
                    } else {
                        time_buttons[i].color = DARKGRAY;
                    }
                }
            }

            if (!typing_started && letter_count > 0) {
                typing_started = true;
                typing_start_time = GetTime();
            }

            if ((IsKeyPressed(KEY_BACKSPACE) && letter_count > 0)) {
                total_characters_typed--;
                letter_count--;
                word[letter_count] = '\0';
            } else if (letter_count < MAX_INPUT_CHAR) {
                int key = GetCharPressed();

                if ((key >= 32 && key <= 125) || key == ' ') {
                    word[letter_count] = (char)key;

                    if (key == ' ' || word[letter_count] == ' ') {
                        word[letter_count] = '\0';
                        typedWords.push_back(word);
                        
                        // Shift words
                        prev_word = word_queue.front();
                        word_queue.pop_front();
                        word_queue.push_back(word_generator.getNextWord());
                        all_displayed_words.push_back(word_queue.back());
                        
                        memset(word, 0, sizeof(char) * (MAX_INPUT_CHAR + 1));
                        letter_count = 0;

                        animating = true;
                        animation_progress = 0.0f;
                    } else {
                        letter_count++;
                    }
                    total_characters_typed++;
                }
            }

            // Handle animation
            if (animating) {
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

            BeginDrawing();
            ClearBackground(BLACK);

            // Draw the three words in the box
            int box_width = 740;
            int box_height = 150;

            DrawTextInBounds(prev_word, word_queue[0], word_queue[1], 410, 65, box_width, box_height);

            // Sentence Button
            DrawRectangleRec(button_0.rect, button_0.color);
            DrawText("Sentence", button_0.rect.x + button_0.rect.width/2 - MeasureText("Words", 10) - 10, button_0.rect.y + button_0.rect.height/2 - 20 / 2, 20, WHITE);

            // Word Button
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

            // Draw the typed word
            int wordWidth = MeasureText(word, 30);
            int textStartX = CENTER_X - wordWidth / 2;
            DrawTypedWord(word, word_queue[0].c_str(), textStartX, CENTER_Y, 30);

            // Draw the cursor
            if (drawCursor) {
                DrawLine(textStartX + wordWidth, CENTER_Y - 25, 
                         textStartX + wordWidth, CENTER_Y + 25, RAYWHITE);
            }

            // Draw current WPM
            float current_wpm = calculate_wpm();
            DrawText(TextFormat("Current WPM: %.2f", current_wpm), 10, init_height - 40, 20, WHITE);

            EndDrawing();
        } else {
            // Game over state
            BeginDrawing();
            ClearBackground(BLACK);

            float wpm = calculate_wpm();
            float acc = accuracy(typedWords, all_displayed_words);
            DrawText(TextFormat("Final WPM: %.2f", wpm), init_width / 2 - 100, init_height / 2, 30, RAYWHITE);
            DrawText(TextFormat("Accuracy: %.2f%%", acc), init_width / 2 - 100, init_height / 2 + 50, 30, RAYWHITE);

            EndDrawing();

            if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                break;
            }
        }
    }

    free(word);
    CloseWindow();
    return 0;
}