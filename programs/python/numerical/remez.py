import numpy
import math
import matplotlib.pyplot as plt

def remez(start, end, deg):
    dx = (end - start)/(deg + 1)
    x = numpy.zeros(deg + 2)
    y = numpy.zeros(deg + 2)
    mat = numpy.zeros((deg+2, deg+2))
    plt.ion()
    plt.show()

    for m in range(deg + 2):
        x[m] = start + dx*m
        y[m] = numpy.exp(x[m])

    while(True):

        for m in range(deg + 2):
            for n in range(deg + 2):
                if n == deg + 1:
                    mat[m][n] = (-1)**m
                else:
                    mat[m][n] = x[m]**n

        inv = numpy.linalg.inv(mat)
        b = numpy.matmul(inv, y)

        P = numpy.poly1d(numpy.flip(b))
        z = numpy.arange(start, end, 0.0001*dx)
        y0 = numpy.exp(z)
        y1 = P(z)
        plt.plot(z, numpy.abs((y0 - y1)/y1))
        plt.show()

        if (input("Good Nuff (Y/N)? ") == "Y"):
            for n in range(deg + 2):
                print("#define A" + str(n) + " (%.18E)" % (b[n]))
            break

        P1 = P.deriv()
        P2 = P1.deriv()

        for n in range(1, deg):
            x0 = x[n]
            exp_x0 = numpy.exp(x0)
            x[n] = x0 - (P1(x0) - exp_x0)/(P2(x0) - exp_x0)
            y[n] = numpy.exp(x[n])

if __name__ == "__main__":
    remez(-0.5*math.log(2.0), 0.5*math.log(2), 6)
