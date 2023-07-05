///vectors V2(created)JULY 02 2023 Christian Rogers
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include<cmath>
#include<iostream>
#include<vector>
using namespace std;
struct pixel {
    int x;
    int y;
    int RGB[3] = { 0,0,0 };
    void setWhite() {
        RGB[0] = 255;
        RGB[1] = 255;
        RGB[2] = 255;
    }
    void setBlack() {
        RGB[0] = 0;
        RGB[1] = 0;
        RGB[2] = 0;
    }

};
struct XY {
    int x = 0;
    int y = 0;
    int z = 0;
};
struct R3vector {

};

class Helper {
public:
    bool isValidStoi(string in) {
        for (int i = 0; i < in.length();i++) {
            if (45 == (int)in[i]) {
                continue;
            }
            else if (48 > (int)in[i] || (int)in[i] > 57) {
                return false;
            }
        }
        return true;
    }

};
// Global variables(
#define xSIZE 900
#define ySIZE 900
int origin[] = { xSIZE / 2, ySIZE / 2 };
bool isStart = true;
int lineSmoothing = 2;
int scale = 100; //(scale--> 1unit == scale(pixels)
Helper helper;
// The main window class name.
static TCHAR szWindowClass[] = _T("vectors_V1");
// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("vectors_V1");
// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;
// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//

class NormalizedSpace {
private:
public:

};
class Command {

};

class ScreenText {
private:
    string textOut;
public:
    ScreenText() {
        this->textOut = "(0,0)";
    }
    string update(pixel pixelCacheEnd) {
        textOut = "last position drawn(" + to_string((int)ceil((pixelCacheEnd.x - origin[0]) / scale)) + "," + to_string((int)ceil((origin[1] - pixelCacheEnd.y) / scale)) + ")";
        return textOut;
    }
};

class PixelMemory {
private:
    NormalizedSpace grid;
    vector<pixel> pixelCache;
    vector<pixel> temp; //helper for insert

public:
    PixelMemory() {
    }
    void clearPixelMemory() {


    }
    vector<pixel> getPixelCache() {

    }
};

class Interface {
private:
    Command command;
    PixelMemory pixelMem;
    R3vector vectorPerametersPointBased;
    vector<pixel> out;
    //
    ScreenText screenText;
    string tempText;
    LPSTR currentText = NULL;
    int size = 0;
public:
    vector<pixel> call() {
        ///todo
        //screeen refresh 
        return vector<pixel>();
    }
    LPSTR screenTextOut() {
        if (out.size() - 1 < 0) { 
            return const_cast<char*>(tempText.c_str()); 
        }
        else {
            cout << "hello";
            tempText = screenText.update(out[out.size() - 1]);
        }
        currentText = const_cast<char*>(tempText.c_str());
        return const_cast<char*>(tempText.c_str());
    }
    int screenTextLength() {
        size = (int)tempText.length();
        return size;
    }

};

/// start gui
int WINAPI WinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPSTR     lpCmdLine,
    _In_ int       nCmdShow
)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

    if (!RegisterClassEx(&wcex))
    {
        MessageBox(NULL,
            _T("Call to RegisterClassEx failed!"),
            _T("thats not good"),
            NULL);

        return 1;
    }

    // Store instance handle in our global variable
    hInst = hInstance;

    // The parameters to CreateWindowEx explained:
    // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
    // szWindowClass: the name of the application
    // szTitle: the text that appears in the title bar
    // WS_OVERLAPPEDWINDOW: the type of window to create
    // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
    // 500, 100: initial size (width, length)
    // NULL: the parent of this window
    // NULL: this application does not have a menu bar
    // hInstance: the first parameter from WinMain
    // NULL: not used in this application
    HWND hWnd = CreateWindowEx(
        WS_EX_OVERLAPPEDWINDOW,
        szWindowClass,
        szTitle,
        WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
        0, 0,
        xSIZE, ySIZE,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)brush);

    if (!hWnd)
    {
        MessageBox(NULL,
            _T("Call to CreateWindow failed!"),
            _T("thats not good"),
            NULL);

        return 1;
    }

    // The parameters to ShowWindow explained:
    // hWnd: the value returned from CreateWindow
    // nCmdShow: the fourth parameter from WinMain
    ShowWindow(hWnd,
        nCmdShow);
    UpdateWindow(hWnd);

    // Main message loop:
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT ps;
    HDC hdc;
    vector<pixel> pixelCache;
    Interface user;
    LPSTR screenText;
    switch (message)
    {
    case WM_PAINT:
        while (true) {
            // LPSTR screenText;
            pixelCache = user.call();
            hdc = BeginPaint(hWnd, &ps);
            screenText = user.screenTextOut();
            TextOutA(hdc, xSIZE - 200, 2 * user.screenTextLength(), screenText, user.screenTextLength());
            for (int i = 0; i < pixelCache.size(); i++) {
                SetPixel(hdc, pixelCache[i].x, pixelCache[i].y, RGB(pixelCache[i].RGB[0], pixelCache[i].RGB[1], pixelCache[i].RGB[2]));
            }
            pixelCache.clear();
            EndPaint(hWnd, &ps);
            InvalidateRect(hWnd, 0, 1);
        }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }

    return 0;
}

