#pragma once
#include "VZEngine/CoreMinimal.h"
#include "VZEngine/Math/Transformation.h"

struct aiNode;
struct aiScene;
struct aiMesh;

class Model {
public:
	Model();
	~Model();

	//craete a simple shape based on engine shapes
	bool CreateSimpleMesh(GeometricShapes Shape, ShaderPtr ModelShader);
	
	//import a 3d model from a common file type using ASSIMP
	bool ImportMeshFromFile(const char* ImportFilePath, ShaderPtr ModelShader);

	//draw models to the screen
	void Draw();

	//Change the material relevent to the slot index
	//this will error log if the slot doesnt exist
	void SetMaterialBySlot(vzuint SlotIndex, MaterialPtr NewMaterial);
	
	//get a matherila in the material stack if it exist
	MaterialPtr GetMaterialBySlot(vzuint SlotIndex) const;

	//get the directory the model as imported from
	const char* GetFilePath() const { return ModelFilePath; }

private:
	//find all of the mesh in a import file/scene
	void FindAndImportSceneMeshes(aiNode* Node, const aiScene* Scene);

	//convert a mesh from  the importer to our engine mesh calss
	MeshPtr ConvertImportMeshToEngineMesh(aiMesh* ImportMesh, const aiScene* Scene);

public:
	//position, rotation and scale of all the meshes in the model
	CTransform Transform;

private:
	//all the meshes related to this model
	MeshPtrStack MeshStack;

	//all the material relevent to the meshes in this model
	MaterialPtrStack MaterialStack;

	//all the model shader
	ShaderPtr ModelShader;

	//imported file path
	const char* ModelFilePath;
};

