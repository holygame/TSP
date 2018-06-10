#pragma once
#include <vector>
#include "Path.h"
#include "Defs.h"



class Population
{
private:
	std::vector<Path>				m_Paths;
	Path							m_BestPath;
public:
	
	Population();
	Population(const std::vector<City>& cities);
	const Path GetBestPath() const;
	
};
