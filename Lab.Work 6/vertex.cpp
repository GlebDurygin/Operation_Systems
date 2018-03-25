#include "stdafx.h"
#include "vertex.h"
vertex::vertex(){};
vertex::vertex(const vertex* obj) : name(obj->name), population(obj->population) {};

void vertex::setName(std::string name) {
	this->name = name;
};
void vertex::setPopulation(int population) {
	this->population = population;
};
void vertex::setState(int state) {
	this->state = state;
}

std::string vertex::getName() const {
	return this->name;
};
int vertex::getPopulation() const {
	return this->population;
};
int vertex::getState() const {
	return this->state;
}

bool vertex::operator==(const vertex* obj) const {
	return (this->name == obj->name);
};
bool vertex::operator!=(const vertex* obj) const {
	return !(this == obj);
};

vertex* vertex::clone() const {
	return new vertex(this);
};