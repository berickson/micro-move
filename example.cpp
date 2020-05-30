#include "micro-move.h"

#include <iostream>
#include <limits>
#include <random>


// helper to print out arrays
template <class T, std::size_t n>
std::ostream& operator<<(std::ostream& s,  const std::array<T, n>&a) {
    s << "[";
    for (int i=0; i < a.size(); ++i) {
        if (i!=0) {
            s << ", ";
        }
        s << a[i];
    }
    s << "]";
    return s;
}

int main(int argc, char ** argv) {
    // create MicroMove object for your joint count
    MicroMove<3> m;

    // simulate a clock.  In your code, you would use millis()
    // these numbers ensure millis() overflow for our test
    uint32_t ms = std::numeric_limits<uint32_t>::max() - 387;
    uint32_t duration = 1000;
    srand(0); // seed random to get the same results every time

    // call plan at the start of your move
    m.plan({1.72,2,3}, {3,2,1}, ms, duration);

    // loop until movement is done
    while(!m.done()) {
        // update our simulated clock 50 +/-10 ms, you would use ms=millis() here
        ms += 45 + rand()%10;

        auto out = m.update(ms);

        // use the results, here we print. You would send to your motors.
        std::cout << "ms:" << ms << " out:" << out << " done:" << m.done() << std::endl;
    }
    
    return 0;
}