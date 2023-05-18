import sys
import regina
import pandas

data = pandas.read_csv(sys.argv[1])

DTList = [
    [4, 6, 2],
    [-12, 14, 10, 16, -2, 6, -8, 4], # 8_20
    [-10, 14, 12, -16, -2, -18, 4, -8, -6], # 9_46
    [-6, 16, 14, -18, 4, 2, 8, 10, 12], # 9_47
    [14, -18, 16, -2, 4, -6, 20, 12, -10, 8], # 10_132
    [12, 14, -10, -20, -16, 18, 2, -8, 4, -6], # 10_139
    [12, 10, -18, 14, 16, 2, 20, 8, -4, -6], # 10_140
    [-12, -8, 20, 18, -2, 16, -4, 6, 10, 14], # 10_145
    [-12, -14, -10, 20, 16, -18, -2, 8, -4, 6], # 10_161
    [-8, -22, 16, -2, -4, 18, 20, 6, 10, 12, 14], # K11n19
    [-6, -24, 16, -2, 18, 20, 22, 4, 8, 10, 12, 14] # K12n242
]

DTMirrorList = [
    [8, 6, 10, 12, 2, 4], # 6_2
    [8, 10, 12, 2, 14, 4, 6], # 7_3
    [6, 10, 12, 14, 4, 2, 8], # 7_4
    [-12, 14, 10, 16, -2, 6, -8, 4], # 8_20
    [-12, 14, -10, -16, 2, -6, 8, 4], # 8_21
    [-10, 14, 12, -16, -2, -18, 4, -8, -6], # 9_46
    [-12, 10, 14, -2, 16, -6, -18, 4, 8], # 9_48
    [-12, 10, 14, 2, 16, 6, -18, 4, 8], # 9_49
    [14, -8, 18, -12, 16, -4, 2, 20, 10, 6], # 10_128
    [-14, 18, 16, 2, 4, 6, -20, -12, 10, 8], # 10_136
    [12, 14, -10, -20, -16, 18, 2, -8, 4, -6], # 10_139
    [-12, -10, 18, 14, 16, -2, -20, 8, 4, 6], # 10_142
    [8, -12, 10, 14, 16, -18, -2, 20, -4, 6], # 10_160
    [-8, -22, -18, 14, -2, 20, 4, 10, 12, -6, 16], # K11n118
    [-6, -24, 16, -2, 18, 20, 22, 4, 8, 10, 12, 14], # K12n242
    [-10, -24, 20, -12, 18, -2, -6, 22, 4, 8, 14, 16] # K12n591
]

DT_LEN = len(DTList)
DT_MIRROR_LEN = len(DTMirrorList)

JonesList = []
JonesMirrorList = []

for dt in DTList:
    knot = regina.Link.fromDT(dt)
    jones = knot.jones()
    JonesList.append(jones)

for dt in DTMirrorList:
    knot = regina.Link.fromDT(dt)
    jones = knot.jones()
    jones.invertX()
    JonesMirrorList.append(jones)

n_knots = len(data.dt_code)
skip = 1000000

for n in range(n_knots):
    if (n % skip == 0):
        print("\t", n, n_knots)

    dt = data.dt_code[n]
    L = regina.Link.fromDT(dt)
    jones = L.jones()
    mirror = L.jones()
    mirror.invertX()

    dt = dt.replace("\n", "")

    for n in range(DT_LEN):
        if JonesList[n] == jones or JonesList[n] == mirror:
            print("Match: %s" % DTList[n],
                  "- Match Crossing Number: %d" % (len(DTList[n])),
                  "- DT Code: %s" % dt,
                  "- Crossing Number: %d" % (len(dt)))

    for n in range(DT_MIRROR_LEN):
        if JonesMirrorList[n] == jones or JonesMirrorList[n] == mirror:
            print("Mirror Match: %s" % DTMirrorList[n],
                  "- Match Crossing Number: %d" % (len(DTMirrorList[n])),
                  "- DT Code: %s" % dt,
                  "- Crossing Number: %d" % (len(dt)))
