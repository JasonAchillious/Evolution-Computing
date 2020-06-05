#include <iostream>

#include "io_utils.h"
#include "functions.h"
#include "initialization.h"
#include "HD.h"
#include "local_search.h"
#include "test.h"



int vertex_num;
int req_edge_num;
int req_arc_num;
int nonreq_edge_num;
int nonreq_arc_num;
int task_num;
int total_arc_num;
int vehicle_num;
int capacity;
int lower_bound;

int DEPOT;

int trav_cost[MAX_NODE_TAG_LENGTH][MAX_NODE_TAG_LENGTH];
int serve_cost[MAX_NODE_TAG_LENGTH][MAX_NODE_TAG_LENGTH];
int shortest_path[MAX_NODE_TAG_LENGTH][MAX_NODE_TAG_LENGTH][MAX_NODE_TAG_LENGTH];
int min_cost[MAX_NODE_TAG_LENGTH][MAX_NODE_TAG_LENGTH];

task inst_tasks[MAX_TASK_TAG_LENGTH];
arc inst_arcs[MAX_ARCS_TAG_LENGTH];

char input_files_dir[100] = "../instances/eglese";
char output_result_dir[100] = "../results/egl_output";

int main() {
    std::vector<std::string> files;

    getFiles(input_files_dir, files);
    /* input and preprocessing */

    unsigned int num_files = files.size();

    for (unsigned int file_idx = 1; file_idx < num_files; file_idx++) {
        read_file(files[file_idx]);
        cout << files[file_idx] << endl;

        mod_dijkstra();

        // random seed
        clock_t start = clock();
        int tm;
        tm = time(NULL);
        //tm = 1239002157;
        srand(tm);
        //printf("tm = %d\n", tm);
        std::string output_dir_str(output_result_dir);
        string file_path = files[file_idx];
        std::string::size_type idx_s = file_path.find_last_of('/') + 1;
        std::string::size_type idx_e = file_path.find_last_of('.');
        std::string file_name = file_path.substr(idx_s, idx_e);

        std::string output_file_path = output_dir_str + "/" + file_name + "_result.dat" ;

        const char* output_file =  output_file_path.c_str() ;

        FILE* fp;
        fp = fopen(output_file, "w");

        if (fp == NULL) {
            printf("fail to create file(%s) to write results.", output_file);
            exit(1);
        }

        fprintf(fp, "The random seed is %d.\n", tm);
        fprintf(fp, "There are %d vertices, %d tasks, and the capacities of vehicles is %d.\n\n", vertex_num,
                req_edge_num + req_arc_num, capacity);


        int num_loop = 0;
        int max_loop = 10000;

        individual idv = HD_init(0.8, 200);
        individual feasible_solu = local_search(idv);
        while (num_loop < max_loop){
            individual invader = HD_init(0.8, 200);

            individual improve_s = local_search(invader);

            if (improve_s.total_cost < feasible_solu.total_cost){
                feasible_solu = improve_s;
                cout << "new fitness: " << feasible_solu.total_cost << endl;
                fprintf(fp, "new fitness %d.\n", feasible_solu.total_cost);
            }
            num_loop++;
        }


        fclose(fp);
    }
}