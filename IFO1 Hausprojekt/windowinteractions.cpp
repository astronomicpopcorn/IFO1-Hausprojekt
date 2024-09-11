#include "datastructures.h"
#include "constants.h"

#include <windows.h>


// MOUSE INTERACTION DISCONTINUED DUE TO COMPLEXITY

//returns position of window on screen in pixels
bool get_window_position(Vector2D *topleft, Vector2D *size) {
    HWND console_window = GetForegroundWindow();
    if (console_window == NULL) {
        return false;
    }

    RECT window_rect;
    POINT top_left_point = { 0, 0 };

    if (GetClientRect(console_window, &window_rect)) { //GetWindowRect() returns pos of whole window including shadow. GetClientRect() should only return the usable part
        if (ClientToScreen(console_window, &top_left_point))
            topleft->x = top_left_point.x;
        topleft->y = top_left_point.y;
        size->x = window_rect.right - window_rect.left;
        size->y = window_rect.bottom - window_rect.top;
        return true;
    }
    return false;
}

//returns a vector containing the size of the console in characters
//no idea how this actually works
Vector2D get_console_size() {
    Vector2D consolesize;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    consolesize.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    consolesize.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    return consolesize;
}

//returns position of mouse on screen in pixels
Vector2D get_mouse_position() {
    Vector2D result;
    result.x = -1;
    result.y = -1;
    POINT curser_position;
    if (GetCursorPos(&curser_position)) {
        result.x = curser_position.x;
        result.y = curser_position.y;
    }
    return result;
}

//calculate where on the window the mouse is
//this here is where mouse interaction failed. for some reason this is really inaccurate
Vector2D get_mouse_on_window() {
    Vector2D result;
    Vector2D window_position, window_size, mouse_position;
    mouse_position = get_mouse_position();
    if (!get_window_position(&window_position, &window_size) || (mouse_position.x == -1 && mouse_position.y == -1)) {
        result.x = -1;
        result.y = -1;
        return result;
    }
    result.x = mouse_position.x - window_position.x;
    result.y = mouse_position.y - window_position.y;
    if (result.x < 0 || result.x >= window_size.x) {
        result.x = -1;
    }
    if (result.y < 0 || result.y >= window_size.y) {
        result.y = -1;
    }
    return result;
}

//transform pixel coordinates to character coordinates
Vector2D get_mouse_on_console() {
    Vector2D pos = get_mouse_on_window();
    Vector2D consolesize = get_console_size();
    Vector2D topleft, size;
    get_window_position(&topleft, &size);
    pos.x = pos.x / (size.x / consolesize.x);
    pos.y = pos.y / (size.y / consolesize.y);
    return pos;
}

