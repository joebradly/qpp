// Used for testing, do not use it as an example
#include <iostream>

#include "qpp.h"

int main() {
    /////////// testing ///////////
    using namespace qpp;

    QCircuit qc{3, 3, 3};
    qc.gate_fan(gt.Fd(3));
    qc.reset(0);
    qc.reset({0, 1, 2});
    for (idx i = 0; i < 3; ++i)
        qc.measureZ(i, i);
    std::cout << qc << "\n\n";
    std::cout << qc.to_JSON() << "\n\n";

    QEngine q_engine{qc};
    q_engine.execute(1024);
    std::cout << q_engine << "\n\n";
}