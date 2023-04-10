#include "VZEngine/Graphics/Mesh.h"
#include "VZEngine/Graphics/ShaderProgram.h"
#include "VZEngine/Graphics/Material.h"
#include "VZEngine/Graphics/VertexArrayObject.h"
#include "glm/gtc/matrix_transform.hpp"
#include "VZEngine/Game.h"
#include "VZEngine/Graphics/GraphicsEngine.h"

Mesh::Mesh()
{
	cout << "Mesh | Mesh Initialised Mesh." << endl;

}

Mesh::~Mesh()
{
	MeshShader = nullptr;
	MeshVAO = nullptr;

	cout << "Mesh | Mesh Destoryed." << endl;
}

bool Mesh::CreateSimpleShape(GeometricShapes Shape, ShaderPtr MeshShader, vzuint MaterialSlot)
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
	this->MaterialSlot = MaterialSlot;

	cout << "Mesh | Mesh Created Sucessfully." << endl;

	return true;
}

bool Mesh::CreateMesh(vector<Vertex> vertices, vector<vzuint> Indices, ShaderPtr MeshShader, vzuint MaterialSlot)
{
	cout << "Mesh | Creating Mesh." << endl;

	//Create the VAO
	MeshVAO = make_shared<VAO>(vertices, Indices);

	//validate the mesh was creatd
	if (MeshVAO == nullptr) {
		cout << "MEsh | Mesh failed to be created" << endl;
		return false;
	}

	//
	this->MeshShader = MeshShader;
	this->MaterialSlot = MaterialSlot;

	cout << "Mesh | Mesh Created Sucessfully." << endl;

	return true;
}

void Mesh::Draw(MaterialPtr MeshMaterial)
{
	//activate the shader this mesh uses
	MeshShader->RunShader();

	//Run the material for this mesh
	//activate all the required textures in the material
	if (MeshMaterial != nullptr)
	{
		MeshMaterial->Draw(MeshShader);
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

		MeshShader->SetMat4("model", MatTransform);
	}

	//creates the world and screen transformations for this object
	Game::GetGameInstance().GetGraphicEngine()->ApplyScreenTransformation(MeshShader);

	//draw the vao
	MeshVAO->Draw();

}
