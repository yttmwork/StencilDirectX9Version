#include "Window.h"
#include "DirectX.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	if (InitializeWindow(hInstance, "Stencil", 1280, 720) == false)
	{
		return 0;
	}

	if (InitializeDirectX() == false)
	{
		return 0;
	}

	if (LoadingTexture("Res/Sample01.png") == false)
	{
		ReleaseDirectX();
		return 0;
	}

	bool is_game_end = false;
	while (is_game_end == false)
	{
		MSG msg;

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else 
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else 
		{
			StartRendering();

			RenderingTexture("Res/Sample01.png", 0, 0);

			FinishRendering();
		}
	}

	ReleaseAllTexture();
	ReleaseDirectX();

	return 0;
}
