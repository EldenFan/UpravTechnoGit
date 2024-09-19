#define __DEFINE_VSTUB_CONSTS__
#include "vstub.h"
#include <math.h>

namespace std {

    HWND hWndMAIN;
    HWND hWndC;
    HWND hWndG;
    HDC hdcBufC;
    HDC hdcScbC;
    HDC hdcBufG;
    HBITMAP hbmC;
    HBITMAP hsbC;
    HBITMAP hbmG;

    DWORD StartMainThreadId;
    HANDLE StartMainHandle;

    vcstreambuf vcsb;
    ostream vc(&vcsb);

    int CEHeight;
    volatile int KeyPressed;

    void printchar(char c);
    void print_n();
    void print_r();
    void print_c(char c);
    LONG WINAPI wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow);

    int vcstreambuf::sync()
    {
        char* s;
        int i;
        s = str();
        for (i = 0; i < pcount();/*out_waiting();*/ i++) {
            printchar(s[i]);
        }
        freeze(0);
        vc.clear();
        vc.seekp(0);
        RedrawWindow(hWndC, NULL, NULL, RDW_INVALIDATE);
        return i;
    }

    void print_n()
    {
        POINT cp;
        GetCurrentPositionEx(hdcBufC, &cp);
        if (cp.y >= CEHeight - vstubCellH) {
            BitBlt(hdcScbC, 0, 0, vstubWidthC, CEHeight - vstubCellH, hdcBufC, 0, vstubCellH, SRCCOPY);
            BitBlt(hdcBufC, 0, 0, vstubWidthC, vstubHeightC, hdcScbC, 0, 0, SRCCOPY);
            MoveToEx(hdcBufC, 1, cp.y, NULL);
        }
        else {
            MoveToEx(hdcBufC, 1, cp.y + vstubCellH, NULL);
        }
    }

    void print_r()
    {
        POINT cp;
        GetCurrentPositionEx(hdcBufC, &cp);
        MoveToEx(hdcBufC, 1, cp.y, NULL);
    }

    void print_c(char c)
    {
        POINT cp;
        GetCurrentPositionEx(hdcBufC, &cp);
        if (cp.x >= vstubWidthC - 8) {
            print_n();
        }
        TextOut(hdcBufC, 0, 0, &c, 1);
    }

    void printchar(char c)
    {
        if (c == 0) return;
        else if (c == '\n') print_n();
        else if (c == '\r') print_r();
        else print_c(c);
    }

    void drawgrid()
    {
        int i;
        setcolor(64, 64, 64);
        for (i = 10; i < vstubWidthG; i += 10) {
            putline(i, 0, i, vstubHeightG);
        }
        for (i = 10; i < vstubHeightG; i += 10) {
            putline(0, i, vstubWidthG, i);
        }
        setcolor(96, 96, 96);
        putline(vstubWidthG / 2, 0, vstubWidthG / 2, vstubHeightG);
        drawline(0, vstubHeightG / 2, vstubWidthG, vstubHeightG / 2);
    }

    void setcolor(unsigned char r, unsigned char g, unsigned char b)
    {
        HPEN hpen;
        hpen = CreatePen(PS_SOLID, 0, RGB(r, g, b));
        hpen = (HPEN)SelectObject(hdcBufG, hpen);
        if (hpen != NULL)
            DeleteObject(hpen);
    }

    void putline(int x1, int y1, int x2, int y2)
    {
        MoveToEx(hdcBufG, x1, y1, NULL);
        LineTo(hdcBufG, x2, y2);
    }
    void drawline(int x1, int y1, int x2, int y2)
    {
        putline(x1, y1, x2, y2);
        RedrawWindow(hWndG, NULL, NULL, RDW_INVALIDATE);
    }

    void putpixel(int x, int y)
    {
        MoveToEx(hdcBufG, x, y, NULL);
        LineTo(hdcBufG, x + 1, y);
    }
    void drawpixel(int x, int y) {
        putpixel(x, y);
        RedrawWindow(hWndG, NULL, NULL, RDW_INVALIDATE);
    }

    void putarc(int x, int y, int radius, float StartAngle, float SweepAngle)
    {
        if (SweepAngle > 2 * 3.141592654 - 0.00001) {
            Arc(hdcBufG, x - radius, y - radius, x + radius, y + radius, 1, 0, 1, 0);
        }
        else {
            Arc(hdcBufG, x - radius, y - radius, x + radius, y + radius, (int)(50000.0 * cos(StartAngle)), -(int)(50000.0 * sin(StartAngle)), (int)(50000.0 * cos(StartAngle + SweepAngle)), -(int)(50000.0 * sin(StartAngle + SweepAngle)));
        }
        RedrawWindow(hWndG, NULL, NULL, RDW_INVALIDATE);
    }
    void drawarc(int x, int y, int radius, float StartAngle, float SweepAngle)
    {
        putarc(x, y, radius, StartAngle, SweepAngle);
        RedrawWindow(hWndG, NULL, NULL, RDW_INVALIDATE);
    }

    void TFlush(void)
    {
        //	cout.flush();
        vc.flush();
        RedrawWindow(hWndC, NULL, NULL, RDW_INVALIDATE);
    }
    void GFlush(void)
    {
        RedrawWindow(hWndG, NULL, NULL, RDW_INVALIDATE);
    }

    int vgetchar()
    {
        int t;
        TFlush();
        GFlush();
        while (!KeyPressed);
        t = KeyPressed;
        KeyPressed = 0;
        return t;
    }

    DWORD WINAPI StartMain(LPVOID lpParameter)
    {
        int t;
        t = main();
        ExitThread(t);
        return (t);
    }



    LONG WINAPI wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
    {
        HDC hdc;
        PAINTSTRUCT ps;
        switch (msg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:
            if (hWnd == hWndC) {
                hdc = BeginPaint(hWnd, &ps);
                BitBlt(hdc, 0, 0, vstubWidthC, vstubHeightC, hdcBufC, 0, 0, SRCCOPY);
                EndPaint(hWnd, &ps);
            }
            else if (hWnd == hWndG) {
                hdc = BeginPaint(hWnd, &ps);
                BitBlt(hdc, 0, 0, vstubWidthG, vstubHeightG, hdcBufG, 0, 0, SRCCOPY);
                EndPaint(hWnd, &ps);
            }
            else
                break;
            return 0;
        case WM_KEYDOWN:
            KeyPressed = wParam;
            return 0;
        }
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

//int  WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       cmdShow)
{

    static char winMName[] = "CPP Multiple Inheritance Task";
    static char win1Name[] = "Console";
    static char win2Name[] = "Graphic";
    WNDCLASS wc;
    MSG msg;
    HDC hdc;
    HFONT hfnt;
    DWORD ThreadExitCode;

    wc.style = 0;
    wc.lpfnWndProc = (WNDPROC)std::wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = winMName;

    RegisterClass(&wc);
    std::hWndMAIN = CreateWindowEx(0, winMName, winMName, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, std::vstubWidth + 12, std::vstubHeight + 36, HWND_DESKTOP, NULL, hInstance, NULL);
    ShowWindow(std::hWndMAIN, cmdShow);
    UpdateWindow(std::hWndMAIN);

    wc.style = 0;
    wc.lpfnWndProc = (WNDPROC)std::wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = win1Name;
    RegisterClass(&wc);

    std::hWndC = CreateWindowEx(0, win1Name, win1Name, WS_CHILD | WS_CLIPSIBLINGS, 2, 2, std::vstubWidthC, std::vstubHeightC, std::hWndMAIN, NULL, hInstance, NULL);
    hdc = GetDC(std::hWndC);
    std::hdcBufC = CreateCompatibleDC(hdc);
    std::hdcScbC = CreateCompatibleDC(hdc);
    std::hbmC = CreateCompatibleBitmap(hdc, std::vstubWidthC, std::vstubHeightC);
    std::hsbC = CreateCompatibleBitmap(hdc, std::vstubWidthC, std::vstubHeightC);
    SelectObject(std::hdcBufC, std::hbmC);
    SelectObject(std::hdcScbC, std::hsbC);
    ReleaseDC(std::hWndC, hdc);
    ShowWindow(std::hWndC, cmdShow);
    UpdateWindow(std::hWndC);

    wc.style = 0;
    wc.lpfnWndProc = (WNDPROC)std::wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = win2Name;
    RegisterClass(&wc);

    std::hWndG = CreateWindowEx(0, win2Name, win2Name, WS_CHILD | WS_CLIPSIBLINGS, std::vstubWidthC + 4, 2, std::vstubWidthG, std::vstubHeightG, std::hWndMAIN, NULL, hInstance, NULL);
    hdc = GetDC(std::hWndG);
    std::hdcBufG = CreateCompatibleDC(hdc);
    std::hbmG = CreateCompatibleBitmap(hdc, std::vstubWidthG, std::vstubHeightG);
    SelectObject(std::hdcBufG, std::hbmG);
    ReleaseDC(std::hWndG, hdc);
    ShowWindow(std::hWndG, cmdShow);
    UpdateWindow(std::hWndG);

    std::CEHeight = std::vstubHeightC - (std::vstubHeightC % std::vstubCellH);

    SetMapMode(std::hdcBufC, MM_TEXT);
    SetBkColor(std::hdcBufC, RGB(0, 0, 0));
    SetTextColor(std::hdcBufC, std::vstubTextColor);
    hfnt = (HFONT)GetStockObject(OEM_FIXED_FONT);
    SelectObject(std::hdcBufC, hfnt);
    SetTextAlign(std::hdcBufC, TA_UPDATECP);
    MoveToEx(std::hdcBufC, 1, 1, NULL);

    //  cout = vc;
    std::setcolor(255, 255, 0);
    std::KeyPressed = 0;

    std::StartMainHandle = CreateThread(NULL, 0, std::StartMain, NULL, 0, &std::StartMainThreadId);
    if (std::StartMainHandle == NULL)
        return 66;
    SetThreadPriority(std::StartMainHandle, THREAD_PRIORITY_BELOW_NORMAL);

    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        GetExitCodeThread(std::StartMainHandle, &ThreadExitCode);
        if (ThreadExitCode != STILL_ACTIVE) {
            CloseHandle(std::StartMainHandle);
            return (ThreadExitCode);
        }
    }
    TerminateThread(std::StartMainHandle, 0);
    CloseHandle(std::StartMainHandle);
    return msg.wParam;

}

