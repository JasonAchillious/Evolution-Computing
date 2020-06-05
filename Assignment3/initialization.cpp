//
// Created by 志翔 on 2020/6/2.
//

#include "initialization.h"


void mod_dijkstra()
{
    for (int i = 1; i <= vertex_num; i++) {
        for (int j = 1; j <= vertex_num; j++) {
            trav_cost[i][j] = INF;
            serve_cost[i][j] = 0;
        }
    }

    for (int i = 1; i <= total_arc_num; i++) {
        trav_cost[inst_arcs[i].tail_node][inst_arcs[i].head_node] = inst_arcs[i].trav_cost;
    }

    for (int i = 1; i <= task_num; i++) {
        serve_cost[inst_tasks[i].tail_node][inst_tasks[i].head_node] = inst_tasks[i].serv_cost;
    }

    //---------------- original mod_dijkstra --------------------

    int i, j, k, m, minimum;

    for (i = 1; i <= vertex_num; i++)
    {
        for (j = 1; j <= vertex_num; j++)
        {
            if (j == i)
                continue;

            shortest_path[i][j][0] = 1;
            shortest_path[i][j][1] = i;
            min_cost[i][j] = INF;
        }
    }

    int mark[MAX_NODE_TAG_LENGTH], dist[MAX_NODE_TAG_LENGTH], dist1[MAX_NODE_TAG_LENGTH], nearest_neighbor[MAX_NODE_TAG_LENGTH];

    for (i = 1; i <= vertex_num; i++)
    {
        mark[i] = 1;

        for (j = 1; j <= vertex_num; j++)
        {
            if (j == i)
                continue;

            mark[j] = 0;
            dist[j] = trav_cost[i][j];
            dist1[j] = dist[j];
        }

        for (k = 1; k < vertex_num; k++)
        {
            minimum = INF;
            nearest_neighbor[0] = 0;

            for (j = 1; j <= vertex_num; j++)
            {
                if (mark[j])
                    continue;

                if (dist1[j] == INF)
                    continue;

                if (dist1[j] < minimum)
                    minimum = dist1[j];
            }

            if (minimum == INF)
                continue;

            for (j = 1; j <= vertex_num; j++)
            {
                if (mark[j])
                    continue;

                if (dist1[j] == minimum)
                {
                    nearest_neighbor[0] ++;
                    nearest_neighbor[nearest_neighbor[0]] = j;
                }
            }

            int v = nearest_neighbor[1];
            dist1[v] = INF;
            mark[v] = 1;

            if (shortest_path[i][v][0] == 0 || (shortest_path[i][v][0] > 0 && shortest_path[i][v][shortest_path[i][v][0]] != v))
            {
                shortest_path[i][v][0] ++;
                shortest_path[i][v][shortest_path[i][v][0]] = v;
            }

            for (j = 1; j <= vertex_num; j++)
            {
                if (mark[j])
                    continue;

                if (minimum+trav_cost[v][j] < dist[j])
                {
                    dist[j] = minimum+trav_cost[v][j];
                    dist1[j] = minimum+trav_cost[v][j];
                    for (m = 0; m <= shortest_path[i][v][0]; m++)
                    {
                        shortest_path[i][j][m] = shortest_path[i][v][m];
                    }
                }
            }

            for (j = 1; j <= vertex_num; j++)
            {
                if (j == i)
                    continue;

                min_cost[i][j] = dist[j];
            }
        }
    }

    for (i = 1; i <= vertex_num; i++)
    {
        for (j = 1; j <= vertex_num; j++)
        {
            if (shortest_path[i][j][0] == 1)
                shortest_path[i][j][0] = 0;
        }
    }

    for (i = 1; i <= vertex_num; i++)
    {
        shortest_path[i][i][0] = 1;
        shortest_path[i][i][1] = i;
        min_cost[i][i] = 0;
    }
}

individual HD_init(double beta, int k_means_max_iter){
    individual idv;
    vector< vector<int> > task_set(req_edge_num + 1);
    for (int i=0; i < req_edge_num + 1; i++){
        task_set[i].push_back(i);
        //cout << "head: " << inst_tasks[i].head_node << " tail: " << inst_tasks[i].tail_node << endl;
    }
    idv.permu_tasks = hierarchical_decomposition(task_set, 0.5, k_means_max_iter);
    auto find_0 = find(idv.permu_tasks.begin(), idv.permu_tasks.end(), 0);
    if (find_0 != idv.permu_tasks.end()){
        idv.permu_tasks.erase(find_0);
    }

    idv.routes = ulusoy_split(idv.permu_tasks, vehicle_num, capacity);
    for (int i=0; i < idv.routes.size(); i++){
        idv.loads.push_back(get_demand(idv.routes[i]));
        idv.trav_costs.push_back(get_trav_cost(idv.routes[i]));
    }
    idv.total_cost = total_cost_eval(idv.routes);
    return idv;
}

