// laba6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "util.h"
#include "graph.h"

void print_distance(graph* graph, vertex* A, vertex* B) {
	for (edge* edge : graph->getEdges()) {
		if ((edge->getA() == A && edge->getB() == B) || (edge->getA() == B && edge->getB() == A)) {
			std::cout << ": " << edge->getDistance();
		}
	}
}

std::string unique_name(graph* graph) {
	std::string name;
	while (1) {
		std::cout << "Enter locality name: ";
		std::cin >> name;
		if (graph->unique_name(name)) {
			return name;
		}
		std::cout << "This name is already exist." << std::endl;
	}
}

vertex* create_vertex(graph* graph) {
	std::string name;
	int population;

	name = unique_name(graph);
	std::cout << "Enter number of people in the locality: ";
	population = util::readInt();
	std::cout << "----------------------------------------\n";

	vertex* _vertex = new vertex();
	_vertex->setName(name);
	_vertex->setPopulation(population);
	return _vertex;
}

int read_distance() {
	int distance;
	std::cout << "Enter distance between localities: ";
	distance = util::readInt();
	std::cout << "----------------------------------------\n";
	return distance;
}

vertex* get_vertex(graph* graph) {
	std::string name;

	std::cout << "\nEnter a string to exit." << std::endl;
	std::cout << "Enter locality name: ";
	std::cin >> name;

	vertex* vertex = graph->getVertex(name);
	return vertex;
}

edge* create_edge(graph* graph, vertex* vert) {
	int distance;
	vertex* vertex = get_vertex(graph);
	if (vertex == NULL) {
		return NULL;
	}
	
	distance = read_distance();

	edge* _edge = new edge();
	_edge->setA(vert);
	_edge->setB(vertex);
	_edge->setDistance(distance);

	return _edge;
}

void add_vertex(graph* _graph, vertex* vertex) {
	while (_graph->getVerticesSize() != 0) {
		for (auto _vertex :_graph->getVertices())
		{
			std::cout << _vertex->getName();			
			print_distance(_graph, vertex, _vertex);
			std::cout << std::endl;
		}
		
		edge* edge = create_edge(_graph, vertex);
		if (edge == NULL) {
			break;
		}
		_graph->add_edge(edge);
	}
	_graph->add_vertex(vertex);
}

std::string list_vertices(graph* graph) {
	std::list<vertex*> vertices= graph->getVertices();
	if (vertices.size() != 0) {
		for (auto vertex : vertices) {
			std::cout << vertex->getName() << std::endl;
		}
		return  "Enter a string to continue";
	}
	else {
		return "The list is empty.";
	}
}

void print_vertex(std::list<edge*> edges, vertex* vertex) {
	std::cout << vertex->getName() << ": " << vertex->getPopulation() << std::endl;

	for (edge* edge : edges) {
		if (edge->getA() == vertex || edge->getB() == vertex) {
			std::cout << edge->getA()->getName() << " -> " << edge->getB()->getName() << " : " <<
				edge->getDistance() << ";" << std::endl;
		}
	}
	std::cout << "----------------------------------------\n";
}

void print_graph(graph* graph) {
	std::list<vertex*> vertices = graph->getVertices();
	std::list<edge*> edges = graph->getEdges();

	for (vertex* vertex : vertices) {
		print_vertex(edges, vertex);
	}
}

void bypass(graph* graph) {
	std::string root;
	std::cout << "Enter a string to exit.\n";
	std::cout << "Enter the root name: ";
	std::cin >> root;

	if (graph->getVertex(root) == NULL) {
		return;
	}

	std::cout << "----------------------------------------\n";
	for (std::string name : graph->bypass(root)) {
		std::cout << name << std::endl;
	}
	std::cout << "----------------------------------------\n";
	std::cin >> root;
}

void edit_distance(graph* graph, vertex* vert) {
	int distance;

	list_vertices(graph);
	vertex* vertex = get_vertex(graph);

	if (vertex == NULL || vertex -> getName() == vert -> getName()) {
		return;
	}

	print_vertex(graph->getEdges(), vertex);

	edge* _edge = graph->getEdge(vert->getName(), vertex->getName());
	if (_edge != NULL) {
		distance = read_distance();
		_edge->setDistance(distance);
	}
	else {
		distance = read_distance();

		_edge = new edge();
		_edge->setA(vert);
		_edge->setB(vertex);
		_edge->setDistance(distance);
		graph->add_edge(_edge);
	}	
}

