#pragma once

#include <string>
#include <vector>

std::string to_lower_case(const std::string str);
std::vector<std::size_t> find_one_of_substrings(const std::string str, const std::vector<std::string>& substrings);
std::string trim(const std::string str);
bool is_number(const std::string str);
std::vector<std::pair<int, int>> find_eligible_ranges_by_quotation_marks(const std::string str);
std::vector<std::pair<int, int>> find_eligible_ranges_by_brackets(const std::string str );
bool is_pos_in_ranges(std::size_t pos, std::vector<std::pair<int, int>> ranges);
