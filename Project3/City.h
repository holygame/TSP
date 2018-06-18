#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include <functional>
#include <vector>
#include <math.h>
#include "Defs.h"

class City
{
private:
	unsigned int            m_Id;
	int                     m_X;
	int                     m_Y;
	std::vector<float>		m_Distances;

public:

	City(unsigned int id, int x, int y);
	City();

	const int GetX() const;
	const int GetY() const;
	const unsigned int GetID() const;
	const float GetDistanceTo(unsigned int index) const;
	const void updateDistances(const std::vector<City> &cities);
	
};
bool operator==(const City& left, const City& right);
void setDistances(std::vector<City>& cities);
void CitiesFromFile(std::ifstream& FTP, std::vector<City>& Out_Cities);
