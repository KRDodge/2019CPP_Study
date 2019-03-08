#include <windows.h>
#include <tchar.h>
#include <process.h>
#include <time.h>

HWND hwnd;
MSG msg;
WNDCLASS WndClass;
HINSTANCE hInst;

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
void ThreadProc(void *arg);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window Class Name");
	RegisterClass(&WndClass);

	hwnd = CreateWindow(
		_T("Window Class Name"),
		_T("Window Title Name"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

HANDLE hEvent;
int max;
void ThreadProc(void *arg) {
	HDC hdc;
	int i;
	int xPos = *((int *)arg);
	srand((unsigned)time(0));
	hdc = GetDC(hwnd);
	SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));

	for (i = 0; i <= 10; ++i)
	{
		int num;
		WaitForSingleObject(hEvent, INFINITE);
		num = rand() % 500;
		if (num > max) 
		{
			Sleep(3000);
			max = num;
			Rectangle(hdc, xPos, 0, xPos + 20, num);
		}
		SetEvent(hEvent);
	}
	ReleaseDC(hwnd, hdc);
	return;
}

#define THREAD_NUM 10

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	static HANDLE hThread[THREAD_NUM]; 
	static int xPos[THREAD_NUM];
	 
	int i;
	switch (iMsg)
	{
	case WM_CREATE:
		for (i = 0; i < THREAD_NUM; ++i) {
			xPos[i] = i * 100;
		}
		max = 0;
		break;

	case WM_LBUTTONDOWN:
		hEvent = CreateEvent(NULL, FALSE, TRUE, NULL);
		for (i = 0; i < THREAD_NUM; ++i)
		{
			hThread[i] = (HANDLE)_beginthreadex(
				NULL,
				0,
				(unsigned int(_stdcall *)(void *))ThreadProc,
				(void *)&xPos[i],
				0,
				NULL
			);
			Sleep(2000);
		}
		WaitForMultipleObjects(THREAD_NUM, hThread, TRUE, INFINITE);
		CloseHandle(hEvent);
		break;

	case WM_DESTROY:
		for (i = 0; i < THREAD_NUM; ++i) {
			CloseHandle(hThread[i]);
		}
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}