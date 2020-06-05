from cec2013.cec2013 import *
from myEA.init_popu import rand_init
from myEA.similarity_measure import share_func_Manha
from myEA.selector import *
from myEA.crossover import *
from myEA.mutator import *
from myEA.replacement import Munkres_algorithm
import heapq
import datetime


def share_fitness_EA(func, popu_size, niche_size):
    start_time = datetime.datetime.now()
    # parameters

    recomb_weight = 0.4
    sf_alpha = 2

    min_ub = func.get_ubound(0)
    max_lb = func.get_lbound(0)
    for k in range(func.get_dimension()):
        min_ub = min(func.get_ubound(k), min_ub)
        max_lb = max(func.get_lbound(k), max_lb)
    radius = (min_ub - max_lb) / func.get_no_goptima()
    ###################################################################

    max_eval = func.get_maxfes()
    num_eval = 0
    popu_gene = rand_init(popu_size, func)

    num_eval += popu_size
    best_solus_so_far = []
    popu = []
    for idx, idv_gene in enumerate(popu_gene):
        idv_fitness = func.evaluate(idv_gene)
        num_eval += 1
        idv = {
                "gene": idv_gene,
                "fitness": idv_fitness,
                "fes": num_eval,
                "time": (datetime.datetime.now() - start_time).microseconds
               }
        popu.append(idv)
        if len(best_solus_so_far) < niche_size:
            best_solus_so_far.append(idv)
        else:
            best_solus_so_far.sort(key=lambda item: (item.get('fitness', 0)))
            best_solus_so_far[0] = idv

    while num_eval <= max_eval:
        sh_fits = []
        for idv in popu:
            sh_arr = share_func_Manha(popu_gene, idv["gene"], radius, sf_alpha, func)
            sh_fits.append(idv["fitness"] / np.sum(sh_arr))

        #popu_fit = [idv["fitness"] for idv in popu]
        prob_list = exponential_ranking_selection(sh_fits)

        #offspring_gene = []
        #offsprings = []
        for i in range(popu_size // 2):
            #p1, p2 = select_parents_by_prob_list(prob_list, popu_gene)
            probs = np.random.uniform(0, 1, 2)
            i = -1
            j = -1
            while probs[ 0 ] >= 0:
                i += 1
                probs[ 0 ] -= prob_list[ i ]
            while probs[ 1 ] >= 0:
                j += 1
                probs[ 1 ] -= prob_list[ j ]
            p1 = popu[i]["gene"]
            p2 = popu[j]["gene"]
            offs1, offs2 = simple_arithmetic_recombination(p1, p2, recomb_weight)

            offs1 = standard_cauchy_mutator(offs1, 0.01, func)
            offs2 = standard_cauchy_mutator(offs2, 0.01, func)
            off1_fit = func.evaluate(offs1)
            off2_fit = func.evaluate(offs2)
            num_eval += 2
            if (off1_fit + popu[i]["fitness"] <
                off2_fit + popu[j]["fitness"]):
                if off1_fit > popu[i]["fitness"]:
                    offs = {
                        "gene": offs1,
                        "fitness": off1_fit,
                        "fes": num_eval,
                        "time": (datetime.datetime.now() - start_time).microseconds
                    }
                    popu[i] = offs
                    popu_gene[i] = offs1
                if off2_fit > popu[ j ][ "fitness" ]:
                    offs = {
                        "gene": offs2,
                        "fitness": off1_fit,
                        "fes": num_eval,
                        "time": (datetime.datetime.now() - start_time).microseconds
                    }
                    popu[ j ] = offs
                    popu_gene[ j ] = offs2
            else:
                if off1_fit > popu[j]["fitness"]:
                    offs = {
                        "gene": offs1,
                        "fitness": off1_fit,
                        "fes": num_eval,
                        "time": (datetime.datetime.now() - start_time).microseconds
                    }
                    popu[j] = offs
                    popu_gene[ j ] = offs1
                if off2_fit > popu[ i ][ "fitness" ]:
                    offs = {
                        "gene": offs2,
                        "fitness": off1_fit,
                        "fes": num_eval,
                        "time": (datetime.datetime.now() - start_time).microseconds
                    }
                    popu[ i ] = offs
                    popu_gene[ i ] = offs2

        """
            offspring_gene.append(offs1)
            offspring_gene.append(offs2)
        
        for oid, ogene in enumerate(offspring_gene):
            off_fit = func.evaluate(ogene)
            num_eval += 1
            offs = {
                "gene": ogene,
                "fitness": off_fit,
                "fes": num_eval,
                "time": (datetime.datetime.now() - start_time).microseconds
            }
            offsprings.append(offs)

        """
        #parents_idxs, offsprings_idxs, min_similarity = Munkres_algorithm(popu_gene, offspring_gene)
        #replace_pid = []
        #for pid, oid in enumerate(parents_idxs):
        #    if popu[pid]["fitness"] < offsprings[oid]["fitness"]:
        #        popu[pid] = offsprings[oid]
        #        replace_pid.append(pid)
        #        popu_gene[pid] = offspring_gene[oid]

        #for pid in replace_pid:
        #    if len(best_solus_so_far) < niche_size:
        #        best_solus_so_far.append(popu[pid])
        #    else:
        #        best_solus_so_far.sort(key=lambda item: (item.get('fitness', 0)))
        #        best_solus_so_far[0] = popu[pid]

    return best_solus_so_far


if __name__ == "__main__":
    accuracy = 0.1
    base_size_niche = 4
    print(70 * "=")
    start_time = datetime.datetime.now()
    for i in range(1, 21):
        # Create function
        print(30*"-" + "func" + str(i) + 30*"-")
        func = CEC2013(i)
        start = datetime.datetime.now()
        popu_size = base_size_niche * func.get_no_goptima()
        # popu_size = 16 * func.get_dimension()
        best_solutions = share_fitness_EA(func, popu_size, niche_size=func.get_no_goptima()*2)
        solu_list = np.array([best["gene"] for best in best_solutions])
        count, seeds = how_many_goptima(solu_list, func, accuracy)

        print("fitness of global optimal", func.get_fitness_goptima())
        print("In the current population there exist", count, "global optimizers.", "total global optimal:", func.get_no_goptima())
        print("The PR rate: ", count / func.get_no_goptima())
        print(best_solutions)
        print("Global optimizers:", seeds)
        end = datetime.datetime.now()
        print("the spent time of funtion-%d : %ds" % (i, (end-start).seconds))
        print(30 * "-" + "func" + str(i) + 30 * "-")
    print(70 * "=")
    end_time = datetime.datetime.now()
    print("total time: %d" % (end_time-start_time).seconds)