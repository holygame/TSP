#include <iostream>     
#include <algorithm>    
#include <vector>       
#include <ctime>    
#include <array>
#include <random>     
#include <memory>
#include <fstream>
#include "math.h"
#include "City.h"
#include "Path.h"
#include "Population.h"
#include "Defs.h"
#include <chrono>
#include <random>
#include <stdlib.h>
#include <time.h>
#include "Genetic_tools.h"


void Fill_Vector(std::vector<std::vector<int>>& neighborList, unsigned center, unsigned left, unsigned right)
{
	(neighborList.at(center)).emplace_back(right);
	(neighborList.at(center)).emplace_back(left);
}

std::vector<std::vector<int>> Get_NeighborList(const Path& PathA , const Path& PathB)
{
	std::vector<std::vector<int>> neighborList(PATH_SIZE);
	neighborList.reserve(PATH_SIZE);
	for (unsigned r = 0; r < PATH_SIZE; r++)
	{
		(neighborList.at(r)).reserve(4); // each city has a maximum of 4 neighor
	}
	unsigned a_current_city = PathA.Get_IDCity_at(0); // out of range if uncluded in the for loop ( first city is alsoneighbor with the last city)
	unsigned b_current_city = PathB.Get_IDCity_at(0);
	unsigned a_current_right_city = PathA.Get_IDCity_at(1);
	unsigned a_current_left_city = PathA.Get_IDCity_at(PATH_SIZE - 1);
	unsigned b_current_right_city = PathB.Get_IDCity_at(1);
	unsigned b_current_left_city = PathB.Get_IDCity_at(PATH_SIZE - 1);
	Fill_Vector(neighborList, a_current_city, a_current_left_city, a_current_right_city);
	Fill_Vector(neighborList, b_current_city, b_current_left_city, b_current_right_city);

	for (unsigned i = 1; i < PATH_SIZE - 1; i++)
	{
		a_current_city = PathA.Get_IDCity_at(i);
		b_current_city = PathB.Get_IDCity_at(i);
		a_current_right_city = PathA.Get_IDCity_at(i + 1);
		a_current_left_city = PathA.Get_IDCity_at(i - 1);
		b_current_right_city = PathB.Get_IDCity_at(i + 1);
		b_current_left_city = PathB.Get_IDCity_at(i - 1);
		Fill_Vector(neighborList, a_current_city, a_current_left_city, a_current_right_city);
		Fill_Vector(neighborList, b_current_city, b_current_left_city, b_current_right_city);
	}
	a_current_city = PathA.Get_IDCity_at(PATH_SIZE - 1);
	b_current_city = PathB.Get_IDCity_at(PATH_SIZE - 1);
	a_current_right_city = PathA.Get_IDCity_at(0);
	a_current_left_city = PathA.Get_IDCity_at(PATH_SIZE - 2);
	b_current_right_city = PathB.Get_IDCity_at(0);
	b_current_left_city = PathB.Get_IDCity_at(PATH_SIZE - 2);
	Fill_Vector(neighborList, a_current_city, a_current_left_city, a_current_right_city);
	Fill_Vector(neighborList, b_current_city, b_current_left_city, b_current_right_city);
	return neighborList;
}

std::vector<City> Cross_over_ERX(const Path& PathA, const Path& PathB, const std::vector<City>& Cities)
{
	
	auto neighborList = Get_NeighborList(PathA, PathB);
	unsigned int choosen = std::rand() % PATH_SIZE;
	unsigned min=5;
	unsigned size = 5;
	std::vector<City> childSetter(PATH_SIZE , City(100,0,0));
	Path child = Path();
	for (int x = 0; x < PATH_SIZE; x++)
	{
		min = 5;
		childSetter.at(x) = Cities.at(choosen);
		for (int j = 0; j < PATH_SIZE; j++)
		{
			for (std::vector<int>& neighbor : neighborList)
			{
				neighbor.erase(std::remove(neighbor.begin(), neighbor.end(), choosen), neighbor.end());
				neighbor.shrink_to_fit(); // resize automaticly after removing 
			}
			for (const unsigned city_id : neighborList.at(choosen))
			{
				if (size = neighborList.at(city_id).size() <= min)
				{
					min = size;
					choosen = city_id;
				}
			}
			if (neighborList.at(choosen).size() == 0)
			{
				for (int p = 0; p < PATH_SIZE; p++)
				{
					    min = 5;
						if (std::find(childSetter.begin(), childSetter.end(), Cities.at(p))
							== childSetter.end())
						{
							choosen = p;
							min = neighborList.at(p).size();
							break;
						}
				}
			}
		}
	}
	return childSetter;
}

