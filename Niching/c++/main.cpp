/******************************************************************************
 * Version: 1.0
 * Last modified on: 21 January, 2013 
 * Developers: Michael G. Epitropakis, Xiaodong Li.
 *      email: mge_(AT)_cs_(DOT)_stir_(DOT)_ac_(DOT)_uk 
 *           : xiaodong_(DOT)_li_(AT)_rmit_(DOT)_edu_(DOT)_au 
 * ***************************************************************************/
#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <math.h>
#include <cstdlib>
#include <algorithm>
#include <utility>
#include "cec2013.h"
#include "matching.h"
#include <fstream>
#include <string>


//extern void findMatching(MatrixXd& m, MatrixXd& result, int type);

using namespace std;

bool write_results = true;
ofstream outfile;

typedef struct Solu
{
        vector<double> *coord;
        double fitness;
        int eval;
        double created_time;
}Solu;

Solu* deep_copy(const Solu *s);

vector< size_t >  sort_indexes(const vector<Solu>  & v);

double dist_Euclidean(vector<double>, vector<double>);

vector< double > share_func_Eucl(vector<Solu>, Solu jidv, double scalling_beta, double radius, double alpha, CEC2013 func);

pair< vector<double>, vector<double> > simple_arith_recomb(vector<double> p1, vector<double> p2);

vector<double> standard_cauchy_mutator(vector<double> offspring, double alpha, CEC2013 *func);

vector<double> exp_rank_selection(vector<double> fit_list);

vector< pair<int, int> > munkres_assign(vector<Solu> parents, vector<Solu> offsprings);

vector<Solu> my_simple_EA(CEC2013 *func, int popu_size);

int run_time = 10; // How many times does the algorithm run for all 20 functions
string dir_result = "results_test2"; // the directory contains the result files

