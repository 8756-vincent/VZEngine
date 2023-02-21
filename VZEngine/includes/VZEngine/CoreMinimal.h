#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int vzuint;


class GraphicsEngine;
typedef shared_ptr<GraphicsEngine> GraphicsEnginePtr;

class VertexArrayObject;
typedef VertexArrayObject VAO;
typedef shared_ptr<VAO> VAOPtr;
typedef vector<VAOPtr> VAOStack;

class ShaderProgram;
typedef shared_ptr<ShaderProgram> ShaderPtr;

typedef vector<float> PositionMatrix;
typedef vector<vzuint> IndicesMatrix;

//this structure will handle matrix
struct ShapeData {
	vector<float> PostitionMatrix;
	vector<vzuint> IndicesMatrix;

};


enum class GeometricShapes {
	Triangle = 0,
	Polygon,
	Circle
};

//shtore the parameter required to create a shader program
struct VFShaderParams
{
	const wchar_t* VertexShaderPath;
	const wchar_t* FragmentShaderPath;

};
enum class ShaderTypes {
	Vertex = 0,
	Fragment
};