//
// Created by 志翔 on 2020/6/3.
//


#include "functions.h"

void reverse_vt(vector<int>* vt){
    int set_size = vt->size();
    for (int i=0; i < set_size; i++){
        int inv_id = inst_tasks[vt->at(i)].inverse;
        (*vt)[i] = inv_id;
    }
}

vector<int> gen_pt_by_routes(vector< vector<int> > routes){
    vector<int> PT;
    for (int i=0; i < routes.size(); i++){
        for (int j=0; j < routes[i].size(); j++){
            PT.push_back(routes[i][j]);
        }
    }
    return PT;
}

int get_trav_cost(vector<int> route){
    if (route.empty() || route[0] < 0){
        return 0;
    }
    int r_h = inst_tasks[route.front()].head_node;
    int r_t = inst_tasks[route.back()].tail_node;
    int sum_cost = min_cost[DEPOT][r_h] + min_cost[r_t][DEPOT];
    for (int i=0; i < route.size()-1; i++){
        int i_h = inst_tasks[route[i]].head_node;
        int i_t = inst_tasks[route[i]].tail_node;
        int n_h = inst_tasks[route[i+1]].head_node;
        sum_cost += trav_cost[i_h][i_t];
        sum_cost += min_cost[i_t][n_h];
    }
    int b_h = inst_tasks[route.back()].head_node;
    sum_cost += trav_cost[b_h][r_t];
    return  sum_cost;
}

int get_demand(vector<int> route){
    if (route.empty() || route.front() < 0){
        return 0;
    }
    int total_demand = 0;
    for (auto iter = route.begin(); iter != route.end(); iter++){
        total_demand += inst_tasks[*iter].demand;
    }
    return total_demand;
}

int get_sum_of_cost(vector<int> costs){
    int sum = 0;
    for (int i:costs){
        sum += i;
    }
    return sum;
}

vector<int> get_path_id(int start_node, int end_node){
    vector<int> nodes;
    vector<int> pathes;
    for (int k = 1; k <= shortest_path[start_node][end_node][0]; k++) {
        nodes.push_back(shortest_path[start_node][end_node][k]);
    }
    for (int i=0; i < nodes.size()-1; i++){
        pathes.push_back(nodes_with_edgeId[nodes[i]][nodes[i+1]]);
    }
    return pathes;
}

void addEdge(vector < pair<int, int> > adj[], int u,
             int v, int wt)
{
    /*auto iter = find_if(adj[u].begin(), adj[u].end() ,[v](iPair p) { return p.first == v; });
    if (iter != adj[u].end() ){
        if (iter->second > wt){
            *iter = make_pair(v, wt);
            auto iter_u = find_if(adj[v].begin(), adj[v].end() ,[u](iPair p) { return p.first == u; });
            *iter_u = make_pair(u, wt);
        }
    } else {*/
        adj[u].emplace_back(v, wt);
        //adj[v].emplace_back(u, wt);
    //}
}
// from wiki: Dijkstra
vector<int> shortestPath(vector<pair<int,int> > adj[], int src, int V)
{
    vector<int> path(V, -1);

    // 关于stl中的优先队列如何实现，参考下方网址：
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue< iPair, vector <iPair> , greater<iPair> > pq;

    // 距离置为正无穷大
    vector<int> dist(V, INF);

    // 插入源点，距离为0
    pq.push(make_pair(0, src));
    dist[src] = 0;

    /* 循环直到优先队列为空 */
    while (!pq.empty())
    {
        // 每次从优先队列中取出顶点事实上是这一轮最短路径权值确定的点
        int u = pq.top().second;

        pq.pop();

        // 遍历所有边
        for (auto x : adj[u])
        {
            // 得到顶点边号以及边权
            int v = x.first;
            int weight = x.second;

            //可以松弛
            if (dist[v] > dist[u] + weight)
            {
                // 松弛
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
                path[v] = u;
            }
        }
    }
    // 打印最短路
    /*
    printf("End: %d ,Vertex Distance from Source: %d\n", V, src);
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
    fflush(stdout);
    */
    return path;
}

