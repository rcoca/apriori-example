//
//  utils.cpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Author: Razvan Coca (razvan dot coca at  gmail dot com)
// This file is part of a quick test implementation of apriori algorithm
// and is distributed under the terms of GNU Public License GPL v2
//

#include "utils.hpp"
#include <fstream>
#include <sstream>

std::vector<std::string> split(std::string const& str)
{
    std::string buf;
    std::stringstream ss(str);
    std::vector<std::string> tokens;
    while (ss >> buf)
        tokens.push_back(buf);
    return tokens;
}

std::vector<std::vector<std::string>>
load_transactions(std::string const& file)
{
    std::ifstream f(file);
    std::string buf;
    std::vector<std::vector<std::string>> transactions;

    while (std::getline(f, buf))
    {
        transactions.push_back(split(buf));
    }
    return transactions;
}
