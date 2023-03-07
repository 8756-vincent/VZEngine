#pragma once
#include "VZEngine/CoreMinimal.h"
#include "VZEngine/Math/Transformation.h"

class Mesh {
public:
	Mesh();
	~Mesh();

	//Create the mesh out of VAO, a shader and Texture
	bool CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextues);


	void Draw();

	//This holds the position, rotation and scale of the mesh
	CTransform Transform;

private:
	//store the shader this mesh requires
	ShaderPtr MeshShader;
	//Store the textures this mesh requires
	TexturePtrStack MeshTextures;
	//create a new VAO for the mesh
	VAOPtr MeshVAO;

};