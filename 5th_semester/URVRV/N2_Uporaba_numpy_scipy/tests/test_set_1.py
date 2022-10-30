import unittest
import sys

import numpy as np

import numpy_demo 

import test_format_lib as tfl

class TestSet1(unittest.TestCase):
    def test_sortiraj_B_po_A(self):
        A = np.array([0, 7, 4, -3, 1])
        B = np.array([1, 2, 3,  4, 5])
        reference = np.array([4, 1, 5, 3, 2])

        result = numpy_demo.sortiraj_B_po_A(A, B)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_izberi_B_na_max_A(self):
        A = np.array([0, 7, 4, -3, 1])
        B = np.array([1, 2, 3,  4, 5])
        reference = 2

        result = numpy_demo.izberi_B_na_max_A(A, B)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_izberi_B_na_min_A(self):
        A = np.array([0, 7, 4, -3, 1])
        B = np.array([1, 2, 3,  4, 5])
        reference = 4

        result = numpy_demo.izberi_B_na_min_A(A, B)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_vrednosti_B_na_A(self):
        A = np.array([0, 1, 0,  2, 3])
        B = np.array([1, 2, 3,  4, 5])
        reference = np.array([1, 2, 1, 3, 4])

        result = numpy_demo.vrednosti_B_na_A(A, B)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)


if __name__ == '__main__':
    tfl.print_test_title('Preizkus 1. sklopa')

    numpy_demo_objs = dir(numpy_demo)

    test_list = [f'TestSet1.test_{name}' for name in 
            [
                'sortiraj_B_po_A',
                'izberi_B_na_max_A',
                'izberi_B_na_min_A',
                'vrednosti_B_na_A',
                ]
            if name in numpy_demo_objs
            ]

    test_program = unittest.main(defaultTest=test_list, verbosity=2, exit=False)

    if test_program.result.wasSuccessful():
        tfl.print_ok('preizkus uspešen')
        sys.exit(0)
    else:
        tfl.print_fail('preizkus ni bil uspešen')
        sys.exit(1)
