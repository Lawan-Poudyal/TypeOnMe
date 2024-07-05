

bool IsButtonClicked (Rectangle button ){
    return (CheckCollisionPointRec(GetMousePosition(), button ) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));
}
