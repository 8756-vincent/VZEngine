#pragma once
#include "VZEngine/CoreMinimal.h"
#include "VZEngine/Math/Transformation.h"

struct Vertex;

class Mesh {
public:
	Mesh();
	~Mesh();

	//Create the mesh out of VAO, a shader and Texture
	bool CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, vzuint MaterialSlot);

	//create a mesh VAo that have a predefined model
	bool CreateMesh(vector<Vertex> vertices, vector<vzuint> Indices, ShaderPtr MeshShader, vzuint MaterialSlot);

	//handle the drawing of all the required classes
	void Draw(MaterialPtr MeshMaterial);

	//return material slot assigned by the model to the mesh
	vzuint GetMaterialSlot() const { return MaterialSlot; }

public:
	//This holds the position, rotation and scale of the mesh
	CTransform Transform;


private:
	//store the shader this mesh requires
	ShaderPtr MeshShader;
	//assign a material slot to the model class
	vzuint MaterialSlot;


	//create a new VAO for the mesh
	VAOPtr MeshVAO;

};