#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include <sstream>

bool IsValidString(std::string word) {
	std::vector<char> lang{ 'a','b','c','d','e','0','1','2','3','4','5','6','7','8','9' };
	std::vector<std::string> reserved{ "program", "var", "integer", "show", "begin", "end" };

	// Check if word is a reserved word.
	if (std::find(reserved.begin(), reserved.end(), word) != reserved.end())
		return true;

	// If the word is not a reserved word, then it must be a variable name. Check to see if the variable name contains any characters that are not allowed.
	for (auto& c : word) {
		// If the variable name contains characters not in the language, then return false.
		if (std::find(lang.begin(), lang.end(), c) == lang.end())
			return false;
	}
	return true;
}

void ParseTextFile(std::ifstream& in_file, std::ofstream& o_file) {
	o_file.open("finalp2.txt");
	std::string input_text;

	// Read the entire input text file and store it into input_text.
	getline(in_file, input_text, '\0');

	// Remove comments.
	while (input_text.find("/*") != std::string::npos) {
		size_t beg = input_text.find("/*");
		input_text.erase(beg, (input_text.find("*/", beg) - beg) + 2);
	}
	while (input_text.find("//") != std::string::npos) {
		size_t beg = input_text.find("//");
		input_text.erase(beg, input_text.find("\n", beg) - beg);
	}
	
	// We will store the newly parsed input text into output.
	std::string output;

	// Read the input text line by line.
	std::istringstream lines(input_text);
	std::string line;
	while (getline(lines, line)) {
		std::istringstream word(line);
		std::string temp;

		// Make sure we're on a new line
		if (!output.empty() && output[output.length()-1] != '\n') {
			output.append("\n");
		}
		
		// Read each line, word by word
		while (word >> temp) {

			// If the word contains any punctuation:
			if (std::any_of(temp.begin(), temp.end(), [](char c) {return std::ispunct(c); }))
			{
				output.append(" ");
				for (auto& c : temp) {
					if (!ispunct(c))
						output += c;
					else {
						if (c == ';') {
							output = output + " " + c + " " + "\n";
						}
						else {
							output = output + " " + c + " ";
						}
					}
				}
			}
			// If the word doesn't have any punctuation, check to see if it's valid.
			else {
				if (IsValidString(temp))
					output = output + " " + temp;
				else
					std::cout << "Invalid word: " << temp;
			}
		}
	}

	// Remove extra whitespace.
	std::string::iterator new_end =
		std::unique(output.begin(), output.end(),
			[](char lhs, char rhs) { return (lhs == rhs) && (lhs == ' '); }
	);
	output.erase(new_end, output.end());

	// Write to file.
	o_file << output;
	o_file.close();
}

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
