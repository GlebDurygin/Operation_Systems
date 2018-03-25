#pragma once
#include <string>
class vertex {
private:
	std::string name;
	int population;
	int state;
public:
	void setName(std::string name);
	void setPopulation(int Population);
	void setState(int state);

	std::string getName() const;
	int getPopulation() const;
	int getState() const;

	vertex();
	vertex(const vertex* object);

	bool operator==(const vertex* object) const;
	bool operator!=(const vertex* object) const;

	vertex* clone() const;
};