#pragma once
#include "vertex.h"
class edge {
private: 
	int distance;
	vertex* A;
	vertex* B;
public: 
	void setDistance(int distance);
	void setA(vertex* A);
	void setB(vertex* B);

	int getDistance() const;
	vertex* getA() const;
	vertex* getB() const;

	edge();
	edge(const edge* object);

	bool operator==(const edge* obj) const;
	bool operator!=(const edge* obj) const;

	edge* clone() const;
};
