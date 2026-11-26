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
	if (!stoi(word)) return false;
	size_t result = stoi(word);
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

	std::ifstream fin("in.txt");
	std::string delimeters;
	std::getline(fin, delimeters);
	std::string str;

	while (std::getline(fin,str)) {
		
		Simple_number max_num{ 0 };
		Simple_number min_num{INT64_MAX};
		size_t pos_of_word = str.find_first_not_of(delimeters);
		while (pos_of_word < str.size()) {
			std::string word = Find_word(str, delimeters, pos_of_word);
			size_t counter_numbers = 0;
			if (is_number(word)) {
				size_t value_word = stoi(word);
				if (is_simple(value_word)) {
					if (max_num.number > value_word) {
						max_num.number = value_word;
						max_num.lenght = word.length();
						max_num.pos = pos_of_word;
						max_num.str = word;
					}
					if (min_num.number < value_word) {
						min_num.number = value_word;
						min_num.lenght = word.length();
						min_num.pos = pos_of_word;
						min_num.str = word;
					}
					++counter_numbers;
				}
			}

		}

	}



	return 0;
}