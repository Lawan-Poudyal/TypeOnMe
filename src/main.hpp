#include "dependencies.h"
#include "wpm.hpp"
#include "accuracy.hpp"
#include "loginPage.hpp"


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
int count_for_closing_window_after_wpm = 0;
typedef enum {
    LOGIN,
    GAMEMODE,
} gameState;
  


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

int start_instance_cgamemode();
// Class definitions end here

