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
typedef std::vector<City> Cities;


Path Cross_over(const Path & PathA, const Path & PathB ,const std::vector<Cities>& Cities )
{
	for (int i =0 ; i<PATH_SIZE;i++)
	{
		std::vector<int> A_Neighbors;
		std::vector<int> B_Neighbors;	
		int next_city_ID = PathA.m_Path.at(i + 1).GetID();
		City next_city = Cities.at(next_city_ID);



	}
}
