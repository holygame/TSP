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
	Path test = Path(Cities);
	test.SetLenght();
	unsigned n = GEN_NUMBER;
	std::cout << " starting length " << test.GetLength() << std::endl;
	Evolve_Population(p, Cities , n);
	test = Cross_over(p.GetSortedPathAt(0), d.GetSortedPathAt(0), Cities);
	std::cout << "cross over best path " << test.GetLength() << std::endl;
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(stop - start);
	std::cout << "Time taken by function: "
		<< duration.count() << " milliseconds" << std::endl;

	std::cin.get();
	
}


