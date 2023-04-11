#include "VZEngine/Graphics/Material.h"
#include "VZEngine/Graphics/texture.h"
#include "VZEngine/Graphics/ShaderProgram.h"
#include "VZEngine/Game.h"


Material::Material()
{
	//make sure the base colour can be set to engine dafault
	if (Game::GetGameInstance().GetDefaultEngineTexture() != nullptr) {
		BaseColour.TextureV3 = Game::GetGameInstance().GetDefaultEngineTexture();
		SpceularColour.TextureV3 = Game::GetGameInstance().GetDefaultEngineTexture();
		EmissiveColour.TextureV3 = Game::GetGameInstance().GetDefaultEngineTexture();
	}
	else {
		BaseColour.TextureV3 = SpceularColour.TextureV3 = EmissiveColour.TextureV3 = nullptr;
	}

	EmissiveColour.MultiplierV3 = Vector3(0.1f);
	Shininess = 0.1f;

}

Material::~Material()
{
	BaseColour.TextureV3 = SpceularColour.TextureV3 = EmissiveColour.TextureV3 = nullptr;
}

void Material::Draw(ShaderPtr Shader)
{
	//base colour to shader
	if (BaseColour.TextureV3 != nullptr)
	{
		//activate the texture for slot 0
		BaseColour.TextureV3->ActivateTexture(0);
		//telling the shader to get the texture colour from slot 0
		Shader->SetInt("ImportMat.TColour", 0);
		//bind the texture to opengl
		BaseColour.TextureV3->BindTexture();
	}

	Shader->SetVector3("ImportMat.MColour", BaseColour.MultiplierV3);

	//base colour to shader
	if (SpceularColour.TextureV3 != nullptr)
	{
		//activate the texture for slot 0
		SpceularColour.TextureV3->ActivateTexture(1);
		//telling the shader to get the texture colour from slot 0
		Shader->SetInt("ImportMat.TSpceular", 1);
		//bind the texture to opengl
		SpceularColour.TextureV3->BindTexture();
	}

	Shader->SetVector3("ImportMat.MSpceular", SpceularColour.MultiplierV3);

	//base colour to shader
	if (EmissiveColour.TextureV3 != nullptr)
	{
		//activate the texture for slot 0
		EmissiveColour.TextureV3->ActivateTexture(2);
		//telling the shader to get the texture colour from slot 0
		Shader->SetInt("ImportMat.TEmissive", 2);
		//bind the texture to opengl
		EmissiveColour.TextureV3->BindTexture();
	}

	Shader->SetVector3("ImportMat.MEmissive", EmissiveColour.MultiplierV3);


	Shader->SetFloat("ImportMat.Shininess", Shininess);

}