bool edit_menu(graph* graph, vertex* vertex) {
	int n = 0;

	std::cout << "Enter '1' to edit name of locality;" << std::endl;
	std::cout << "Enter '2' to edit population of locality;" << std::endl;
	std::cout << "Enter '3' to edit distance between localities;" << std::endl;
	std::cout << "Enter '4' to exit." << std::endl;
	std::cin >> n;
	std::cout << "----------------------------------------" << std::endl;

	switch (n) {
	case 1: {
		vertex->setName(unique_name(graph));
		return true;
	};
	case 2: {
		vertex->setPopulation(util::readInt());
		return true;
	};
	case 3: {
		edit_distance(graph, vertex);
		return true;
	};
	case 4: {
		return false;
	}
	}
	return false;
}

void edit_vertex(graph* graph) {
	list_vertices(graph);
	std::string name;
	std::cout << "Enter name of locality: ";
	std::cin >> name;

	vertex* vertex = graph->getVertex(name);
	if (vertex == NULL) {
		std::cout << "There isn't such locality";
		std::cin >> name;
		return;
	}

	do {
		print_vertex(graph->getEdges(), vertex);
	} while (edit_menu(graph, vertex));
}

void delete_lone_vertex(graph* graph, std::list<vertex*> vertices) {
	
	for (vertex* vertex : vertices) {
		edge* edge = graph->getEdge(vertex->getName());
		if (edge == NULL) {
			graph->remove_vertex(vertex->getName());
		}
	}
	
}

void delete_vertex(graph* graph) {
	std::list<vertex*> vertices;
	list_vertices(graph);

	std::cout << "Enter a string to exit;\n";
	std::cout << "Enter locality name: ";

	std::string name;
	std::cin >> name;

	vertex* vert = graph->getVertex(name);
	
	if (vert == NULL) {
		return;
	}

	vertices.push_back(vert);
	for (edge* edge : graph->getEdges()) {
		if (edge->getA() == vert || edge->getB() == vert) {
			vertices.push_back(edge->getA());
			vertices.push_back(edge->getB());
			//graph->remove_edge(edge->getA()->getName(), edge->getB()->getName());
			graph->remove_edge(edge);
		}
	}

	vertices.sort([](const vertex* vertex1, const vertex* vertex2) {
		return vertex1->getName() < vertex2->getName();
	});
	vertices.unique();
	if(graph->getVerticesSize() > 2){
		delete_lone_vertex(graph, vertices);
	}
	else {
		graph->remove_vertex(vert->getName());
	}
	
}

void shortest_path(graph* graph) {
	std::vector<std::string> path;
	std::string start;
	std::string dest;
	list_vertices(graph);

	while (1) {
		std::cout << "Enter start locality: ";
		std::cin >> start;

		if (graph->getVertex(start) == NULL) {
			std::cout << "There isn't such locality!\n";
		}
		else {
			break;
		}
	}

	while (1) {
		std::cout << "Enter destination locality: ";
		std::cin >> dest;

		if (graph->getVertex(dest) == NULL) {
			std::cout << "There isn't such locality!\n";
		}
		else {
			break;
		}
	}

	std::cout << "Shortest path between localities: " << graph->ford_bellman(start, dest, path) << std::endl;
	std::cout << "Path : " << path[graph->getVertex(dest)->getState()] << std::endl;
	std::cin >> start;
}
bool main_menu(graph* graph) {
	int n = 0;

	std::cout << "Enter '1' to add locality;\n";
	std::cout << "Enter '2' to edit locality;\n";
	std::cout << "Enter '3' to delete locality;\n";
	std::cout << "Enter '4' to list vertices;\n";
	std::cout << "Enter '5' to print graph;\n";
	std::cout << "Enter '6' to bypass the graph;\n";
	std::cout << "Enter '7' to find shortest path;\n";
	std::cout << "Enter '8' to exit.\n";
	std::cin >> n;
	std::cout << "----------------------------------------\n";

	switch (n) {
		case 1: {
			add_vertex(graph, create_vertex(graph));
			return true;
		}
		case 2: {
			edit_vertex(graph);
			return true;
		}
		case 3: {
			delete_vertex(graph);
			return true;
		}
		case 4: {
			std::string str = list_vertices(graph);
			std::cout << str << std::endl;			
			std::cin >> str;
			return true;
		}
		case 5: {
			print_graph(graph);
			return true;
		}
		case 6: {
			bypass(graph);
			return true;
		}
		case 7: {
			shortest_path(graph);
			return true;
		}
		case 8: {
			return false;
		}
	}
}

int main()
{	
	graph* _graph = new graph();
	while(main_menu(_graph));
	delete _graph;

    return 0;
}

