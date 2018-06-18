#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include "Path.h"
#include <random>
#include "Defs.h"
#include "City.h"


Path::Path(const Path &t_path)
{
	m_Path = t_path.GetPath();
	m_Length = t_path.GetLength();
}
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
	m_Length = 0;
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
const void Path::SetPath(std::vector<City>& Cities) 
{
	m_Path = Cities;
	this->SetLenght();
}

const float Path::GetLength() const
{
	return m_Length;
}

std::vector<City> Path::GetPath() const
{
	return m_Path;
}

const unsigned Path::Get_IDCity_at(int index) const
{
	return m_Path.at(index).GetID();
}



Path::Path()
	: m_Length(0)
{
	m_Path.resize(PATH_SIZE);
}

const void Path::SetCityAt(unsigned index, const City& city)
{
	m_Path.at(index) = city;
}



std::ostream& operator<<(std::ostream& out , const Path& t_path)
{
	out << "|-";
	for (int i = 0; i < PATH_SIZE; i++)
	{
		out << t_path.GetPath().at(i).GetID() << "-";
	}
	out << "|\n";
	out << "path size " << t_path.GetPath().size() << std::endl; 
	std::vector<City> temp1 = t_path.GetPath();
	std::sort(temp1.begin(), temp1.end(), [](const City& a, const City& b)
	{
		return a.GetID() < b.GetID();
	});
	for (int i = 0; i < PATH_SIZE; i++)
	{
		out << temp1.at(i).GetID() << "-";
	}
	return out;
}