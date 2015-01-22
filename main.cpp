//
//  main.cpp
// ~~~~~~~~~~~~~~~~~~~~~
//
// Author: Razvan Coca (razvan dot coca at  gmail dot com)
// This file is part of a quick test implementation of apriori algorithm
// and is distributed under the terms of GNU Public License GPL v2
//

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>
#include <set>
#include <algorithm>

#include "utils.hpp"
#include "transaction_table.hpp"
#include "combination.hpp"


int main(int argc, char* argv[])
{
    if(argc<4)
    {
        std::clog<<"usage "<<argv[0]<<" transactions_file.txt min_support 'score' "<<std::endl;
        return 1;
    }
    int min_supp=std::atoi(argv[2]);
    double xscore=std::stof(argv[3]);
    auto transactions=transactions_table_t(load_transactions(argv[1]));
    auto L=transactions.apriori_rules(min_supp);
    std::cout<<std::endl;
    std::cout<<"******* sets with support >="<<min_supp<<" *******"<<std::endl;
    std::cout<<std::endl;
    for(auto & set:L)
    {
        for(auto i:set)std::cout<<transactions[i]<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
    std::cout<<"******* rules ******* ( support * trust >= "<<xscore<<")"<<std::endl;
    std::cout<<std::endl;
    for(auto &rule:L)
    {
        std::size_t len=rule.size();
        std::vector<std::size_t> orule(rule.begin(),rule.end());
        for(std::size_t i=1;i<len;++i)
        {
            combination_t C(orule,i);
            do
            {
                item_set_t combination=C();
                std::size_t support,count,score;
                std::tie(support,count,score)=transactions.confidence(combination,rule);
                double trust=double(score)/double(count);
                std::vector<std::size_t> consequents;//(rule.begin(),rule.end());
                std::set_difference(rule.begin(),rule.end(),combination.begin(),combination.end(),std::back_inserter(consequents));
                if(support*trust>=xscore)
                {
                    for(auto& item:combination) std::cout<<transactions[item]<<" ";
                    std::cout<<"=> ";
                    for(auto& item:consequents) std::cout<<transactions[item]<<" ";
                    std::cout<<"[support: "<<support<<" confidence: "<<trust<<" xscore: "<<support*trust<<"]"<<std::endl;
                }

            }while(C.next());

        }
    }
    std::cout<<std::endl;
    return 0;
}

