
from utils.read_utils import *
from EAcode.eval_func import *
import random
import argparse
import matplotlib.pyplot as plt
import os

parser = argparse.ArgumentParser(description='Process the random search - generating and test.')

parser.add_argument('-f', '--instance', type = str, default="wi29.tsp",
                      help='the name of tsp file that need to read and test')
parser.add_argument('-e', '--eval_num', type = int, default=500000,
                      help='Number of evaluation')
parser.add_argument('-p', '--popu_size', type = int, default=10,
                      help='Size of population.')

parser.add_argument('-s', '--start_city', type=int, default=0,
                      help='The index of starting city')
parser.add_argument('-l', '--tour_length', type=int, default=28,
                      help='The expected tour length')

parser.add_argument('--plot', type=bool, default=False,
                      help='The expected tour length')

args = parser.parse_args()

tsp_file = args.instance
eval_num = args.eval_num

context = read_tsp(os.path.join("./instances/", tsp_file))
map_dict = context2dict(context)
dim = map_dict['DIMENSION']
# edge_wight_type = map_dict[ 'EDGE_WEIGHT_TYPE' ]
cities = map_dict['NODE_COORD_SECTION']

start_city = args.start_city
choices = list(range(dim))
choices.remove(start_city)
assert args.tour_length < dim
idv = random.sample(choices, args.tour_length)
best_fitness = circuit_euc_dist(start_city, idv, cities)
best_so_far_fitness = [best_fitness]
best_solu = ",".join(map(str, idv))
best_so_far_Solution = [best_solu]
best_index = [0]

result = dict()


for j in range(1, eval_num):
            random.shuffle(idv)
            fitness = circuit_euc_dist(start_city, idv, cities)
            if best_fitness > fitness:
                    best_fitness = fitness
                    best_solu = ",".join(map(str, idv))
                    best_so_far_Solution.append(best_solu)
                    best_so_far_fitness.append(best_fitness)
                    best_index.append(j)
result[ "fitness_test" ] = best_so_far_fitness
result[ "solution_test" ] = best_so_far_Solution
result[ "index_test" ] = best_index

if args.plot:
    fig = plt.figure(figsize=(4, 4))
    plt.tight_layout()
    plt.plot(result["index_test"], result["fitness_test"], color="b")
    plt.title("random search", fontsize='large', fontweight='bold')

    plt.ylabel("Distance")
    plt.xlabel("Evalution *10")
    plt.show()

print("best fitness: ", result["fitness_test"][-1])
print("best solution: ", result["solution_test"][-1])



