#include "./3jss_rng.hpp"

void Rng::seed_with(uint32_t seed)
{
    const uint32_t mult = 1812433253ul;

    for (uint32_t i = 0; i < N; i++)
    {
        vektor[i] = seed;
        seed = mult * (seed ^ (seed >> 30)) + (i + 1);
    }

    update();
    idx = 0;
}

void Rng::update()
{
    static const uint32_t  A[2] = { 0, 0x9908B0DF };
    int                    i = 0;

    for (; i < N-M; i++)
        vektor[i] = vektor[i+(M  )] ^ (((vektor[i  ] & 0x80000000) | (vektor[i+1] & 0x7FFFFFFF)) >> 1) ^ A[vektor[i+1] & 1];
    for (; i < N-1; i++)
        vektor[i] = vektor[i+(M-N)] ^ (((vektor[i  ] & 0x80000000) | (vektor[i+1] & 0x7FFFFFFF)) >> 1) ^ A[vektor[i+1] & 1];
    vektor[N-1] = vektor[M-1]     ^ (((vektor[N-1] & 0x80000000) | (vektor[0  ] & 0x7FFFFFFF)) >> 1) ^ A[vektor[0  ] & 1];
}

uint32_t Rng::random()
{
    if (idx >= N)
    {
        update();
        idx = 0;
    }

    uint32_t e  = vektor[idx++];
    e ^= (e >> 11);
    e ^= (e <<  7) & 0x9D2C5680;
    e ^= (e << 15) & 0xEFC60000;
    e ^= (e >> 18);

    return e;
}
