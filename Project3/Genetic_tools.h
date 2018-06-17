#pragma once
#include <iostream>
#include "Path.h"
#include "City.h"


void Mutatation(Path& PathA);
Path Cross_over(const Path& PathA, const Path& PathB, const std::vector<City>& Cities);
void Fill_Vector(std::vector<std::vector<int>>& neighbors, unsigned center, unsigned left, unsigned right);
Population Evolve_Population(const Population& pop, const std::vector<City>& Cities);
Path Survivor(const Population& pop);