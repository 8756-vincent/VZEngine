#pragma once
#include "VZEngine/CoreMinimal.h"

class Material {
public:
	Material();
	~Material();

	void Draw(ShaderPtr Shader);

	TexturePtr BaseColour;
	
};