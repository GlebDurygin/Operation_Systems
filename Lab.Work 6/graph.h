#pragma once
#include "edge.h"
#include <list>
#include <queue> 
class graph {
private:
	std::list<vertex*> vertices;
	std::list<edge*> edges;
public:
	void add_vertex(vertex* obj);
	void add_edge(edge* obj);

	void remove_vertex(std::string name);
	void remove_edge(edge* edge);

	vertex* getVertex(std::string name) const;
	vertex* getVertexByState(int state) const;
	edge* getEdge(std::string A, std::string B) const;
	edge* getEdge(std::string name) const;

	int getVerticesSize();
	int getEdgesSize();

	std::list<vertex*> getVertices();
	std::list<std::string> bypass(std::string root);

	std::list<edge*> getEdges();

	bool unique_name(std::string name) const;

	int ford_bellman(std::string start, std::string dest, std::vector<std::string> &path) const;
	~graph();
};