#include "VZEngine/Graphics/VertexArrayObject.h"
#include "GL/glew.h"


VertexArrayObject::VertexArrayObject(GeometricShapes ChosenShape)
{
	ID = EAB = VAB = 0;

	//localised version of the chosen matrices
	PositionMatrix ChosenPositions = PositionMatrix();
	IndicesMatrix ChosenIndices = IndicesMatrix();


	// 
	switch (ChosenShape)
	{
	case GeometricShapes::Triangle:
		ChosenPositions = TrianglePosition;
		ChosenIndices = TriangleIndices;
		break;
	case GeometricShapes::Polygon:
		ChosenPositions = PolyPosition;
		ChosenIndices = PolyIndices;
		break;
	case GeometricShapes::Circle:
		ChosenPositions = CirclePosition;
		ChosenIndices = CircleIndices;
		break;
	case GeometricShapes::Circle20:
		ChosenPositions = Circle20Position;
		ChosenIndices = Circle20Indices;
		break;
	default:
		break;
	}

	Shape.PostitionMatrix = ChosenPositions;
	Shape.IndicesMatrix = ChosenIndices;

	//Handle the posistions
	//create the ID for our VAO
	glGenVertexArrays(1, &ID);

	//bind the data to this vertex array
	glBindVertexArray(ID);

	// Create an id for our array buffer
	glGenBuffers(1, &VAB);
	//bind the above IDs to the OpenGL
	glBindBuffer(GL_ARRAY_BUFFER, VAB);
	// Run through the data and attach the vertices to VAB
	glBufferData(
		GL_ARRAY_BUFFER,
		Shape.PostitionMatrix.size() * sizeof(float),
		&Shape.PostitionMatrix[0],
		GL_STATIC_DRAW
	);

	//Handle the indices
	//create an id for our element array buffer
	glGenBuffers(1, &EAB);
	//bind the above ID to OpenGL as the element buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EAB);
	//Run through the data attach the indices to the EAB
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		Shape.IndicesMatrix.size() * sizeof(vzuint),
		&Shape.IndicesMatrix[0],
		GL_STATIC_DRAW
	);

	//assign the vertices and indices to the VAO
	glVertexAttribPointer(
		0,					// Date set - 0 = the first data set in the array
		3,					// How many numbers in out matrix to make a triangle
		GL_FLOAT, GL_FALSE, // data type, whether you want to normalise the values
		sizeof(float) * 6,	// stride = the length it takes to get to each numbers
		(void*)0			// offset if how many number to skip in the matrix
	);

	//enable the vertex array
	glEnableVertexAttribArray(0);

	//Assign the colour to the shader
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT, GL_FALSE,
		sizeof(float) * 6,
		(void*)(3 * sizeof(float))
	);

	//enableing the colour array
	glEnableVertexAttribArray(1);


	// clear the buffer
	glBindVertexArray(0);

}

VertexArrayObject::~VertexArrayObject()
{
	// clean up the VAO in OpenGL
	glDeleteVertexArrays(1, &ID);

	// ckean up the vertors
	Shape.PostitionMatrix.clear();
	Shape.IndicesMatrix.clear();

	cout << "Deleted VAO..." << endl;

}

void VertexArrayObject::Draw()
{
	//bind out VAO to the current buffer
	glBindVertexArray(ID);
	// draw the 3D object/VAO
	glDrawElements(
		GL_TRIANGLES,					//what type of objects are we drawing
		Shape.IndicesMatrix.size(),		//how many vertices do we draw
		GL_UNSIGNED_INT,				//what is the type data that's being input
		(void*)0						//how may should we skip?
	);

	//clear the VAO from the current array to allow for the next object
	glBindVertexArray(0);
}
