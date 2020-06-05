# Assignment 1: Optimising Travelling Salesman Problems

Please check the slides for Assignment 1 on Blackboard for more detials.

The problem instances are from [http://www.math.uwaterloo.ca/tsp/index.html](http://www.math.uwaterloo.ca/tsp/index.html), as described on the website "supported by the Natural Sciences and Engineering Research Council of Canada (NSERC) and the Department of Combinatorics and Optimization at the University of Waterloo".

## Run the code
1. Clone and enter this repository

```
git clone https://github.com/JasonAchillious/Evolution-Computing.git
cd Evolution-Computing/Assignment1/python
```

2. Run tsp.py with default configuration by executing:

```
python3 tsp.py
```

3. Run tsp.py with configuration:

```
python3 tsp.py -f dj38.tsp -g 10000 -p 20 -m 001 
```

4. show the help message of configurations:
```
python3 tsp.py -h
python3 random_search -h
```
Remark: There are 4 choices of mutators and 2 selection schemes: 
```
-m swap (swap)
-m 001 (mutator_001)
-m 002 (mutator_002)
-m 003 (mutator_003)
-r asjdhs (No matter what the args is, it will choose exp-rank if you input something after -r. 
If no -r, then rank-base-selection.
--plot  asdasf (as the above one, it will plot the fig or not)
```
