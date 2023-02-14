#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef unsigned int vzuint;


class GraphicsEngine;
typedef shared_ptr<GraphicsEngine> GraphicsEnginePtr;

class VertexArrayObject;
typedef VertexArrayObject VAO;
typedef shared_ptr<VAO> VAOPtr;
typedef vector<VAOPtr> VAOStack;

typedef vector<float> PositionMatrix;
typedef vector<vzuint> IndicesMatrix;

//this structure will handle matrix
struct ShapeData {
	vector<float> PostitionMatrix;
	vector<vzuint> IndicesMatrix;

};