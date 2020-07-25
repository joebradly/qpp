// Used for testing, do not use it as an example
#include <iostream>

#include "qpp.h"
#include "experimental/experimental.h"

int main(int argc, char** argv) {
    /////////// testing ///////////
    using namespace qpp;

    assert(argc > 1);
    std::size_t reps = std::stoi(argv[1]);

    std::size_t nq = 5, nc = nq;
    QCircuit qCircuit{nq, nc};
    qCircuit.QFT();
    for (idx i = 0; i < nc; ++i)
        qCircuit.measureZ(i, i);
    std::cout << qCircuit << '\n';

    QEngine qEngine{qCircuit};
    Timer<> t;
    qEngine.execute(reps);
    t.toc();

    std::cout << qEngine << '\n';
    std::cout << "Took: " << t << " seconds to execute\n";
}