void Mutatation(Path& PathA) // prototype implementation , very bad design !
{
	unsigned i, j;
	i = std::rand() % PATH_SIZE;
	j = std::rand() % PATH_SIZE;
	auto oldP = PathA.GetPath();
	auto oldL = PathA.GetLength();
	auto temp = PathA.GetPath();
	std::swap(temp[i], temp[j]);
	PathA.SetPath(temp);

	if (PathA.GetLength() > oldL )
	{
		PathA.SetPath(oldP);
	}
}

Path Survivor(const Population& pop)
{
	std::vector<Path> PathList = pop.GetSortedPaths();
	Population fighters = Population();
	for (int i = 0; i < TOURNEMENT_SIZE; i++)
	{
		int randIndex = std::rand() % POP_SIZE;
		fighters.AppendPath(PathList[randIndex]);
	}
	fighters.GetSortedPaths();
	return fighters.GetSortedPathAt(0);
}

std::vector<City> Cross_over_IGX(const Path& PathA, const Path& PathB, const std::vector<City>& Cities)
{
	std::vector<City> childSetter;
	auto neighborList = Get_NeighborList(PathA, PathB);
	float Distance = 100000000.0f;
	for (int go = 0; go < PATH_SIZE; go++)
	{
		unsigned found = 0;
		unsigned choosen = 1; // we choose 1 by default to reduce cost time of randomly generating a starting point
		childSetter.reserve(PATH_SIZE);
		childSetter.emplace_back(Cities.at(choosen));
		Distance = 100000000.0f;
		for (unsigned City_id : neighborList.at(choosen))
		{
			
			if (float temp = Cities.at(choosen).GetDistanceTo(City_id) < Distance &&
				std::find(childSetter.begin(), childSetter.end(), Cities.at(City_id))
				== childSetter.end())
			{
				Distance = temp;
				choosen = City_id;
				found = 1;
			}
		}
		if (found)
		{
			childSetter.emplace_back(Cities.at(choosen));
		}
		else if (found == 0)
		{
			for (int i = 1; i <= PATH_SIZE; i++)
			{
				if (std::find(childSetter.begin(), childSetter.end(), Cities.at(i))
					== childSetter.end())
				{
					childSetter.emplace_back(Cities.at(i));
					break;
				}
			}
		}
	}
	return childSetter;
}

/*
 This Function serve the purpose of evolving a certain population by creating anaother superior one.
 note that this code should be operational but is definitly not optimised yet 
 */
Population Evolve_Population(const Population& pop , const std::vector<City>& Cites , int n)
{
	
	
	Population evolvedPopulation = Population(); // Create a new population that can take up to POP_SIZE paths
	Path bestPath = pop.GetSortedPathAt(0);
	evolvedPopulation.AppendPath(bestPath) ;
	for ( int i = 0 ; i< POP_SIZE ; ++i)
	{
		Path selected = Survivor(pop); 
		if (unsigned do_cross = std::rand() % 100 < CROSSOVER_RATE)
		{
			Path temp1 =Survivor(pop); 
			Path temp2 = Survivor(pop;
			selected.SetPath(Cross_over_IGX(temp1,temp2, Cities));
		}
		if (unsigned do_mute = std::rand() % 100 < MUTATION_RATE)
		{
				Mutatation(selected);
		}
		evolvedPopulation.AppendPath(selected);
	}
	evolvedPopulation.SortPaths();
	return evolvedPopulation;
	
}

/*
 This Function serve the purpose of evolving a certain population whithout creating another one.
 it's causing me bugs for now 
 */
void Evolve_Population(Population& pop , const std::vector<City>& Cities , unsigned &n)
{
	if ( n != 0 )
	{
		Path selected = Path();
		Path temp1 = Path();
		Path temp2 = Path();
		Population evolved_pop = Population();
		evolved_pop.AppendPath(pop.GetSortedPathAt(0)); // take the best path of the last gen
		for (int i = 1; i < POP_SIZE; i++)
		{
			selected = Survivor(pop);
			if (unsigned do_cross = std::rand() % 100 < CROSSOVER_RATE)
			{
				temp1 = Survivor(pop);
				temp2 = Survivor(pop);
				if ( temp1.GetLength() != temp2.GetLength())
					selected.SetPath(Cross_over_IGX(temp1, temp2, Cities));
			}
			if (unsigned do_mute = std::rand() % 100 < MUTATION_RATE)
			{
				Mutatation(selected);
			}
			evolved_pop.AppendPath(selected);
		}
		evolved_pop.SortPaths();
		n--;
		std::cout << " gen " << GEN_NUMBER - n << " best path " << evolved_pop.GetSortedPathAt(0).GetLength() << " \n";
		return Evolve_Population(evolved_pop, Cities , n );
	}
}