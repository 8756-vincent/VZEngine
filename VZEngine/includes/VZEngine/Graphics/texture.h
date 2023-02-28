#pragma once
#include "VZEngine/Graphics/texture.h"
#include "VZEngine/CoreMinimal.h"

//hold the image data for conversion to the texture file
struct ImportImageData {
	int w = 0;
	int h = 0;
	int channels = 0;
};

class Texture {
public:
	Texture();
	~Texture();

	//create texture file from imported image path
	bool CreateTextureFromFilePath(const char* FilePath);

	//return the openGL texture ID
	vzuint GetID() const { return TextureID; }

	//bind  the texture as the current texture in open gl
	void BindTexture();

	//assigns the relvant data to the current loaded texture
	void ActivateTexture();

	//clear the texture in open gl
	static void RestTexture();

	//return the file path
	const char* GetFilePath() const { return FilePath; }

private:
	//hold the ID for the texture in OpenGl
	vzuint TextureID;
	//hold the file path to avoid duplicates
	const char* FilePath;


};