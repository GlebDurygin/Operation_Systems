#include "stdafx.h"
#include "graph.h"
#include <algorithm>
#include <iostream>

graph::~graph() {
	vertices.remove_if([](const vertex* vertex) {
		return true;
	});
	edges.remove_if([](const edge* edge) {
		return true;
	});
}

void graph::add_vertex(vertex* obj){
	if (obj == NULL) {
		return;
	}
	vertices.push_back(obj);
}
void graph::add_edge(edge* obj){
	if (obj == NULL) {
		return;
	}
	for (edge* edge : edges) {
		if (*obj == edge) {
			remove_edge(edge);
			
			break;
		}
	}
	edges.push_back(obj);
}

void graph::remove_vertex(std::string name){
	vertices.remove_if([name](const vertex* vertex) {
		return vertex->getName() == name;
	});
}
/*void graph::remove_edge(std::string name_A, std::string name_B){
	edges.remove_if([name_A, name_B](const edge* edge) {
		return (edge->getA()->getName() == name_A && edge->getB()->getName() == name_B) 
				|| (edge->getA()->getName() == name_B && edge->getB()->getName() == name_A);
	});
}*/
void graph::remove_edge(edge* _edge) {
	edges.remove_if([_edge](const edge* edge) {
		return *_edge == edge;
	});
}

int graph::getVerticesSize() {
	return vertices.size();
}
int graph::getEdgesSize() {
	return edges.size();
}

vertex* graph::getVertex(std::string name) const {
	for (auto vertex : vertices) {
		if (vertex->getName() == name) {
			return vertex;
		}
	}

	return NULL;
}
vertex* graph::getVertexByState(int state) const {
	for (auto vertex : vertices) {
		if (vertex->getState() == state) {
			return vertex;
		}
	}

	return NULL;
}
edge* graph::getEdge(std::string A, std::string B) const {
	for (auto edge : edges) {
		if ((edge->getA()->getName() == A && edge->getB()->getName() == B) ||
			(edge->getA()->getName() == B && edge->getB()->getName() == A)) {
			return edge;
		}
	}

	return NULL;
}
edge* graph::getEdge(std::string name) const {
	for (edge* edge : edges) {
		if ((edge->getA()->getName() == name) || (edge->getB()->getName() == name)) {
			return edge;
		}
	}

	return NULL;
}
std::list<vertex*> graph::getVertices() {
	vertices.sort([](const vertex* vertex1, const vertex* vertex2) {
		return vertex1->getName() < vertex2->getName();
	});
	return vertices;
}
std::list<edge*> graph::getEdges() {
	return edges;
}

bool graph::unique_name(std::string name) const {
	for (vertex* vertex : vertices) {
		if (vertex->getName() == name) {
			return false;
		}
	}
	return true;
}

std::list<std::string>  graph::bypass(std::string root) {
	for (vertex* vertex : vertices) {
		vertex->setState(0);
	}

	std::list<std::string> names;
	std::queue<vertex*> vert_queue;

	vertex* vertex = getVertex(root);
	vert_queue.push(vertex);
	vertex->setState(1);

	while (!vert_queue.empty()) {
		for (edge* edge : edges) {
			if (edge->getA() == vertex || edge->getB() == vertex) {
				if (edge->getA()->getState() == 0) {
					vert_queue.push(edge->getA());
					(edge->getA())->setState(1);
				}

				if (edge->getB()->getState() == 0) {
					vert_queue.push(edge->getB());
					(edge->getB())->setState(1);
				}
			}
		}

		names.push_back(vertex->getName());
		vertex->setState(2);
		vert_queue.pop();
		if (!vert_queue.empty()) {
			vertex = vert_queue.front();
		}
	}

	return names;
}

int graph::ford_bellman(std::string start, std::string dest, std::vector<std::string> &path) const {
	const int INF = 1000000;
	const int VERT_SIZE = vertices.size();
	bool flag;
	int i = 0;

	std::vector<edge*> v_edges(edges.begin(), edges.end());
	for (vertex* vertex : vertices) {
		vertex->setState(i++);
		path.push_back(vertex->getName());
	}

	int number = getVertex(start)->getState();
	std::vector<int> dist(VERT_SIZE, INF);
	dist[number] = 0;

	for (int i = 0; i < VERT_SIZE; i++) {
		for (int j = 0; j < v_edges.size(); j++) {
			int from, to;
			if (v_edges[j]->getA()->getState() == i) {
				from = v_edges[j]->getA()->getState();
				to = v_edges[j]->getB()->getState();
			}
			else {
				from = v_edges[j]->getB()->getState();
				to = v_edges[j]->getA()->getState();
			}
			int distance = v_edges[j]->getDistance();

			if (dist[from] == INF) {
				continue;
			}

			if (dist[to] > dist[from] + distance) {
				dist[to] = dist[from] + distance;
				std::string name = getVertexByState(to)->getName();
				path[to] = path[from] + "->" +  name;
			}			
		}
	}

	return dist[getVertex(dest)->getState()];
}