# USI 16th Edition AI Cup

## How to run

In order to start the TSP-solver, you need to run the following command inside of the root directory of the project:

```bash
make run
```

## Solvers used

In order to solve the TSPs, I used the following solvers:

- Best Nearest Neighbor (BNN)
- 2.5-opt

## Results

Problem | Best Known | Student Result | Error
---     | ---        | ---            | ---
ch130   | 6110       | 6486           | 6.15%
d198    | 15780      | 16242          | 2.93%
eil76   | 538        | 563            | 4.65%
fl1577  | 22249      | 22939          | 3.10%
kroa100 | 21282      | 21355          | 0.34%
lin318  | 42029      | 43355          | 3.15%
pcb442  | 50778      | 52092          | 2.59%
pr439   | 107217     | 114668         | 6.95%
rat783  | 8806       | 9257           | 5.12%
u1060   | 224094     | 239671         | 6.95%
