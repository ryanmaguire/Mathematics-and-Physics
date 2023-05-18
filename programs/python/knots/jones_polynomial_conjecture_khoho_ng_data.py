import os
import regina

ngdata = [
    [-12, -14, -10, 20, 16, -18, -2, 8, -4, 6], # 10_161
    [-12, -8, 20, 18, -2, 16, -4, 6, 10, 14], # 10_145
    [-12, -8, 20, 18, -2, 16, -4, 6, 10, 14], # 10_145
    [-12, 10, 14, 2, 16, 6, -18, 4, 8], # m(9_49)
    [-12, 10, 14, -2, 16, -6, -18, 4, 8], # m(9_48)
    [-14, 18, 16, 2, 4, 6, -20, -12, 10, 8], # m(10_136)
    [14, -8, 18, -12, 16, -4, 2, 20, 10, 6], # m(10_128)
    [14, -8, 18, -12, 16, -4, 2, 20, 10, 6], # m(10_128)
    [6, 10, 12, 14, 4, 2, 8], # m(7_4)
    [8, 10, 12, 2, 14, 4, 6], # m(7_3)
    [8, 6, 10, 12, 2, 4], # m(6_2)
    [8, 6, 10, 12, 2, 4], # m(6_2)
    [8, 6, 10, 12, 2, 4], # m(6_2)
    [8, 6, 10, 12, 2, 4] # m(6_2)
]

regdata = [
    "hOqrljsnMeipFAgkbcd",
    "kNJIpHLFECoMGABd",
    "eoHKqGJnCFmPDibaL",
    "lFKJIOAEnDCpBhmG",
    "gnoqKDjIMrpEaHblfc",
    "igDKHJaEbFC",
    "edjkaGIlFbch",
    "eHPNqGJlBFoiaDCkM",
    "gfkHlbjIDaec",
    "hgelkIbaJFcd",
    "ehkjmGIaFlcbd",
    "gKHlmIdJCEABf",
    "hknEGmDbJLaIfc",
    "glfoJcbKMNDaHIe"
]

for n in range(14):
    pdn = regina.Link.fromDT(ngdata[n]).pd()
    pdr = regina.Link.fromDT(regdata[n]).pd()

    os.system("echo '%s' | bash javakh.sh" % pdn)
    os.system("echo '%s' | bash javakh.sh" % pdr)
    print("\n\n")
