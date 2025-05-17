#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>



std::string toUpperCase(std::string word);
std::string round_double_to_string(double value, int precision);
void loadFile(std::vector<std::string>& lines, const std::string& filename);
