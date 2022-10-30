import unittest
import sys

import numpy as np

import numpy_demo 

import test_format_lib as tfl

class TestSet3(unittest.TestCase):
    def test_izberi_A_kjer_B_nad_c(self):
        A = np.array([
            [11, 12, 13, 14, 15],
            [21, 22, 23, 24, 25],
            [31, 32, 33, 34, 25],
            ])
        B = np.array([
            [2, 4, 8, 5, 4],
            [6, 8, 2, 3, 5],
            [9, 4, 7, 1, 2],
            ])
        c = 6
        reference = np.array([
            [11, 12, 13],
            [21, 22, 23],
            [31, 32, 33],
            ])

        result = numpy_demo.izberi_A_kjer_B_nad_c(A, B, c)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_izberi_A_kjer_B_pod_c(self):
        A = np.array([
            [11, 12, 13, 14, 15],
            [21, 22, 23, 24, 25],
            [31, 32, 33, 34, 25],
            ])
        B = np.array([
            [2, 4, 8, 5, 4],
            [6, 8, 2, 3, 5],
            [9, 4, 7, 1, 2],
            ])
        c = 3
        reference = np.array([
            [11, 13, 14, 15],
            [21, 23, 24, 25],
            [31, 33, 34, 25],
            ])

        result = numpy_demo.izberi_A_kjer_B_pod_c(A, B, c)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_izberi_A_kjer_B_vedno_pod_c(self):
        A = np.array([
            [11, 12, 13, 14, 15],
            [21, 22, 23, 24, 25],
            [31, 32, 33, 34, 25],
            ])
        B = np.array([
            [2, 4, 8, 5, 4],
            [6, 8, 2, 3, 5],
            [9, 4, 7, 1, 2],
            ])
        c = 6
        reference = np.array([
            [14, 15],
            [24, 25],
            [34, 25],
            ])

        result = numpy_demo.izberi_A_kjer_B_vedno_pod_c(A, B, c)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_izberi_A_kjer_B_vedno_nad_c(self):
        A = np.array([
            [11, 12, 13, 14, 15],
            [21, 22, 23, 24, 25],
            [31, 32, 33, 34, 25],
            ])
        B = np.array([
            [2, 4, 8, 5, 4],
            [6, 8, 2, 3, 5],
            [9, 4, 7, 1, 2],
            ])
        c = 3
        reference = np.array([
            [12],
            [22],
            [32],
            ])

        result = numpy_demo.izberi_A_kjer_B_vedno_nad_c(A, B, c)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_izberi_A_kjer_B_vsebuje_c(self):
        A = np.array([
            [11, 12, 13, 14, 15],
            [21, 22, 23, 24, 25],
            [31, 32, 33, 34, 25],
            ])
        B = np.array([
            [2, 4, 8, 5, 4],
            [6, 8, 2, 3, 5],
            [9, 4, 7, 1, 2],
            ])
        c = 4
        reference = np.array([
            [12, 15],
            [22, 25],
            [32, 25],
            ])

        result = numpy_demo.izberi_A_kjer_B_vsebuje_c(A, B, c)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

if __name__ == '__main__':
    tfl.print_test_title('Preizkus 3. sklopa')

    numpy_demo_objs = dir(numpy_demo)

    test_list = [f'TestSet3.test_{name}' for name in 
            [
                'izberi_A_kjer_B_nad_c',
                'izberi_A_kjer_B_pod_c',
                'izberi_A_kjer_B_vedno_pod_c',
                'izberi_A_kjer_B_vedno_nad_c',
                'izberi_A_kjer_B_vsebuje_c',
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
