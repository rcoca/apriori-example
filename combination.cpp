//
//  combination.cpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Author: Razvan Coca (razvan dot coca at  gmail dot com)
// This file is part of a quick test implementation of apriori algorithm
// and is distributed under the terms of GNU Public License GPL v2
//

#include "combination.hpp"
#include <algorithm>

combination_t::combination_t(std::vector<std::size_t> const& items_,std::size_t rank_):
    items{items_},nitems(items_.size()),rank(rank_),window(nitems,false)
{
    init();
}
void combination_t::init()
{
    std::fill(window.begin() + rank, window.end(), true);
}
bool combination_t::next()
{
    return std::next_permutation(window.begin(), window.end());
}
std::set<std::size_t> combination_t::operator()()
{
    std::set<std::size_t> comb;
    for (std::size_t i = 0; i < nitems; ++i)
    {
         if(!window[i]) comb.insert(items[i]);
    }
    return comb;
}
