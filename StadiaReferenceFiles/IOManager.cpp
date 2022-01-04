#include "IOManager.h"
#include <assert.h>
#include <windowsx.h> 
#include "utf8Everywhere.h"

// static member variable definition and initialization
const std::wstring windowClassName = widen("StadiaWindowClass");

int       IOManager::windowHeight = 600;
int       IOManager::windowWidth = 800;
short     IOManager::lastMousePositionX = 0;
short     IOManager::lastMousePositionY = 0;
HWND      IOManager::windowHandle = nullptr;
HINSTANCE IOManager::instanceHandle = nullptr;
bool      IOManager::cursorCaptured = false;
std::queue<InputEvent> IOManager::inputEvents;



// utility function declaration
void registerWindowClass(HINSTANCE hInst, WNDPROC callback);

HWND createWindowInstance(int heightPx, int widthPx, // inside frame
     int cmdShow, HINSTANCE instanceHandle);

void IOManager::startup(HINSTANCE instHandle, int cmdShow) {
    instanceHandle = instHandle;
    registerWindowClass(instanceHandle, wndProc);
    windowHandle = createWindowInstance(windowHeight, windowWidth,
        cmdShow, instanceHandle);
}

const HWND IOManager::getHandle() const {
    return windowHandle;
}

int IOManager::getWindowHeight() const {
    return windowHeight;
}

int IOManager::getWindowWidth() const {
    return windowWidth;
}

void IOManager::shutdown() {
    setCursorVisible(true);
    setCursorCaptured(false);
    UnregisterClass(windowClassName.c_str(), instanceHandle);
    DestroyWindow(windowHandle);
}

bool IOManager::pump(InputEvent* e) {
    // check if there are any queued events
    if(inputEvents.size() > 0) {
        // populate e and return
        *e = inputEvents.front();
        inputEvents.pop();
        return true;
    }
    *e = InputEvent(); // clear
    return false; // no events remain
}

void IOManager::setCursorCaptured(bool isCaptured) {
    cursorCaptured = isCaptured;
    if(isCaptured) {
        RECT windowRectangle;
        GetWindowRect(windowHandle, &windowRectangle);
        ClipCursor(&windowRectangle);
    } else {
        ClipCursor(NULL); // frees cursor
    }
}
void IOManager::setCursorVisible(bool isVisible) {
    ShowCursor(isVisible);
}

void IOManager::update() {
    if(cursorCaptured) {
        // set cursor back to center of screen
        RECT windowRectangle;
        GetWindowRect(windowHandle, &windowRectangle);
        int centerX = windowRectangle.left + ((windowRectangle.right - windowRectangle.left) / 2);
        int centerY = windowRectangle.top + ((windowRectangle.bottom - windowRectangle.top) / 2);
        SetCursorPos(centerX, centerY);
    }
    
    // structure to hold windows message
    MSG message;
    //    HWND hwnd;      handle to window who's procedure is to recieve the message
    //    UINT message;   constant value identifying type of message
    //    WPARAM wparam;  information about the message - dependent on type of message
    //    LPARAM lparam;  information about the message - dependent on type of message
    //    DWORD time;     time message was posted
    //    POINT pt;       x,y coordinates of mouse cursor when message was posted
    // PeekMessage fills &msg data structure or returns 0 if there are no more message
    while(PeekMessage(&message, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&message);
        DispatchMessage(&message); // forwards call to wndProc
    }
}

