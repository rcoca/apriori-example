//
//  transaction_table.cpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Author: Razvan Coca (razvan dot coca at  gmail dot com)
// This file is part of a quick test implementation of apriori algorithm
// and is distributed under the terms of GNU Public License GPL v2
//

#include "transaction_table.hpp"
#include <algorithm>

transactions_table_t::transactions_table_t(std::vector<std::vector<std::string>> const& trans_list)
{
    std::size_t id=0;
    for(auto & trans:trans_list)
    {
        item_set_t transaction;
        for(auto& item:trans)
        {
            if(names_table.insert(std::make_pair(item,id)).second)
            {
                id_table.insert(std::make_pair(id,item));
                ++id;
            }
            transaction.insert(names_table[item]);
        }
        if(!transaction.empty())
            transactions.push_back(transaction);
    }
}

bool is_in(item_set_t const& needle,item_set_t const& haystack)
{
    std::size_t count=0;
    auto i=needle.begin();
    for(;i!=needle.end();++i)
    {
        if(std::find(haystack.begin(),haystack.end(),*i)!=haystack.end())
            ++count;
    }
    return count>=needle.size();
}
bool is_in(const item_set_t &needle,const std::vector<item_set_t > &haystack)
{
    for(auto & s:haystack)
        if(is_equal(s,needle)) return true;
    return false;
}
bool is_equal(item_set_t const& lhs, item_set_t const& rhs)
{
    std::size_t count=0;
    auto i=rhs.begin();
    auto j=lhs.begin();
    for(;i!=rhs.end()&&j!=lhs.end();++i,++j)
    {
        if(*i==*j)
            ++count;
    }
    return count>=rhs.size();
}
std::size_t transactions_table_t::count(item_set_t const& s)
{
    std::size_t count=0;
    for(auto& trans:transactions)
    {
        if(is_in(s,trans))
            count++;
    }
    return count;
}

std::size_t transactions_table_t::item_count()
{
    return names_table.size();
}
std::string const& transactions_table_t::operator[](std::size_t id_)
{
    return id_table[id_];
}

std::size_t transactions_table_t::operator[](std::string const& name_)
{
    return names_table[name_];
}


std::vector<item_set_t >  transactions_table_t::init_candidates(std::size_t min_support)
{
    std::vector<item_set_t > L;
    for(auto i:this->id_table)
    {
        auto candidate=item_set_t{i.first};
        if(this->count(candidate)>=min_support)
            L.push_back(candidate);
    }
    return L;
}
std::vector<item_set_t >  transactions_table_t::candidates(std::vector<item_set_t > & L,std::size_t min_support)
{
    std::vector<item_set_t > ret;
    for(auto x:L)
    {
        for(auto y:L)
        {
            item_set_t c=x;
            c.insert(y.begin(),y.end());
            if(c.size()!=x.size()+1) continue;
            if(this->count(c)>=min_support && ! is_in(c,ret))
            {
                ret.push_back(c);
            }
        }
    }
    return ret;
}
std::vector<item_set_t >  transactions_table_t::apriori_rules(std::size_t min_support)
{
    std::vector<item_set_t> ret;
    std::vector<item_set_t > L=init_candidates(min_support);
    for(auto k=1;!L.empty();++k)
    {
        auto C=candidates(L,min_support);
        if(!C.empty()) L=C;
        else break;
        std::copy(L.begin(),L.end(),std::back_inserter(ret));
    }
    return ret;
}

std::tuple<std::size_t, std::size_t,std::size_t>
transactions_table_t::confidence(item_set_t const& antecedents,item_set_t const &consequents)
{
    std::size_t support=0,count=0,score=0;
    for(auto t:transactions)
    {
        if(is_in(consequents,t))
            support++;
        if(is_in(antecedents,t))
        {
            count++;
            if(is_in(consequents,t))
                score++;
        }

    }
    return std::make_tuple(support,count,score);
}

std::tuple<std::size_t, std::size_t,std::size_t>
transactions_table_t::confidence(item_set_t const& antecedents,std::vector<std::size_t> const &consequents)
{
    return confidence(antecedents,item_set_t(consequents.begin(),consequents.end()));
}
