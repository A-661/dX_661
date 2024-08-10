#include <Windows.h>
#include <iostream>

int CALLBACK WinMain(        // callback is a function modifier that tells to use another calling convention (stdcall)
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance, //always equals NULL
	LPSTR lpCmdLine,
	int nCmdShow)
{
	const wchar_t* pClassName = L"class name xdddddd";       // idk why the wchar_t*, thats better than "auto"
	// register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;              // Allocates a unique device context for each window in the class.
	wc.lpfnWndProc = DefWindowProc;   // window procedure
	wc.cbClsExtra = 0;                // 0 extra bytes in class structure
	wc.cbWndExtra = 0;                // 0 extra bytes for every window of this class
	wc.hInstance = hInstance;         // window class instance
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;        // we have no menu, have no icons etc.
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);             // ptr to our configuration
	// create window instance
	HWND hWnd = CreateWindowEx(
		0, pClassName, L"Window name ig", WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, // play with styles
		700, 200, //position
		800, 600, //resolution
		nullptr, nullptr, hInstance, nullptr
	);
	// show window(kinda drawcall)
	ShowWindow(hWnd, SW_SHOW);
	while (true);              // welp :(  thats better than nothing
	return 0;
}

