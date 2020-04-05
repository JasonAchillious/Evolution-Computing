from EAcode.initialization import *
from utils.read_utils import *
from EAcode.eval_func import *
from EAcode.selection_schemes import *
from EAcode.mutator import *
import matplotlib.pyplot as plt
import random
import pandas as pd


"""
    ea_simple is for generating the data and analysis.
    ea_test if for testing and plot.
    Both are in the same of EA algorithm.
    
"""

def ea_simple(tsp_file_path, output_path, gen_num, test_num, popu_size,
               tour_length=None, start_city=None, p_cities=None, **kwargs):

    context = read_tsp(tsp_file_path)
    map_dict = context2dict(context)
    dim = map_dict['DIMENSION']
    # edge_wight_type = map_dict[ 'EDGE_WEIGHT_TYPE' ]
    cities = map_dict['NODE_COORD_SECTION']

    if tour_length is None:
        tour_length = dim
    assert tour_length <= dim

    num_pass_city = tour_length - 1

    if start_city is None:
        start_city = random.randint(0, dim-1)
    if p_cities is None:
        c_choice = list(range(dim))
        if start_city in c_choice:
            c_choice.remove(start_city)
        p_cities = random.sample(c_choice, num_pass_city)

    test = 0
    result = dict()
    print("starting city: ", start_city)
    while test < test_num:
        print("test:", test)

        popu = init_random(popu_size, p_cities, num_pass_city)

        best_so_far_fitness = [ ]
        best_so_far_solu = [ ]
        fitness_list = [ circuit_euc_dist(start_city, idv, cities) for idv in popu ]

        best_fitness = min(fitness_list)
        best_index = fitness_list.index(best_fitness)
        best_solu = ",".join(map(str, popu[ best_index ]))

        best_so_far_fitness.append(best_fitness)
        best_so_far_solu.append(best_solu)

        gen = 1
        while gen < gen_num:
            prob_list = kwargs["selector"](fitness_list)
            new_parents = [select_individual(popu, prob_list) for i in range(popu_size)]
            for idv in new_parents:
                if kwargs["mutator"].__code__.co_argcount > 1:
                    kwargs["mutator"](idv, kwargs["mut_args"])
                else:
                    kwargs["mutator"](idv)
            fitness_list = [circuit_euc_dist(start_city, idv, cities) for idv in popu]

            if best_fitness > min(fitness_list):
                best_fitness = min(fitness_list)
                best_index = fitness_list.index(best_fitness)
                best_solu = ",".join(map(str, popu[best_index]))
                best_so_far_fitness.append(best_fitness)
                best_so_far_solu.append(best_solu)
            else:
                best_so_far_fitness.append(best_fitness)
                best_so_far_solu.append(best_solu)

            gen += 1

        result["fitness_test" + str(test) ] = best_so_far_fitness
        result["solution_test" + str(test) ] = best_so_far_solu
        test += 1
    df = pd.DataFrame(result)
    df.to_csv(output_path, index=False)


def ea_test(tsp_file_path, gen_num, popu_size, plot=False,
               tour_length=None, start_city=None, p_cities=None, **kwargs):

    context = read_tsp(tsp_file_path)
    map_dict = context2dict(context)
    dim = map_dict['DIMENSION']
    # edge_wight_type = map_dict[ 'EDGE_WEIGHT_TYPE' ]
    cities = map_dict['NODE_COORD_SECTION']

    if tour_length is None:
        tour_length = dim
    assert tour_length <= dim

    num_pass_city = tour_length - 1

    if start_city is None:
        start_city = random.randint(0, dim-1)
    if p_cities is None:
        c_choice = list(range(dim))
        if start_city in c_choice:
            c_choice.remove(start_city)
        p_cities = random.sample(c_choice, num_pass_city)


    result = dict()
    print("starting city: ", start_city)

    popu = init_random(popu_size, p_cities, num_pass_city)

    best_so_far_fitness = [ ]
    best_so_far_solu = [ ]
    fitness_list = [ circuit_euc_dist(start_city, idv, cities) for idv in popu ]

    best_fitness = min(fitness_list)
    best_index = fitness_list.index(best_fitness)
    best_solu = ",".join(map(str, popu[ best_index ]))

    best_so_far_fitness.append(best_fitness)
    best_so_far_solu.append(best_solu)

    gen_index = [0]

    gen = 1
    while gen < gen_num:
        prob_list = kwargs["selector"](fitness_list)
        new_parents = [select_individual(popu, prob_list) for i in range(popu_size)]
        for idv in new_parents:
                kwargs["mutator"](idv)
        fitness_list = [circuit_euc_dist(start_city, idv, cities) for idv in popu]

        if best_fitness > min(fitness_list):
                best_fitness = min(fitness_list)
                best_index = fitness_list.index(best_fitness)
                best_solu = ",".join(map(str, popu[best_index]))
                best_so_far_fitness.append(best_fitness)
                best_so_far_solu.append(best_solu)
                gen_index.append(gen)

        gen += 1
    result[ "fitness_test" ] = best_so_far_fitness
    result[ "solution_test" ] = best_so_far_solu
    result[ "index_test" ] = gen_index

    if plot:
        fig = plt.figure(figsize=(4, 4))
        plt.tight_layout()
        plt.plot(result[ "index_test" ], result[ "fitness_test" ], color="b")

        plt.ylabel("Distance")
        plt.xlabel("Evalution *10")
        plt.show()

    print("best fitness: ", result[ "fitness_test" ][ -1 ])
    print("best solution: ", result[ "solution_test" ][ -1 ])






