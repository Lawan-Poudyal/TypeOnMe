#include "raylib.h"
#include <vector>
#include <string>

// Define the Key class
class Key {
public:
    Rectangle rect;
    std::string label;
    int keycode;
    Color defaultColor;
    Color pressedColor;
    bool isPressed;

    Key(float x, float y, float width, float height, std::string label, int keycode)
        : rect{ x, y, width, height },
          label(label),
          keycode(keycode),
          defaultColor(LIGHTGRAY),
          pressedColor(BLUE),
          isPressed(false) {}

    void Draw() {
        Color currentColor = isPressed ? pressedColor : defaultColor;
        DrawRectangleRec(rect, currentColor);
        DrawText(label.c_str(), rect.x + rect.width / 4, rect.y + rect.height / 4, 20, BLACK);
    }

    void Update() {
        isPressed = IsKeyDown(keycode);
    }
};

int main() {
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Interactive Keyboard");

    std::vector<Key> keys;

    // Define key positions and sizes
    float keyWidth = 50;
    float keyHeight = 50;
    float startX = 50;
    float startY = 50;
    float gap = 10;

    // Define rows of keys
    std::vector<std::vector<std::pair<std::string, int>>> keyRows = {
        { {"1", KEY_ONE}, {"2", KEY_TWO}, {"3", KEY_THREE}, {"4", KEY_FOUR}, {"5", KEY_FIVE},
          {"6", KEY_SIX}, {"7", KEY_SEVEN}, {"8", KEY_EIGHT}, {"9", KEY_NINE}, {"0", KEY_ZERO},
          {"-", KEY_MINUS}, {"=", KEY_EQUAL}, {"delete", KEY_BACKSPACE} },

        { {"tab", KEY_TAB}, {"Q", KEY_Q}, {"W", KEY_W}, {"E", KEY_E}, {"R", KEY_R},
          {"T", KEY_T}, {"Y", KEY_Y}, {"U", KEY_U}, {"I", KEY_I}, {"O", KEY_O},
          {"P", KEY_P}, {"[", KEY_LEFT_BRACKET}, {"]", KEY_RIGHT_BRACKET}, {"\\", KEY_BACKSLASH} },

        { {"caps lock", KEY_CAPS_LOCK}, {"A", KEY_A}, {"S", KEY_S}, {"D", KEY_D}, {"F", KEY_F},
          {"G", KEY_G}, {"H", KEY_H}, {"J", KEY_J}, {"K", KEY_K}, {"L", KEY_L},
          {";", KEY_SEMICOLON}, {"'", KEY_APOSTROPHE}, {"enter", KEY_ENTER} },

        { {"shift", KEY_LEFT_SHIFT}, {"Z", KEY_Z}, {"X", KEY_X}, {"C", KEY_C}, {"V", KEY_V},
          {"B", KEY_B}, {"N", KEY_N}, {"M", KEY_M}, {",", KEY_COMMA}, {".", KEY_PERIOD},
          {"/", KEY_SLASH}, {"shift", KEY_RIGHT_SHIFT} },

        { {"ctrl", KEY_LEFT_CONTROL}, {"alt", KEY_LEFT_ALT}, {"cmd", KEY_LEFT_SUPER},
          {" ", KEY_SPACE}, {"cmd", KEY_RIGHT_SUPER}, {"alt", KEY_RIGHT_ALT}, {"ctrl", KEY_RIGHT_CONTROL} }
    };

    // Create Key objects for each key in each row
    for (size_t row = 0; row < keyRows.size(); ++row) {
        float y = startY + row * (keyHeight + gap);
        float x = startX;
        for (const auto& keyDef : keyRows[row]) {
            keys.push_back(Key(x, y, keyWidth, keyHeight, keyDef.first, keyDef.second));
            x += keyWidth + gap;
            if (keyDef.first == "tab" || keyDef.first == "caps lock" || keyDef.first == "shift" || keyDef.first == "ctrl" || keyDef.first == "alt" || keyDef.first == "cmd" || keyDef.first == "enter") {
                x += keyWidth;
            }
        }
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update
        for (auto &key : keys) {
            key.Update();
        }

        // Draw
        BeginDrawing();
        ClearBackground(WHITE);

        for (auto &key : keys) {
            key.Draw();
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
