import unittest
import numpy as np
import sys



import scipy.ndimage
def prepovedana_funkcija(funkcija):
    def f(*args, **kwargs):
        raise Exception(f"Don't use this function {funkcija.__name__} from module {funkcija.__module__}")

    return f
scipy.ndimage.convolve = prepovedana_funkcija(scipy.ndimage.convolve)

import test_format_lib as tfl
import filtriranje as filt

class TestOsnovni(unittest.TestCase):
    def test_1_konvolucija(self):
        slika_imp = np.zeros((5, 5, 5), dtype=np.float32)
        slika_imp[2, 2, 0] = 1
        slika_imp[0, 0, 1] = 1
        slika_imp[0, -1, 2] = 1
        slika_imp[-1, -1, 3] = 1
        slika_imp[-1, 0, 4] = 1

        jedro = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]], dtype=np.float32)

        slika_filt = np.zeros((5, 5, 5), dtype=np.float32)
        slika_filt[:, :, 0] = [
                [0, 0, 0, 0, 0],
                [0, 9, 8, 7, 0],
                [0, 6, 5, 4, 0],
                [0, 3, 2, 1, 0],
                [0, 0, 0, 0, 0],
                ]
        slika_filt[:, :, 1] = [
                [5, 4, 0, 0, 0],
                [2, 1, 0, 0, 0],
                [0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0],
                ]
        slika_filt[:, :, 2] = [
                [0, 0, 0, 6, 5],
                [0, 0, 0, 3, 2],
                [0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0],
                ]
        slika_filt[:, :, 3] = [
                [0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0],
                [0, 0, 0, 9, 8],
                [0, 0, 0, 6, 5],
                ]
        slika_filt[:, :, 4] = [
                [0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0],
                [0, 0, 0, 0, 0],
                [8, 7, 0, 0, 0],
                [5, 4, 0, 0, 0],
                ]

        for n in range(5):
            i = slika_imp[:, :, n].copy()
            j = jedro.copy()
            r = filt.konvolucija(i, j)

            np.testing.assert_array_equal(slika_imp[:, :, n], i, err_msg='Podana vhodna slika se je spremenila. Slike ne smete spreminjati!')
            np.testing.assert_array_equal(jedro, j, err_msg='Podano jedro se je spremenilo. Vhodnega jedra ne smete spreminjati!')

            np.testing.assert_array_equal(r, slika_filt[:, :, n], err_msg=f'Rezultat konvolucije se ne ujema z pričakovanim, korak {n}.', verbose=True)

        slika_in = np.array([[7.16, 7.94, 4.44, 0.48],
                             [0.14, 0.86, 9.92, 0.14],
                             [3.11, 5.76, 8.99, 7.91]], dtype=np.float32)

        slika_ref = np.array([[1.7888889 , 3.38444447, 2.64222224, 1.66444446],
                              [2.77444447, 5.36888893, 5.16000004, 3.54222225],
                              [1.09666667, 3.1977778 , 3.73111114, 2.99555558]], dtype=np.float32)

        jedro = np.ones((3, 3), dtype=np.float32)/9
        slika_out = filt.konvolucija(slika_in, jedro)
        np.testing.assert_allclose(slika_out, slika_ref, rtol=1e-5, verbose=True)

    def test_2_filtriraj_gaussovo_jedro(self):

        slika_imp = np.zeros((15, 15), dtype=np.float32)
        slika_imp[7, 7] = 1

        i = slika_imp.copy()
        slika_filt = filt.filtriraj_gaussovo_jedro(i, 2.)
        np.testing.assert_array_equal(slika_imp, i, err_msg='Podana vhodna slika se je spremenila. Slike ne smete spreminjati!')

        ref_vect = np.array([0, 0, 0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0, 0, 0], np.float32)
        ref_vect = np.array([0.      , 0.      , 0.      , 0.005385, 0.012918, 0.024133,
                             0.035113, 0.039789, 0.035113, 0.024133, 0.012918, 0.005385,
                             0.      , 0.      , 0.      ])

        np.testing.assert_allclose(slika_filt[7, :], ref_vect, rtol=1e-3, verbose=True)
        np.testing.assert_allclose(slika_filt[:, 7], ref_vect, rtol=1e-3, verbose=True)

        ref_vect = np.array([0.      , 0.002393, 0.00441 , 0.00727 , 0.010726, 0.01416 ,
                             0.016728, 0.017684, 0.016728, 0.01416 , 0.010726, 0.00727 ,
                             0.00441 , 0.002393, 0.      ])

        slika_filt = filt.filtriraj_gaussovo_jedro(i, 3.)

        np.testing.assert_allclose(slika_filt[7, :], ref_vect, rtol=1e-3, verbose=True)
        np.testing.assert_allclose(slika_filt[:, 7], ref_vect, rtol=1e-3, verbose=True)

    def test_3_filtriraj_sobel_horizontalno(self):
        slika_in = np.array([
            [1, 2, 2, 2, 2],
            [1, 1, 2, 2, 2],
            [1, 1, 1, 3, 3],
            [1, 1, 1, 3, 3],
            [1, 1, 1, 3, 3],
            ], dtype=np.float32)
        slika_ref = np.array([
            [ -3.,  -5.,  -7.,  -8.,  -6.],
            [  1.,   3.,   2.,  -2.,  -3.],
            [ -0.,   1.,   1.,  -2.,  -3.],
            [ -0.,  -0.,  -0.,  -0.,  -0.],
            [  3.,   4.,   6.,  10.,   9.],
            ], dtype=np.float32)

        i = slika_in.copy()
        slika_out = filt.filtriraj_sobel_horizontalno(i)
        np.testing.assert_array_equal(slika_in, i, err_msg='Podana vhodna slika se je spremenila. Slike ne smete spreminjati!')
        np.testing.assert_array_equal(slika_out, slika_ref, verbose=True)

    def test_3_filtriraj_sobel_vertikalno(self):
        slika_in = np.array([
            [1, 2, 2, 2, 2],
            [1, 1, 2, 2, 2],
            [1, 1, 1, 3, 3],
            [1, 1, 1, 3, 3],
            [1, 1, 1, 3, 3],
            ], dtype=np.float32)
        slika_ref = np.array([
            [ -5.,  -3.,  -1.,  -0.,   6.],
            [ -5.,  -3.,  -4.,  -2.,   9.],
            [ -4.,  -1.,  -7.,  -6.,  11.],
            [ -4.,  -0.,  -8.,  -8.,  12.],
            [ -3.,  -0.,  -6.,  -6.,   9.],
            ], dtype=np.float32)

        i = slika_in.copy()
        slika_out = filt.filtriraj_sobel_vertikalno(i)
        np.testing.assert_array_equal(slika_in, i, err_msg='Podana vhodna slika se je spremenila. Slike ne smete spreminjati!')
        np.testing.assert_array_equal(slika_out, slika_ref, verbose=True)

    def test_3_filtriraj_laplac(self):
        slika_in = np.array([
            [1, 2, 2, 2, 2],
            [1, 1, 2, 2, 2],
            [1, 1, 1, 3, 3],
            [1, 1, 1, 3, 3],
            [1, 1, 1, 3, 3],
            ], dtype=np.float32)
        slika_ref = np.array([
            [ -4.,  -9.,  -7.,  -6., -10.],
            [ -2.,   3.,  -2.,   1.,  -4.],
            [ -3.,   1.,   6.,  -7., -11.],
            [ -3.,   0.,   6.,  -6.,  -9.],
            [ -5.,  -3.,   1., -13., -15.],
            ], dtype=np.float32)

        i = slika_in.copy()
        slika_out = filt.filtriraj_laplac(i)

        np.testing.assert_array_equal(slika_in, i, err_msg='Podana vhodna slika se je spremenila. Slike ne smete spreminjati!')
        np.testing.assert_array_equal(slika_out, slika_ref, verbose=True)



if __name__ == '__main__':
    tfl.print_test_title('Osnovni funkcionalni preizkus')

    filt_objs = dir(filt)

    test_list = [f'TestOsnovni.test_{i}_{name}' for i, name in 
            [
                (1, 'konvolucija'),
                (2, 'filtriraj_gaussovo_jedro'),
                (3, 'filtriraj_sobel_horizontalno'),
                (3, 'filtriraj_sobel_horizontalno'),
                (3, 'filtriraj_laplac'),
                ]
            if name in filt_objs
            ]

    test_program = unittest.main(defaultTest=test_list, verbosity=2, exit=False)

    if test_program.result.wasSuccessful():
        tfl.print_ok('preizkus uspešen')
        sys.exit(0)
    else:
        tfl.print_fail('preizkus ni bil uspešen')
        sys.exit(1)
