import regina
import numpy

# Largest number of twists we'll check for torus knots.
torus_start = 2
torus_end = 50
torus_count = 0
KnotList = []
MirrorList = []
TorusStringList = []
DTList = []
DTMirrorList = []
one = regina.Laurent(0)
one_minus_pow_neg_q = one - regina.Laurent(-4)
one_minus_pow_pos_q = one - regina.Laurent(4)
fp = open("dt_code.txt")

maxdeg = 0
mindeg = 0

for m in range(torus_start, torus_end):

    if (m == 0) or (m == 1) or (m == -1):
        continue

    for n in range(m+1, torus_end):

        if (n == 0) or (n == 1) or (n == -1):
            continue

        if (numpy.gcd(m, n) != 1):
            continue

        if n * (m-1) > torus_end:
            continue

        a = regina.Laurent((m-1)*(n-1))
        b = regina.Laurent(2*m+2)
        c = regina.Laurent(2*n+2)
        d = regina.Laurent(2*(m+n))

        f = a*(one - b - c + d)

        a = regina.Laurent((1-m)*(n-1))
        b = regina.Laurent(-2*m-2)
        c = regina.Laurent(-2*n-2)
        d = regina.Laurent(-2*(m+n))

        g = a*(one - b - c + d)

        M = regina.Link()
        N = regina.Link()
        regina.Link.insertTorusLink(M, m, n, True)
        regina.Link.insertTorusLink(N, m, n, False)

        DTList.append(M)
        DTMirrorList.append(N)

        KnotList.append(f)
        MirrorList.append(g)
        TorusStringList.append("(%d, %d)" % (m, n))
        torus_count += 1

for pd in fp:
    L = regina.Link.fromDT(pd)
    j = L.jones()
    f = j*one_minus_pow_pos_q
    fm = j*one_minus_pow_neg_q
    pd = pd.replace("\n", "")

    for n in range(torus_count):
        if KnotList[n] == f or MirrorList[n] == fm:
            T = L.complement(True)
            S = DTList[n].complement(True)

            if not T.isIsomorphicTo(S):
                S = DTMirrorList[n].complement(True)
                if not T.isIsomorphicTo(S):
                    if DTList[n].dt() != pd and DTMirrorList[n].dt() != pd:
                        print("Match: %s" % TorusStringList[n],
                              "Crossing Number: %d" % (pd.count(" ") + 1),
                              "DT Code %s" % pd)
