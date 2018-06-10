

#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include "Path.h"
#include <random>
#include "Defs.h"

Path::Path(const std::vector<City>& cities)
	:m_Path(cities)
 
{
	m_Path.reserve(PATH_SIZE); // comeback to it might cuz a  bug
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(m_Path.begin(), m_Path.end(), g);
	unsigned int next_city_ID = 0;
	float Distance_To_Next_City = 0;
	for (unsigned int i = 0; i<PATH_SIZE - 1; i++)
	{
		next_city_ID = m_Path.at(i + 1).GetID();
		Distance_To_Next_City = m_Path.at(i).GetDistanceTo(next_city_ID);
		m_Length += Distance_To_Next_City;
	}
	next_city_ID = m_Path.at(0).GetID(); // loopback 51  --> 0
	Distance_To_Next_City = m_Path.at(PATH_SIZE - 1).GetDistanceTo(next_city_ID);
	m_Length += Distance_To_Next_City;
}

const void Path::SetLenght()   
{
	unsigned int next_city_ID = 0;
	float Distance_To_Next_City = 0;
	for (unsigned int i = 0; i<PATH_SIZE - 1; i++)
	{
		next_city_ID = m_Path.at(i + 1).GetID();
		Distance_To_Next_City = m_Path.at(i).GetDistanceTo(next_city_ID);
		m_Length += Distance_To_Next_City;
	}
	next_city_ID = m_Path.at(0).GetID();
	Distance_To_Next_City = m_Path.at(PATH_SIZE - 1).GetDistanceTo(next_city_ID);
	m_Length += Distance_To_Next_City;
}

const float Path::GetLength() const
{
	return m_Length;
}


Path::Path()
	: m_Length(0)
{
	m_Path.reserve(PATH_SIZE);
}
