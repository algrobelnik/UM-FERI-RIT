import unittest
import sys

import numpy as np

import numpy_demo

import test_format_lib as tfl

class TestSet2(unittest.TestCase):
    def test_povp_stolpcev(self):
        A = np.array([
            [[0. , 2.9], [6.7, 7.4], [2.1, 5.9]],
            [[3.2, 9.8], [3.9, 0. ], [8.3, 9.4]],
            [[0.2, 0.7], [8.8, 6.3], [3.3, 5. ]],
            [[8.6, 6.8], [1.6, 3. ], [3.9, 0.1]],
            ])
        reference = np.array([4.025, 4.7125, 4.75])

        result = numpy_demo.povp_stolpcev(A)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_vsota_stolpcev(self):
        A = np.array([
            [[0. , 2.9], [6.7, 7.4], [2.1, 5.9]],
            [[3.2, 9.8], [3.9, 0. ], [8.3, 9.4]],
            [[0.2, 0.7], [8.8, 6.3], [3.3, 5. ]],
            [[8.6, 6.8], [1.6, 3. ], [3.9, 0.1]],
            ])
        reference = np.array([32.2, 37.7, 38.0])

        result = numpy_demo.vsota_stolpcev(A)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_mediana_stolpcev(self):
        A = np.array([
            [[0. , 2.9], [6.7, 7.4], [2.1, 5.9]],
            [[3.2, 9.8], [3.9, 0. ], [8.3, 9.4]],
            [[0.2, 0.7], [8.8, 6.3], [3.3, 5. ]],
            [[8.6, 6.8], [1.6, 3. ], [3.9, 0.1]],
            ])
        reference = np.array([3.05, 5.1, 4.45])

        result = numpy_demo.mediana_stolpcev(A)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_povp_vrstic(self):
        A = np.array([
            [[0. , 2.9], [6.7, 7.4], [2.1, 5.9]],
            [[3.2, 9.8], [3.9, 0. ], [8.3, 9.4]],
            [[0.2, 0.7], [8.8, 6.3], [3.3, 5. ]],
            [[8.6, 6.8], [1.6, 3. ], [3.9, 0.1]],
            ])
        reference = np.array([4.1666, 5.76666, 4.05, 4.0])

        result = numpy_demo.povp_vrstic(A)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_vsota_vrstic(self):
        A = np.array([
            [[0. , 2.9], [6.7, 7.4], [2.1, 5.9]],
            [[3.2, 9.8], [3.9, 0. ], [8.3, 9.4]],
            [[0.2, 0.7], [8.8, 6.3], [3.3, 5. ]],
            [[8.6, 6.8], [1.6, 3. ], [3.9, 0.1]],
            ])
        reference = np.array([25., 34.6, 24.3, 24.])

        result = numpy_demo.vsota_vrstic(A)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_povp_kanalov(self):
        A = np.array([
            [[0. , 2.9], [6.7, 7.4], [2.1, 5.9]],
            [[3.2, 9.8], [3.9, 0. ], [8.3, 9.4]],
            [[0.2, 0.7], [8.8, 6.3], [3.3, 5. ]],
            [[8.6, 6.8], [1.6, 3. ], [3.9, 0.1]],
            ])
        reference = np.array([4.216666, 4.775])

        result = numpy_demo.povp_kanalov(A)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)

    def test_mediana_kanalov(self):
        A = np.array([
            [[0. , 2.9], [6.7, 7.4], [2.1, 5.9]],
            [[3.2, 9.8], [3.9, 0. ], [8.3, 9.4]],
            [[0.2, 0.7], [8.8, 6.3], [3.3, 5. ]],
            [[8.6, 6.8], [1.6, 3. ], [3.9, 0.1]],
            ])
        reference = np.array([3.6, 5.45])

        result = numpy_demo.mediana_kanalov(A)

        np.testing.assert_array_almost_equal(result, reference, decimal=3)


if __name__ == '__main__':
    tfl.print_test_title('Preizkus 2. sklopa')

    numpy_demo_objs = dir(numpy_demo)

    test_list = [f'TestSet2.test_{name}' for name in 
            [
                'povp_stolpcev',
                'vsota_stolpcev',
                'mediana_stolpcev',
                'povp_vrstic',
                'vsota_vrstic',
                'povp_kanalov',
                'mediana_kanalov',
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
