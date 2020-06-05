//
// Created by 志翔 on 2020/6/4.
//

#include "local_search.h"

vector<int> reverse_subroute(vector<int> route){
    int len = route.size();
    if (len == 0){
        return route;
    }
    int p1 = rand() % len;
    int p2 = rand() % len;
    int min_p = min(p1, p2);
    int max_p = max(p1, p2);
    auto it1 = route.begin();
    auto it2 = route.begin();
    advance(it1, min_p);
    advance(it2, max_p);
    reverse(it1, it2);
    for (int i = min_p; i <= max_p; i++){
        int inv_id = inst_tasks[route[i]].inverse;
        route[i] = inv_id;
    }
    return route;
}

vector< vector<int> > merge_split(vector< vector<int> > routes){
    int len = routes.size();
    int num_route = (rand() % (len-2+1))+ 2;

    vector<int> rand_nums(len);
    for (int i=0; i < len; i++){
        rand_nums[i] = i;
    }
    random_shuffle(rand_nums.begin(), rand_nums.end());

    vector< vector<int> > choosed_routes(num_route);
    for (int i=0; i < num_route; i++){
        choosed_routes[i] = routes[rand_nums[i]];
    }

    vector<int> unorder_list = gen_pt_by_routes(choosed_routes);
    vector< vector<int> > order_sp(5);
    for (int i=1; i <= 5; i++){
        order_sp[i-1] = gen_pt_by_routes(scanning_path(unorder_list, num_route, i));
    }


    vector< vector<int> > best_solu = ulusoy_split(order_sp[0], num_route, capacity);
    vector< vector<int> > tmp;
    int best_solu_cost = total_cost_eval(best_solu);
    for (int i=1; i < 5; i++){
        tmp = ulusoy_split(order_sp[i], num_route, capacity);
        int tmp_cost = total_cost_eval(tmp);
        if (tmp_cost < best_solu_cost){
            best_solu_cost = tmp_cost;
            best_solu = tmp;
        }
    }
    for (int i=0; i < num_route; i++){
        routes[rand_nums[i]].assign(best_solu[i].begin(), best_solu[i].end());
    }
    return routes;
}

individual local_search(individual idv){
    bool change = true;
    bool update = false;
    while (change) {
        change = false;
        for (int i=0; i < idv.routes.size(); i++){
            vector<int> reversed = reverse_subroute(idv.routes[i]);
            int n_cost = get_trav_cost(reversed);
            if (n_cost < idv.trav_costs[i]){
                idv.routes[i] = reversed;
                idv.trav_costs[i] = n_cost;
                change = true;
                update = true;
            }
        }
    }
    if (!update){
        vector< vector<int> > solu = merge_split(idv.routes);
        int solu_cost = total_cost_eval(solu);
        if (solu_cost < idv.total_cost) {
            update = true;
            idv.routes = solu;
            idv.total_cost = solu_cost;
            for (int i = 0; i < idv.routes.size(); i++) {
                //idv.trav_costs[i] = get_trav_cost(idv.routes[i]);
                //idv.loads[i] = get_demand(idv.routes[i]);
            }
        }

        if (update){
            change = true;
            while (change) {
                change = false;
                for (int i=0; i < idv.routes.size(); i++){
                    vector<int> reversed = reverse_subroute(idv.routes[i]);
                    int n_cost = get_trav_cost(reversed);
                    if (n_cost < idv.trav_costs[i]){
                        idv.routes[i] = reversed;
                        idv.trav_costs[i] = n_cost;
                        change = true;
                    }
                }
            }
        }
    }
    idv.total_cost = get_sum_of_cost(idv.trav_costs);
    idv.permu_tasks = gen_pt_by_routes(idv.routes);
    return idv;
}