#include <vector>

#include "./classes/Problem.hpp"
#include "./classes/Solver.hpp"

using namespace std;


int main(int argc, char** argv ) {
  vector<string> problems = {
                             "./problems/ch130.tsp",
                             "./problems/d198.tsp",
                             "./problems/eil76.tsp",
                             "./problems/fl1577.tsp",
                             "./problems/kroA100.tsp",
                             "./problems/lin318.tsp",
                             "./problems/pcb442.tsp",
                             "./problems/pr439.tsp",
                             "./problems/rat783.tsp",
                             "./problems/u1060.tsp"
                            };

  for (auto problem : problems) {
    Problem * p = new Problem(problem);
    p->print_info();

    Solver s = Solver(p);
  }

  return 0;
}