int main()
{
    
    double pr[run_time][21][3];
    double sr[21][3];
    double f1[run_time][21][3];
    memset(pr, 0, 21*3*sizeof(int));
    memset(f1, 0, 21*3*sizeof(int));
    memset(sr, 0, 21*3*sizeof(int));
    double accuracy[3]= {0.1, 0.01, 0.001};
	/* Iterate through functions */
    time_t algo_start_time = time(0);
    CEC2013 *pFunc;
    for (int t=0; t<run_time; t++) {
        time_t each_run_start = time(0);
        /* Iterate through functions */
        cout << "==============================run "<< t <<"=============================" <<endl;
        for (int index = 1; index <= 20; ++index) {
            time_t each_func_start = time(0);

            if (write_results){
                string file_name = "./" + dir_result + "/problem-" + to_string(index) + "-run-" + to_string(t+1) + ".dat";
                
                outfile.open(file_name, fstream::out);

                if (!outfile.is_open()){
                    cout << "fail to open " << file_name << endl; 
                    return 1;
                }
                cout << "open file success"<<endl;
            }
            
            /* Create one */
            cout << "-------------------------------------------------------" <<endl;
            pFunc = new CEC2013(index);
            /* population size in experiment:
	          int popu_size = 0;
            if (pFunc->get_no_goptima() < 20){
                popu_size = 4 * pFunc->get_no_goptima();
            }else{
                popu_size = 16*pFunc->get_dimension();
            }
            */
            int popu_size = pFunc->get_no_goptima();
            if (popu_size % 2 != 0) popu_size++;
    
            cout << "population size: " << popu_size << endl;
            int dim = pFunc->get_dimension();
            cout << "f" << index << " dim: " << dim << endl;
            
            unsigned int niche_size = pFunc->get_no_goptima();

            vector<Solu> optimal_candidates = my_simple_EA(pFunc, popu_size);

            vector< vector<double> > optimals;
            for (unsigned int i=0; i<optimal_candidates.size(); i++){
                optimals.push_back(*(optimal_candidates[i].coord));
            }
            for (std::vector< std::vector<double> >::iterator it = optimals.begin();
                 it != optimals.end(); ++it) {
                cout << "Fitness: " << pFunc->evaluate(*it) << "\tGene:\t";
                for (std::vector<double>::iterator jt = it->begin();
                     jt != it->end(); ++jt) {
                    cout << *jt << "\t";
                }
                cout << endl;
            }

            if (write_results){
                for (auto iter = optimal_candidates.begin();
                iter != optimal_candidates.end(); iter++){
                    vector<double>* gene = iter->coord;
                    for (auto it = gene->begin(); it != gene->end(); it++){
                        outfile << *it << " ";
                    }
                    outfile << "= " << iter->fitness << " ";
                    outfile << "@" << " ";
                    outfile << iter->eval << " ";
                    outfile << iter->created_time << " ";
                    outfile << 1 << endl;
                }
                outfile.close();
            }
            /* Calculate how many global optima are in the population */

	        cout << "optimal_fitness: " << pFunc->get_fitness_goptima() << endl;
            for (int i=0; i<3; i++) {
                std::vector<std::vector<double> > seeds;
                int num_found_peek = how_many_goptima(optimals, seeds, pFunc, accuracy[i], pFunc->get_rho());
                cout << "In the current population there exist "
                     << num_found_peek
                     << " global optimizers." << endl;
                int num_gopt = pFunc->get_no_goptima();
                pr[t][index][i] = ((double)num_found_peek) / num_gopt;
                if (num_found_peek == num_gopt){
                    sr[index][i]++;
                }
                f1[t][index][i] = ((double)num_found_peek) / optimals.size();
                cout << "+++++++++++++" << "scenario-" << i+1 << "+++++++++++++++" << endl;
                cout << "Accuracy: " << accuracy[i] << endl;
                cout << "peek rate: " << pr[t][index][i] << endl;
                cout << "f1 score: " << f1[t][index][i] << endl;
            }
            /* Clean up */
            cout << "-------------------------------------------------------" <<endl;
            delete pFunc;
            for (vector<Solu>::iterator iter = optimal_candidates.begin();
                iter != optimal_candidates.end(); iter++){
                    delete iter->coord;
                    iter->coord = nullptr;
            }

            cout << "Function running time: " << difftime(time(0), each_func_start)<<endl;
        }
        cout << "==========================================================" <<endl;
        cout << "time of a single running: " << difftime(time(0), each_run_start) << endl;
    }
	double pr_avg[21][3];
	double f1_avg[21][3];
   memset(pr_avg, 0, 21*3*sizeof(double));
   memset(f1_avg, 0, 21*3*sizeof(double));

   for (int i=1; i<21; i++) {
      for (int k=0; k<3; k++) {
            sr[i][k] /= run_time;
       }
    }
   double sum_pr[3] = {0,0,0};
   for (int i=1; i<21; i++) {
       for (int t = 0; t < run_time; t++) {
           for (int k=0; k<3; k++) {
                pr_avg[i][k] += pr[t][i][k];
                f1_avg[i][k] += f1[t][i][k];

            }
        }
        
       cout << "function-" << i << ":" << endl;
       for (int k=0; k<3; k++) {
            pr_avg[i][k] /= run_time;
            f1_avg[i][k] /= run_time;
            sum_pr[k] += pr_avg[i][k];
            cout << "accuracy: " << accuracy[k] << " PR: "
            << pr_avg[i][k] << " f1: " << f1_avg[i][k] <<
            " SR: " << sr[i][k] <<endl;
       }
   }
   for (int k=0; k < 3; k++){
      cout << "scenario-1 (accurracy = "<< accuracy[k] << "): sum of PR: " << sum_pr[k] << endl;
   }
   cout << "total running time: " << difftime(time(0), algo_start_time) << endl;

   return EXIT_SUCCESS;
}

Solu* deep_copy(const Solu *s){
    Solu *new_s = new Solu;
    new_s->coord = new vector<double>;
    new_s->coord->assign(s->coord->begin(), s->coord->end());
    new_s->fitness = s->fitness;
    new_s->created_time = s->created_time;
    new_s->eval = s->eval;
    return new_s;
}

double dist_Euclidean(vector<double> p1, vector<double> p2){
    double diff = 0;
    int dim = p1.size();
    for (int i=0; i<dim; i++){
        diff += pow ( (p1[i] - p2[i]), 2 );
    }
    return sqrt(diff);
}

vector<double> share_func_Eucl(vector<Solu> popu, double scalling_beta , double radius, double alpha, CEC2013 *func){
    int popu_size = popu.size();
    int dim = func->get_dimension();
    
    vector<double> share_fits(popu_size);

    for (int i=0; i < popu_size; i++){
        double sh_sum = 0;
        for (int j=0; j < popu_size; j++){
                double dist = dist_Euclidean(*(popu[i].coord), *(popu[j].coord));
                if (dist < radius) {
                    sh_sum += 1 - pow( (dist / radius), alpha);
                }
        }
        share_fits[i] = pow(popu[i].fitness , scalling_beta) / sh_sum;
    }

    return share_fits;
}

