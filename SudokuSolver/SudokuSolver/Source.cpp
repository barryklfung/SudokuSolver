#include <iostream>
#include <string>
#include <sstream>
#include <regex>

bool sudo_valid(int row, int col, int value, int matrix[8][8]){
	//square must be empty
	if (matrix[row][col] != 0) return false;
	//row check
	for (int i = 0; i < 9; i++)
		if (matrix[i][col] == value) return false;
	//column check
	for (int i = 0; i < 9; i++)
		if (matrix[row][i] == value) return false;
	//square check
	int row_start = row / 3;
	int col_start = col / 3;
	for (int i = 0; i < 3 ; i++)
		for (int j = 0; j < 3; j++)
			if (matrix[row_start + i][col_start + j] == value) return false;
	//It passes
	return true;
}

int main(){
	//Initializations for variables.
	int matrix[8][8] = {0};
	int row, col, value;
	//std::stringstream ss;
	std::string input = "";
	std::regex input_test("[a-g][1-9]\\s[1-9]") ;
	
	//Lookuptable for char-int transformations, taken from Stack Overflow
	char int_to_char[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
	int char_to_int[CHAR_MAX + 1] = {};
	for (int i = 0; i < sizeof(int_to_char); ++i) {
		char_to_int[int_to_char[i]] = i;
	}

	//Input: method of input can vary
	while (input != "f" && input != "m"){
		std::cout << "Input either 'f' for file input, or 'm' manual input." << std::endl;
		std::getline(std::cin, input);

		//Error messages
		if (input != "f" && input != "m") std::cout << "Not a valid input" << std::endl;
	}
	if (input == "f"){
		//TODO: File Parsing
	}
	else {
		//manual input
		while (input != "q"){
			std::cout << "Input values in the format '(row 'a-i')(column '1-9') (value)' e.g. 'a9 7'. Enter 'q' terminate" << std::endl;
			std::getline(std::cin, input);
			// check for valid input.
			if ((!std::regex_match(input, input_test))||(input == "q"))
				std::cout << "Your output: \"" << input <<"\" is not in the format '(row 'a-i')(column '1-9') (value)'" << std::endl;
			else if (input != "q"){
				row = char_to_int[input[0]];
				col = input[1] - '0' - 1;
				value = input[3] - '0' - 1;
				//validate input
				if (sudo_valid(row, col, value, matrix))
					matrix[row][col] = value;
				else
					std::cout << "Your input \"" << input << "\" is not a valid sudoku entry"<< std::endl;
			}
		}
	}
	return 0;
}
