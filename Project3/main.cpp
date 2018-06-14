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
typedef std::vector<City> Cities;

using namespace std::chrono;

void CitiesFromFile(std::ifstream& FTP , std::vector<City>& Out_Cities)
{
	std::string line;
	std::string token;
	std::string delimiter = " ";
	std::array<int,3> temparray;
	size_t n_line = 0;
	while (std::getline(FTP, line)) 
	{
		size_t pos = 0;
		size_t i = 0;
		while(i<3)
		{
			pos = line.find(delimiter);
			token = line.substr(0, pos);
			temparray.at(i) = std::stoi(token);
			i++;
			line.erase(0, pos + delimiter.length());
		}
		Out_Cities.emplace_back(City(n_line++, temparray[1], temparray[2]));
	}
}

void setDistances(std::vector<City>& cities)
{
	for (int i = 0; i < PATH_SIZE; i++)
	{
		cities.at(i).updateDistances(cities);
	}
}

void Fill_Vector(std::vector<std::vector<int>>& neighbors , unsigned center , unsigned left , unsigned right)
{
	neighbors.at(center).emplace_back(right);
	neighbors.at(center).emplace_back(left);
}

Path Cross_over(const Path& PathA, const Path& PathB, const std::vector<City>& Cities)
{
	std::vector<std::vector<int>> neighbors;
	neighbors.reserve(PATH_SIZE);
	for (unsigned r = 0; r < PATH_SIZE; r++)
	{
		neighbors.at(r).reserve(4);
	}
	unsigned a_current_city = PathA.Get_IDCity_at(0);
	unsigned b_current_city = PathA.Get_IDCity_at(0);
	unsigned a_current_right_city = PathA.Get_IDCity_at(1);
	unsigned a_current_left_city = PathA.Get_IDCity_at(PATH_SIZE - 1);
	unsigned b_current_right_city = PathB.Get_IDCity_at(1);
	unsigned b_current_left_city = PathB.Get_IDCity_at(PATH_SIZE - 1);
	Fill_Vector(neighbors, a_current_city, a_current_left_city, a_current_right_city);
	Fill_Vector(neighbors, b_current_city, b_current_left_city, b_current_right_city);
	
	for (unsigned i = 1 ; i < PATH_SIZE - 1; i++)
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
	for (int i = 0; i < PATH_SIZE; i++)
	{
		min = 5;
		child.SetCityAt(i, Cities.at(choosen));
		for (int j = 0; i < PATH_SIZE; j++)
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
				for (int p = 0; i < PATH_SIZE; p++)
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
	return child;
}

void Mutatation(const Path & PathA)
{
	
}

int main()
{
	
	auto start = high_resolution_clock::now();
	std::vector<City> Cities;
	Cities.reserve(PATH_SIZE);
	std::ifstream file("C:/Users/user/eil51.tsp");
	if (file.is_open())
	{
		CitiesFromFile(file, Cities);
		setDistances(Cities);
	}
	else 
	{
		std::cout << "Error opening file";
	}

	Population p(Cities);
	Population d(Cities);
	Path test = Cross_over(p.GetBestPath(), d.GetBestPath() , Cities);
	std::cout << "best generated path "<< p.GetBestPath().GetLength() << std::endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	std::cout << "Time taken by function: "
		<< duration.count() << " milliseconds" << std::endl;

	std::cin.get();
	
}


