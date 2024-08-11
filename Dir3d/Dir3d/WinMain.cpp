#include <Windows.h>
#include <iostream>
#include <sstream>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {      //custom window proc
	switch (msg) {                           // checks the value of uMsg to determine what action to take based on the type of message received
	case WM_CLOSE:
		PostQuitMessage(661);                   // posts a quit message to the message queue. Exit code
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'F':
			SetWindowText(hWnd, L"Respects");
			break;
		case 'W':
			SetWindowText(hWnd, L"Forward");
			break;
		case 'A':
			SetWindowText(hWnd, L"Left");
			break;
		case 'S':
			SetWindowText(hWnd, L"Backwards");
			break;
		case 'D':
			SetWindowText(hWnd, L"Right");
			break;
		default:
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case 'W':
		case 'A':
		case 'S':
		case 'D':
			SetWindowText(hWnd, L"Not Moving");
			break;
		default:
			SetWindowText(hWnd, L"Window name ig");
			break;
		}
		break;
	/*
	case WM_CHAR:                                       // check buttons with WM_CHAR message
		static std::wstring title;
		title.push_back((char)wParam);
		SetWindowText(hWnd, title.c_str());
		break;
	*/
	case WM_LBUTTONDOWN:                                // LMB message
		POINTS pt = MAKEPOINTS(lParam);                 // x-coordinate is in the low-order word, and the y-coordinate is in the high-order word
		std::wostringstream oss;
		oss << L"Click XY-pos = {" << pt.x << L", " << pt.y << L"}";
		SetWindowText(hWnd, oss.str().c_str());
	// any more WM actions
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int CALLBACK wWinMain(        // callback is a function modifier that tells to use another calling convention (stdcall)
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance, //always equals NULL
	PWSTR lpCmdLine,
	int nCmdShow)
{
	const wchar_t* pClassName = L"class name xdddddd";       // idk why the wchar_t*, thats better than "auto"
	// register window class
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;              // Allocates a unique device context for each window in the class.
	wc.lpfnWndProc = WindowProc;      // window procedure, default: DefWindowProc
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

	// message pump
	MSG msg;
	BOOL gResult;
	while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)              // ptr to message, ptr to window, selection   //if Message != WM_Quit { message processing }
	{
		TranslateMessage(&msg);                 // create WM_CHAR from WM_KEYDOWN
		DispatchMessage(&msg);
	}

	if (gResult == -1) {                        // if error
		return -1;
	}
	else
	{
		return msg.wParam;                     // Exit code
	}
}