vector<size_t>  sort_indexes(const vector<Solu> &v) {
    // initialize original index locations
    vector< size_t>  idx(v.size());
    for (size_t i = 0; i != idx.size(); ++i) idx[i] = i;

    // sort indexes based on comparing values in v
    sort(idx.begin(), idx.end(),
         [& v](size_t i1, size_t i2) {return v[i1].fitness <  v[i2].fitness;});

    return idx;
}

pair< vector<double>, vector<double> > simple_arith_recomb(vector<double> p1, vector<double> p2){
    size_t dim = p1.size();
    
    double prob = rand_uniopen();
    int recomb_p = rand_int(dim);
    
    double weight = rand_uniform() / 5 + 0.2;
    vector<double> offs1(dim);
    vector<double> offs2(dim);

    if (prob < 0.5){
        for (int i=0; i<recomb_p; i++){
            offs1[i] = p1[i];
            offs2[i] = p2[i];
        }
        for (size_t i=recomb_p; i<dim; i++){
            offs1[i] = weight*p1[i] + (1-weight)*p2[i];
            offs2[i] = weight*p2[i] + (1-weight)*p1[i];
        }
    } else {
        for (int i=0; i<recomb_p; i++){
            offs1[i] = weight*p1[i] + (1-weight)*p2[i];
            offs2[i] = weight*p2[i] + (1-weight)*p1[i];
        }
        for (size_t i=recomb_p; i<dim; i++){
            offs1[i] = p1[i];
            offs2[i] = p2[i];
        }
    }
    pair<vector<double>, vector<double> > offs_pair(offs1, offs2);
    return offs_pair;
}

vector<double> standard_cauchy_mutator(vector<double> offspring, double alpha, CEC2013 *func){
    int dim = offspring.size();
    
    double set_boundary_rate = 0.3;
    bool illegal = true;
    vector<double> mutated_offs(dim);
    while (illegal){
        illegal = false;
        for (int i=0; i<dim; i++){
            mutated_offs[i] = offspring[i];
        }
        for (int i=0; i<dim; i++){
            double ub = func->get_ubound(i);
            double lb = func->get_lbound(i);
            mutated_offs[i] += alpha*(ub - lb)*rand_cauchy();
            if (mutated_offs[i] > ub){
                double prob = rand_uniform();
                if (prob < set_boundary_rate){
                    mutated_offs[i] = ub;
                } else {
                    illegal = true;
                    break;
                }
            }
            if (mutated_offs[i] < lb){
                double prob = rand_uniform();
                if (prob < set_boundary_rate){
                    mutated_offs[i] = lb;
                } else {
                    illegal = true;
                    break;
                }
            }
        }
    }
    
    return mutated_offs;
}

vector<double> exp_rank_selection(vector<double> fit_list) {
    int len = fit_list.size();
    vector<int> idx(len);
    for (int i = 0; i < len; ++i) idx[i] = i;

    // sort indexes based on comparing values in v
    sort(idx.begin(), idx.end(),
         [fit_list](size_t i1, size_t i2) -> bool { return fit_list[i1] < fit_list[i2]; });
    // DEBUG
    /*-------------------------------------*/
    //cout << "idx :" << endl;
    //for (int i=0; i < len; i++){
    //    cout << idx[i] << endl;
    //}
    /*-------------------------------------*/

    double C = len - (exp(1.0) - exp(1.0-len))/ (exp(1) - 1);
    // DEBUG cout << C << endl;
    vector<double> prob_list(len);
    for (int i=0; i<len; i++){
        prob_list[i] = (1 - exp(-idx[i])) / C;
    }


    return prob_list;
}

vector< pair<int, int> > munkres_assign(vector<Solu> parents, vector<Solu> offsprings){
    int num_pare = parents.size();
    int num_offs = offsprings.size();

    vector< pair<int, int> > pare_assign_offs; 
    MatrixXd result(num_pare, num_offs);
    result.fill(0);
    MatrixXd dists(num_pare, num_offs);
  
    // read elements into the temporary matrix
    for (int i=0; i<num_pare; i++) {
        for (int j=0; j<num_offs; j++) {
          dists(i, j) = dist_Euclidean(*(parents[i].coord), *(offsprings[j].coord));
        }
    }

    findMatching(dists, result, MATCH_MIN);

    for (int i=0; i<num_pare; i++) {
        for (int j=0; j<num_offs; j++) {
           if (result(i,j) == 1){
               pair<int , int> assign_p(i,j);
               pare_assign_offs.push_back(assign_p);
           } 
        }
    }
    return pare_assign_offs;
}

