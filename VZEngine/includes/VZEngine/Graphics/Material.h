#pragma once
#include "VZEngine/CoreMinimal.h"
#include "VZEngine/Math/Transformation.h"

struct Vec3Texture {
	TexturePtr TextureV3;
	Vector3 MultiplierV3 = Vector3(1.0f);

};

class Material {
public:
	Material();
	~Material();

	void Draw(ShaderPtr Shader);

	Vec3Texture BaseColour;
	Vec3Texture SpecularColour;
	Vec3Texture EmissiveColour;
	
	float Shininess;
};