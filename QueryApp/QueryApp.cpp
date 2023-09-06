// QueryApp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Expression.h"
#include "ConstantExpression.h"
#include "ValueReceiverJson.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main()
{
    std::string input = "first";

    std::cout << "Enter json file with values:" << std::endl;
    std::getline(std::cin, input);

    std::ifstream ifs(input); 
    json j;
    ifs >> j; 

    ValueReceiverJson values(j);

    std::cout << "Type an expression\n";
    while (input != "") {
        std::getline(std::cin, input);

        if (input != "") {
            try {
                Expression* exp = Expression::parse(input);
                if(exp->get_value(&values))
                    std::cout << "TRUE" << std::endl;
                else
                    std::cout << "FALSE" << std::endl;
                delete exp;
            }
            catch (const std::runtime_error& e) {
                std::cout << "An exception has occured: " << e.what() << std::endl;
            }        
            catch (const std::invalid_argument& e) {
                std::cout << "Invalid argument: " << e.what() << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cout << "Out of range: " << e.what() << std::endl;
            }
        }        
    }    
}