vector<Solu> my_simple_EA(CEC2013 *func, int popu_size){
    cout << "start EA" << endl;

    time_t single_run_start_t = time(0);
    int dim = func->get_dimension();
    int max_eval = func->get_maxfes();
    //cout << max_eval << endl;
    int num_eval = 0;

    double volumn = 1;
    for (int k=0; k<dim; k++){
        volumn *= func->get_ubound(k) - func->get_lbound(k);
    }
    
    double radius = pow(volumn / func->get_fitness_goptima(), 1.0 / dim);
    double mut_alpha = 0.005 * pow(volumn , 1.0 / (double)dim);

    // initilize population
    //---------------------------------------------
    vector<Solu> popu;
    //vector<Solu> optimum_candidates;

    for (int i=0; i < popu_size; i++){
        vector<double> *coord = new vector<double>(dim);

        for (int k=0; k<dim; k++){
            double ub = func->get_ubound(k);
            double lb = func->get_lbound(k);
            (*coord)[k] = lb + rand_uniform() * (ub-lb);
        }
        double fitness = func->evaluate(*coord);
        num_eval++;
        time_t c_time = time(0);
        Solu idv;  
        idv.coord = coord;
        idv.fitness = fitness;
        idv.eval = num_eval;
        idv.created_time = difftime(c_time, single_run_start_t);
        popu.push_back(idv);        
    }

    while(num_eval <= max_eval){
        vector<double> sh_fits = share_func_Eucl(popu, 1.0, radius, 2.0, func);
        vector<double> prob_list = exp_rank_selection(sh_fits);
        vector<Solu> offsprings;

        for (int i=0; i < (int)(popu_size/2) ; i++) {
            int p1_id = -1;
            int p2_id = -1;
            double prob_p1 = rand_uniform();
            
            while (prob_p1 > 0) {
                p1_id++;
                prob_p1 -= prob_list[p1_id];
            }

            double prob_p2 = rand_uniform();
            while (prob_p2 > 0) {
                p2_id++;
                prob_p2 -= prob_list[p2_id];
            }
           
            vector<double> p1 = *(popu[p1_id].coord);
            vector<double> p2 = *(popu[p2_id].coord);
	        
            pair<vector<double>, vector<double>> off_pair= simple_arith_recomb(p1, p2);
            
            vector<double> offs1_coord = standard_cauchy_mutator(off_pair.first, mut_alpha, func);
            vector<double> offs2_coord = standard_cauchy_mutator(off_pair.second, mut_alpha, func);

	        vector<double> *offs1_coord_p = new vector<double>(offs1_coord);	    
	        vector<double> *offs2_coord_p = new vector<double>(offs2_coord);

            time_t c_time = time(0);
            Solu offs1;
            offs1.coord = offs1_coord_p;
            offs1.fitness = func->evaluate(offs1_coord);
            num_eval++;
            offs1.eval = num_eval;
            offs1.created_time = difftime(c_time, single_run_start_t);
            offsprings.push_back(offs1);

            c_time = time(0);
            Solu offs2;
            offs2.coord = offs2_coord_p;
            offs2.fitness = func->evaluate(offs2_coord);
            num_eval++;
            offs2.eval = num_eval;
            offs2.created_time = difftime(c_time, single_run_start_t);
            offsprings.push_back(offs2);
	        if (num_eval > max_eval){
		        return popu;
	        }

        }
 
        vector< pair<int, int> > assignments = munkres_assign(popu, offsprings);

        vector<Solu> tmp;
        vector<Solu> trush;
        for (size_t i=0; i < assignments.size(); i++){
            
            int pid = assignments[i].first;
            int oid = assignments[i].second;
            
            if (popu[pid].fitness < offsprings[oid].fitness){
                trush.push_back(popu[pid]);
                tmp.push_back(offsprings[oid]);
            }else{
                trush.push_back(offsprings[oid]);
                tmp.push_back(popu[pid]);
            }
        }
       
       for (size_t i=0; i < trush.size(); i++){
            if (NULL != trush[i].coord){
                    delete trush[i].coord;
                    trush[i].coord = NULL;
            }
       }
       trush.clear();
	    popu.clear();
       popu.swap(tmp);

       offsprings.clear();
       vector<Solu>().swap(offsprings);
       
    }

    return popu;
}
