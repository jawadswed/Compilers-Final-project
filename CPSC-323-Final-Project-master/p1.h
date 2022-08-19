#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

bool IsValidString(std::string word);

void ParseTextFile(std::ifstream& in_file, std::ofstream& o_file);


//int main() {
//
//	std::ifstream in_file("finalp1.txt");
//	std::ofstream o_file;
//
//	Parse(in_file, o_file);
//
//	std::cin.ignore();
//	std::cin.get();
//
//	return 0;
//}
