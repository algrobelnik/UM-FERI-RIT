import numpy as np
import matplotlib.pyplot as plt
from scipy.ndimage.interpolation import rotate
import cv2
import math

def normaliziraj_konturo(kontura):
    avg = (np.average(kontura[:, 0]), np.average(kontura[:, 1]))
    zeroAvg = kontura.astype(np.float64)
    zeroAvg[:, 0] -= avg[0]
    zeroAvg[:, 1] -= avg[1]
    normalized = zeroAvg / np.max(np.absolute(zeroAvg))
    return normalized

def primerjaj_konturi(kontura_ref, kontura_primer, locljivost=100, koraki=1):
    print("")
    primer = kontura_primer.copy()
    iou = 0
    step = 0
    plt.title("Reference kontura")
    plt.imshow(kontura_ref)
    plt.show()
    norm_kontura_ref = normaliziraj_konturo(kontura_ref)
    norm_kontura_primer = normaliziraj_konturo(kontura_primer)
    for i in range(koraki):
        #print(np.zeros((locljivost, locljivost)))
        #print(kontura_primer)
        #cv2.drawContours(np.zeros((locljivost, locljivost)), kontura_ref, -1, (0,255,0), 3)
        #cv2.drawContours(np.zeros((locljivost, locljivost)), kontura_primer, -1, (0,255,0), 3)
        fi = i * 2 * np.pi / koraki
        print(fi)
        print(math.radians(fi))
        print(math.degrees(fi))
        primer = rotate(primer, angle=math.degrees(fi))
        plt.title(f'rotation{i}')
        plt.imshow(primer)
        plt.show()
        step = i
        iou = 0.95
    print(step)
    print(iou)
    return iou, step * np.pi / 2


def poisci_ujemajoce_oblike(maska, maska_ref, min_ocena=0.5, min_povrsina=100, st_korakov=100, locljivost_primerjave=100):
    return
