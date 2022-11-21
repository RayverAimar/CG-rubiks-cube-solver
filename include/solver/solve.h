#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "search.h"
#include <string>
#include<vector>


std::string solver(char* cube);
std::vector<std::string> get_solution(std::string Cube);
std::string format_solution(std::vector<std::string>);
std::vector<std::string> string_to_vector(std::string);