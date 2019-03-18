#include "Window.h"
#include "DirectX.h"
#include "Game.h"
#include <vector>

#define PRACTICE01

void FinishApp()
{
	ReleaseAllTexture();
	ReleaseDirectX();
}

void Practice01()
{
	StartRendering();
	SetUpStencilMaskRenderState(1, D3DCMPFUNC::D3DCMP_ALWAYS);
	RenderingTexture("Res/StencilMask.png", 0, 0, 0);

	SetUpStencilRenderState(1, D3DCMPFUNC::D3DCMP_EQUAL);
	RenderingTexture("Res/Sample01.png", 0, 0, 0);

	FinishRendering();
}

void Practice02()
{
	UpdateCharacter();

	StartRendering();
	
	RenderingBg();
	RenderingCharacter();
	RenderingMapChip();
	RenderingCharacterShadow();
	
	FinishRendering();
}

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmpLine,
	INT       nCmdShow)
{
	std::vector<const char*> file_list = 
	{
		"Res/Sample01.png",
		"Res/StencilMask.png",
		"Res/CharacterRun01.png",
		"Res/CharacterRun02.png",
		"Res/CharacterRun03.png",
		"Res/CharacterRun04.png",
		"Res/CharacterRun05.png",
		"Res/MapChip.png",
		"Res/BackGround.png",
	};

	if (InitializeWindow(hInstance, "Stencil", 512, 512) == false)
	{
		return 0;
	}

	if (InitializeDirectX() == false)
	{
		return 0;
	}

	for (auto itr = file_list.begin(); itr != file_list.end(); itr++)
	{
		if (LoadingTexture((*itr)) == false)
		{
			FinishApp();
			return 0;
		}
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
#ifdef PRACTICE01
			Practice01();
#else
			Practice02();
#endif
		}
	}

	FinishApp();

	return 0;
}
