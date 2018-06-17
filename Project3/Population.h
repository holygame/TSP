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
	const std::vector<Path> GetSortedPaths() const;
	const Path GetSortedPathAt(unsigned index) const;
	void AppendPath(Path t_path);
	
	
};
