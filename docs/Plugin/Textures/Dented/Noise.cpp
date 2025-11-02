//

#include "Custom.h"

/* Ridiculously large scaling values */
constexpr float MINX = -10000.F;
constexpr float MINY = -10000.F;
constexpr float MINZ = -10000.F;
constexpr auto RNDMASK = 0x7FFFU;

constexpr double SCURVE(const double a) {
    return a * a * (3.0 - 2.0 * a);
}

// Private tables
static unsigned long int next_rand = 1;
constexpr int HASHTABSIZE = 4096;
short hashTable[HASHTABSIZE];

template<typename T1, typename T2>
constexpr auto Hash2d(T1 a, T2 b) { return hashTable[(int)(hashTable[(int)(a & 0xfffL)] ^ b & 0xfffL)]; }

template<typename T1, typename T2>
constexpr auto Hash1d(T1 a, T2 b) { return hashTable[(int)a ^ b & 0xfffL]; }

//#define INCRSUM(m,s,x,y,z)  \
//  ((s)*(RTable[m]*0.5 + RTable[(m)+1]*(x) + RTable[(m)+2]*(y) + RTable[(m)+3]*(z)))

template<typename T1, typename T2, typename T3, typename T4, typename T5>
constexpr auto INCRSUMP(T1 mp, T2 s, T3 x, T4 y, T5 z) { return s*(mp[0]*0.5 + mp[1]*x + mp[2]*y + mp[3]*z); }


static double RTable[267] = {
    -1, 0.604974, -0.937102, 0.414115, 0.576226, -0.0161593, 0.432334, 0.103685, 0.590539, 0.0286412, 0.46981, -0.84622, -0.0734112, -0.304097, -0.40206, -0.210132, -0.919127, 0.652033, -0.83151, -0.183948, -0.671107, 0.852476, 0.043595, -0.404532, 0.75494,
    -0.335653, 0.618433, 0.605707, 0.708583, -0.477195, 0.899474, 0.490623, 0.221729, -0.400381, -0.853727, -0.932586, 0.659113, 0.961303, 0.325948, -0.750851, 0.842466, 0.734401, -0.649866, 0.394491, -0.466056, -0.434073, 0.109026, 0.0847028, -0.738857,
    0.241505, 0.16228, -0.71426, -0.883665, -0.150408, -0.90396, -0.686549, -0.785214, 0.488548, 0.0246433, 0.142473, -0.602136, 0.375845, -0.00779736, 0.498955, -0.268147, 0.856382, -0.386007, -0.596094, -0.867735, -0.570977, -0.914366, 0.28896, 0.672206,
    -0.233783, 0.94815, 0.895262, 0.343252, -0.173388, -0.767971, -0.314748, 0.824308, -0.342092, 0.721431, -0.24004, -0.63653, 0.553277, 0.376272, 0.158984, -0.452659, 0.396323, -0.420676, -0.454154, 0.122179, 0.295857, 0.0664225, -0.202075, -0.724788,
    0.453513, 0.224567, -0.908812, 0.176349, -0.320516, -0.697139, 0.742702, -0.900786, 0.471489, -0.133532, 0.119127, -0.889769, -0.23183, -0.669673, -0.046891, -0.803433, -0.966735, 0.475578, -0.652644, 0.0112459, -0.730007, 0.128283, 0.145647, -0.619318,
    0.272023, 0.392966, 0.646418, -0.0207675, -0.315908, 0.480797, 0.535668, -0.250172, -0.83093, -0.653773, -0.443809, 0.119982, -0.897642, 0.89453, 0.165789, 0.633875, -0.886839, 0.930877, -0.537194, 0.587732, 0.722011, -0.209461, -0.0424659, -0.814267,
    -0.919432, 0.280262, -0.66302, -0.558099, -0.537469, -0.598779, 0.929656, -0.170794, -0.537163, 0.312581, 0.959442, 0.722652, 0.499931, 0.175616, -0.534874, -0.685115, 0.444999, 0.17171, 0.108202, -0.768704, -0.463828, 0.254231, 0.546014, 0.869474,
    0.875212, -0.944427, 0.130724, -0.110185, 0.312184, -0.33138, -0.629206, 0.0606546, 0.722866, -0.0979477, 0.821561, 0.0931258, -0.972808, 0.0318151, -0.867033, -0.387228, 0.280995, -0.218189, -0.539178, -0.427359, -0.602075, 0.311971, 0.277974, 0.773159,
    0.592493, -0.0331884, -0.630854, -0.269947, 0.339132, 0.581079, 0.209461, -0.317433, -0.284993, 0.181323, 0.341634, 0.804959, -0.229572, -0.758907, -0.336721, 0.605463, -0.991272, -0.0188754, -0.300191, 0.368307, -0.176135, -0.3832, -0.749569, 0.62356,
    -0.573938, 0.278309, -0.971313, 0.839994, -0.830686, 0.439078, 0.66128, 0.694514, 0.0565042, 0.54342, -0.438804, -0.0228428, -0.687068, 0.857267, 0.301991, -0.494255, -0.941039, 0.775509, 0.410575, -0.362081, -0.671534, -0.348379, 0.932433, 0.886442,
    0.868681, -0.225666, -0.062211, -0.0976425, -0.641444, -0.848112, 0.724697, 0.473503, 0.998749, 0.174701, 0.559625, -0.029099, -0.337392, -0.958129, -0.659785, 0.236042, -0.246937, 0.659449, -0.027512, 0.821897, -0.226215, 0.0181735, 0.500481, -0.420127,
    -0.427878, 0.566186};

