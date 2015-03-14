#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <regex>

void sudoku_solver(int matrix[9][9]){
//To write - Sudoku Solver

}
bool sudo_valid(int row, int col, int value, int matrix[9][9]){
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

void print_matrix(int matrix[9][9]){
	char int_to_char[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i' };
	std::cout << "    1   2   3    4   5   6    7   8   9  " << std::endl;
	std::cout << "  =======================================" << std::endl;
	for (int row = 0; row < 9; row++){
		std::cout << int_to_char[row] << " ";
		for (int col = 0; col < 9; col++)
			if (matrix[row][col] == 0)
				if ((col % 3 == 0) && col != 0)
					std::cout << "||   ";
				else
					std::cout << "|   ";
			else
				if ((col % 3 == 0) && col != 0)
					std::cout << "|| " << matrix[row][col] << " ";
				else
					std::cout << "| " << matrix[row][col] << " ";
		std::cout << "|" << std::endl;
		if (row != 8){
			if (row % 3 == 2)std::cout << "  =======================================" << std::endl;
			else std::cout << "  ---------------------------------------" << std::endl;
		}
	}
	std::cout << "  =======================================" << std::endl;
}

int main(){
	//Initializations for variables.
	int matrix[9][9] = {0};
	for (int row = 0; row < 9; row++)
		for (int col = 0; col < 9; col++)
			matrix[row][col] = 0;
	/*	for (int i = 0; i< 9; i++)
		std::fill_n(matrix[i], 8, 0);*/
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
		std::cout << "Enter the relative path to your .txt file:" << std::endl;
		std::cin >> input;
		std::ifstream infile(input);
		std::string line;
		int i = 1;
		while (std::getline(infile, input)){
			if (!std::regex_match(input, input_test))
				std::cout << "Line " << i << ": \"" << input << "\" was ignored as an incorrectly formatted entry." << std::endl;
			else {
				row = char_to_int[input[0]];
				col = input[1] - '0' - 1;
				value = input[3] - '0';
				//validate input
				if (sudo_valid(row, col, value, matrix))
					matrix[row][col] = value;
				else
					std::cout << "Line "<< i << ": \"" << input << "\" was ignored as an invalid sudoku entry." << std::endl;
			}
			i++;
		}
	}
	else {
		//manual input
		while (input != "q"){
			std::cout << "Input values in the format '(row 'a-i')(column '1-9') (value)' e.g. 'a9 7'. Enter 'q' to terminate." << std::endl;
			std::getline(std::cin, input);
			// check for valid input.
			if ((!std::regex_match(input, input_test))&&(input != "q"))
				std::cout << "Your input: \"" << input <<"\" is not correcty formatted." << std::endl;
			else if (input != "q"){
				row = char_to_int[input[0]];
				col = input[1] - '0' - 1;
				value = input[3] - '0';
				//validate input
				if (sudo_valid(row, col, value, matrix))
					matrix[row][col] = value;
				else
					std::cout << "Your input \"" << input << "\" is not a valid sudoku entry"<< std::endl;
			}
		}
	}
	sudoku_solver(matrix);
	print_matrix(matrix);
	std::cout << "Here is the finished sudoku puzzle. Enter any character and enter to terminate the program" << std::endl;
	std::cin >> input;
	return 0;
}
