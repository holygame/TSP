#pragma once
#include <iostream>
#include "City.h"
#include "Defs.h"

class Path
{
private:
	std::vector<City>					m_Path;
	float								m_Length;
public:

	Path();
	Path(const Path &t_path);
	Path(const std::vector<City>& cities);
	const void SetLenght();
	const float GetLength() const;
	std::vector<City> GetPath() const;
	const void SetPath(const std::vector<City>& Cities);
	const unsigned int Get_IDCity_at(int index) const ;
	const void SetCityAt(unsigned index, const City& city);
};

std::ostream& operator<<(std::ostream& out, const Path& t_path);