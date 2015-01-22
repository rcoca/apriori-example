//
//  transaction_table.hpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Author: Razvan Coca (razvan dot coca at  gmail dot com)
// This file is part of a quick test implementation of apriori algorithm
// and is distributed under the terms of GNU Public License GPL v2
//

#ifndef TRANSACTION_TABLE_HPP
#define TRANSACTION_TABLE_HPP
#include <vector>
#include <map>
#include <set>

typedef std::set<std::size_t> item_set_t;

struct transactions_table_t
{
    transactions_table_t(std::vector<std::vector<std::string>> const& trans_list);
    std::size_t count(item_set_t const& s);
    std::size_t item_count();
    std::vector<item_set_t > init_candidates(std::size_t min_support);
    std::vector<item_set_t > candidates(std::vector<item_set_t > & L,std::size_t min_support);
    std::vector<item_set_t > apriori_rules(std::size_t min_support);
    std::tuple<std::size_t, std::size_t,std::size_t>
        confidence(item_set_t const& antecedents,item_set_t const &consequents);
    std::tuple<std::size_t, std::size_t,std::size_t>
        confidence(const item_set_t &antecedents, const std::vector<std::size_t> &consequents);
    std::string const& operator[](std::size_t id_);
    std::size_t operator[](std::string const& name_);

private:
    std::map<std::string,std::size_t>   names_table;
    std::map<std::size_t,std::string>   id_table;
    std::vector<item_set_t>          transactions;
};
bool is_in(item_set_t const& needle, item_set_t const& haystack);
bool is_equal(item_set_t const& lhs,item_set_t const& rhs);
bool is_in(const item_set_t &needle,const std::vector<item_set_t > &haystack);

#endif // TRANSACTION_TABLE_HPP
