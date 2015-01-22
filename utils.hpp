//
//  utils.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Author: Razvan Coca (razvan dot coca at  gmail dot com)
// This file is part of a quick test implementation of apriori algorithm
// and is distributed under the terms of GNU Public License GPL v2
//

#ifndef UTILS_HPP
#define UTILS_HPP
#include <string>
#include <vector>

std::vector<std::string> split(std::string const& str);

std::vector<std::vector<std::string> >
load_transactions(std::string const& file);

#endif // UTILS_HPP
