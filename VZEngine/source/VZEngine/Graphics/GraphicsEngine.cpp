#include "VZEngine/Graphics/GraphicsEngine.h"
#include "GL/glew.h"
#include "VZEngine/Graphics/Mesh.h"
#include "VZEngine/Graphics/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "VZEngine/Graphics/texture.h"

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireFrameMode = false;
	EngineDefaultCam = Vector3(0.0f, 0.0f, -2.0f);
}

GraphicsEngine::~GraphicsEngine()
{
	//clear the mesh stack
	MeshStack.clear();

	//clear shader
	Shader = nullptr;

	//remove textures from memory
	TextureStack.clear();

	//this will handle deleting the SDL window frome memory
	SDL_DestroyWindow(SdlWindow);
	//destory the GL context for SDL
	SDL_GL_DeleteContext(SdlGLContext);
	//close the sdl frameworl
	SDL_Quit();

	cout << "Destory Graphics Engine" << endl;
}

bool GraphicsEngine::InitGE(const char* WTitle, bool bFullscreen, int WWidth, int WHeight)
{
	//make sure SDL initialises
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL failed" << SDL_GetError() << endl;
		return false;
	}
	//use OpenGl 4.6 and set dafault attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	// set the fullscreen flag
	int FullscreenFlag = 0;

	if (bFullscreen)
	{
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;
	}
	else {
		FullscreenFlag = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;
	}

	//create the SDL2 window

	SdlWindow = SDL_CreateWindow(
		WTitle,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WWidth, WHeight,
		FullscreenFlag
	);

	if (SdlWindow == nullptr)
	{
		cout << "SDL window failed: " << SDL_GetError() << endl;
		return false;
	}
	
	//add all the gl attributes to the window
	SdlGLContext = SDL_GL_CreateContext(SdlWindow);
	if (SdlGLContext == NULL)
	{
		cout << "SDL GL Context failed: " << SDL_GetError() << endl;
		return false;
	}

	//to make glew work we need to mark experimental true
	glewExperimental = GL_TRUE;

	const GLenum InitGLEW = glewInit();

	if (InitGLEW != GLEW_OK)
	{
		cout << "GLEW failed: " << glewGetErrorString(InitGLEW) << endl;
		return false;
	}

	//enable 3D depth
	glEnable(GL_DEPTH_TEST);

	return true;
}

void GraphicsEngine::PresentGraphics()
{
	//present the new graphics using openGL
	SDL_GL_SwapWindow(SdlWindow);
}

void GraphicsEngine::ClearGraphics()
{
	//set the background colour
	glClearColor(0.23f, 0.38f, 0.47f, 1.0f);

	//clear screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{
	ClearGraphics();

	HandleWireFrameMode(false);

	for (MeshPtr LMesh : MeshStack) {
		LMesh->Draw();
	}

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

MeshPtr GraphicsEngine::CreateSimpleMeshShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures)
{
	//initialise a new mesh class
	MeshPtr NewMesh = make_shared<Mesh>();

	//make sure it worked
	if (!NewMesh->CreateSimpleShape(Shape, MeshShader, MeshTextures))
		return  nullptr;

	//add mesh into the stack of meshes to be rendered
	MeshStack.push_back(NewMesh);

	return NewMesh;
}

ShaderPtr GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
	//create a new shader class
	ShaderPtr NewShader = make_shared<ShaderProgram>();

	//initialise the shader into openGL using the file paths
	NewShader->InitVFShader(ShaderFilePaths);

	//add the shader to out graphics engine
	Shader = NewShader;

	return NewShader;

}

TexturePtr GraphicsEngine::CreateTexture(const char* FilePath)
{
	TexturePtr NewTexture = nullptr;

	//Run Through all the textures and check if one with the same path exits
	for (TexturePtr TestTexture : TextureStack)
	{
		//if we find a texture with the same file path
		if (TestTexture->GetFilePath() == FilePath)
		{
			//pass in the already created texture
			NewTexture = TestTexture;
			cout << "Texture found! Assigning current texture." << endl;
			break;
		}
	}

	//if there is no texture already in existance
	if (NewTexture == nullptr)
	{
		cout << " Creating new texture..." << endl;

		//create a new texture as a shard_ptr
		NewTexture = make_shared <Texture>();

		//if the file was found assign it to the texture stack
		if (NewTexture->CreateTextureFromFilePath(FilePath)){
			cout << "Texture "
				<< NewTexture->GetID()
				<< " creaeting success!Adding to Texture Stack." 
				<< endl;

			//add the texture to the texture stack
			TextureStack.push_back(NewTexture);
		}
	}

	return NewTexture;
}

void GraphicsEngine::ApplyScreenTransformation(ShaderPtr Shader)
{
	//angle of the camera planes - basically your zoom
	float FOV = 70.f;
	//position of the camera/view space
	Vector3 ViewPosition = EngineDefaultCam;
	//find the size of the screen and calculate the aspect ration
	int WWidth, WHeight = 0;
	//use sdl to get the size of the window
	SDL_GetWindowSize(SdlWindow, &WWidth, &WHeight);
	//calculate the aspects ratio from the window size
	float AR = static_cast<float>(WWidth) / static_cast<float>(max(WHeight, 1));

	//create the default coordinates for the projection and view
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	//update the coordinates for 3D
	view = glm::translate(view, ViewPosition);
	//create the perspective view to allow us to see in 3D
	//also adjusting the newar and far clip
	projection = glm::perspective(glm::radians(FOV), AR, 0.01f, 1000.0f);
	
	Shader->SetMat4("view", view);
	Shader->SetMat4("projection", projection);


}

void GraphicsEngine::HandleWireFrameMode(bool bShowWireFrameMode)
{
	// if wireframe is set, change it
	if (bShowWireFrameMode != bWireFrameMode)
	{
		bWireFrameMode = bShowWireFrameMode;

		//change how openGl renders between the vertices
		if (bWireFrameMode)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}

		cout << "Wireframe Mode Updated..." << endl;
	}
}
