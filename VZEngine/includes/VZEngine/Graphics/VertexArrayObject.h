#pragma once
#include "VZEngine/CoreMinimal.h"

const PositionMatrix TrianglePosition{
	//x		//y		//z
	-0.5f,	-0.5f,	0.0f,	//bottom left
	 0.5f,	-0.5f,	0.0f,	//bottom right
	 0.0f,	 0.5f,	0.0f	//top

};
const IndicesMatrix TriangleIndices{
	0, 1, 2
};

const PositionMatrix PolyPosition{
	//x		//y		//z
	-0.5f,	-0.5f,	0.0f,	//bottom left
	 0.5f,	-0.5f,	0.0f,	//bottom right
	 0.5f,	 0.5f,	0.0f,	//top right
	-0.5f,	 0.5f,	0.0f	//top left

};
const IndicesMatrix PolyIndices{
	0, 3, 1,	// Triangle 1
	3, 2, 1		// Triangle 2
};

const PositionMatrix CirclePosition{
	//x		//y		//z
	-0.5f,	-0.5f,	0.0f,	//bottom left
	 0.5f,	-0.5f,	0.0f,	//bottom right
	 0.5f,	 0.5f,	0.0f,	//top right
	-0.5f,	 0.5f,	0.0f	//top left

	-0.7f,	 0.7f,	0.0f	//top left
	-0.7f,	 0.7f,	0.0f	//top left

};
const IndicesMatrix CircleIndices{
	0, 5, 4,	// Triangle 1
	//1, 1, 1,	// Triangle 2
	//2, 2, 2,	// Triangle 1
	//3, 3, 3,	// Triangle 2
	//0, 3, 1,	// Triangle 1
	//3, 2, 1,	// Triangle 2
};

class VertexArrayObject {
public:
	VertexArrayObject();
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