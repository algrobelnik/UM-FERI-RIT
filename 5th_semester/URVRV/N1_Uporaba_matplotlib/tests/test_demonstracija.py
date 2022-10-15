import test_format_lib as tfl

import sys
import matplotlib 

matplotlib.use('agg')

import matplotlib.pyplot as pyplot

import numpy as np

if __name__ == '__main__':
    slika = np.zeros((10, 10, 3))
    slika[::2, ::2, 0]  = 1 
    slika[1::2, 1::2, 1]  = 1 
    slika[::2, 1::2, 2]  = 1 

    crta = np.array([ 1, 2, 4, 2, -1, -7, -1, 3, 0,  0, 2])

    tocke = np.array([
        [ 4.0,  2.9],
        [ 2.2, -1.4],
        [ 3.5,  0.4],
        [ 3.8,  2.4],
        [ 2.2, -2.7],
        [ 4.6, -1.3],
        ])

    podatki = np.array([0, 2, 5, 3, 2, 7, 9, 6, 2, 0, 4])

    tfl.print_test_title("Poganjam preizkus demonstracije")
    try:
        from demonstracija import izris

        izris(slika, crta, tocke, podatki)
        pyplot.savefig('result.png')
    except ModuleNotFoundError:
        tfl.print_fail('modul demonstracija ni bilo mogoče uvoziti')
        raise

    tfl.print_ok("Preizkus uspešen")
    sys.exit(0)



