#include "VZEngine/Collisions/Collision.h"
#include "VZEngine/Graphics/ShaderProgram.h"
#include "VZEngine/Graphics/Mesh.h"
#include "VZEngine/Graphics/Material.h"
#include "GL/glew.h"

Collision::Collision(Vector3 Location, Vector3 Offset)
{
	Transform.Location = Location;
	this->Offset = Offset;
	DebugMesh = nullptr;
	DebugShader = nullptr;
	cout << "Creating collision." << endl;
}

Collision::~Collision()
{
	DebugMesh = nullptr;
	DebugShader = nullptr;

	cout << "Collision Destroyed." << endl;
}

BoxCollision::BoxCollision(Vector3 Location, Vector3 Offset, Vector3 Dimensions) : Collision(Location, Offset)
{
	this->Dimensions = Dimensions;

	//find the min and max vectors in world space for this box
	Min = FindCenter() - (Dimensions / 2.0f);
	Max = FindCenter() + (Dimensions / 2.0f);
}

BoxCollision::~BoxCollision()
{
}

bool BoxCollision::IsOverLapping(Collision& OtherCol)
{
	const BoxCollision& OtherBox = dynamic_cast<BoxCollision&>(OtherCol);

	//return true if the box is within the other box
	//are the minimum values higher than the max and visa versa
	return(
		OtherBox.Min.x <= Max.x &&
		OtherBox.Max.x >= Min.x &&

		OtherBox.Min.y <= Max.y &&
		OtherBox.Max.y >= Min.y &&

		OtherBox.Min.z <= Max.z &&
		OtherBox.Max.z >= Min.z
		);
}

Vector3 BoxCollision::FindCenter()
{
	return Transform.Location + Offset;
}

void BoxCollision::DebugDraw(Vector3 Colour)
{
	//if there is no debug mesh then create one
	if (DebugMesh == nullptr) {
		//make a wireframe shader
		DebugShader = make_shared<ShaderProgram>();
		DebugShader->InitVFShader({
			L"Game/Shaders/WireframeShader/WireframeShader.svert",
			L"Game/Shaders/WireframeShader/WireframeShader.sfrag"
			});

		//create a box
		DebugMesh = make_shared<Mesh>();
		if (!DebugMesh->CreateSimpleShape(GeometricShapes::Cube, DebugShader, 0)) {
			DebugMesh = nullptr;
			DebugShader = nullptr;
			return;
		}

		//craete a material and remove maps
		DebugMaterial = make_shared<Material>();
		DebugMaterial->BaseColour.TextureV3 = nullptr;
		DebugMaterial->SpecularColour.TextureV3 = nullptr;
		DebugMaterial->EmissiveColour.TextureV3 = nullptr;

	}

	//convert current rendering mode into line mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//transform the debug mesh to fit the collision values
		DebugMesh->Transform.Location = FindCenter();
		DebugMesh->Transform.Rotation = Transform.Rotation;
		DebugMesh->Transform.Scale = Dimensions / 2.0f;
		//draw the mesh
		DebugMesh->Draw(DebugMaterial);
		//change the volour of the debug wireframe mesh
		DebugShader->RunShader();
		DebugShader->SetVector3("InColour", Colour);
	//return to the default draw mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void BoxCollision::SetLocation(Vector3 NewLocation)
{
	Collision::SetLocation(NewLocation);

	//update the min and max with the new location
	Min = FindCenter() - (Dimensions / 2.0f);
	Max = FindCenter() + (Dimensions / 2.0f);
}

void BoxCollision::SetDimensions(Vector3 NewDimensions)
{
	//Set the dimensions to the new dimensions
	Dimensions = NewDimensions;
	//update the min and max with the new dimentsions
	Min = FindCenter() - (Dimensions / 2.0f);
	Max = FindCenter() + (Dimensions / 2.0f);
}
