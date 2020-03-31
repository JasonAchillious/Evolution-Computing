
from utils.read_utils import *
from EAcode.eval_func import *
import random
import pandas as pd

tsp_file_path = ["wi29.tsp", "dj38.tsp", "qa194.tsp"]
output_path = "./results/"

eval_num = 500000
test_num = 50


for f in tsp_file_path:

    context = read_tsp("./instances/" + f)
    map_dict = context2dict(context)
    dim = map_dict['DIMENSION']
    # edge_wight_type = map_dict[ 'EDGE_WEIGHT_TYPE' ]
    cities = map_dict['NODE_COORD_SECTION']

    start_city = 0
    idv = list(range(1, 29))
    best_fitness = circuit_euc_dist(0, idv, cities)
    best_so_far_fitness = [best_fitness]
    best_solu = ",".join(map(str, idv))
    best_so_far_Solution = [best_solu]
    best_index = [0]

    result = dict()
    for i in range(test_num):
            print("test" + str(i))
            for j in range(1, eval_num):
                random.shuffle(idv)
                fitness = circuit_euc_dist(0, idv, cities)
                if best_fitness > fitness:
                    best_fitness = fitness
                    best_solu = ",".join(map(str, idv))
                    best_so_far_Solution.append(best_solu)
                    best_so_far_fitness.append(best_fitness)
                    best_index.append(j)
            result[ "fitness_test" + str(i) ] = best_so_far_fitness
            result[ "solution_test" + str(i) ] = best_so_far_Solution
            result[ "index_test" + str(i) ] = best_index
    avg = []


