#include "City.h"
#include "Defs.h"

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

const bool City::operator==(const City& other) const
{
	return this->m_Id == other.m_Id;
}