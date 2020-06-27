#pragma once

#ifndef __MATCHING_H__
#define __MATCHING_H__

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <Eigen/Dense>
#include <matching.h>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using namespace std;

const int MATCH_MIN = 0;
const int MATCH_MAX = 1;


void reduce(MatrixXd& m);

int hasMark(VectorXd& v);

void swapStarsAndPrimes(int i, int j, MatrixXd& stars, MatrixXd& primes);

void findMatching(MatrixXd& m, MatrixXd& result, int type);
#endif
