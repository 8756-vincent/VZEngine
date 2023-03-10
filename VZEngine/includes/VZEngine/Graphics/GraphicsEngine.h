#pragma once
#include "SLD2/SDL.h"
#include "VZEngine/CoreMinimal.h"
#include "VZEngine/Math/Transformation.h"

class GraphicsEngine {
public:
	GraphicsEngine();
	~GraphicsEngine();

	//create the window
	bool InitGE(const char* WTitle, bool bFullscreen, int WWidth, int WHeight);

	//show the newest frame graphics
	void PresentGraphics();
	//clear the old frame graphics
	void ClearGraphics();
	
	void Draw();

	//return the sdl window
	SDL_Window* GetWindow() const;

	// add a new vao to the VAOStack using a shape define
	MeshPtr CreateSimpleMeshShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures);

	//add a new shader
	//@param 1 - Vertex Shader
	//@param 2 - Fragment Shader
	ShaderPtr CreateShader(VFShaderParams ShaderFilePaths);

	//create a texture and add it to the texture stack
	//avoid duplicates
	TexturePtr CreateTexture(const char* FilePath);

	//creaete the 3D space for the model to relate itself to
	//screen and camera coordiantes
	void ApplyScreenTransformation(ShaderPtr Shader);

	

private:
	//this will hold the window
	SDL_Window* SdlWindow;
	//this will allow opneGL to work in sdl
	SDL_GLContext SdlGLContext;

	// handle wireframe mdoe
	void HandleWireFrameMode(bool bShowWireFrameMode);

	//set wireframe
	bool bWireFrameMode;

	//single shader
	ShaderPtr Shader;
	//store a vector of textures
	TexturePtrStack TextureStack;

	//Store all meshes in the game
	MeshPtrStack MeshStack;

public:
	//default camera position
	Vector3 EngineDefaultCam;

};