#include "../include/Graph.h"

#include <queue>
#include <iostream>

Vertex* Graph::getVertex(std::string _name)
{
    if (vertexList.size() == 0) {
        return NULL;
    }
    else {
        for (std::size_t i = 0; i < vertexList.size(); i++) {
            if (vertexList[i].getName() == _name)
                return &vertexList[i];
        }
    }
    return NULL;
}

Graph::Graph(bool isDirected )
{
    directed = isDirected;
}

int Graph::addVertex(std::string _name)
{
    if (getVertex(_name) != NULL) {
        return -1; // Vertex exist
    }
    else {
        vertexList.push_back(Vertex(_name));
        return 0;
    }
}

int Graph::addEdge(std::string firstName, std::string secondName)
{
    Vertex* first = getVertex(firstName);
    Vertex* second = getVertex(secondName);
    if ((first == NULL) || (second == NULL))
        return -2; //Vertex does not exist
    if (directed)
    {
        return first->addEdge(second);
    }
    else
    {
        if (first->getName() > second->getName()) {
            return first->addEdge(second);
        }
        else {
            return second->addEdge(first);
        }

    }

}

int Graph::getPath(std::string firstName, std::string secondName, std::vector<Vertex*>* path)
{
    if (firstName == secondName) {
        printf("%s \n", firstName.c_str());
        return 0;
    }
    Vertex* first = getVertex(firstName);
    Vertex* second = getVertex(secondName);
    if ((first == NULL) || (second == NULL))
        return -2; //Vertex does not exist
    std::queue<Vertex*> foundVertexs;
    foundVertexs.push(first);
    first->setRoot(first);
    bool flag = false;
    Vertex* currentVertex;
    while ((foundVertexs.size() != 0) && (!flag)) {
        currentVertex = foundVertexs.front();
        foundVertexs.pop();
        if (currentVertex->getDeg() != 0) {
            Vertex* currentEdge;
            for (int i = 0; i < currentVertex->getDeg(); i++) {
                currentEdge = currentVertex->getEdge(i);
                if (currentEdge->getRoot() == NULL) {
                    currentEdge->setRoot(currentVertex);
                    if (currentEdge->getName() == secondName) {
                        flag = true;
                    }
                    foundVertexs.push(currentEdge);
                }
            }
        }
        if (!directed) {
            for (size_t i = 0; i < vertexList.size(); i++)
            {
                Vertex* current = vertexList[i].findEdge(currentVertex->getName());
                if (current != NULL) {
                    if (vertexList[i].getRoot() == NULL) {
                        vertexList[i].setRoot(currentVertex);
                        if (vertexList[i].getName() == secondName) {
                            flag = true;
                            break;
                        }
                        foundVertexs.push(&vertexList[i]);
                    }
                }
            }
        }
    }
    if (flag)
    {
        Vertex* current = second;
        while (current != current->getRoot()) {
            path->push_back(current);
            current = current->getRoot();
        }
        printf("%s ---> ", (first->getName()).c_str());
        for (int i = path->size()-1; i > 0; i--) {
            printf("%s ---> ", ((*path)[i]->getName()).c_str());
        }
        printf("%s \n", ((*path)[0]->getName()).c_str());
    }
    for (size_t i = 0; i < vertexList.size(); i++){
        vertexList[i].setRoot(NULL);
    }
    if (flag)
        return 0;
    printf("Path does not exist \n");
    return -1; //Path does not exist
}

void Graph::show()
{
    if (!vertexList.empty()) {
        for (size_t i = 0; i < vertexList.size(); i++) {
            printf("%s :", (vertexList[i].getName()).c_str());
            for (int j = 0; j < vertexList[i].getDeg(); j++) {
                printf("%s ", (vertexList[i].getEdge(j)->getName()).c_str());
            }
            if (!directed)
            {
                for (size_t k = 0; k < vertexList.size(); k++) {
                    Vertex* current = vertexList[k].findEdge(vertexList[i].getName());
                    if(current!= NULL)
                        printf("%s ", (vertexList[k].getName()).c_str());
                }
            }
            printf("\n");
        }
    }
}

Graph::~Graph()
{
    vertexList.clear();
}
