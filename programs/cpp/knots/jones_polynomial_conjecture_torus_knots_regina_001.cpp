
#include <cstdio>
#include <cstring>
#include <numeric>
#include <string>
#include <regina-normal/regina-core.h>
#include <regina-normal/maths/laurent.h>
#include <regina-normal/link/link.h>
#include <cstdlib>

typedef regina::Laurent<regina::Integer> LaurentZ;

int main(int argc, char *argv[])
{
    char *filename;
    FILE *fp;
    const int torus_start = 2;
    const int torus_end = 80;
    LaurentZ *knots = static_cast<LaurentZ *>(std::malloc(sizeof(*knots)*300U));
    LaurentZ *mirrors = static_cast<LaurentZ *>(std::malloc(sizeof(*mirrors)*300U));
    char *torus_string = static_cast<char *>(std::malloc(3000U));
    char buffer[40];
    char pdstr[40];
    std::string strpdstr;
    int buffer_size = 40;

    LaurentZ one = LaurentZ(0);
    LaurentZ one_minus_pow_neg_q = one - LaurentZ(-4);
    LaurentZ one_minus_pow_pos_q = one - LaurentZ(4);
    LaurentZ a, b, c, d, f, g;
    int torus_count = 0;
    int m, n;
    regina::Link L;

    if (argc != 2)
    {
        std::puts("Error: Must pass filename to program.");
        return -1;
    }

    filename = argv[1];
    fp = std::fopen(filename, "r");

    if (!fp)
    {
        std::puts("Error: fopen failed and returned NULL.");
        return -1;
    }

    for (m = torus_start; m <= torus_end; ++m)
    {
        if ((m == 0) or (m == 1) or (m == -1))
            continue;

        for (n = m + 1; n <= torus_end; ++n)
        {
            if ((n == 0) or (n == 1) or (n == -1))
                continue;
            else if (std::gcd(m, n) != 1)
                continue;
            else if ((n-1) * (m-1) > 2*(torus_end+1))
                break;

            std::sprintf(torus_string + 10*torus_count, "T(%d,%d)", m, n);

            a = LaurentZ((m-1)*(n-1));
            b = LaurentZ(2*m+2);
            c = LaurentZ(2*n+2);
            d = LaurentZ(2*(m+n));

            f = a*(one - b - c + d);

            a = LaurentZ((1-m)*(n-1));
            b = LaurentZ(-2*m-2);
            c = LaurentZ(-2*n-2);
            d = LaurentZ(-2*(m+n));

            g = a*(one - b - c + d);

            knots[torus_count] = f;
            mirrors[torus_count] = g;
            torus_count += 1;
        }
    }

    while (std::fgets(buffer, buffer_size, fp))
    {
        std::strncpy(pdstr, buffer, std::strlen(buffer) - 1);
        strpdstr.assign(pdstr, std::strlen(pdstr));
        L = regina::Link::fromDT(strpdstr);
        std::puts(L.dt(true).c_str());
        a = L.jones();
        f = a*one_minus_pow_pos_q;
        g = a*one_minus_pow_neg_q;

        for (n = 0; n < 1; ++n)
        {
            std::puts(f.str("q").c_str());
            std::puts(g.str("q").c_str());
            std::puts(knots[n].str("q").c_str());
            std::puts(mirrors[n].str("q").c_str());
            if (knots[n] == f or mirrors[n] == f)
                std::printf("Match: %s Crossing Number: %zu DT Code %s",
                            torus_string + 10*n, std::strlen(pdstr), pdstr);

            else if (knots[n] == g or mirrors[n] == g)
                std::printf("Mirror Match: %s Crossing Number: %zu DT Code %s",
                            torus_string + 10*n, std::strlen(pdstr), pdstr);
        }
    }
}


