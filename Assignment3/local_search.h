//
// Created by 志翔 on 2020/6/4.
//

#ifndef SAHID_LOCAL_SEARCH_H
#define SAHID_LOCAL_SEARCH_H


#include "functions.h"


vector< int > reverse_subroute(vector<int> route);

vector< vector<int> > merge_split(vector< vector<int> > routes);

individual local_search(individual idv);


#endif //SAHID_LOCAL_SEARCH_H
