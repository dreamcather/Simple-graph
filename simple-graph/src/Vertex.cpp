#include "Vertex.h"





Vertex::Vertex(std::string _name)
{
	name = _name;
	root = NULL;
}

std::string Vertex::getName()
{
	return name;
}

int Vertex::getDeg()
{
	return adjancentEdges.size();
}

Vertex * Vertex::getRoot()
{
	return root;
}

void Vertex::setRoot(Vertex * tmp)
{
	root = tmp;
}

Vertex * Vertex::findEdge(std::string _name)
{
	if (adjancentEdges.size() == 0) {
		return NULL;
	}
	else {
		for (int i = 0; i < adjancentEdges.size(); i++) {
			if (adjancentEdges[i]->getName() == _name)
				return adjancentEdges[i];
		}
		return NULL;
	}
}

int Vertex::addEdge(Vertex * value)
{
	if (findEdge(value->getName()) != NULL)
		return -1;
	adjancentEdges.push_back(value);
	return 0;
}

Vertex * Vertex::getEdge(int i)
{
	return adjancentEdges[i];
}

Vertex::~Vertex()
{
	adjancentEdges.clear();
	root = NULL;
}
