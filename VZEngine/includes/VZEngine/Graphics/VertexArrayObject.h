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
	-0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	//bottom left
	 0.5f,	-0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	//bottom right
	 0.5f,	 0.5f,	0.0f,	0.0f, 1.0f, 0.0f,	//top right
	-0.5f,	 0.5f,	0.0f,	0.0f, 1.0f, 0.0f	//top left

};
const IndicesMatrix PolyIndices{
	0, 3, 1,	// Triangle 1
	3, 2, 1		// Triangle 2
};

const PositionMatrix CirclePosition{
	//x		//y		//z
	 0.0f,	 0.0f,	0.0f,	//middle				0

	 //top
	 0.7f,	 0.0f,	0.0f,	//				1
	 0.5f,	 0.5f,	0.0f,	//				2

	-0.7f,	 0.0f,	0.0f,	// 				3
	-0.5f,	 0.5f,	0.0f,	// 				4

	 0.0f,	 0.7f,	0.0f,	//				5
	 0.5f,	 0.5f,	0.0f,	//				6

	 0.0f,	 0.7f,	0.0f,	//				7
	-0.5f,	 0.5f,	0.0f,	//				8

	//bottom
	0.7f,	 0.0f,	0.0f,	//				9
	0.5f,	-0.5f,	0.0f,	//				10

	-0.7f,	 0.0f,	0.0f,	// 				11
	-0.5f,	 -0.5f,	0.0f,	// 				12

	 0.0f,	 -0.7f,	0.0f,	//				13
	 0.5f,	 -0.5f,	0.0f,	//				14

	 0.0f,	 -0.7f,	0.0f,	//				15
	-0.5f,	 -0.5f,	0.0f,	//				16

	

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