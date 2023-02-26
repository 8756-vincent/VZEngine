#pragma once
#include "VZEngine/CoreMinimal.h"
const PositionMatrix TrianglePosition{
	//x		//y		//z		//colour
	-0.5f,	-0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	//bottom left
	 0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	//bottom right
	 0.0f,	 0.5f,	0.0f,	0.0f, 0.0f, 1.0f	//top

};
const IndicesMatrix TriangleIndices{
	0, 1, 2
};

const PositionMatrix PolyPosition{
	//x		//y		//z		//colour
	-0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//bottom left
	 0.5f,	-0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//bottom right
	 0.5f,	 0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//top right
	-0.5f,	 0.5f,	0.0f,	1.0f, 1.0f, 0.0f	//top left

};
const IndicesMatrix PolyIndices{
	0, 3, 1,	// Triangle 1
	3, 2, 1		// Triangle 2
};

const PositionMatrix CirclePosition{
	//x		//y		//z
	 0.0f,	 0.0f,	0.0f,	1.0f, 0.0f, 0.0f,	//middle				0

	 //top
	 0.7f,	 0.0f,	0.0f,	1.0f, 1.0f, 0.0f,	//tri-right				1
	 0.5f,	 0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	//tri-right				2

	-0.7f,	 0.0f,	0.0f,	1.0f, 0.0f, 1.0f,	//tri-left 				3
	-0.5f,	 0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	//tri-left 				4

	 0.0f,	 0.7f,	0.0f,	1.0f, 1.0f, 0.0f,	//tri-right				5
	 0.5f,	 0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	//tri-right				6

	 0.0f,	 0.7f,	0.0f,	1.0f, 0.0f, 1.0f,	//tri-left				7
	-0.5f,	 0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	//tri-left				8

	//bottom
	0.7f,	 0.0f,	0.0f,	1.0f, 1.0f, 0.0f,	//tri-right				9
	0.5f,	-0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	//tri-right				10

	-0.7f,	 0.0f,	0.0f,	1.0f, 0.0f, 1.0f,	//tri-left 				11
	-0.5f,	 -0.5f,	0.0f,	1.0f, 1.0f, 0.0f,	//tri-left 				12

	 0.0f,	 -0.7f,	0.0f,	1.0f, 1.0f, 1.0f,	//tri-right				13
	 0.5f,	 -0.5f,	0.0f,	1.0f, 0.0f, 0.0f,	//tri-right				14

	 0.0f,	 -0.7f,	0.0f,	1.0f, 0.0f, 0.0f,	//tri-left				15
	-0.5f,	 -0.5f,	0.0f,	1.0f, 1.0f, 1.0f	//tri-left				16

	

};
const IndicesMatrix CircleIndices{
	0, 1, 2,	// right
	0, 3, 4,	// left
	0, 5, 6,	// right
	0, 7, 8,	// 
	0, 9, 10,	// 
	0, 11, 12,	// 
	0, 13, 14,	// 
	0, 15, 16,	// 
};

const PositionMatrix Circle20Position{
	//x		//y		//z
	 0.0f,	 0.0f,	0.0f,			1.0f, 1.0f, 1.0f,	//middle				0
	 //baseline
	 0.7f,	 0.0f,	0.0f,			1.0f, 0.0f, 0.0f,	//tri-right				1

	 0.6f,	 0.35f,	0.0f,			0.0f, 1.0f, 0.0f,	//tri-right				2
	 0.35f,	 0.6f,	0.0f,			0.0f, 0.0f, 1.0f,	//tri-left 				3

	 //baseline
	 0.0f,	 0.7f,	0.0f,			1.0f, 0.0f, 0.0f,	//tri-left 				4

	-0.35f,	 0.6f,	0.0f,			0.0f, 1.0f, 0.0f,	//tri-right				5
	-0.6f,	 0.35f,	0.0f,			0.0f, 0.0f, 1.0f,	//tri-right				6

	//baseline
	-0.7f,	 0.0f,	0.0f,			1.0f, 0.0f, 0.0f,	//tri-left				7

	//baseline dup
	 0.7f,	 0.0f,	0.0f,			1.0f, 0.0f, 0.0f,	//tri-right				8

	 0.6f,	 -0.35f,	0.0f,			0.0f, 0.0f, 1.0f,	//tri-right				9
	 0.35f,	 -0.6f,	0.0f,			1.0f, 0.0f, 0.0f,	//tri-left 				10

	 //baseline
	 0.0f,	 -0.7f,	0.0f,			0.0f, 1.0f, 0.0f,	//tri-left 				11

	-0.35f,	 -0.6f,	0.0f,			0.0f, 0.0f, 1.0f,	//tri-right				12
	-0.6f,	 -0.35f,	0.0f,			1.0f, 0.0f, 0.0f,	//tri-right				13

	//baseline dup
	-0.7f,	 0.0f,	0.0f,			1.0f, 0.0f, 0.0f,	//tri-left				14



};
const IndicesMatrix Circle20Indices{
	0, 1, 2,	// right
	0, 2, 3,	// left
	0, 3, 4,	// right

	0, 4, 5,	// 
	0, 5, 6,	// 
	0, 6, 7,	// 

	0, 8, 9,	// 
	0, 9, 10,	// 
	0, 10, 11,	// 

	0, 11, 12,	// 
	0, 12, 13,	// 
	0, 13, 14,	// 


};

class VertexArrayObject {
public:
	VertexArrayObject(GeometricShapes ChosenShape);
	~VertexArrayObject();

	void Draw();

private:
	ShapeData Shape;

	//this is our version of unsighed int
	// ID = ID for the VAO
	// VAB = ID for the Vertices
	//EAB = ID for the Indices
	vzuint ID, VAB, EAB;

};