#include "raylib.h"
#include <vector>
#include <string>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <cstring>

#define MAX_INPUT_CHAR 500

// Declarations and definition of global variables
using namespace std;
const int init_width = 1500;
const int init_height = 768;
const int CENTER_X = init_width / 2;
const int CENTER_Y = init_height / 2;
int global_seed = time(NULL);

double typing_start_time = 0.0;
bool typing_started = false;
int total_characters_typed = 0;

vector<string> typedWords;
vector<string> all_displayed_words;

float animation_progress = 1.0f;
const float ANIMATION_DURATION = 0.3f; // Animation duration in seconds

// Function prototypes
float calculate_wpm();
float accuracy(const vector<string>& typedWords, const vector<string>& all_displayed_words);
void DrawTextInBounds(const string& prev_word, const string& current_word, const string& next_word, int start_x, int start_y, int max_width, int max_height);

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
    int seed;

public:
    WordGenerator(const vector<string>& dict, int s) : dictionary(dict), seed(s) {
        srand(seed);
    }

    string getNextWord() {
        return dictionary[rand() % dictionary.size()];
    }
};

// Struct
typedef struct Button {
    Rectangle rect;
    Color color;
} Button;

Button button_0 = {0}; //the button
Button button_1 = {0}; //the button

void init_button(Button *button, Rectangle rect, Color color){
    button->rect = rect;
    button->color = color;
}

bool is_mouse_over_button(Button button){
    return CheckCollisionPointRec(GetMousePosition(), button.rect);
}

int DrawTime() {
    static bool timer_initialized = false;
    static double timer_start = 0.0;
    int seconds = 15;

    if (typing_started && !timer_initialized) {
        timer_start = GetTime();
        timer_initialized = true;
    }

    if (timer_initialized) {
        double elapsed = GetTime() - timer_start;
        seconds = 15 - static_cast<int>(elapsed);
        if (seconds < 0) seconds = 0;
    }

    DrawText(TextFormat("Time: %i", seconds), init_width-200, 40, 20, WHITE);
    return seconds;
}

float calculate_wpm() {
    if (!typing_started) return 0.0f;
    float elapsed_time = (GetTime() - typing_start_time) / 60.0f; // convert seconds to minutes
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
    Rectangle rect = {float(start_x), float(start_y), float(max_width-300), float(max_height)};
    DrawRectangleRec(rect, BLUE);

    int word_height = 40;
    int padding = 20;

    // Calculate positions
    int left_x = start_x + padding;
    int center_x = start_x + (max_width - 300) / 2;
    int right_x = start_x + max_width - 300 - padding;
    int y = start_y + (max_height - word_height) / 2;

    // Calculate animated positions (right to left)
    float anim_left_x = left_x + (center_x - left_x) * (1 - animation_progress);
    float anim_center_x = center_x + (right_x - center_x) * (1 - animation_progress);
    float anim_right_x = right_x + (max_width - 300) * (1 - animation_progress);

    // Draw previous word (left)
    DrawText(prev_word.c_str(), anim_left_x, y, 30, LIGHTGRAY);

    // Draw current word (center)
    int current_word_width = MeasureText(current_word.c_str(), 30);
    DrawText(current_word.c_str(), anim_center_x - current_word_width / 2, y, 30, WHITE);

    // Draw next word (right)
    int next_word_width = MeasureText(next_word.c_str(), 30);
    DrawText(next_word.c_str(), anim_right_x - next_word_width, y, 30, LIGHTGRAY);
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

        // Update
        if(is_mouse_over_button(button_0)){
            button_0.color = BLUE;
        } else {
            button_0.color = RED;
        }

        if(is_mouse_over_button(button_1)){
            button_1.color = BLUE;
        } else {
            button_1.color = RED;
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw the three words in the box
        DrawTextInBounds(prev_word, word_queue[0], word_queue[1], 410, 65, 1150, 150);

        // Sentence Button
        DrawRectangleRec(button_0.rect, button_0.color);
        DrawText("Sentence", button_0.rect.x + button_0.rect.width/2 - MeasureText("Words", 10) - 10, button_0.rect.y + button_0.rect.height/2 - 20 / 2, 20, WHITE);

        // Word Button
        DrawRectangleRec(button_1.rect, button_1.color);
        DrawText("Words", button_1.rect.x + button_1.rect.width/2 - MeasureText("Words", 10) - 10, button_1.rect.y + button_1.rect.height/2 - 20 / 2, 20, WHITE);

        // Draw the typed word
        int wordWidth = MeasureText(word, 30);
        int textStartX = CENTER_X - wordWidth / 2;
        DrawText(word, textStartX, CENTER_Y, 30, RAYWHITE);

        // Draw the cursor
        if (drawCursor) {
            DrawLine(textStartX + wordWidth, CENTER_Y - 25, 
                     textStartX + wordWidth, CENTER_Y + 25, RAYWHITE);
        }

        // Draw current WPM
        float current_wpm = calculate_wpm();
        DrawText(TextFormat("Current WPM: %.2f", current_wpm), 10, init_height - 40, 20, WHITE);

        if (remaining_time <= 0) {
            // Display final results
            ClearBackground(BLACK);
            float wpm = calculate_wpm();
            float acc = accuracy(typedWords, all_displayed_words);
            DrawText(TextFormat("Final WPM: %.2f", wpm), init_width / 2 - 100, init_height / 2, 30, RAYWHITE);
            DrawText(TextFormat("Accuracy: %.2f%%", acc), init_width / 2 - 100, init_height / 2 + 50, 30, RAYWHITE);
            EndDrawing();
            
            // Wait for 2 seconds before closing
            WaitTime(2.0);
            break;
        }

        EndDrawing();
    }

    free(word);
    CloseWindow();
    return 0;
}