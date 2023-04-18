#include "VZEngine/Graphics/Model.h"
#include "VZEngine/Graphics/Mesh.h"
#include "VZEngine/Game.h"
#include "VZEngine/Graphics/Vertex.h"
#include "VZEngine/Collisions/Collision.h"

//ASSIMP HEADERS
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"


Model::Model()
{
	ModelFilePath = "";
	ModelCollsion = nullptr;
}

Model::~Model()
{
	MeshStack.clear();
	MaterialStack.clear();
	ModelShader = nullptr;
}

bool Model::CreateSimpleMesh(GeometricShapes Shape, ShaderPtr ModelShader)
{
	//initialise the mesh
	MeshPtr NewMesh = make_shared<Mesh>();	

	//try to create the simple shape
	if (!NewMesh->CreateSimpleShape(Shape, ModelShader, 0))
		return false;

	//clear the old data if there is any and assign the new mesh data
	MeshStack.clear();
	MaterialStack.clear();
	this->ModelShader = ModelShader;

	//assign the dafault engine material to the first material slot
	MaterialStack.push_back(Game::GetGameInstance().GetDefaultEngineMaterial());

	//assign the mesh to the model mesh stack
	MeshStack.push_back(NewMesh);

	return true;
}

bool Model::ImportMeshFromFile(const char* ImportFilePath, ShaderPtr ModelShader)
{
	this->ModelShader = ModelShader;

	//create an importer using assimp
	Assimp::Importer Importer;
	//attempt to import the new mesh based on the file path using the importer
	const aiScene* Scene = Importer.ReadFile(ImportFilePath, aiProcess_Triangulate);

	//check if the file impoorted correctly
	//!Scene means the file path probably didnt work
	//! //AI_SCENE_FLAGS_INCOMPLETE means the file is probably corrupted or cant be read by ASSIMP
	//! //!Scene->mRootNode means it's also either corrupted or not supported by assimp
	if (!Scene || Scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode)
	{
		cout << "Model | Error importing model from" << ImportFilePath << " - " << Importer.GetErrorString() << endl;
		return false;
	}

	//assign the model shader
	this->ModelShader = ModelShader;

	//save the file path
	ModelFilePath = ImportFilePath;

	//find and impot all of the meshes using the imported scene
	FindAndImportSceneMeshes(Scene->mRootNode, Scene);

	//run through all the new material slots and assign the default material
	for (vzuint i = 0; i < MaterialStack.size(); i++) {
		MaterialStack[i] = Game::GetGameInstance().GetDefaultEngineMaterial();
	}

	return true;
}

void Model::Draw()
{
	if (ModelCollsion != nullptr) {
		ModelCollsion->SetLocation(Transform.Location);
	}

	//cycle through the meshes and draw each one
	for (MeshPtr LMesh : MeshStack) {

		//assign the model transformations to the model
		LMesh->Transform = this->Transform;

		//draw the mesh using the material slot it has been assign
		LMesh->Draw(MaterialStack[LMesh->GetMaterialSlot()]);

	}
}

void Model::SetMaterialBySlot(vzuint SlotIndex, MaterialPtr NewMaterial)
{
	//check if the index is valid to the array
	if (MaterialStack.size() <= SlotIndex)
	{
		cout << "Model | No Material slot exists of that index." << endl;
		return;
	}

	//reassign the array item
	MaterialStack[SlotIndex] = NewMaterial;
}

MaterialPtr Model::GetMaterialBySlot(vzuint SlotIndex) const
{
	//check if the index is valid to the array
	if (MaterialStack.size() <= SlotIndex)
	{
		cout << "Model | No Material slot exists of that index." << endl;
		return nullptr;
	}

	return MaterialStack[SlotIndex];
}

CollisionPtr Model::AddCollisionToModel(Vector3 Dimensions, Vector3 Offset)
{
	ModelCollsion = make_shared<BoxCollision>(Transform.Location, Offset, Dimensions);

	return ModelCollsion;
}


void Model::FindAndImportSceneMeshes(aiNode* Node, const aiScene* Scene)
{
	//run through all of the root node meshes in the root node the scene import those
	for (vzuint i = 0; i < Node->mNumMeshes; i++)
	{
		aiMesh* ImpMesh = Scene->mMeshes[Node->mMeshes[i]];

		//convert the imported mesh to our engines mesh
		MeshPtr ConvertedMesh = ConvertImportMeshToEngineMesh(ImpMesh, Scene);

		//add the new convert mesh into our mesh array
		if (ConvertedMesh != nullptr)
			MeshStack.push_back(ConvertedMesh);

	}


	//check through all meshes that are children of the root meshes
	//wont run if the mesh has no children
	for (vzuint i = 0; i < Node->mNumChildren; i++) {
		FindAndImportSceneMeshes(Node->mChildren[i], Scene);
	}

}

MeshPtr Model::ConvertImportMeshToEngineMesh(aiMesh* ImportMesh, const aiScene* Scene)
{
	//initialise local versions of the mesh vertices and indices
	vector<Vertex> Vertices;
	vector<vzuint> Indices;

	//loop through all of the vertices and store their location, no9rmal value and tex coord
	for (vzuint i = 0; i < ImportMesh->mNumVertices; i++)
	{

		Vertex LVertex;

		//find the position of the vertex
		LVertex.Postion = Vector3(
			ImportMesh->mVertices[i].x,
			ImportMesh->mVertices[i].y,
			ImportMesh->mVertices[i].z
		);

		//find the normal value of the vertex(facing direction)
		LVertex.Normal = Vector3(
			ImportMesh->mNormals[i].x,
			ImportMesh->mNormals[i].y,
			ImportMesh->mNormals[i].z
		);

		//find the texture coordinates of the vertex
		LVertex.TextCoord = Vector2(
			ImportMesh->mTextureCoords[0][i].x,
			ImportMesh->mTextureCoords[0][i].y
		);

		//add the vertex into the vertices array
		Vertices.push_back(LVertex);
	}

	if (Vertices.size() < 3)
	{
		cout << "Model | One of the imported Mesh doesnt have enough Vertices" << ModelFilePath << endl;
		return nullptr;
	}

	//next we find the indices
	//to find the indices we can use a value called faces
	//faces are basically 3 vertices
	for (vzuint i = 0; i < ImportMesh->mNumFaces; i++)
	{
		//store the face
		aiFace Face = ImportMesh->mFaces[i];

		//run through loop to detect of the indices in the face
		for (vzuint j = 0; j < Face.mNumIndices; j++)
		{
			//add each index to the indices array
			Indices.push_back(Face.mIndices[j]);
		}
	}

	//find the assign material slots
	vzuint MaterialIndex = ImportMesh->mMaterialIndex;

	//resize the material stack to whatever the largest material slot index is
	if (MaterialStack.size() < MaterialIndex + 1) {
		//change the size of the array to the largest index + 1
		MaterialStack.resize(MaterialIndex + 1 );
	}

	//create and assign the mesh
	MeshPtr ConvertedMesh = make_shared<Mesh>();

	ConvertedMesh->CreateMesh(Vertices, Indices, ModelShader, MaterialIndex);

	return ConvertedMesh;
}
