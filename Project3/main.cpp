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
struct Timer
{
	std::chrono::time_point<std::chrono::steady_clock> start,end;
	std::chrono::duration<float> duration;
	std::string fncname;
	Timer(std::string t_fncname)
	{
		start = std::chrono::high_resolution_clock::now();
		fncname = t_fncname;
	}
	~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;
		float ms = duration.count() * 1000.0f;
		std::cout << " Function " << fncname <<" took " << ms << "ms\n";
 	}
};

int main()
{
	{
		Timer timer("main");
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
		unsigned n = GEN_NUMBER;
		Population p(Cities);
		std::cout << " starting length " << p.GetSortedPathAt(0).GetLength() << std::endl;
		Evolve_Population(p, Cities, n);
	}
	std::cin.get();
	
}