vector< vector<int> > ulusoy_split(vector<int> PT, int max_route, int capa){
    vector< vector<int> > routes(max_route);
    int len = PT.size();
    if (len == 0)
        return routes;
    int V = vertex_num + 1;
    /*
    // Construct a new directed graph
    vector<iPair > adj[V];
    for (int i=0; i < len; i++){
        int head = inst_tasks[PT[i]].head_node;
        int tail = inst_tasks[PT[i]].tail_node;
        int weight = trav_cost[head][tail] + min_cost[DEPOT][head] + min_cost[tail][DEPOT];
        addEdge(adj, head, tail, weight);
    }
    for (int i=0; i < len-1; i++){
        int tail = inst_tasks[PT[i]].tail_node;
        int post_head = inst_tasks[PT[i+1]].head_node;
        if (tail != post_head) {
            addEdge(adj, tail, post_head, 0);
        }
    }
    int ptr1 = 0;
    int ptr2 = ptr1+1;
    while (ptr1 < len && ptr2 < len){
        vector<int> partition;
        for (int i=ptr1; i <= ptr2; i++){
            partition.push_back(PT[i]);
        }
        while (get_demand(partition) <= capa){
            int wt = get_trav_cost(partition);
            int h_p = inst_tasks[partition.front()].head_node;
            int t_p = inst_tasks[partition.back()].tail_node;
            addEdge(adj, h_p, t_p, wt);
            ptr2++;
            if (ptr2 >= len) break;
            partition.push_back(PT[ptr2]);
        }
        partition.clear();
        ptr1++;
        ptr2 = ptr1 + 1;
    }*/
    /*
    // Find shortest path in new graph.
    int start = inst_tasks[PT.front()].head_node;
    vector<int> path = shortestPath(adj, start, V);

    vector<int> s_path;
    int end = inst_tasks[PT.back()].tail_node;
    s_path.push_back(end);
    int lp = path[end];
    while (lp != start){
        if (lp == -1) break;
        s_path.push_back(lp);
        lp = path[lp];
    }
    s_path.push_back(start);
    reverse(s_path.begin(), s_path.end());
    */
    // split the permutation into routes by the shortest path in new graph

    int num_route = 0;
    bool satisfied_constraint = false;
    int ptr = 0;
    int p_path = 0;
    while (num_route < max_route && ptr < len){
        vector<int> route;
        while (ptr < len){
            route.push_back(PT[ptr]);
            ptr++;
            if (ptr >= len || get_demand(route) + inst_tasks[PT[ptr]].demand > capa){
                break;
            }
        }
        routes[num_route] = route;
        num_route++;
    }

    return routes;

}

int total_cost_eval(vector< vector<int> > routes){
    int fitness = 0;
    for (int i=0; i < routes.size(); i++){
        fitness += get_demand(routes[i]);
        fitness += get_trav_cost(routes[i]);
    }
    return fitness;
}

bool sp_better_rules(int t1, int t2, int choosed_idx, int load){
    switch (choosed_idx) {
        case 1:
            return min_cost[inst_tasks[t1].head_node][DEPOT] >= min_cost[inst_tasks[t2].head_node][DEPOT];
        case 2:
            return min_cost[inst_tasks[t1].head_node][DEPOT] < min_cost[inst_tasks[t2].head_node][DEPOT];
        case 3:
            return (inst_tasks[t1].serv_cost / inst_tasks[t1].demand)
            >= (inst_tasks[t2].serv_cost / inst_tasks[t2].demand);
        case 4:
            return (inst_tasks[t1].serv_cost / inst_tasks[t1].demand)
                   < (inst_tasks[t2].serv_cost / inst_tasks[t2].demand);
        case 5:
            if (load <= capacity){
                return min_cost[inst_tasks[t1].head_node][DEPOT] >= min_cost[inst_tasks[t2].head_node][DEPOT];
            } else{
                return min_cost[inst_tasks[t1].head_node][DEPOT] < min_cost[inst_tasks[t2].head_node][DEPOT];
            }
        default:
            printf("Dose not have this rule!\n");
            exit(1);
    }
}



vector< vector<int> > scanning_path(vector<int> group, int num_route, int choosed_rule){
    int k = 0;
    vector< vector<int> > ordered_routes(num_route);
    while (!group.empty()){
        vector<int> load(num_route, 0);
        //vector<int> cost(num_route, 0);
        int endpoint = DEPOT;
        vector<int> route;
        int d = -1;
        while (!group.empty() && d != INF) {
            d = INF;
            int task = -1;
            bool ishead = true;
            for (int j : group) {
                if (load[k] + inst_tasks[j].demand <= capacity) {
                    int head = inst_tasks[j].head_node;
                    int tail = inst_tasks[j].tail_node;
                    int t_min_dist = min(min_cost[endpoint][head], min_cost[endpoint][tail]);
                    if (t_min_dist < d) {
                        d = t_min_dist;
                        if (min_cost[endpoint][head] < min_cost[endpoint][tail]) {
                            task = j;
                        } else {
                            task = inst_tasks[j].inverse;
                            ishead = false;
                        }
                    } else if (t_min_dist == d
                    && sp_better_rules(j, task, choosed_rule, get_demand(route))) {
                        if (min_cost[endpoint][head] < min_cost[endpoint][tail]) {
                            task = j;
                        } else {
                            task = inst_tasks[j].inverse;
                            ishead = false;
                        }
                    }
                }
            }
            if (task != -1) {
                vector<int>::iterator iter = find(group.begin(), group.end(), task);
                if (iter != group.end()) {
                    group.erase(iter);
                    route.push_back(task);
                    load[k] += inst_tasks[task].demand;
                } else {
                    int task_inv = inst_tasks[task].inverse;
                    vector<int>::iterator inv_iter = find(group.begin(), group.end(), task_inv);
                    group.erase(inv_iter);
                    route.push_back(task);
                    load[k] += inst_tasks[task].demand;
                }
                if (ishead)
                    endpoint = inst_tasks[task].tail_node;
                else
                    endpoint = inst_tasks[task].head_node;
            }
        }
        if (k >= num_route) break;
        ordered_routes[k].swap(route);
        k++;
    }

    return ordered_routes;
}