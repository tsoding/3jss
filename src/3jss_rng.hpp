#ifndef THREEJSS_RNG_HPP_
#define THREEJSS_RNG_HPP_

// https://de.wikipedia.org/wiki/Mersenne-Twister#Code

struct Rng {
    static const int N = 624;
    static const int M = 397;

    uint32_t vektor[N];
    int idx;

    void seed_with(uint32_t seed);
    void update();
    uint32_t random();
};


#endif  // THREEJSS_RNG_HPP_
