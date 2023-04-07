#include "VZEngine/Graphics/Material.h"
#include "VZEngine/Graphics/texture.h"
#include "VZEngine/Graphics/ShaderProgram.h"
#include "VZEngine/Game.h"


Material::Material()
{
	//make sure the base colour can be set to engine dafault
	if (Game::GetGameInstance().GetDefaultEngineTexture() != nullptr)
		BaseColour = Game::GetGameInstance().GetDefaultEngineTexture();
	else
		BaseColour = nullptr;
}

Material::~Material()
{
	BaseColour = nullptr;
}

void Material::Draw(ShaderPtr Shader)
{
	if (BaseColour != nullptr)
	{
		//activate the texture for slot 0
		BaseColour->ActivateTexture(0);
		//telling the shader to get the texture colour from slot 0
		Shader->SetInt("TextureColour", 0);
		//bind the texture to opengl
		BaseColour->BindTexture();
	}
}
