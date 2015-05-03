//Constraint Satisfaction Routines (Working with constraints and variables)
//Based on CSC384 class files from University of Toronto
#include <string>
#include <vector>
#include <iostream>


//Class Variable, specifically working with INT type domains
class Variable{
	std::vector<int> dom;
	std::vector<int> curdom;
	std::string name;
public:
	Variable(int domain[9], std::string inname);// Constructor and Destructor
	~Variable();
	//Class Methodds
	void add_domain_values(std::vector<int> values);
	int value_index(int value);
	void prune_value(int value);
	int domain_size();
	std::vector<int> domain();
	int cur_domain_size();
	std::vector<int> cur_domain();
	bool in_cur_domain(int value);
	void print_var();
};

Variable::Variable(int domain[9], std::string inname){
	for (int i = 0; i < 9; i++){
		if (domain[i] != 0)
			dom.push_back(i + 1);
			curdom.push_back(i + 1);
	}
	name = inname;
}

void Variable::add_domain_values(std::vector<int>values){
	for (int i = 0; i < values.size(); i++){
		dom.push_back(values[i]);
		curdom.push_back(values[i]);
	}
}

int Variable::value_index(int value){
	std::vector<int>::iterator it = std::find(dom.begin(), dom.end(), value);
	return int(it - dom.begin());
}

void Variable::prune_value(int value){
	if (std::find(curdom.begin(), curdom.end(), value) != curdom.end()){
		curdom.erase(std::find(curdom.begin(), curdom.end(), value));
	}
}

int Variable::domain_size(){
	return dom.size();
}

std::vector<int> Variable::domain(){
	return dom;
}

int Variable::cur_domain_size(){
	return curdom.size();
}

std::vector<int> Variable::domain(){
	return curdom;
}

bool Variable::in_cur_domain(int value){
	return (std::find(curdom.begin(), curdom.end(), value)!= curdom.end()))
}

void Variable::print_var(){
	std::cout << "Name: " << name << std::endl;
	std::cout << "Domain: [";
	for (std::vector<int>::const_iterator i = dom.begin(); i != (dom.end() - 1); ++i)
		std::cout << *i << ', ';
	std::cout << *(dom.end()-1) << ']' << std::endl;
	std::cout << "Current Domain: [";
	for (std::vector<int>::const_iterator i = curdom.begin(); i != (curdom.end() - 1); ++i)
			std::cout << *i << ', ';
	std::cout << *(curdom.end() - 1) << ']' << std::endl;
}

//Class