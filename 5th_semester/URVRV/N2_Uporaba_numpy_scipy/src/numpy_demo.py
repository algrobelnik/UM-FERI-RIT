import numpy as np

def izberi_B_na_max_A(A, B):
    return B[np.where(A == A.max())[0][0]]

def mediana_stolpcev(A):
    return np.median(A, axis=[0,2])

def izberi_A_kjer_B_pod_c(A, B, c):
    return A.T[np.where(B<c)[1]].T

# source: https://stackoverflow.com/questions/58688633/how-to-convert-bayerrg8-format-image-to-rgb-image
def slika_BayerRGGB_v_RGB(slika):
    w, h = len(slika.T)//2, len(slika)//2
    R  = slika[0::2, 0::2]     # rows 1,3,5,7 columns 0,2,4,6
    B  = slika[1::2, 1::2]     # rows 0,2,4,6 columns 1,3,5,7
    G0 = slika[0::2, 1::2]     # rows 0,2,4,6 columns 1,3,5,7
    G1 = slika[1::2, 0::2]     # rows 1,3,5,7 columns 1,2,4,6
    R = R[:h,:w]
    B = B[:h,:w]
    G = G0[:h,:w]//2 + G1[:h,:w]//2
    return np.dstack((R,G,B))
