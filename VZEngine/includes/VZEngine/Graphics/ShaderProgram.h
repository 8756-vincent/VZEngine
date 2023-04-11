#pragma once
#include "VZEngine/CoreMinimal.h"
#include "glm/glm.hpp"

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	//initialise our shader as a vertex fragment shader
	bool InitVFShader(VFShaderParams ShadefilePaths);

	//Run the shader program as the current shader to be interacted with in OpenGL
	void RunShader();

	vzuint GetID() const { return ProgramID; }

	//allow changing mat 4 variables in shader code
	void SetMat4(const char* ShaderVariable, glm::mat4 Value);

	//allow changing integer values in shader code
	void SetInt(const char* ShaderVarName, int Value);

	//change float
	void SetFloat(const char* ShaderVarName, float Value);
	//change vector 3
	void SetVector3(const char* ShaderVarName, glm::vec3 Value);


private:
	//attach the shader to the VAO in openGL
	bool AttachShader(const wchar_t* ShaderFile, ShaderTypes Type);

	//link the shader to OpenGL
	bool Link();


private:
	//openGL will assign as ID to out Shader
	vzuint ProgramID;
	//array that will hold IDs to our unique shaders
	//0 - Vertex
	//1 - Fragment
	vzuint VFShaderIDs[2] = { 0 };

};