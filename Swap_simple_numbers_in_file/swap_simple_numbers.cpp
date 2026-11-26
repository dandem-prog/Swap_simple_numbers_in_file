#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <climits>
struct Simple_number {
	int64_t number;
	size_t pos;
	size_t lenght;
	std::string str;
};
void check_input_file(std::ifstream& fin) {
	if (!fin.good()) {
		throw "file is not exist\n";
	}
	if (!fin) {
		throw "input file error\n";
	}
	if (fin.peek() == EOF) {
		throw "File is empty\n";
	}
}
bool is_simple(int n) {
	if (n < 2) return false;

	for (int i = 2; i * i < n; ++i) {
		if (n % i == 0) {
			return false;
		}
	}

	return true;
}
bool is_number(std::string& word) {

	try {
		if (!stoi(word));
	}

	catch (std::exception& e) {
		return false;
	}
	size_t result = stoi(word);
	result = std::to_string(result).length();
	if (result != word.length()) return false;
	return true;
}
std::string Find_word(std::string& str, std::string& delim, size_t& pos) {
	size_t start_pos = str.find_first_not_of(delim, pos);
	if (start_pos == std::string::npos) {
		pos = std::string::npos;
		return "";
	}
	size_t end_pos = str.find_first_of(delim, start_pos);
	if (end_pos == std::string::npos) end_pos = str.length();

	size_t size_word = end_pos - start_pos;
	return str.substr(start_pos, size_word);
}

int main() {

	try {
	std::ofstream fout("out.txt");
	std::ifstream fin("in.txt");
	check_input_file(fin);
	std::string delimeters;
	std::getline(fin, delimeters);
	std::string str;
	fout << delimeters << '\n';

		while (std::getline(fin, str)) {

		Simple_number max_num{ 0 };
		Simple_number min_num{ INT64_MAX };
		size_t pos_of_word = str.find_first_not_of(delimeters);
		size_t counter_numbers = 0;
		while (pos_of_word < str.size()) {
			std::string word = Find_word(str, delimeters, pos_of_word);
			size_t start_pos = str.find_first_not_of(delimeters, pos_of_word);
			if (is_number(word)) {
				size_t value_word = stoi(word);
				if (is_simple(value_word)) {
					if (max_num.number < value_word) {
						max_num.number = value_word;
						max_num.lenght = word.length();
						max_num.pos = pos_of_word;
						max_num.str = word;
					}
					if (min_num.number > value_word) {
						min_num.number = value_word;
						min_num.lenght = word.length();
						min_num.pos = pos_of_word;
						min_num.str = word;
					}
					++counter_numbers;
				}
			}
			pos_of_word = word.length() + start_pos + 1;
		}
		if (counter_numbers >= 2) {
			if (min_num.pos > max_num.pos) {
				str.replace(min_num.pos, min_num.lenght, max_num.str);
				str.replace(max_num.pos, max_num.lenght, min_num.str);
			}
			else {
				str.replace(max_num.pos, max_num.lenght, min_num.str);
				str.replace(min_num.pos, min_num.lenght, max_num.str);
			}
			fout << str << '\n';
		}
		else {
			fout << "*" << str << '\n';
		}
		}
	}
	catch (const char* e) {
		std::cerr << e;
	}


	return 0;
}