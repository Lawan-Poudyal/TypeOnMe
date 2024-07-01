#include "dependencies.h"
#include "wpm.hpp"
#include "accuracy.hpp"

// Declarations and definition of global variables
using namespace std;

const int init_width  = GetScreenWidth();
const int init_height = GetScreenHeight();
void clearWindow();
int global_seed = time(NULL);
int gtotal_letter_count = 0;
int in_positionY = init_height / 2 - 10;
int in_positionX = init_width / 2;
vector<string> typedWords;
vector<string> ext_random_words;

// Class definitions
class Cursor {
public:
    int pos1_x;
    int pos2_x;
    int pos1_y;
    int pos2_y;

    Cursor(const char* word, int letter_count, bool drawCursor, int c_height) {
        if (drawCursor && letter_count < MAX_INPUT_CHAR) {
            DrawLine(MeasureText(word, 30) + in_positionX + 10 + GetScreenWidth() / 2, in_positionY + GetScreenHeight() / 2  - c_height / 2,
                     in_positionX + MeasureText(word, 30) + 10 + GetScreenWidth() / 2, in_positionY + c_height / 2 + GetScreenHeight()/ 2 , RAYWHITE);
        }
    }
};

class WordGenerator {
public:
    vector<string> RandomWord(vector<string> dictionary, int seed, int n) {
        srand(seed);
        vector<string> return_list;

        for (int i = 0; i < n; i++) {
            return_list.push_back(dictionary[rand() % dictionary.size()]);
        }

        return return_list;
    }
};
// Class definitions end here

int main(void) {
    int spaces = 0;
    float wpm;
    int count_for_closing_window_after_wpm = 0;
    char* word = (char*) malloc(sizeof(char) * MAX_INPUT_CHAR + 1);
    word[MAX_INPUT_CHAR] = '\0';
    string gray_word;
    int letter_count = 0;
    float cursorContent = 0.0f;
    bool drawCursor = true;
    bool truth_value = true;
    time_t start_time = 0; // Initialize start_time

    // Initialize the Raylib window and set the target FPS to 200
    InitWindow(init_width, init_height, "TypeOnMe");
    SetTargetFPS(200);

    // A list of words to use
    vector<string> dictionary = {
        "very", "cool", "looking", "guy", "is", "democrat", "nation", "signify", "hello", "hey",
        "hello", "rather", "punctual", "philosophical", "romantic", "exquisite", "random",
        "slash", "govern", "mesh", "jeopardy", "utopia", "rant"
    };

    WordGenerator random_word_gen; // Move outside of while loop to avoid re-initialization

    // Initialize random words to avoid accessing uninitialized vector
    ext_random_words = random_word_gen.RandomWord(dictionary, global_seed, 4);

    while (!WindowShouldClose()) {
        if (gtotal_letter_count == 1) {
            if (truth_value) {
                start_time = time(NULL); // Use time(NULL) for start time
                truth_value = !truth_value;
            }
        }

        if (spaces == 4) {
            count_for_closing_window_after_wpm++;
            if (start_time != 0) { // Ensure start_time is properly initialized
                wpm = calculate_wpm(start_time);
                DrawText(to_string(wpm).c_str(), init_width / 2, init_height / 2 + 100, 30, RAYWHITE);
                DrawText(to_string(accuracy(typedWords, ext_random_words)).c_str(), init_width / 2, init_height / 2 + 150, 30, RAYWHITE);
            }
        }

        if (IsKeyPressed(KEY_BACKSPACE) && letter_count > 0) {
            if (word[letter_count - 1] == ' ') {
                spaces--;
            }
            gtotal_letter_count--;
            letter_count--;
            word[letter_count] = '\0';
        } else if (letter_count < MAX_INPUT_CHAR) {
            int key = GetCharPressed();

            if ((key >= 32 && key <= 125) || key == ' ') {
                word[letter_count] = (char) key;

                if (key == ' ' || word[letter_count] == ' ') {
                    spaces++;
                    word[letter_count] = '\0';
                    typedWords.push_back(word);
                    memset(word, 0, sizeof(char) * MAX_INPUT_CHAR + 1);
                    letter_count = 0;
                } else {
                    cout << word << endl;
                    letter_count++;
                    gtotal_letter_count++;
                    in_positionX -= 0;
                }
            }
        }

        cursorContent += GetFrameTime();
        if (cursorContent >= 0.5f) {
            cursorContent = 0.0f;
            drawCursor = !drawCursor;
        }

        // Re-generate random words only when needed
        if (spaces == 0) {
            ext_random_words = random_word_gen.RandomWord(dictionary, global_seed, 4);
        }

        int word_width = 0;
        ClearBackground(BLACK);  // Clear background at the beginning of drawing

        for (string random_word : ext_random_words) {
            DrawText(random_word.c_str(), 2.5 * word_width + 10, 30, 30, RAYWHITE);
            word_width += MeasureText(random_word.c_str(), 50);
        }

        if (spaces < ext_random_words.size()) { // Check boundary
            gray_word = ext_random_words[spaces]; // Assign the string directly
            DrawText(gray_word.c_str(), in_positionX+ GetScreenWidth()/2, in_positionY+GetScreenHeight()/2, 30, DARKGRAY); // Use c_str() for rendering
        }

        DrawText(word, in_positionX+GetScreenWidth()/2, in_positionY+GetScreenHeight()/2, 30, RAYWHITE);

        // Blinking Cursor Next to Text
        Cursor cursor_1(word, letter_count, drawCursor, 50);

        EndDrawing();

        if (count_for_closing_window_after_wpm) {
            sleep(2);
            break;
        }
    }
    free(word);  // Only free `word`
    CloseWindow();
    return 0;
}
