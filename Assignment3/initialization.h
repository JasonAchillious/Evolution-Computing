//
// Created by 志翔 on 2020/6/2.
//

#ifndef SAHID_INITIALIZATION_H
#define SAHID_INITIALIZATION_H


#include "functions.h"
#include "HD.h"

void mod_dijkstra();

individual HD_init(double beta, int k_means_max_iter);

population mixed_popu_init();

#endif //SAHID_INITIALIZATION_H

