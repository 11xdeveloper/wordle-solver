#include "Utils.h"

std::string toUpperCase(std::string word) {
	std::string upperCase;

	for (char c : word) {
		upperCase += std::toupper(c);
	}

	return upperCase;
}

std::string round_double_to_string(double value, int precision) {
	double rounded_value = std::floor(value * std::pow(10, precision) + 0.5) / std::pow(10, precision);
	std::stringstream ss;
	ss << std::fixed << std::setprecision(precision) << rounded_value;
	return ss.str();
}

void loadFile(std::vector<std::string>& lines, const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("Failed to open file: " + filename);
	}

	std::string line;

	while (std::getline(file, line)) {
		lines.push_back(line);
	}
}

