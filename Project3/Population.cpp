#include "Population.h"
#include "City.h"
#include "Path.h"
#include "Defs.h"


Population::Population(const std::vector<City>& cities)

{
	m_Paths.reserve(POP_SIZE);
	for (unsigned int i = 0; i < POP_SIZE; i++)
	{

		Path temp_Path = Path(cities); // for some "reasons"?? m_Paths.emplace_back(Path(cities) doesn't work.
		m_Paths.emplace_back(temp_Path);
	}
	std::sort(m_Paths.begin(), m_Paths.end(), [](const Path& a, const Path& b)
	{
		return a.GetLength() < b.GetLength();
	});
	
}


const std::vector<Path> Population::GetSortedPaths() const
{
	return m_Paths;
}

const Path Population::GetSortedPathAt(unsigned index) const
{
	return m_Paths.at(index);
}

void Population::AppendPath(Path t_path) 
{
	m_Paths.emplace_back(t_path);
}

Population::Population()
{
	m_Paths.reserve(POP_SIZE);
}

Population::Population(const Population& other)
{
	m_Paths = other.GetSortedPaths();
}

void Population::SortPaths()
{
	std::sort(m_Paths.begin(), m_Paths.end(), [](const Path& a, const Path& b)
	{
		return a.GetLength() < b.GetLength();
	});
}