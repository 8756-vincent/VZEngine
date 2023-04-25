#pragma once
#pragma once
#include "VZEngine/CoreMinimal.h"
#include "VZEngine/Math/Transformation.h"

class Collision {
public:
	Collision(Vector3 Location, Vector3 Offset);
	~Collision();

	//detect if two collisions are overlapping
	virtual bool IsOverLapping(Collision& OtherCol) { return false; }

	//Get the center of the collision
	virtual Vector3 FindCenter() { return Vector3(0.0f); }

	//draw a collision for debugging
	virtual void DebugDraw(Vector3 Colour) {  }

	//Transform function
	//set the location of the collision
	virtual void SetLocation(Vector3 NewLocation) { Transform.Location = NewLocation; }
	//update the offset
	virtual void SetOffset(Vector3 NewOffset) { Offset = NewOffset; }
	//set the rotation of the collision
	virtual void SetRotation(Vector3 NewRotation) { Transform.Rotation = NewRotation; }
	//set the roation x of the collision
	virtual void SetRotationX(float Value) { Transform.Rotation.x = Value; }
	//set the roation y of the collision
	virtual void SetRotationY(float Value) { Transform.Rotation.y = Value; }
	//set the roation z of the collision
	virtual void SetRotationZ(float Value) { Transform.Rotation.z = Value; }

protected:
	//transforms for the collision in world space
	CTransform Transform;

	//offset for the center location
	Vector3 Offset;

	//visual mesh for debugging
	MeshPtr DebugMesh;
	ShaderPtr DebugShader;
	MaterialPtr DebugMaterial;
};

class BoxCollision :
	public Collision {
public:
	BoxCollision(Vector3 Location, Vector3 Offset, Vector3 Dimensions);
	~BoxCollision();

	bool IsOverLapping(Collision& OtherCol) override;
	Vector3 FindCenter() override;
	//draw a mesh to the dimension of the box
	//truen the mesh into a wireframe view to not obscure the actual object
	//create the mesh and a shader only if we need to debug the collision
	void DebugDraw(Vector3 Colour) override;
	void SetLocation(Vector3 NewLocation) override;

	//return the size of the box
	Vector3 GetDimensions() const { return Dimensions; }

	//set the diments of the box
	void SetDimensions(Vector3 NewDimensions);

protected:
	//bounding box values
	Vector3 Dimensions;

	//the bouding vectors between the minimum and maximum size of the collision
	Vector3 Min;
	Vector3 Max;
};