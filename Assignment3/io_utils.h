//
// Created by 志翔 on 2020/6/1.
//

#ifndef SAHID_IO_H
#define SAHID_IO_H

#include <string>
#include <vector>
#include <io.h>
#include <time.h>

#include "functions.h"



void getFiles( std::string path, std::vector<std::string>& files );
void read_file (std::string file_path);
void write_result (char* output_result_dir, std::string file_path);

#endif //SAHID_IO_H
