#include <windows.h>
//Like main in a regular c program WinMain uses hInst to get the current frame/window, hPrev for the previous
//LSPRT (not sure about the last 2)
LRESULT CALLBACK WinProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,LPSTR lpcmd,int nShow)
{
    //create text boxk that displays message with an ok button
    //MessageBox(NULL, "First Message", "Temp", MB_OK);

    //Creating a window
    //this is a struct for creating a window
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH) COLOR_WINDOW;
    //seting the cursor
    wc.hCursor = LoadCursor(NULL,IDC_ARROW);
    wc.hInstance = hInst;
    //need the prefix L
    wc.lpszClassName = L"tempWindow";
    wc.lpfnWndProc = WinProc;

    if(!RegisterClassW(&wc))
    {
        return -1;
    }
                                                    //// | combines the window items
    CreateWindowW(L"tempWindow",L"New window name",WS_OVERLAPPED | WS_VISIBLE,100,100,500,500,NULL,NULL,NULL,NULL);

    //need a loop to create the window
    MSG msg = {0};
    while(GetMessage(&msg,NULL,NULL,NULL) )
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }

    return 0;

}

//Another important function ( the window,msg (unsigned int) , and the last 2 are mouse clicks)
LRESULT CALLBACK WinProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    switch(Msg)
    {
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hwnd,Msg,wParam,lParam);

    }

}
