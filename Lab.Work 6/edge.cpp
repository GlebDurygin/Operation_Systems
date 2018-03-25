#include "stdafx.h"
#include "edge.h"
edge::edge() {};
edge::edge(const edge* obj) : distance(obj->distance), A(obj->A->clone()), B(obj->B->clone()) {};


void edge::setDistance(int distance) {
	this->distance = distance;
}
void edge::setA(vertex* A) {
	this->A = A;
}
void edge::setB(vertex* B) {
	this->B = B;
}

int edge::getDistance() const {
	return this->distance;
}
vertex* edge::getA() const {
	return this->A;
}
vertex* edge::getB() const {
	return this->B;
}

bool edge::operator==(const edge* obj) const {
	return (this->A == obj->A && this->B == obj->B) || (this->A == obj->B && this->B == obj->A);
}
bool edge::operator!=(const edge* obj) const {
	return !(this == obj);
}

edge* edge::clone() const {
	return new edge(this);
};