//
// Created by 志翔 on 2020/6/1.
//

#ifndef SAHID_HD_H
#define SAHID_HD_H

#include "functions.h"


using namespace std;

double closeness_tasks(vector<int> t1, vector<int> t2);

vector<virtual_task> k_means_init_max_sum(vector<virtual_task> lower_layer, int num_cluster);

void k_means_init_rand(vector< vector<int> >* clusters,
                       vector<int>* centroid_set,
                       int task_size,
                       int num_cluster,
                       bool is_centroid[],
                       int cluster_id[]);

vector< vector< vector<int> > > k_means(vector< vector<int> > lower_layer, int num_cluster, int max_iter);

vector<int> hierarchical_decomposition(vector< vector<int> >  VT, double beta, int k_mean_max_iter);

#endif //SAHID_HD_H
