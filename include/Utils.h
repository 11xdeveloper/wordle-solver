#pragma once

#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>


std::string toUpperCase(std::string word);
std::string selectRandomWord(std::vector<std::string> words);
void loadFile(std::vector<std::string>& lines, const std::string& filename);
