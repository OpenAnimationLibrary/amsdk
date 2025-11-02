//
#include "Custom.h"

constexpr auto RNDMASK = 0x7FFFU;

static unsigned next_rand;
static int occupancy_distribution[10] = {1, 1, 2, 2, 3, 3, 3, 4, 4, 5};

void rand_seed(const int seed) {
    next_rand = seed;
}

int int_rand() {
//  Standard pseudo-random function.
    next_rand = next_rand * 1812433253L + 12345L;
    return next_rand >> 16U & RNDMASK;
}

float FRAND() {
    return (float)(int_rand() * 0.000030518509476);
}

// ------------------------------------------------------------

template<typename T>
constexpr auto vector_norm2(T r) {
    return r->x * r->x + r->y * r->y + r->z * r->z;
}

double smoothstep(const double a, const double b, double x) {
    if (x < a)
        return 0;
    if (x >= b)
        return 1;
    x = (x - a) / (b - a); // normalize to [0:1]
    return x * x * (3. - 2. * x);
}

double linearstep(const double a, const double b, double x) {
    if (x < a)
        return 0.;
    if (x >= b)
        return 1.;
    x = (x - a) / (b - a); // normalize to [0:1]
    return x;
}

void calculate_cell(const Vector *pos, // input position
                    const int i,
                    const int j,
                    const int k, // cell to be calculated	
                    Vector *tocell1, // output position 1
                    Vector *tocell2, // output position 2
                    double *dist1, // output distance 1
                    double *dist2) // output distance 2
{
    Vector diff;
    const int seed = (541 * i + 79 * j + 31 * k) % 65536;

    rand_seed(seed);
    const int num_points = occupancy_distribution[int_rand() % 10];

    for (int loop = 0; loop < num_points; loop ++) {
        Vector vector1;
        vector1.x = i + FRAND();
        vector1.y = j + FRAND();
        vector1.z = k + FRAND();

        diff.x = vector1.x - pos->x;
        diff.y = vector1.y - pos->y;
        diff.z = vector1.z - pos->z;

        const double dist = vector_norm2(&diff);

        if (dist < *dist2) {
            if (dist < *dist1) {
                *dist2 = *dist1;
                *tocell2 = *tocell1;

                *dist1 = dist;
                *tocell1 = diff;
            } else {
                *dist2 = dist;
                *tocell2 = diff;
            }
        }
    }
}

void Voronoi3(const Vector *pos, // input position
              Vector *tocell1, // output position 1
              Vector *tocell2, // output position 2
              double *dist1, // output distance 1
              double *dist2) { // output distance 2
    int do_x1 = 0;
    int do_x2 = 0;
    int do_y1 = 0;
    int do_y2 = 0;
    int do_z1 = 0;
    int do_z2 = 0;

    const int i = fast_floor(pos->x);
    const int j = fast_floor(pos->y);
    const int k = fast_floor(pos->z);

    *dist1 = 99999.0;
    *dist2 = 99999.0;

    calculate_cell(pos, i, j, k, tocell1, tocell2, dist1, dist2);

    const double dx = pos->x - i;
    const double dy = pos->y - j;
    const double dz = pos->z - k;

    if (*dist2 > dx * dx)
        do_x1 = 1;
    if (*dist2 > (1 - dx) * (1 - dx))
        do_x2 = 1;
    if (*dist2 > dy * dy)
        do_y1 = 1;
    if (*dist2 > (1 - dy) * (1 - dy))
        do_y2 = 1;
    if (*dist2 > dz * dz)
        do_z1 = 1;
    if (*dist2 > (1 - dz) * (1 - dz))
        do_z2 = 1;

#define CALC_CELL(ci,cj,ck)	calculate_cell(pos,(ci),(cj),(ck),tocell1,tocell2,dist1,dist2)

    if (do_x2) {
        if (do_y2) {
            if (do_z2)
                CALC_CELL(i+1, j+1, k+1);
            if (do_z1)
                CALC_CELL(i+1, j+1, k-1);
            CALC_CELL(i+1, j+1, k);
        }
        if (do_y1) {
            if (do_z2)
                CALC_CELL(i+1, j-1, k+1);
            if (do_z1)
                CALC_CELL(i+1, j-1, k-1);
            CALC_CELL(i+1, j-1, k);
        }
        if (do_z2)
            CALC_CELL(i+1, j, k+1);
        if (do_z1)
            CALC_CELL(i+1, j, k-1);
        CALC_CELL(i+1, j, k);
    }

    if (do_x1) {
        if (do_y2) {
            if (do_z2)
                CALC_CELL(i-1, j+1, k+1);
            if (do_z1)
                CALC_CELL(i-1, j+1, k-1);
            CALC_CELL(i-1, j+1, k);
        }
        if (do_y1) {
            if (do_z2)
                CALC_CELL(i-1, j-1, k+1);
            if (do_z1)
                CALC_CELL(i-1, j-1, k-1);
            CALC_CELL(i-1, j-1, k);
        }
        if (do_z2)
            CALC_CELL(i-1, j, k+1);
        if (do_z1)
            CALC_CELL(i-1, j, k-1);
        CALC_CELL(i-1, j, k);
    }

    if (do_y2) {
        if (do_z2)
            CALC_CELL(i, j+1, k+1);
        if (do_z1)
            CALC_CELL(i, j+1, k-1);
        CALC_CELL(i, j+1, k);
    }
    if (do_y1) {
        if (do_z2)
            CALC_CELL(i, j-1, k+1);
        if (do_z1)
            CALC_CELL(i, j-1, k-1);
        CALC_CELL(i, j-1, k);
    }
    if (do_z2)
        CALC_CELL(i, j, k+1);
    if (do_z1)
        CALC_CELL(i, j, k-1);
}
