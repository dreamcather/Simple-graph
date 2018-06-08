#pragma once
#include "Vertex.h"
class Vertex;
class Graph
{
public:
private:
	bool directed;
	std::vector<Vertex> vertexList;
public:
	Graph(bool isDirected);
	Vertex* getVertex(std::string _name);
	int addVertex(std::string _name);
	int addEdge(std::string firstName, std::string secondName);
	int getPath(std::string firstName, std::string secondName);
	void show();
	~Graph();
};