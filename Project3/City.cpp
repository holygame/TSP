#include "City.h"
#include "Defs.h"
#include <array>
#include <vector>
#include <iostream>   
#include <fstream>

City::City()
	:m_Id(0), m_X(0), m_Y(0)
{
	m_Distances.reserve(PATH_SIZE);
}

City::City(unsigned int id, int x, int y)
	: m_Id(id), m_X(x), m_Y(y)
{
	m_Distances.reserve(PATH_SIZE);
}

const unsigned int City::GetID() const
{
	return m_Id;
}

const int City::GetX() const
{
	return m_X;
}

const int City::GetY() const
{
	return m_Y;
}


const float City::GetDistanceTo(unsigned int index) const
{
	return m_Distances[index];
	
}

const void City::updateDistances(const std::vector<City>& cities)
{

	for ( const City& city : cities)
	{
		m_Distances.emplace_back((float)round(sqrt(pow((m_X - city.GetX()), 2) + pow((m_Y - city.GetY()), 2))));
		
	}
}


void CitiesFromFile(std::ifstream& FTP, std::vector<City>& Out_Cities)
{
	std::string line;
	std::string token;
	std::string delimiter = " ";
	std::array<int, 3> temparray;
	size_t n_line = 0;
	while (std::getline(FTP, line))
	{
		size_t pos = 0;
		size_t i = 0;
		while (i<3)
		{
			pos = line.find(delimiter);
			token = line.substr(0, pos);
			temparray.at(i) = std::stoi(token);
			i++;
			line.erase(0, pos + delimiter.length());
		}
		Out_Cities.emplace_back(City(n_line++, temparray[1], temparray[2]));
	}
}

void setDistances(std::vector<City>& cities)
{
	for (int i = 0; i < PATH_SIZE; i++)
	{
		cities.at(i).updateDistances(cities);
	}
}

bool operator==(const City& left, const City& right) 
{
	return left.GetID() == right.GetID();
}