#pragma once
#include <iostream>
#include "Path.h"
#include "City.h"


void Mutatation(Path& PathA);
std::vector<City> Cross_over(const Path& PathA, const Path& PathB, const std::vector<City>& Cities);
void Fill_Vector(std::vector<std::vector<int>>& neighbors, unsigned center, unsigned left, unsigned right);
void Evolve_Population(Population& pop, const std::vector<City>& Cities, unsigned  &n);
Path Survivor(const Population& pop);