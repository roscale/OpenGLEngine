//
// Created by roscale on 11/4/17.
//

#include <fstream>
#include <iostream>
#include "util.hpp"

FileNotFound::FileNotFound(const std::string& message) : std::exception() {
	this->message = message;
}

const char* FileNotFound::what() const throw() {
	return message.c_str();
}

std::string util::readFile(const std::string& filename) {
	std::ifstream fileStream(filename);
	if (!fileStream.is_open()) {
		throw FileNotFound("File "+ filename + " couldn't be opened.\n");
	}

	return std::string( (std::istreambuf_iterator<char>(fileStream) ),
	                     (std::istreambuf_iterator<char>()    ) );
}

float map(float x, float in_min, float in_max, float out_min, float out_max) {
	return out_min + ((out_max - out_min) / (in_max - in_min)) * (x - in_min);
}
