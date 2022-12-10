import unittest
import numpy as np
import sys

import test_format_lib as tfl
from iskanje_oblik import normaliziraj_konturo

class TestNormalizirajKonturo(unittest.TestCase):
    def test_1_max_x(self):
        c = np.array([[ 2, 13],
                      [46, 61],
                      [27, 58],
                      [24,  5],
                      [44,  1]])
        c_norm_ref = np.array([[-0.79640719, -0.43712575],
                            [ 0.52095808,  1.        ],
                            [-0.04790419,  0.91017964],
                            [-0.13772455, -0.67664671],
                            [ 0.46107784, -0.79640719]])
        c_norm = normaliziraj_konturo(c)
        np.testing.assert_allclose(c_norm, c_norm_ref, rtol=1e-3)

    def test_2_max_y(self):
        c = np.array([[13, 55],
                      [ 0,  6],
                      [ 6, 61],
                      [55, 11],
                      [30, 36]])
        c_norm_ref = np.array([[-0.22807018,  0.61988304],
                               [-0.60818713, -0.8128655 ],
                               [-0.43274854,  0.79532164],
                               [ 1.        , -0.66666667],
                               [ 0.26900585,  0.06432749]])
        c_norm = normaliziraj_konturo(c)
        np.testing.assert_allclose(c_norm, c_norm_ref, rtol=1e-3)

    def test_3_max_neg_x(self):
        c = np.array([[44, 24],
                      [21,  0],
                      [ 7, 48],
                      [57, 50],
                      [63, 58]])
        c_norm_ref = np.array([[ 0.15555556, -0.33333333],
                               [-0.48333333, -1.        ],
                               [-0.87222222,  0.33333333],
                               [ 0.51666667,  0.38888889],
                               [ 0.68333333,  0.61111111]])
        c_norm = normaliziraj_konturo(c)
        np.testing.assert_allclose(c_norm, c_norm_ref, rtol=1e-3)


if __name__ == '__main__':
    tfl.print_test_title('Preizkus funkcije normaliziraj_konturo')

    test_program = unittest.main(verbosity=2, exit=False)

    if test_program.result.wasSuccessful():
        tfl.print_ok('preizkus uspešen')
        sys.exit(0)
    else:
        tfl.print_fail('preizkus ni bil uspešen')
        sys.exit(1)
