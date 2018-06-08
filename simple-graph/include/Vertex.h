#include <vector>
class Vertex
{
private:
	std::string name;
	std::vector<Vertex*> adjancentEdges;
	int deg;
	Vertex* root;
public:
	Vertex(std::string _name);
	std::string getName();
	int getDeg();
	Vertex* getRoot();
	void setRoot(Vertex* tmp);
	Vertex* findEdge(std::string _name);
	int addEdge(Vertex* value);
	Vertex* getEdge(int i);
	~Vertex();
};
