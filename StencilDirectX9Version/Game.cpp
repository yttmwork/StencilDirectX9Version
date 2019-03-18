#include <vector>
#include "Game.h"
#include "DirectX.h"

const int AnimationChangeFrame = 5;

std::vector<const char*> CharacterAnimList =
{
	"Res/CharacterRun01.png",
	"Res/CharacterRun02.png",
	"Res/CharacterRun03.png",
	"Res/CharacterRun04.png",
	"Res/CharacterRun05.png",
};

int AnimationFrameCounter = 0;
int AnimationId = 0;

void UpdateCharacter()
{
	AnimationFrameCounter++;

	if (AnimationFrameCounter == AnimationChangeFrame)
	{
		AnimationFrameCounter = 0;
		AnimationId++;
		if (AnimationId >= CharacterAnimList.size())
		{
			AnimationId = 0;
		}
	}
}

void RenderingCharacter()
{
	SetUpStencilRenderState(1, D3DCMPFUNC::D3DCMP_GREATEREQUAL);
	RenderingTexture(CharacterAnimList[AnimationId], 100.0f, 384.0f, 0.0f);
}

void RenderingCharacterShadow()
{
	SetUpStencilRenderState(3, D3DCMPFUNC::D3DCMP_EQUAL);
	RenderingTexture(CharacterAnimList[AnimationId], 100.0f, 384.0f, 0.0f, 0);
}

void RenderingBg()
{
	SetUpStencilRenderState(1, D3DCMPFUNC::D3DCMP_GREATEREQUAL);
	RenderingTexture("Res/BackGround.png", 0.0f, 0.0f, 0.0f);
}

void RenderingMapChip()
{
	SetUpStencilRenderState(3, D3DCMPFUNC::D3DCMP_GREATEREQUAL);
	float first_pos_x = 0.0f;	// マップチップ開始位置(X)
	float first_pos_y = 448.0f;	// マップチップ開始位置(Y)
	float chip_size = 32.0f;	// チップサイズ
	int chip_height_num = 2;	// 縦のチップ数
	int chip_width_num = 16;	// 横のチップ数

	for (int i = 0; i < chip_height_num; i++)
	{
		for (int j = 0; j < chip_width_num; j++)
		{
			RenderingTexture("Res/MapChip.png", first_pos_x + (chip_size * j), first_pos_y + (chip_size * i), 0.0f);
		}
	}
}