// create InputEvent for interesting messages and append to queue
LRESULT WINAPI IOManager::wndProc(HWND windowHandle, // handle to window
                                  UINT message,      // message from system
                                  WPARAM wParam,     // additional message information
                                  LPARAM lParam) {   // additional message information
    InputEvent e;  // modify this event - it will be pushed to event queue
    switch(message) {
    case WM_QUIT:
        e.eventType = EventType::APP_QUIT;
    case WM_CLOSE:
        // deactivate window, remove keyboard focus and destroy it
        e.eventType = EventType::APP_QUIT;
        DestroyWindow(windowHandle);
        break;
    case WM_DESTROY:
        e.eventType = EventType::APP_QUIT;
        // tell system that our thread is will quit
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
        e.eventType = EventType::MOUSE_CLICK;
        e.mouseButton = MouseButton::LEFT;
        break;
    case WM_LBUTTONUP:
        e.eventType = EventType::MOUSE_RELEASE;
        e.mouseButton = MouseButton::LEFT;
        break;
    case WM_KEYDOWN:
    case WM_KEYUP:
        if(message == WM_KEYUP)   e.eventType = EventType::KEY_UP;
        if(message == WM_KEYDOWN) e.eventType = EventType::KEY_DOWN;

        if(wParam == VK_SPACE)    e.key = Key::SPACE;
        if(wParam == VK_ESCAPE)   e.key = Key::ESCAPE;
        if(wParam == VK_BACK)     e.key = Key::BACKSPACE;
        if(wParam == VK_TAB)      e.key = Key::TAB;
        if(wParam == VK_RETURN)   e.key = Key::RETURN;
        if(wParam == VK_SHIFT)    e.key = Key::SHIFT;
        if(wParam == VK_CONTROL)  e.key = Key::CONTROL;
        if(wParam == VK_MENU)     e.key = Key::ALT;
        if(wParam == VK_LWIN)     e.key = Key::WINDOWS;
        if(wParam == VK_RWIN)     e.key = Key::WINDOWS;
        if(wParam == VK_CAPITAL)  e.key = Key::CAPS_LOCK;
        if(wParam == VK_INSERT)   e.key = Key::INSERT;
        if(wParam == VK_DELETE)   e.key = Key::DEL;
        if(wParam == VK_HOME)     e.key = Key::HOME;
        if(wParam == VK_END)      e.key = Key::END;
        if(wParam == VK_PRIOR)    e.key = Key::PAGE_UP;
        if(wParam == VK_NEXT)     e.key = Key::PAGE_DOWN;
        if(wParam == VK_SNAPSHOT) e.key = Key::PRINT_SCREEN;
        if(wParam == VK_SCROLL)   e.key = Key::SCROLL_LOCK;
        if(wParam == VK_PAUSE)    e.key = Key::PAUSE;
        if(wParam == VK_UP)       e.key = Key::UP_ARROW;
        if(wParam == VK_DOWN)     e.key = Key::DOWN_ARROW;
        if(wParam == VK_LEFT)     e.key = Key::LEFT_ARROW;
        if(wParam == VK_RIGHT)    e.key = Key::RIGHT_ARROW;
        if(wParam == '0')         e.key = Key::NUMBER_0;
        if(wParam == '1')         e.key = Key::NUMBER_1;
        if(wParam == '2')         e.key = Key::NUMBER_2;
        if(wParam == '3')         e.key = Key::NUMBER_3;
        if(wParam == '4')         e.key = Key::NUMBER_4;
        if(wParam == '5')         e.key = Key::NUMBER_5;
        if(wParam == '6')         e.key = Key::NUMBER_6;
        if(wParam == '7')         e.key = Key::NUMBER_7;
        if(wParam == '8')         e.key = Key::NUMBER_8;
        if(wParam == '9')         e.key = Key::NUMBER_9;
        if(wParam == VK_NUMPAD0)  e.key = Key::NUMPAD_0;
        if(wParam == VK_NUMPAD1)  e.key = Key::NUMPAD_1;
        if(wParam == VK_NUMPAD2)  e.key = Key::NUMPAD_2;
        if(wParam == VK_NUMPAD3)  e.key = Key::NUMPAD_3;
        if(wParam == VK_NUMPAD4)  e.key = Key::NUMPAD_4;
        if(wParam == VK_NUMPAD5)  e.key = Key::NUMPAD_5;
        if(wParam == VK_NUMPAD6)  e.key = Key::NUMPAD_6;
        if(wParam == VK_NUMPAD7)  e.key = Key::NUMPAD_7;
        if(wParam == VK_NUMPAD8)  e.key = Key::NUMPAD_8;
        if(wParam == VK_NUMPAD9)  e.key = Key::NUMPAD_9;
        if(wParam == VK_ADD)      e.key = Key::ADD;
        if(wParam == VK_SUBTRACT) e.key = Key::SUBTRACT;
        if(wParam == VK_MULTIPLY) e.key = Key::MULTIPLY;
        if(wParam == VK_DIVIDE)   e.key = Key::DIVIDE;
        if(wParam == VK_DECIMAL)  e.key = Key::DECIMAL;
        if(wParam == VK_F1)       e.key = Key::F1;
        if(wParam == VK_F2)       e.key = Key::F2;
        if(wParam == VK_F3)       e.key = Key::F3;
        if(wParam == VK_F4)       e.key = Key::F4;
        if(wParam == VK_F5)       e.key = Key::F5;
        if(wParam == VK_F6)       e.key = Key::F6;
        if(wParam == VK_F7)       e.key = Key::F7;
        if(wParam == VK_F8)       e.key = Key::F8;
        if(wParam == VK_F9)       e.key = Key::F9;
        if(wParam == VK_F10)      e.key = Key::F10;
        if(wParam == VK_F11)      e.key = Key::F11;
        if(wParam == VK_F12)      e.key = Key::F12;
        if(wParam == 'A')         e.key = Key::A;
        if(wParam == 'B')         e.key = Key::B;
        if(wParam == 'C')         e.key = Key::C;
        if(wParam == 'D')         e.key = Key::D;
        if(wParam == 'E')         e.key = Key::E;
        if(wParam == 'F')         e.key = Key::F;
        if(wParam == 'G')         e.key = Key::G;
        if(wParam == 'H')         e.key = Key::H;
        if(wParam == 'I')         e.key = Key::I;
        if(wParam == 'J')         e.key = Key::J;
        if(wParam == 'K')         e.key = Key::K;
        if(wParam == 'L')         e.key = Key::L;
        if(wParam == 'M')         e.key = Key::M;
        if(wParam == 'N')         e.key = Key::N;
        if(wParam == 'O')         e.key = Key::O;
        if(wParam == 'P')         e.key = Key::P;
        if(wParam == 'Q')         e.key = Key::Q;
        if(wParam == 'R')         e.key = Key::R;
        if(wParam == 'S')         e.key = Key::S;
        if(wParam == 'T')         e.key = Key::T;
        if(wParam == 'U')         e.key = Key::U;
        if(wParam == 'V')         e.key = Key::V;
        if(wParam == 'W')         e.key = Key::W;
        if(wParam == 'X')         e.key = Key::X;
        if(wParam == 'Y')         e.key = Key::Y;
        if(wParam == 'Z')         e.key = Key::Z;

        break;
    case WM_MOUSEMOVE:
        e.eventType = EventType::MOUSE_MOVE;
        // mouse position
        e.x = GET_X_LPARAM(lParam);
        e.y = GET_Y_LPARAM(lParam);
        // mouse movement
        e.moveX = e.x - lastMousePositionX;
        e.moveY = e.y - lastMousePositionY;
        // record mouse position for future reference
        lastMousePositionX = e.x;
        lastMousePositionY = e.y;
        break;
    case WM_SIZE:
        // window resize
        e.eventType = EventType::WINDOW_RESIZE;
        e.x = LOWORD(lParam); // width of window in px
        e.y = HIWORD(lParam); // height of window in px (excluding title bar)
        break;
    case WM_KILLFOCUS:
        IOManager::setCursorCaptured(false);
        setCursorVisible(true);
        break;
    default:
        // unhandled message - call the default windows procedure
        return DefWindowProc(windowHandle, message, wParam, lParam);
    }
    inputEvents.push(e);
    // message was handled
    return 0;
}

