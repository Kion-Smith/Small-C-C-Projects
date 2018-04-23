#include <windows.h>
//Like main in a regular c program WinMain uses hInst to get the current frame/window, hPrev for the previous
//LSPRT (not sure about the last 2)
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,LPSTR lpcmd,int nShow)
{
    //create text boxk that displays message with an ok button
    MessageBox(NULL, "First Message", "Temp", MB_OK);
    return 0;

}

//Another important function ( the window,msg (unsigned int) , and the last 2 are mouse clicks)
LRESULT CALLBACK WinProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{


}
