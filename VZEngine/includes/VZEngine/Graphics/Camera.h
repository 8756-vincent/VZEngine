#pragma once
#include "VZEngine/Math/Transformation.h"
#include "VZEngine/CoreMinimal.h"
struct STCameraData
{
	//speed of camera
	float Speed = 5.0f;
	//view space we can see in degress
	float FOV=60.0f;

	//how close can models get to the camera before disppearing
	float NearClip = 0.01f;
	//opposit of near clip
	float FarClip = 1000.0f;

	float LookSensitivity = 20.0f;
};

class Camera {
public:
	Camera();

	//move camera in 3D space
	void Translate(Vector3 Location);
	void FOV(float FOVIncrease);

	void AddMovementInput(Vector3 Direction);

	//return the transform data
	CTransform GetTransform() const {return Transform; }

	//return the current facing directions
	CDirection GetDirection() const { return Directions; }

	//return extra camera info
	STCameraData GetCameraData() const { return CameraData; }

	//return a view matrix that considers postion and 
	glm::mat4 GetViewMatrix() const;

	//Rotate the camera based on yaw
	void RotatePitch(float Amount);
	
	//Rotate the camera based on yaw
	void RotateYaw(float Amount);

private:

	//find the current direction vectors based on the roation 
	void UpdateDirectionVectors();

private:
	
	//transforms of the camera
	//Location, Roation, Scale - we dont need that
	CTransform Transform;

	//Forward, Right and Up Direction
	CDirection Directions;

	//hold all the extra camera info
	STCameraData CameraData;

};