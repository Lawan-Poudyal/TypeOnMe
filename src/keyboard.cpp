#include <raylib.h>
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
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Interactive Keyboard");

    std::vector<Key> keys;

    // Define the keys (for simplicity, let's define a few keys)
    keys.push_back(Key(50, 100, 50, 50, "A", KEY_A));
    keys.push_back(Key(110, 100, 50, 50, "S", KEY_S));
    keys.push_back(Key(170, 100, 50, 50, "D", KEY_D));
    keys.push_back(Key(230, 100, 50, 50, "F", KEY_F));

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
