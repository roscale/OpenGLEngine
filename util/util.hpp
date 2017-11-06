//
// Created by roscale on 11/4/17.
//

#pragma once

#include <string>

class FileNotFound : public std::exception {
private:
	std::string message;

public:
	explicit FileNotFound(const std::string& message);

	const char* what() const throw() override;
};


namespace util {
	std::string readFile(const std::string& path);
}


float map(float x, float in_min, float in_max, float out_min, float out_max);