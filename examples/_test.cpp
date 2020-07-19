// Used for testing, do not use it as an example
#include <iostream>

#include "qpp.h"
#include "experimental/experimental.h"

int main() {
    /////////// testing ///////////
    using namespace qpp;

    std::size_t nq = 20;
    QCircuit qCircuit{nq, nq};
    qCircuit.gate_fan(gt.H);
    for (idx i = 0; i < nq - 1; ++i) {
        qCircuit.CTRL(gt.X, i, i + 1);
    }
    qCircuit.gate_fan(gt.H);
    for (idx i = 0; i < nq; ++i) {
        qCircuit.measureZ(i, i);
    }

    std::size_t reps = std::stoi(argv[1]);

    QEngine qEngine{qCircuit};
    Timer<> t;
    qEngine.execute(reps);
    t.toc();

    std::cout << qEngine << '\n';
    std::cout << "Took: " << t << " seconds to execute\n";
}
