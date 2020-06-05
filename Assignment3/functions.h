//
// Created by 志翔 on 2020/6/1.
//

#ifndef SAHID_FUNCTIONS_H
#define SAHID_FUNCTIONS_H

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 2100000000
#define DUMMY_CYCLE 0
#define MAX_NODE_TAG_LENGTH 300
#define MAX_ARCS_TAG_LENGTH 1001
#define MAX_TASK_TAG_LENGTH 1001

using namespace std;

typedef struct task
{
    int head_node;
    int tail_node;
    int dead_cost;
    int serv_cost;
    int demand;
    int inverse;
} task;

typedef struct arc
{
    int tail_node;
    int head_node;
    int trav_cost;
} arc;

typedef struct virtual_task
{
    vector<task> vt_set;

} virtual_task;

typedef struct individual
{
    vector<int> permu_tasks;
    vector< vector<int> > routes;
    int total_cost;
    vector< int > loads;
    vector< int > trav_costs;

} individual;

typedef struct population
{
    individual elite;
    vector<individual> crossover_class;
    vector<individual> ls_class;
    int best_so_far_cost;
} population;

typedef pair<int, int> iPair;

extern int vertex_num;
extern int req_edge_num;
extern int req_arc_num;
extern int nonreq_edge_num;
extern int nonreq_arc_num;
extern int task_num;
extern int total_arc_num;
extern int vehicle_num;
extern int capacity;
extern int lower_bound;

extern int DEPOT;

extern int trav_cost[MAX_NODE_TAG_LENGTH][MAX_NODE_TAG_LENGTH];
extern int serve_cost[MAX_NODE_TAG_LENGTH][MAX_NODE_TAG_LENGTH];
extern int shortest_path[MAX_NODE_TAG_LENGTH][MAX_NODE_TAG_LENGTH][MAX_NODE_TAG_LENGTH];
extern int min_cost[MAX_NODE_TAG_LENGTH][MAX_NODE_TAG_LENGTH];


extern task inst_tasks[MAX_TASK_TAG_LENGTH];
extern arc inst_arcs[MAX_ARCS_TAG_LENGTH];

void reverse_vt(vector<int>* vt);

vector<int> gen_pt_by_routes(vector< vector<int> > routes);

int get_trav_cost(vector<int> route);

int get_demand(vector<int> route);

int get_sum_of_cost(vector<int> costs);

void addEdge(vector <pair<int, int> > adj[], int u,
             int v, int wt);

vector<int> shortestPath(vector<pair<int,int> > adj[], int V, int src);

vector< vector<int> > ulusoy_split(vector<int> PT, int max_route, int capa);

int total_cost_eval(vector< vector<int> > routes);

vector< vector<int> > scanning_path(vector<int> group, int num_route, int choosed_rule);

#endif //SAHID_FUNCTIONS_H
