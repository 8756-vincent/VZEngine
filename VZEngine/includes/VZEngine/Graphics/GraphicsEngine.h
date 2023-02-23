#pragma once
#include "SLD2/SDL.h"
#include "VZEngine/CoreMinimal.h"

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
	void CreateVAO(GeometricShapes Shape);

	//add a new shader
	//@param 1 - Vertex Shader
	//@param 2 - Fragment Shader
	void CreateShader(VFShaderParams ShaderFilePaths);


private:
	//this will hold the window
	SDL_Window* SdlWindow;
	//this will allow opneGL to work in sdl
	SDL_GLContext SdlGLContext;

	// stack all the VAOs
	VAOStack VAOs;

	// handle wireframe mdoe
	void HandleWireFrameMode(bool bShowWireFrameMode);

	//set wireframe
	bool bWireFrameMode;

	//single shader
	ShaderPtr Shader;
};