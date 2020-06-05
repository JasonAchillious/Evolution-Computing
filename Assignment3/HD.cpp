//
// Created by 志翔 on 2020/6/1.
//
#include "HD.h"

#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <iostream>

double closeness_tasks(vector<int> t1, vector<int> t2){
    int sum = 0;
    int v1 = inst_tasks[t1.front()].head_node;
    int u1 = inst_tasks[t1.back()].tail_node;
    int v2 = inst_tasks[t2.front()].head_node;
    int u2 = inst_tasks[t2.back()].tail_node;
    if (v1 == DEPOT && u1 == DEPOT){
        sum += min_cost[v2][DEPOT];
        sum += min_cost[u2][DEPOT];
        return sum / 2.0;
    } else if (v2 == DEPOT && u2 == DEPOT){
        sum += min_cost[v1][DEPOT];
        sum += min_cost[v1][DEPOT];
        return sum / 2.0;
    } else {
        sum += min_cost[v1][v2];
        sum += min_cost[u1][u2];
        sum += min_cost[v1][u2];
        sum += min_cost[u1][v2];
        return sum / 4.0;
    }
}

vector<virtual_task> k_means_init_max_sum(vector<virtual_task> lower_layer, int num_cluster){
    vector<virtual_task> centroid_set;
    virtual_task dummy_vt;
    dummy_vt.vt_set.push_back(inst_tasks[DUMMY_CYCLE]);
    centroid_set.push_back(dummy_vt);
    for (int i=1; i < num_cluster; i++){
        double sum[lower_layer.size()];
        for (int j=0; j < lower_layer.size(); j++){
            for (int k=0; k < i; k++){
                //sum[j] += closeness_tasks(centroid_set[k], lower_layer[j]);
            }
        }
        int maxPosition = max_element(sum, sum+lower_layer.size()) - sum;
        centroid_set.push_back(lower_layer[maxPosition]);
    }
    return centroid_set;
}

void k_means_init_rand(vector< vector<int> >* clusters,
                       vector< int >* centroid_set,
                       int task_size,
                       int num_cluster,
                       bool is_centroid[],
                       int cluster_id[]
                       ){

    virtual_task dummy_vt;
    dummy_vt.vt_set.push_back(inst_tasks[DUMMY_CYCLE]);
    (*centroid_set).push_back(DUMMY_CYCLE);
    (*clusters)[0].push_back(DUMMY_CYCLE);
    is_centroid[0] = true;
    cluster_id[DUMMY_CYCLE] = 0;


    //----------unduplicated random int-------------------
    vector<int> rand_nums(task_size-1);
    for (int i=0; i < task_size-1; i++){
        rand_nums[i] = i+1;
    }

    random_shuffle(rand_nums.begin(), rand_nums.end());

    //-----------pick up first n-1 virtual task-----------
    for (int i=1; i < num_cluster; i++) {
        (*centroid_set).push_back(rand_nums[i]);
        (*clusters)[i].push_back(rand_nums[i]);
        is_centroid[rand_nums[i]] = true;
        cluster_id[rand_nums[i]] = i;
    }
}


