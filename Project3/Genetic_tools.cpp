#include <iostream>     
#include <algorithm>    
#include <vector>       
#include <ctime>    
#include <array>
#include <random>     
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


void Fill_Vector(std::vector<std::vector<int>>& neighbors, unsigned center, unsigned left, unsigned right)
{
	(neighbors.at(center)).emplace_back(right);
	(neighbors.at(center)).emplace_back(left);
}

Path Cross_over(const Path& PathA, const Path& PathB, const std::vector<City>& Cities)
{
	std::vector<std::vector<int>> neighbors(PATH_SIZE);
	neighbors.reserve(PATH_SIZE);
	for (unsigned r = 0; r < PATH_SIZE; r++)
	{
	(neighbors.at(r)).reserve(4);
	}
	unsigned a_current_city = PathA.Get_IDCity_at(0);
	unsigned b_current_city = PathB.Get_IDCity_at(0);
	unsigned a_current_right_city = PathA.Get_IDCity_at(1);
	unsigned a_current_left_city = PathA.Get_IDCity_at(PATH_SIZE - 1);
	unsigned b_current_right_city = PathB.Get_IDCity_at(1);
	unsigned b_current_left_city = PathB.Get_IDCity_at(PATH_SIZE - 1);
	Fill_Vector(neighbors, a_current_city, a_current_left_city, a_current_right_city);
	Fill_Vector(neighbors, b_current_city, b_current_left_city, b_current_right_city);

	for (unsigned i = 1; i < PATH_SIZE - 1; i++)
	{
		a_current_city = PathA.Get_IDCity_at(i);
		b_current_city = PathB.Get_IDCity_at(i);
		a_current_right_city = PathA.Get_IDCity_at(i + 1);
		a_current_left_city = PathA.Get_IDCity_at(i - 1);
		b_current_right_city = PathB.Get_IDCity_at(i + 1);
		b_current_left_city = PathB.Get_IDCity_at(i - 1);
		Fill_Vector(neighbors, a_current_city, a_current_left_city, a_current_right_city);
		Fill_Vector(neighbors, b_current_city, b_current_left_city, b_current_right_city);
	}
	a_current_city = PathA.Get_IDCity_at(PATH_SIZE - 1);
	b_current_city = PathB.Get_IDCity_at(PATH_SIZE - 1);
	a_current_right_city = PathA.Get_IDCity_at(0);
	a_current_left_city = PathA.Get_IDCity_at(PATH_SIZE - 2);
	b_current_right_city = PathB.Get_IDCity_at(0);
	b_current_left_city = PathB.Get_IDCity_at(PATH_SIZE - 2);
	Fill_Vector(neighbors, a_current_city, a_current_left_city, a_current_right_city);
	Fill_Vector(neighbors, b_current_city, b_current_left_city, b_current_right_city);
	unsigned int choosen = std::rand() % PATH_SIZE;
	unsigned min;
	Path child = Path();
	for (int x = 0; x < PATH_SIZE; x++)
	{
		min = 5;
		child.SetCityAt(x, Cities.at(choosen));
		for (int j = 0; j < PATH_SIZE; j++)
		{
			for (auto& neighbor : neighbors)
			{
				std::remove(neighbor.begin(), neighbor.end(), choosen);
				neighbor.shrink_to_fit();
			}
			for (auto& city_id : neighbors.at(choosen))
			{
				if (int size = neighbors.at(city_id).size() <= min)
				{
					min = size;
					choosen = city_id;
				}
			}
			if (neighbors.at(choosen).empty() == true)
			{
				for (int p = 0; p < PATH_SIZE; p++)
				{
					min = 5;
					for (auto& city_id : neighbors.at(p))
					{
						if (std::find(child.GetPath().begin(), child.GetPath().end(), Cities.at(city_id)) == child.GetPath().end())
						{
							choosen = city_id;
							min = neighbors.at(city_id).size();
						}
					}
				}
			}
		}
	}
	child.SetLenght();
	return child;
}

void Mutatation(const Path & PathA)
{
	
}