void registerWindowClass(const HINSTANCE instanceHandle,
    const WNDPROC callback) {
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_HREDRAW | CS_VREDRAW;     // redraw on resize
    wc.lpfnWndProc   = callback;                    // callback
    wc.cbClsExtra    = 0;                           // extra bytes after class
    wc.cbWndExtra    = 0;                           // extra bytes after window
    wc.hInstance     = instanceHandle;              // app instance
    wc.hIcon         = LoadIcon(instanceHandle, IDI_APPLICATION); // large icon
    wc.hIconSm       = LoadIcon(instanceHandle, IDI_APPLICATION); // small icon
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW); // cursor
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);      // color to paint background
    wc.lpszMenuName  = NULL;                        // menu
    wc.lpszClassName = windowClassName.c_str();             // class name
    // register the window class
    if(!RegisterClassEx(&wc)) throw std::exception("unable to register window class");
}

HWND createWindowInstance(int heightPx, int widthPx, int cmdShow, HINSTANCE instanceHandle) {
    // dimensions of render target
    RECT rect ={ 0, 0, widthPx, heightPx };
    // enlarge to account for window border
    AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);

    // create window
    // find center of screen
    POINT center;
    center.x = (GetSystemMetrics(SM_CXSCREEN) - widthPx) / 2;
    center.y = (GetSystemMetrics(SM_CYSCREEN) - heightPx) / 2;

    static const std::wstring windowTitle = widen("Stadia");
    HWND windowHandle = CreateWindow(
        windowClassName.c_str(), // registered WNDCLASS
        windowTitle.c_str(),     // title
        WS_OVERLAPPEDWINDOW,     // style flags
        center.x, center.y,      // starting coordinates
        rect.right - rect.left,  // width
        rect.bottom - rect.top,  // height
        nullptr, nullptr,        // parent window, menu handle
        instanceHandle,          // app instance
        nullptr);                // creation parameters
    if(!windowHandle) throw std::exception("unable to create window");

    // window is initially hidden. show and update
    ShowWindow(windowHandle, cmdShow);
    UpdateWindow(windowHandle);
    return windowHandle;
}