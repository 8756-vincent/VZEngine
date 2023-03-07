#include "VZEngine/Graphics/Mesh.h"
#include "VZEngine/Graphics/ShaderProgram.h"
#include "VZEngine/Graphics/texture.h"
#include "VZEngine/Graphics/VertexArrayObject.h"
#include "glm/gtc/matrix_transform.hpp"

Mesh::Mesh()
{
	cout << "Mesh | Mesh Initialised Mesh." << endl;

}

Mesh::~Mesh()
{
	MeshShader = nullptr;
	MeshTextures.clear();
	MeshVAO = nullptr;

	cout << "Mesh | Mesh Destoryed." << endl;
}

bool Mesh::CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, TexturePtrStack MeshTextures)
{
	cout << "Mesh | Mesh Creating Mesh." << endl;

	//Create the VAO
	MeshVAO = make_shared<VAO>(Shape);

	//validate the mesh was creatd
	if (MeshVAO == nullptr) {
		cout << "MEsh | Mesh failed to be created" << endl;
		return false;
	}

	//
	this->MeshShader = MeshShader;
	this->MeshTextures = MeshTextures;

	cout << "Mesh | Mesh Created Sucessfully." << endl;

	return true;
}

void Mesh::Draw()
{
	//activate the shader this mesh uses
	MeshShader->RunShader();

	//activate the required textures for this mesh
	for (vzuint Index = 0; Index < MeshTextures.size(); Index++) {

		//Activating the texture through openGL
		MeshTextures[Index]->ActivateTexture(Index);
		//setting the textures number as the active texture in the shader
		MeshShader->SetInt("TextureColour", Index);
		//Binding the texture to the shader
		MeshTextures[Index]->BindTexture();

	}

	//initialise a static varible to check if any changes to transform
	static CTransform OldTransform;

	if (Transform != OldTransform)
	{
		OldTransform = Transform;

		glm::mat4 MatTransform = glm::mat4(1.0f);

		// translate - rotate - scale -- in this order
		MatTransform = glm::translate(MatTransform, Transform.Location);

		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.x), Vector3(1.0f, 0.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.y), Vector3(0.0f, 1.0f, 0.0f));
		MatTransform = glm::rotate(MatTransform, glm::radians(Transform.Rotation.z), Vector3(0.0f, 0.0f, 1.0f));

		MatTransform = glm::scale(MatTransform, Transform.Scale);

		MeshShader->SetMat4("transform", MatTransform);
	}


	//draw the vao
	MeshVAO->Draw();

}
