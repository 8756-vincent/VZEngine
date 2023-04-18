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

class Texture;
typedef shared_ptr<Texture> TexturePtr;
typedef vector<TexturePtr> TexturePtrStack;

class ShaderProgram;
typedef shared_ptr<ShaderProgram> ShaderPtr;

class Mesh;
typedef shared_ptr<Mesh> MeshPtr;
typedef	vector<MeshPtr> MeshPtrStack;

class Model;
typedef shared_ptr<Model> ModelPtr;
typedef	vector<ModelPtr> ModelPtrStack;

class Material;
typedef shared_ptr<Material> MaterialPtr;
typedef	vector<MaterialPtr> MaterialPtrStack;

class Camera;
typedef shared_ptr<Camera> CameraPtr;

class Collision;
typedef shared_ptr<Collision> CollisionPtr;
typedef	vector<CollisionPtr> CollisionPtrStack;

class BoxCollision;
typedef shared_ptr<BoxCollision> BoxCollisionPtr;


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
	Circle,
	Circle20,
	Cube
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