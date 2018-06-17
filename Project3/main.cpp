#include <iostream>     
#include <algorithm>    
#include <vector>       
#include <ctime>    
#include <array>
#include <functional>
#include <random>     
#include <fstream>
#include "math.h"
#include "City.h"
#include "Path.h"
#include "Population.h"
#include "Genetic_tools.h"
#include "Defs.h"
#include <chrono>
typedef std::vector<City> Cities;

using namespace std::chrono;


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
	Path test = Path();
	test = Cross_over(p.GetSortedPathAt(0), d.GetSortedPathAt(0), Cities);
	for (int i = 0; i < 100; i++)
	{
		Mutatation(test);
	}
	for (int j = 0 ; j < GEN_NUMBER; j++)
	{
		p = Evolve_Population(p, Cities);
		std::cout << "best generated path for gen : "<< j << p.GetSortedPathAt(0).GetLength() << "\n";
	}
	
	std::cout << "cross over best path " << test.GetLength() << std::endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	std::cout << "Time taken by function: "
		<< duration.count() << " milliseconds" << std::endl;

	std::cin.get();
	
}