vector< vector< vector<int> > > k_means(vector< vector<int> > lower_layer, int num_cluster, int max_iter){
    vector< vector<int> > clusters(num_cluster);
    int layer_size = lower_layer.size();
    int cluster_id[layer_size];
    bool is_centroid[layer_size];
    for (int i=0; i < layer_size; i++){
        is_centroid[i] = false;
        cluster_id[i] = -1;
    }
    // ------------initialize the centroids----------------------
    vector<int> centroid_set;
    k_means_init_rand(&clusters, &centroid_set, lower_layer.size(), num_cluster, is_centroid, cluster_id);

    // ------------start loop---------------------------------------
    bool stop_criteria = false;
    int num_iter = 0;
    while(!stop_criteria && num_iter < max_iter){
        // Assignment
        for (int i=0; i < layer_size; i++){
            if (is_centroid[i]) continue;
            double min_dist = INF;
            int origin_cluster_id = cluster_id[i];
            for (int j=0; j < num_cluster; j++){
                double dist = closeness_tasks(lower_layer[i], lower_layer[centroid_set[j]]);
                if (min_dist > dist){
                    min_dist = dist;
                    cluster_id[i] = j;
                }
            }
            if (origin_cluster_id == -1) {
                clusters[cluster_id[i]].push_back(i);
            } else if (origin_cluster_id == cluster_id[i]){
                continue;
            } else {
                auto iter = find(clusters[origin_cluster_id].begin(),
                        clusters[origin_cluster_id].end(),
                        i);
                if(iter!= clusters[origin_cluster_id].end()) {
                    clusters[origin_cluster_id].erase(iter);
                    clusters[cluster_id[i]].push_back(i);
                }
            }
        }

        // Update
        stop_criteria = true;
        for (int i=0; i < num_cluster; i++){
            int cluster_size = clusters[i].size();
            vector<double> min_avg_dist(cluster_size);
            for (int j=0; j < cluster_size; j++){
                min_avg_dist[j] = 0;
                for (int k=0; k < cluster_size; k++){
                    min_avg_dist[j] += closeness_tasks(lower_layer[clusters[i][j]]
                            , lower_layer[clusters[i][k]]);
                }
                min_avg_dist[j] /= cluster_size;
            }
            auto min_iter = min_element(min_avg_dist.begin(), min_avg_dist.end());
            int min_idx = distance(min_avg_dist.begin(), min_iter);

            if (is_centroid[clusters[i][min_idx]]){
                continue;
            }else {
                is_centroid[centroid_set[i]] = false;
                centroid_set[i] = clusters[i][min_idx];
                is_centroid[centroid_set[i]] = true;
            }
            stop_criteria = false;
        }
        num_iter++;
    }

    vector< vector< vector<int> > > groups;
    for (int i = 0; i < num_cluster; i++) {
        vector< vector<int> > vec;
        for (int j = 0; j < clusters[i].size(); j++) {
            vec.push_back( lower_layer[clusters[i][j]]  );
        }
        groups.push_back(vec);
    }
    return groups;
}

vector<int> best_insertion_heuristic(vector< vector<int> > group){
    int endpoint = DEPOT;
    vector<int> ordered_group;
    while (!group.empty()){
        vector<int> dists(group.size());
        bool is_head[group.size()];
        for (int j=0; j < group.size(); j++){

            int vt_front_head = inst_tasks[group[j].front()].head_node;
            int vt_back_tail = inst_tasks[group[j].back()].tail_node;

            if(min_cost[endpoint][vt_front_head] < min_cost[endpoint][vt_back_tail]){
                dists[j] = min_cost[endpoint][vt_front_head];
                is_head[j] = true;
            }else{
                dists[j] = min_cost[endpoint][vt_back_tail];
                is_head[j] = false;
            }

        }

        auto min_iter = min_element(dists.begin(), dists.end());
        int min_idx = distance(dists.begin(), min_iter);

        if (is_head[min_idx])
            endpoint = inst_tasks[group[min_idx].back()].tail_node;
        else
            endpoint = inst_tasks[group[min_idx].front()].head_node;

        if (group[min_idx].size() == 1){
            if (is_head[min_idx]){
                ordered_group.push_back(group[min_idx].front());
            } else {
                int inv_id = inst_tasks[group[min_idx].front()].inverse;
                ordered_group.push_back(inv_id);
            }
        }else {
            if (!is_head[min_idx]) {
                reverse_vt(&group[min_idx]);
            }

            for (int i = 0; i < group[min_idx].size(); i++) {
                ordered_group.push_back(group[min_idx][i]);
            }
        }

        group.erase(group.begin()+min_idx);
    }
    return ordered_group;
}

vector<int> hierarchical_decomposition(vector< vector<int> > VT, double beta, int k_mean_max_iter){
    while (VT.size() > 1){
        int rand_ub = (int) ceil(beta * VT.size());
        int num_cluster = rand() % rand_ub + 1;
        vector< vector< vector<int> > > groups = k_means(VT, num_cluster, k_mean_max_iter);
        //cout << "num of groups: " << groups.size() << endl;
        VT.clear();
        for (int i=0; i < groups.size(); i++){
            VT.push_back(best_insertion_heuristic(groups[i]));
        }
    }
    return VT.front();
}

