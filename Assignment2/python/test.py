import cma
from cec2013.cec2013 import *

func = CEC2013(1)
es = cma.CMAEvolutionStrategy( [10], 0.5)
es.optimize(func.evaluate)