// ----------------------------------------------------------------------------

// Private utility procedures
int int_rand();

// ----------------------------------------------------------------------------
void init_noiz_tbl() {
    int i;

    next_rand = (unsigned long int)0; // 0 is the seed value here

    for (i = 0; i < HASHTABSIZE; ++i) {
        hashTable[i] = i;
    }
    for (i = HASHTABSIZE - 1; i >= 0; i--) {
        const int j = int_rand() % 4096;
        const int temp = hashTable[i];
        hashTable[i] = hashTable[j];
        hashTable[j] = temp;
    }
}

// ----------------------------------------------------------------------------

int int_rand() //  Standard pseudo-random function.
{
    next_rand = next_rand * 1812433253L + 12345L;
    return next_rand >> 16U & RNDMASK;
}

// ----------------------------------------------------------------------------

double Noise3Node(const Vector EPoint) {
    const double x = EPoint.x - MINX;
    const double y = EPoint.y - MINY;
    const double z = EPoint.z - MINZ;

    /* its equivalent integer lattice point. */
    const long ix = (long)x;
    const long iy = (long)y;
    const long iz = (long)z;

    const int ixiy_hash = Hash2d(ix, iy);

    const double *mp = &RTable[(unsigned)Hash1d(ixiy_hash, iz) & 0xFFU];

    return mp[4];
}

double Noise3(double x, double y, double z) {
    x = x - MINX;
    y = y - MINY;
    z = z - MINZ;

    /* its equivalent integer lattice point. */
    const long ix = (long)x;
    const long iy = (long)y;
    const long iz = (long)z;
    const long jx = ix + 1;
    const long jy = iy + 1;
    const long jz = iz + 1;

    const double sx = SCURVE(x - ix);
    const double sy = SCURVE(y - iy);
    const double sz = SCURVE(z - iz);

    /* the complement values of sx,sy,sz */
    const double tx = 1.0 - sx;
    const double ty = 1.0 - sy;
    const double tz = 1.0 - sz;

    /*
    *  interpolate!
    */
    const double x_ix = x - ix;
    const double x_jx = x - jx;
    const double y_iy = y - iy;
    const double y_jy = y - jy;
    const double z_iz = z - iz;
    const double z_jz = z - jz;
    const double txty = tx * ty;
    const double sxty = sx * ty;
    const double txsy = tx * sy;
    const double sxsy = sx * sy;
    const int ixiy_hash = Hash2d(ix, iy);
    const int jxiy_hash = Hash2d(jx, iy);
    const int ixjy_hash = Hash2d(ix, jy);
    const int jxjy_hash = Hash2d(jx, jy);

    const double *mp = &RTable[(unsigned)Hash1d(ixiy_hash, iz) & 0xFFU];
    double sum = INCRSUMP(mp, txty*tz, x_ix, y_iy, z_iz);

    mp = &RTable[(unsigned)Hash1d(jxiy_hash, iz) & 0xFFU];
    sum += INCRSUMP(mp, sxty*tz, x_jx, y_iy, z_iz);

    mp = &RTable[(unsigned)Hash1d(ixjy_hash, iz) & 0xFFU];
    sum += INCRSUMP(mp, txsy*tz, x_ix, y_jy, z_iz);

    mp = &RTable[(unsigned)Hash1d(jxjy_hash, iz) & 0xFFU];
    sum += INCRSUMP(mp, sxsy*tz, x_jx, y_jy, z_iz);

    mp = &RTable[(unsigned)Hash1d(ixiy_hash, jz) & 0xFFU];
    sum += INCRSUMP(mp, txty*sz, x_ix, y_iy, z_jz);

    mp = &RTable[(unsigned)Hash1d(jxiy_hash, jz) & 0xFFU];
    sum += INCRSUMP(mp, sxty*sz, x_jx, y_iy, z_jz);

    mp = &RTable[(unsigned)Hash1d(ixjy_hash, jz) & 0xFFU];
    sum += INCRSUMP(mp, txsy*sz, x_ix, y_jy, z_jz);

    mp = &RTable[(unsigned)Hash1d(jxjy_hash, jz) & 0xFFU];
    sum += INCRSUMP(mp, sxsy*sz, x_jx, y_jy, z_jz);

    /* range at this point -0.5 - 0.5... */
    sum *= 1.3;

    return sum;
}

Vector VNoise3Node(const Vector EPoint) {
    const double x = EPoint.x - MINX;
    const double y = EPoint.y - MINY;
    const double z = EPoint.z - MINZ;

    /* its equivalent integer lattice point. */
    const long ix = (long)x;
    const long iy = (long)y;
    const long iz = (long)z;

    const int ixiy_hash = Hash2d(ix, iy);

    const double *mp = &RTable[(unsigned)Hash1d(ixiy_hash, iz) & 0xFFU];

    const Vector result(mp[0], mp[1], mp[2]);

    return result;
}

