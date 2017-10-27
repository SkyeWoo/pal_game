#include "common.h"
#include "Controller.h"

Controller *g_pController;

extern LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
extern void Init(HWND hWnd);
extern void Destroy();

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE phInst, LPSTR CmdLine, int CmdShow) {
	srand(time(NULL));	// 利用时间设置随机种子产生随机数
	WNDCLASSEX wcs;
	HWND hWnd;
	MSG msg;
	LPCWSTR appName = L"pal_game";

	wcs.cbClsExtra = 0;
	wcs.cbSize = sizeof(WNDCLASSEX);
	wcs.cbWndExtra = 0;
	wcs.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcs.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcs.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcs.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wcs.hInstance = hInst;
	wcs.lpfnWndProc = WndProc;
	wcs.lpszClassName = appName;
	wcs.lpszMenuName = NULL;
	wcs.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wcs))
	{
		MessageBox(NULL, L"注册窗口类失败!", L"错误", MB_OK);
		return 0;
	}

	hWnd = CreateWindowEx(WS_EX_APPWINDOW, appName, appName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX& ~WS_THICKFRAME, CW_USEDEFAULT, CW_USEDEFAULT,
		810, 638, GetDesktopWindow(), NULL, hInst, NULL);
	if (FAILED(hWnd))
	{
		MessageBox(NULL, L"创建窗口失败!", L"错误", MB_OK);
		return 0;
	}

	Init(hWnd);

	::ShowWindow(hWnd, SW_SHOWDEFAULT);
	::UpdateWindow(hWnd);

	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (g_pController != nullptr)
			{
				g_pController->RenderScene();
				Sleep(10);
			}
		}
	}

	UnregisterClass(appName, wcs.hInstance);
	Destroy();
	return 0;
}

void Init(HWND hWnd)
{
	if (g_pController == nullptr)
	{
		g_pController = new Controller(hWnd);
	}
}

void Destroy()
{
	if (g_pController != nullptr)
	{
		delete g_pController;
		g_pController = nullptr;
	}
}

LRESULT WINAPI WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_DESTROY:
		PostQuitMessage(0); return 0; break;
	case WM_KEYUP:
		if (g_pController != nullptr) {
			if (wParam == VK_UP)
				g_pController->setGoingUp(false);
			else if (wParam == VK_DOWN)
				g_pController->setGoingDown(false);
			else if (wParam == VK_LEFT)
				g_pController->setGoingLeft(false);
			else if (wParam == VK_RIGHT)
				g_pController->setGoingRight(false);
			else if (wParam == VK_SPACE)
				g_pController->setRoleFire(false);
		}
		break;
	case WM_KEYDOWN:
		if (g_pController != nullptr) {
			static int page = 0;
			switch (wParam) {
			case VK_UP:
				g_pController->setGoingUp(true); break;
			case VK_DOWN:
				g_pController->setGoingDown(true); break;
			case VK_LEFT:
				if (g_pController->getState() == -1) {
					if (--page < 0) page = 10;
					g_pController->flag_intr = page;
				}
				else g_pController->setGoingLeft(true);
				break;
			case VK_RIGHT:
				if (g_pController->getState() == -1) {
					if (++page >= 11) page = 0;
					g_pController->flag_intr = page;
				}
				else g_pController->setGoingRight(true);
				break;
			case VK_SPACE:
				g_pController->setRoleFire(true); break;
			case VK_ESCAPE:
				if (g_pController->getState() == -1)
					g_pController->flag_intr = -1;
				else g_pController->GamePause();
				break;
			case 'R':
				g_pController->ResetRole(); break;
			case 'I':
				g_pController->flag_intr = 0; break;
			case VK_RETURN:
				g_pController->GameStart(); break;
			}
			break;
		}
	case MM_MCINOTIFY:
		break;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}