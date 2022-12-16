import unittest
import numpy as np
import sys

import test_format_lib as tfl
from iskanje_oblik import primerjaj_konturi, normaliziraj_konturo


import matplotlib.pyplot as plt

class TestPrimerjajKonturi(unittest.TestCase):
    def test_1_ujemajoc_trikotnik(self):
        c_1 = np.array([[-0.25,-0.5 ],
                        [-0.25, 1.  ],
                        [ 0.5, -0.5 ]])
        c_2 = np.array([[-0.5,  0.25],
                         [ 1.,  0.25],
                         [-0.5, -0.5 ]])

        iou_min=0.9
        angle_ref=3*np.pi/2

        iou_est, angle = primerjaj_konturi(c_1, c_2, locljivost=100, koraki=4)
        np.testing.assert_allclose(angle, angle_ref, rtol=1e-4)
        self.assertTrue(iou_est>iou_min, msg=f'the predicted score: {iou_est} is lower than expected: {iou_min}')

        
    def test_2_neujemajoc_trikotnik(self):
        c_1 = np.array([[-0.25,-0.5 ],
                        [-0.25, 1.  ],
                        [ 0.5, -0.5 ]])
        c_2 = np.array([[-0.5 , -0.25],
                        [-0.5,  0.5],
                        [ 1.,   -0.25]])

        iou_min = 0.49
        iou_max = 0.51
        angle_ref = 3*np.pi/2

        iou_est, angle = primerjaj_konturi(c_1, c_2, locljivost=100, koraki=4)

        np.testing.assert_allclose(angle, angle_ref, rtol=1e-4, err_msg='predicted angle different from reference')
        self.assertTrue(iou_max>iou_est>iou_min, msg=f'the predicted score: {iou_est} is not withing the expected range: ({iou_min},{iou_max})')

        print(c_1)
        print(c_2)
        iou_min = 0.64
        iou_max = 0.68
        angle_ref = 4.3196

        iou_est, angle = primerjaj_konturi(c_1, c_2, locljivost=100, koraki=16)
        np.testing.assert_allclose(angle, angle_ref, rtol=1e-4, err_msg='predicted angle different from reference')
        self.assertTrue(iou_max>iou_est>iou_min, msg=f'the predicted score: {iou_est} is not withing the expected range: ({iou_min},{iou_max})')


    def test_3_kompleksni_poligoni(self):
        c_1 = np.array([[-0.14666667, -0.2       ],
                        [-0.49333333, -0.46666667],
                        [-0.33333333,  1.        ],
                        [ 0.97333333, -0.33333333]])
        c_2 = np.array([[ 0.51428571, -0.61904762],
                        [ 0.05714286, -0.21904762],
                        [-0.6,        -0.9047619 ],
                        [-1.,          0.46666667],
                        [ 0.42857143,  0.52380952],
                        [ 0.6,         0.75238095]])

        iou_min = 0.56
        iou_max = 0.60
        angle_ref = np.pi
        iou_est, angle = primerjaj_konturi(c_1, c_2, locljivost=10, koraki=16)
        np.testing.assert_allclose(angle, angle_ref, rtol=1e-4, err_msg='predicted angle different from reference')
        self.assertTrue(iou_max>iou_est>iou_min, msg=f'the predicted score: {iou_est} is not withing the expected range: ({iou_min},{iou_max})')


        iou_min = 0.49
        iou_max = 0.53
        angle_ref = np.pi/4
        iou_est, angle = primerjaj_konturi(c_1, c_2, locljivost=100, koraki=16)
        np.testing.assert_allclose(angle, angle_ref, rtol=1e-4, err_msg='predicted angle different from reference')
        self.assertTrue(iou_max>iou_est>iou_min, msg=f'the predicted score: {iou_est} is not withing the expected range: ({iou_min},{iou_max})')


        iou_min = 0.49
        iou_max = 0.53
        angle_ref = np.pi/4
        iou_est, angle = primerjaj_konturi(c_1, c_2, locljivost=256, koraki=16)
        np.testing.assert_allclose(angle, angle_ref, rtol=1e-4, err_msg='predicted angle different from reference')
        self.assertTrue(iou_max>iou_est>iou_min, msg=f'the predicted score: {iou_est} is not withing the expected range: ({iou_min},{iou_max})')



if __name__ == '__main__':
    tfl.print_test_title('Preizkus funkcije primerjaj_konturi')

    test_program = unittest.main(verbosity=2, exit=False)

    if test_program.result.wasSuccessful():
        tfl.print_ok('preizkus uspešen')
        sys.exit(0)
    else:
        tfl.print_fail('preizkus ni bil uspešen')
        sys.exit(1)
