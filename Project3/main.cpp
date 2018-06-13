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


Path Cross_over(const Path& PathA, const Path& PathB, const std::vector<Cities>& Cities)
{
	int neighbors[PATH_SIZE * 4];
	unsigned int a_current_city = PathA.Get_IDCity_at(0);
	unsigned int b_current_city = PathA.Get_IDCity_at(0);
	unsigned int a_current_right_city = PathA.Get_IDCity_at(1);
	unsigned int a_current_left_city = PathA.Get_IDCity_at(PATH_SIZE - 1);
	unsigned int b_current_right_city = PathB.Get_IDCity_at(1);
	unsigned int b_current_left_city = PathB.Get_IDCity_at(PATH_SIZE - 1);
	Neighbors[a_current_city] = a_current_right_city;
	Neighbors[a_current_city] = a_current_left_city;
	Neighbors[b_current_city] = b_current_right_city;
	Neighbors[b_current_city] = b_current_left_city;
	for (int i = 1 ; i < PATH_SIZE - 1; i++)
	{
		a_current_city = PathA.Get_IDCity_at(i);
		b_current_city = PathB.Get_IDCity_at(i);
		a_current_right_city = PathA.Get_IDCity_at(i + 1);
		a_current_left_city = PathA.Get_IDCity_at(i - 1);
		b_current_right_city = PathB.Get_IDCity_at(i + 1);
		b_current_left_city = PathB.Get_IDCity_at(i - 1);
		Neighbors[a_current_city * 4] = a_current_right_city;
		Neighbors[a_current_city * 4 + 1] = a_current_left_city;
		Neighbors[b_current_city * 4 + 2] = b_current_right_city;
		Neighbors[b_current_city * 4 + 3] = b_current_left_city;
	}
	a_current_city = PathA.Get_IDCity_at(PATH_SIZE - 1);
	b_current_city = PathB.Get_IDCity_at(PATH_SIZE - 1);
	a_current_right_city = PathA.Get_IDCity_at(0);
	a_current_left_city = PathA.Get_IDCity_at(PATH_SIZE - 2);
	b_current_right_city = PathB.Get_IDCity_at(0);
	b_current_left_city = PathB.Get_IDCity_at(PATH_SIZE - 2);
	Neighbors[(PATH_SIZE - 1) * 4] = a_current_right_city;
	Neighbors[(PATH_SIZE - 1) * 4 + 1] = a_current_left_city;
	Neighbors[(PATH_SIZE - 1) * 4 + 2] = b_current_right_city;
	Neighbors[(PATH_SIZE - 1) * 4 + 3] = b_current_left_city;
	unsigned int choosen = std::rand() % PATH_SIZE;
	int min;
	Path child = Path();
	for (int i = 0; i < PATH_SIZE; i++)
	{
		min = 5;
		child.SetCityAt(i, Cities.at(choosen));
		for (int j = 0; i < PATH_SIZE; i++)
		{
		
		}
		

	}

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
	std::cout << "best generated path "<< p.GetBestPath().GetLength() << std::endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	std::cout << "Time taken by function: "
		<< duration.count() << " milliseconds" << std::endl;

	std::cin.get();
	
}


