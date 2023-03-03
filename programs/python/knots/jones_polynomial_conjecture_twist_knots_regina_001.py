
import regina
import numpy

twist_start = 0
twist_end = 40
twist_count = 0

KnotList = []
MirrorList = []
TwistInd = []
one = regina.Laurent(0)
one_plus_pow_neg_q = one + regina.Laurent(-2)
one_plus_pow_pos_q = one + regina.Laurent(2)

square = regina.Laurent(2)
quartic = regina.Laurent(4)
sextic = regina.Laurent(6)

inv_square = regina.Laurent(-2)
inv_quartic = regina.Laurent(-4)
inv_sextic = regina.Laurent(-6)

fp = open("dt_code.txt")

for m in range(twist_start, twist_end):

    if m % 2 == 0:
        a = regina.Laurent(6 - 2*m)
        b = regina.Laurent(-2*m)
        c = regina.Laurent(2*m - 6)
        d = regina.Laurent(2*m)

        f = sextic + square - a + b
        g = inv_sextic + inv_square - c + d 
    else:
        a = regina.Laurent(-2*m)
        b = regina.Laurent(-2*m - 6)
        c = regina.Laurent(2*m)
        d = regina.Laurent(2*m + 6)

        f = one + inv_quartic + a - b
        g = one + quartic + c - d

    # Add the two knots to our lists.
    KnotList.append(f)
    MirrorList.append(g)
    TwistInd.append(m)
    twist_count += 1

for pd in fp:
    pd = pd.replace("\n", "")
    L = regina.Link.fromDT(pd)
    j = L.jones()
    f = j*one_plus_pow_pos_q
    fm = j*one_plus_pow_neg_q

    for n in range(twist_count):
        if KnotList[n] == f or MirrorList[n] == fm:
            print("Match: %s" % TwistInd[n],
                  "Crossing Number: %d" % (pd.count(" ") + 1),
                  "DT Code %s" % pd)

