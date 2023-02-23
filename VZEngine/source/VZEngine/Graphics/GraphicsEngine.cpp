#include "VZEngine/Graphics/GraphicsEngine.h"
#include "GL/glew.h"
#include "VZEngine/Graphics/VertexArrayObject.h"
#include "VZEngine/Graphics/ShaderProgram.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GraphicsEngine::GraphicsEngine()
{
	SdlWindow = nullptr;
	SdlGLContext = NULL;
	bWireFrameMode = false;
}

GraphicsEngine::~GraphicsEngine()
{
	cout << "Destory Graphics Engine" << endl;
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
	//use OpenGl 3.1 and se dafault attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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

	}

	//to make glew work we need to mark experimental true
	glewExperimental = GL_TRUE;

	const GLenum InitGLEW = glewInit();

	if (InitGLEW != GLEW_OK)
	{
		cout << "GLEW failed: " << glewGetErrorString(InitGLEW) << endl;
		return false;
	}

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
	glClear(GL_COLOR_BUFFER_BIT);
}

void GraphicsEngine::Draw()
{
	ClearGraphics();

	HandleWireFrameMode(false);

	vzuint index = 0;



	for (VAOPtr VAO : VAOs) {
		Shader->RunShader();

		//move the object
		glm::mat4 transform = glm::mat4(1.0f);

		//0-triangle
		//1-poly
		//2-circle
		if (index == 0)
		{
			transform = glm::translate(transform, glm::vec3(0.5f, 0.0, 0.0f));
			//radians is rotation amount
			//vec3 is the direction to totate in
			transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));

		}
		else if (index == 1)
		{
			transform = glm::translate(transform, glm::vec3(-0.5f, 0.0, 0.0f));
			//x and y will work for our 2D shapes
			//z must be larger than - or you wont see the objects (1 is dafault)
			transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
		}

		Shader->SetMat4("transform", transform);


		//draw each VAO
		VAO->Draw();

		index++;
	}

	index = 0;

	PresentGraphics();
}

SDL_Window* GraphicsEngine::GetWindow() const
{
	return SdlWindow;
}

void GraphicsEngine::CreateVAO(GeometricShapes Shape)
{
	VAOPtr NewVAO = make_shared<VAO>(GeometricShapes::Triangle);

	VAOs.push_back(NewVAO);
}

void GraphicsEngine::CreateShader(VFShaderParams ShaderFilePaths)
{
	//create a new shader class
	ShaderPtr NewShader = make_shared<ShaderProgram>();

	//initialise the shader into openGL using the file paths
	NewShader->InitVFShader(ShaderFilePaths);

	//add the shader to out graphics engine
	Shader = NewShader;

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
