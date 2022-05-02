#pragma once
#include <Windows.h>
#include <queue>
#include "Subsystem.h"
#include "InputEvent.h"


// input manager handles user input
// only one instance may exist
class IOManager : private Subsystem<IOManager> {
public:
    // call first
    void                 startup(HINSTANCE instanceHandle, // app instance
                                 int cmdShow);             // initial window appearance

    const HWND           getHandle() const;

    int                  getWindowHeight() const; // in pixels
    int                  getWindowWidth() const;  // in pixels
    
    // call each frame before using IOManager
    void                 update();  

    // get user input event
    // returns false when no events remain
    // populates e with user input
    bool                 pump(InputEvent* e);
    
    // when captured, mouse remains centered
    static void          setCursorCaptured(bool);
    static void          setCursorVisible(bool);

    // call last
    static void          shutdown();

    // windows callback for all messages from the operating system
    static LRESULT WINAPI wndProc(HWND, UINT, WPARAM, LPARAM);

private:
    static int                    windowHeight;
    static int                    windowWidth;
    static std::queue<InputEvent> inputEvents;
    static short                  lastMousePositionX; // px
    static short                  lastMousePositionY; // px
    static bool                   cursorCaptured;

    // handles to the windows os
    static HWND                   windowHandle;        // handle to app window
    static HINSTANCE              instanceHandle;      // handle to app

};