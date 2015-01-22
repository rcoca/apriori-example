//
//  combination.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Author: Razvan Coca (razvan dot coca at  gmail dot com)
// This file is part of a quick test implementation of apriori algorithm
// and is distributed under the terms of GNU Public License GPL v2
//

#ifndef COMBINATION_HPP
#define COMBINATION_HPP
#include <set>
#include <vector>

struct combination_t
{
      combination_t(std::vector<std::size_t> const& items_,std::size_t rank_);
      void init();
      bool next();
      std::set<std::size_t> operator()();
private:
      std::vector<std::size_t> items;
      std::size_t              nitems;
      std::size_t              rank;
      std::vector<bool>        window;
};

#endif // COMBINATION_HPP
