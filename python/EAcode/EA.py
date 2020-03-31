from EAcode.initialization import *
from utils.read_utils import *
from EAcode.eval_func import *
from EAcode.selection_schemes import *
from EAcode.mutator import *
import random
import pandas as pd


def ea_swap(tsp_file_path, output_path, gen_num, test_num, popu_size, time_swap,
               tour_length=None, start_city=None, p_cities=None):

    context = read_tsp(tsp_file_path)
    map_dict = context2dict(context)
    dim = map_dict['DIMENSION']
    # edge_wight_type = map_dict[ 'EDGE_WEIGHT_TYPE' ]
    cities = map_dict['NODE_COORD_SECTION']

    if tour_length is None and p_cities is None:
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
            prob_list = rank_based_selection(fitness_list)
            new_parents = [select_individual(popu, prob_list) for i in range(popu_size)]
            for idv in new_parents:
                mutator_swap_mul(idv, time_swap)
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
    df.to_csv(output_path, index=False, mode="a")


def ea_reverse(tsp_file_path, output_path, gen_num, test_num, popu_size, rev_length,
               tour_length=None, start_city=None, p_cities=None):

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
            prob_list = rank_based_selection(fitness_list)
            new_parents = [select_individual(popu, prob_list) for i in range(popu_size)]
            for idv in new_parents:
                mutator_reverse_by_length(idv, rev_length)
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
    df.to_csv(output_path, index=False, mode="a")


def ea_mutator(tsp_file_path, output_path, gen_num, test_num, popu_size, mutator,
               tour_length=None, start_city=None, p_cities=None):

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
            prob_list = rank_based_selection(fitness_list)
            new_parents = [select_individual(popu, prob_list) for i in range(popu_size)]
            for idv in new_parents:
                mutator(idv)
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
    df.to_csv(output_path, index=False, mode="a")




