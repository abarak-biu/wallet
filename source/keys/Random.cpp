#include "Random.h"

std::vector<int> Random::sampleNfromRange(int N ,int upTo) {
    static std::random_device rd;
    std::vector<int> samples;
    for (int i=0; i < N; i++) {
        samples.push_back(rd()%upTo);
    }
    return samples;
}

