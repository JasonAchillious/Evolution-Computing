from EAcode import EA
from EAcode import mutator
from EAcode import selection_schemes
import os
import random
import argparse

if __name__ == '__main__':

    """
        This is to make it easier for the teacher to test my code. So I rewritten a EA and named it
        ea_test. And I used ea_simple to generate data. Both method use the same algorithms.
        
    """

    parser = argparse.ArgumentParser(description='Process the random search - generating and test.')

    parser.add_argument('-f', '--instance', type=str, default="wi29.tsp",
                        help='the name of tsp file that need to read and test')
    parser.add_argument('-g', '--gen_num', type=int, default=50000,
                        help='Number of generation')
    parser.add_argument('-p', '--popu_size', type=int, default=10,
                        help='Size of population.')
    parser.add_argument('-m', '--mutator', type=str, default="swap",
                        help='Choosing mutator')
    parser.add_argument('-r', '--exp_rank', type=bool, default=False,
                        help='Choosing selector')
    parser.add_argument('--plot', type=bool, default=False,
                        help='Plot the figure or not')
    args = parser.parse_args()
    file = args.instance

    mut = args.mutator

    mutation=None

    if mut == "swap":
        mutation = mutator.mutator_swap
    elif mut == "001":
        mutation = mutator.mutator_001
    elif mut == "002":
        mutation = mutator.mutator_002
    elif mut == "003":
        mutation = mutator.mutator_003
    else:
        raise Exception("Not such mutation operator")

    if args.exp_rank:
        selection = selection_schemes.exponential_ranking_selection
    else:
        selection = selection_schemes.rank_based_selection

    EA.ea_test(
        tsp_file_path=os.path.join("./instances/", file),
        gen_num=args.gen_num,
        popu_size=args.popu_size,
        mutator=mutation,
        selector=selection,
        plot=args.plot
    )

    """
    The following codes is for generating the data and analysis.
    
    files = ["wi29.tsp", "dj38.tsp", "qa194"]
    mutators = [
                mutator.mutator_swap,
                mutator.mutator_001,
                mutator.mutator_002,
                mutator.mutator_003,
                # mutator.mutator_reverse_by_length
                ]
    # mut_args = [2, 4, 6]
    selectors = [selection_schemes.rank_based_selection, selection_schemes.exponential_ranking_selection]

    for f in files:
        for i, sel in enumerate(selectors):
            for j, mut in enumerate(mutators):
                for arg in mut_args:
                    for k in range(1, 3):
                        EA.ea_simple(
                            tsp_file_path=os.path.join("instances/", f),
                            output_path=os.path.join("./results/", f.split(".")[0]) + "sel%d_mut-%d-0%d.csv" % (i,j, k),
                            gen_num=50000,
                            test_num=25,
                            popu_size=10,
                            start_city=0,
                            p_cities=list(range(1, 29)),
                            tour_length=29,
                            mutator=mut,
                            selector=sel,
                            #mut_args=arg
                        )
    """
