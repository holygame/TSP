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
	Path(const std::vector<City>& cities);
	const void SetLenght();
	const float GetLength() const;
	friend Path Cross_over(const Path & PathA, const Path & PathB);
	
};