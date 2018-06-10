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
	m_BestPath = m_Paths.at(0);
}


const Path Population::GetBestPath() const
{
	
	return m_BestPath;
}


Population::Population()
	: m_BestPath(Path())
{
	m_Paths.reserve(POP_SIZE);
}