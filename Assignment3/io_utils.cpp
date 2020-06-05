//
// Created by 志翔 on 2020/6/1.
//
#include "io_utils.h"

void getFiles( std::string path, std::vector<std::string>& files ) {
    //文件句柄
    long hFile = 0;
    //文件信息 file info
    struct _finddata_t fileinfo;
    std::string p;
    if ((hFile = _findfirst(p.assign(path).append("/*").c_str(), &fileinfo)) != -1) {
        do {
            //如果是目录,迭代之 If it is a dir, iterate it.
            //如果不是,加入列表 If it is a file, add it to list.
            if ((fileinfo.attrib & _A_SUBDIR)) {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("/").append(fileinfo.name), files);
            } else {
                files.push_back(p.assign(path).append("/").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }

}

void read_file(std::string file_path){
    char dummy_string[50];

    FILE *fp;
    fp = fopen(file_path.c_str(), "r");
    if (fp == NULL) {
        printf("The file do not exits. Check the path of instances");
        exit(1);
    }

    while (1) {
        fscanf(fp, "%s", dummy_string);
        //printf("dummy_string = %s\n", dummy_string);

        if (strcmp(dummy_string, "VERTICES") == 0) {
            fscanf(fp, "%s", dummy_string);
            fscanf(fp, "%d", &vertex_num);
        } else if (strcmp(dummy_string, "ARISTAS_REQ") == 0) {
            fscanf(fp, "%s", dummy_string);
            fscanf(fp, "%d", &req_edge_num);
        } else if (strcmp(dummy_string, "ARISTAS_NOREQ") == 0) {
            fscanf(fp, "%s", dummy_string);
            fscanf(fp, "%d", &nonreq_edge_num);
        } else if (strcmp(dummy_string, "VEHICULOS") == 0) {
            fscanf(fp, "%s", dummy_string);
            fscanf(fp, "%d", &vehicle_num);
        } else if (strcmp(dummy_string, "CAPACIDAD") == 0) {
            fscanf(fp, "%s", dummy_string);
            fscanf(fp, "%d", &capacity);
        } else if (strcmp(dummy_string, "LISTA_ARISTAS_REQ") == 0) {
            task_num = 2 * req_edge_num + req_arc_num;
            total_arc_num = task_num + 2 * nonreq_edge_num + nonreq_arc_num;

            fscanf(fp, "%s", dummy_string);

            for (int i = 1; i <= req_edge_num; i++) {
                fscanf(fp, "%s", dummy_string);
                fscanf(fp, "%d,", &inst_tasks[i].head_node);
                fscanf(fp, "%d)", &inst_tasks[i].tail_node);
                fscanf(fp, "%s", dummy_string);
                fscanf(fp, "%d", &inst_tasks[i].serv_cost);
                fscanf(fp, "%s", dummy_string);
                fscanf(fp, "%d", &inst_tasks[i].demand);
                inst_tasks[i].dead_cost = inst_tasks[i].serv_cost;
                inst_tasks[i].inverse = i + req_edge_num;

                inst_tasks[i + req_edge_num].head_node = inst_tasks[i].tail_node;
                inst_tasks[i + req_edge_num].tail_node = inst_tasks[i].head_node;
                inst_tasks[i + req_edge_num].dead_cost = inst_tasks[i].dead_cost;
                inst_tasks[i + req_edge_num].serv_cost = inst_tasks[i].serv_cost;
                inst_tasks[i + req_edge_num].demand = inst_tasks[i].demand;
                inst_tasks[i + req_edge_num].inverse = i;

                inst_arcs[i].head_node = inst_tasks[i].head_node;
                inst_arcs[i].tail_node = inst_tasks[i].tail_node;
                inst_arcs[i].trav_cost = inst_tasks[i].dead_cost;
                inst_arcs[i + req_edge_num].head_node = inst_arcs[i].tail_node;
                inst_arcs[i + req_edge_num].tail_node = inst_arcs[i].head_node;
                inst_arcs[i + req_edge_num].trav_cost = inst_arcs[i].trav_cost;
            }
        } else if (strcmp(dummy_string, "LISTA_ARISTAS_NOREQ") == 0) {
            fscanf(fp, "%s", dummy_string);

            for (int i = task_num + 1; i <= task_num + nonreq_edge_num; i++) {
                fscanf(fp, "%s", dummy_string);
                fscanf(fp, "%d,", &inst_arcs[i].head_node);
                fscanf(fp, "%d)", &inst_arcs[i].tail_node);
                fscanf(fp, "%s", dummy_string);
                fscanf(fp, "%d", &inst_arcs[i].trav_cost);

                inst_arcs[i + nonreq_edge_num].head_node = inst_arcs[i].tail_node;
                inst_arcs[i + nonreq_edge_num].tail_node = inst_arcs[i].head_node;
                inst_arcs[i + nonreq_edge_num].trav_cost = inst_arcs[i].trav_cost;
            }
        } else if (strcmp(dummy_string, "DEPOSITO") == 0) {
            fscanf(fp, "%s", dummy_string);
            fscanf(fp, "%d", &DEPOT);
            break;
        }
    }

    fclose(fp);

    inst_tasks[DUMMY_CYCLE].tail_node = DEPOT;
    inst_tasks[DUMMY_CYCLE].head_node = DEPOT;
    inst_tasks[DUMMY_CYCLE].dead_cost = 0;
    inst_tasks[DUMMY_CYCLE].serv_cost = 0;
    inst_tasks[DUMMY_CYCLE].demand = 0;
    inst_tasks[DUMMY_CYCLE].inverse = DUMMY_CYCLE;
    inst_arcs[DUMMY_CYCLE].tail_node = 1;
    inst_arcs[DUMMY_CYCLE].head_node = 1;
    inst_arcs[DUMMY_CYCLE].trav_cost = 0;
}

void write_result(char* output_result_dir, std::string file_path){
    std::string output_dir_str(output_result_dir);

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

    //fprintf(fp, "The random seed is %d.\n", tm);
    fprintf(fp, "There are %d vertices, %d tasks, and the capacities of vehicles is %d.\n\n", vertex_num,
            req_edge_num + req_arc_num, capacity);


    fclose(fp);
}
