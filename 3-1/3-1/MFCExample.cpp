#include "pch.h"
#include <iostream>
#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	static LPCTSTR szAppName = "EasyText";
	static LPCTSTR szTitleName = "Practice";

	MSG msg;
	WNDCLASSEX WndClass;

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbWndExtra = 0;
	WndClass.cbClsExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(0, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = szAppName;
	WndClass.hIconSm = 0;

	RegisterClassEx(&WndClass);


	HWND hwnd = CreateWindow(
		szAppName,
		szTitleName,
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

	while(GetMessage(&msg,0,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message,WPARAM wParam, LPARAM lParam)
{
	POINT MousePoint;
	HDC hdc;
	RECT rect;
	PAINTSTRUCT ps;
	LPCTSTR szMsg1 = "I love Window Programming!";
	LPCTSTR szMsg2 = "키보드가 눌렸습니다.";
	LPCTSTR szMsg3 = "키보드가 떼어졌습니다.";
	LPCTSTR szMsg4 = "마우스가 눌렸습니다.";
	LPCTSTR szMsg5 = "마우스가 이동중입니다.";
	LPSTR szMsg6 = new char[10];
	

	switch(message)
	{
	case WM_CREATE:
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 10, 10, szMsg1, strlen(szMsg1));
		EndPaint(hwnd, &ps);
		break;

	case WM_KEYDOWN:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, szMsg2, strlen(szMsg2), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hwnd, hdc);
		break;

	case WM_KEYUP:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, szMsg3, strlen(szMsg3), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		break;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		MousePoint.x = LOWORD(lParam);
		MousePoint.y = HIWORD(lParam);
		wsprintf(szMsg6, "X:%ld, Y:%ld", MousePoint.x, MousePoint.y);
		TextOut(hdc, MousePoint.x, MousePoint.y, szMsg6, strlen(szMsg6));

		GetClientRect(hwnd, &rect);
		DrawText(hdc, szMsg4, strlen(szMsg4), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hwnd, hdc);
		break;

	case WM_LBUTTONUP:
		InvalidateRect(hwnd, 0, TRUE);
		break;
		
	case WM_MOUSEMOVE:
		hdc = GetDC(hwnd);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, szMsg5, strlen(szMsg5), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		ReleaseDC(hwnd, hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

