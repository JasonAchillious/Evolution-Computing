//
// Created by 志翔 on 2020/6/4.
//

#include "test.h"

/**
* DEBUG for dijkstra
*
*/

void test_dijkstra(){
    for (int i=1; i<vertex_num; i++) {
        for (int j = 1; j < vertex_num; j++) {
            cout << "---------------------------------------------------------------" << endl;
            cout << "min_cost(" << i << "," << j << "):" << min_cost[i][j] << endl;
            cout << "trav_cost(" << i << "," << j << "):" << trav_cost[i][j] << endl;
            cout << "serve_cost(" << i << "," << j << "):" << trav_cost[i][j] << endl;
            cout << "path node: " << endl;
            for (int k = 1; k <= shortest_path[i][j][0]; k++) {
                cout << shortest_path[i][j][k] << " ";
            }
            cout << endl;
        }
    }
}

void test_ulusoy(vector< vector<int> > routes){
    for (int i=0; i < routes.size(); i++){
        cout << "routes " << i << ": ";
        for (int j=0; j < routes[i].size(); j++){
            cout<< routes[i][j] << " ";
        }
        cout << endl;
    }
}

bool PT_ligal(individual idv){
    int size = idv.permu_tasks.size();
    vector<int> permu;
    for (int i=0; i < size; i++){
        int t = idv.permu_tasks[i];
        if (t > req_edge_num){
            int inv = inst_tasks[t].inverse;
            permu.push_back(inv);
        } else{
            permu.push_back(t);
        }
    }
    sort(permu.begin(), permu.end());
    for (int k = 0; k < size; k++) {
        cout <<  permu[k] << " ";
    }
    cout << endl;
    for (int i=0; i < size - 1; i++){
        if (permu[i] + 1 != permu[i+1]){
            return false;
        }
    }
    return true;
}