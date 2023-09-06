#include "utilities.h"
#include "pch.h"

std::string to_lower_case(const std::string str)
{
    std::string lowerCaseCopy;
    for (char c : str) {
        lowerCaseCopy.push_back(std::tolower(static_cast<unsigned char>(c)));
    }
    return lowerCaseCopy;
}

std::vector<std::size_t> find_one_of_substrings(const std::string str, const std::vector<std::string>& substrings)
{
    std::vector<std::size_t> positions;

    std::size_t start_index = 0;
    std::size_t new_position = std::string::npos;
    do {
        new_position = std::string::npos;
        for (const std::string sub_str : substrings) {
            std::size_t pos = str.find(sub_str, start_index);
            if (pos != std::string::npos)
                if (new_position == std::string::npos)
                    new_position = pos;
                else
                    if (pos < new_position)
                        new_position = pos;
        }
        if (new_position != std::string::npos) {
            positions.push_back(new_position);
            start_index = new_position + 1;
        }
    } while (new_position != std::string::npos);


    return positions;
}

std::string trim(const std::string str)
{
    size_t start = str.find_first_not_of(" \t\n\r\f\v");

    size_t end = str.find_last_not_of(" \t\n\r\f\v");

    if (start == std::string::npos) {
        return "";
    }

    return str.substr(start, end - start + 1);
}

bool is_number(const std::string str)
{
    for (char c : str)
        if (isdigit(c) == false)
            return false;

    return true;
}

std::vector<std::pair<int, int>> find_eligible_ranges_by_quotation_marks(const std::string str)
{
    std::vector<std::pair<int, int>> eligable_ranges;
    std::size_t current_start = 0, quatation_pos;
    bool in_quatation = false;

    do {
        quatation_pos = str.find('\"', current_start);

        if (quatation_pos != std::string::npos) {
            if (in_quatation == false) {
                if (quatation_pos != 0)
                    eligable_ranges.push_back(std::pair<int, int>(current_start, quatation_pos - 1));
                in_quatation = true;
            }
            else 
                in_quatation = false;                
            
            current_start = quatation_pos + 1;
        }
    } while (quatation_pos != std::string::npos);

    if (quatation_pos == std::string::npos)
        eligable_ranges.push_back(std::pair<int, int>(current_start, str.length() + 1));

    return eligable_ranges;
}

std::vector<std::pair<int, int>> find_eligible_ranges_by_brackets(const std::string str)
{
    std::vector<std::pair<int, int>> eligable_ranges;
    std::vector<std::pair<int, int>> eligable_ranges_by_quotation = find_eligible_ranges_by_quotation_marks(str);
    std::size_t current_start = 0, last_start_depth0 = 0, current_depth = 0;
    std::size_t bracket_left_pos, bracket_right_pos;

    do {
        bool eligible_pos_by_quotation = false;
        std::size_t pos;
        for (pos = current_start; eligible_pos_by_quotation == false && pos != std::string::npos; pos = str.find('(', current_start)) {
            eligible_pos_by_quotation = is_pos_in_ranges(pos, eligable_ranges_by_quotation);
            current_start = pos + 1;
        }
            
        bracket_left_pos = pos;

        eligible_pos_by_quotation = false;
        for (pos = current_start; eligible_pos_by_quotation == false && pos != std::string::npos; pos = str.find(')', current_start)) {
            eligible_pos_by_quotation = is_pos_in_ranges(pos, eligable_ranges_by_quotation);
            current_start = pos + 1;
        }
            
        bracket_right_pos = pos;        

        if (bracket_left_pos < bracket_right_pos) {
            if (current_depth == 0 && bracket_left_pos > last_start_depth0)
                eligable_ranges.push_back(std::pair<int, int>(last_start_depth0, bracket_left_pos - 1));

            current_depth++;
            current_start = bracket_left_pos + 1;
        }

        if (bracket_right_pos < bracket_left_pos) {
            current_depth--;
            if (current_depth == 0)
                last_start_depth0 = bracket_right_pos + 1;
            current_start = bracket_right_pos + 1;
        }
    } while (bracket_left_pos != std::string::npos || bracket_right_pos != std::string::npos);

    if (current_depth == 0)
        eligable_ranges.push_back(std::pair<int, int>(last_start_depth0, str.length() + 1));

    return eligable_ranges;
}

bool is_pos_in_ranges(std::size_t pos, std::vector<std::pair<int, int>> ranges)
{
    for (std::pair<int, int> range : ranges) {
        if (pos >= range.first && pos <= range.second)
            return true;
    }

    return false;
}
