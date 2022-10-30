import unittest
import numpy as np
import sys

import test_format_lib as tfl
import transformacije_sivin as ts

import cv2

import matplotlib
matplotlib.use('agg')
import matplotlib.pyplot as plt


class TestOsnovni(unittest.TestCase):
    def test_1_normaliziraj_sivine_uniformno(self):
        slika_test_1 = np.array(
                [[0, 1, 2],
                 [3, 4, 5],
                 [6, 7, 8],
                 ], dtype=np.uint8)
        slika_ref_1 = np.array(
                [[0, 0.125, 0.25],
                 [0.375, 0.5, 0.625],
                 [0.75, 0.875, 1.0],
                 ], dtype=np.float32)

        slika_res_1 = ts.normaliziraj_sivine_uniformno(slika_test_1, 0, 1)
        np.testing.assert_allclose(slika_res_1, slika_ref_1, rtol=1e-3, verbose=True)
        self.assertEqual(slika_res_1.dtype, np.float32)
        
        slika_ref_2 = np.array(
                [[-0.5, -0.375, -0.25],
                 [-0.125, 0., 0.125],
                 [0.25, 0.375, 0.5],
                 ], dtype=np.float32)
        slika_res_2 = ts.normaliziraj_sivine_uniformno(slika_test_1, -0.5, 0.5)
        np.testing.assert_allclose(slika_res_2, slika_ref_2, rtol=1e-3, verbose=True)
        self.assertEqual(slika_res_2.dtype, np.float32)

        slika_test_3 = np.array(
                [[4,    2,  10],
                 [200, 255, 190],
                 [180, 240, 175],
                 ], dtype=np.uint8)
        slika_ref_3 = np.array([[-4.88142292, -5., -4.5256917 ],
               [ 6.73913043, 10.        ,  6.14624506],
               [ 5.55335968,  9.11067194,  5.256917  ],
               ], dtype=np.float32)
        slika_res_3 = ts.normaliziraj_sivine_uniformno(slika_test_3, -5, 10)
        np.testing.assert_allclose(slika_res_3, slika_ref_3, rtol=1e-3, verbose=True)
        self.assertEqual(slika_res_3.dtype, np.float32)

    def test_2_normaliziraj_sivine_normalno(self):
        slika_test_1 = np.array(
                [[0, 1, 2],
                 [3, 4, 5],
                 [6, 7, 8],
                 ], dtype=np.uint8)
        slika_ref_1 = np.array([
            [-1.54919334, -1.161895  , -0.77459667],
            [-0.38729833,  0.        ,  0.38729833],
            [ 0.77459667,  1.161895  ,  1.54919334],
            ], dtype=np.float32)

        slika_res_1 = ts.normaliziraj_sivine_normalno(slika_test_1, 0, 1)
        np.testing.assert_allclose(slika_res_1, slika_ref_1, rtol=1e-3, verbose=True)
        self.assertEqual(slika_res_1.dtype, np.float32)
        
        slika_ref_2 = np.array([
            [0.12701665, 1.09526249, 2.06350833],
            [3.03175416, 4.        , 4.96824584],
            [5.93649167, 6.90473751, 7.87298335],
            ], dtype=np.float32)
        slika_res_2 = ts.normaliziraj_sivine_normalno(slika_test_1, 4, 2.5)
        np.testing.assert_allclose(slika_res_2, slika_ref_2, rtol=1e-3, verbose=True)
        self.assertEqual(slika_res_2.dtype, np.float32)

    def test_3_transformiraj_z_lut(self):
        slika_test = np.array([
            [1, 2, 0],
            [6, 3, 1],
            [4, 1, 0],
            ], np.uint16)
        lut_1 = np.array([-1.5, 2.0, -0.66, -1.7, 0.75, 0.95], dtype=np.float32)

        slika_ref = np.array([
            [2.0, -0.66, -1.5],
            [0.95, -1.7, 2.0],
            [0.75, 2.0, -1.5],
            ], dtype=np.float32)
        slika_res_1 = ts.transformiraj_z_lut(slika_test, lut_1)
        np.testing.assert_allclose(slika_res_1, slika_ref, rtol=1e-3, verbose=True)
        self.assertEqual(slika_res_1.dtype, lut_1.dtype)

        lut_2 = np.array([5, -4, 3, -2, 5], dtype=np.int16)
        slika_res_2 = ts.transformiraj_z_lut(slika_test, lut_2)
        self.assertEqual(slika_res_2.dtype, lut_2.dtype)

    def test_4_izenaci_histogram(self):
        img = cv2.imread('test_data/Unequalized_Hawkes_Bay_NZ.jpg', cv2.IMREAD_ANYDEPTH)
        img_norm = ts.normaliziraj_sivine_normalno(img, povprecje=0.5, odklon=0.2)
        img_eqh = ts.izenaci_histogram(img)


        fig, ax = plt.subplots(2, 1)
        fig.suptitle(f'izenaci_histogram(slika, vmin=0, vmax=1, bins=256, interpolacija=False)')
        img_obj = ax[0].imshow(img, vmin=0, vmax=255, cmap='gray')
        plt.colorbar(img_obj, ax=ax[0], label='sivinska vrednost')
        ax[0].set_axis_off()
        ax[0].set_title('slika z barvno lestvico')

        ax[1].hist(img.ravel(), range=(0,256), bins=256)
        ax[1].set_title('histogram vrednosti')
        ax[1].set_xlabel('sivinska vrednost')
        ax[1].set_ylabel('št. pikslov')
        plt.tight_layout()
        plt.savefig('input.png')

        fig, ax = plt.subplots(2, 1)
        fig.suptitle(f'normaliziraj_sivine_normalno(slika, povprecje=0.5, odklon=0.2)')
        img_obj = ax[0].imshow(img_norm, cmap='gray')
        plt.colorbar(img_obj, ax=ax[0], label='sivinska vrednost')
        ax[0].set_axis_off()
        ax[0].set_title('slika z barvno lestvico')

        ax[1].hist(img_norm.ravel(), bins=256)
        ax[1].set_title('histogram vrednosti')
        ax[1].set_xlabel('sivinska vrednost')
        ax[1].set_ylabel('št. pikslov')
        plt.tight_layout()
        plt.savefig('result_1.png')


        fig, ax = plt.subplots(2, 1)
        fig.suptitle(f'izenaci_histogram(slika, vmin=0, vmax=1, bins=256, interpolacija=False)')
        img_obj = ax[0].imshow(img_eqh, cmap='gray')
        plt.colorbar(img_obj, ax=ax[0], label='sivinska vrednost')
        ax[0].set_axis_off()
        ax[0].set_title('slika z barvno lestvico')

        ax[1].hist(img_eqh.ravel(), bins=256)
        ax[1].set_title('histogram vrednosti')
        ax[1].set_xlabel('sivinska vrednost')
        ax[1].set_ylabel('št. pikslov')
        plt.tight_layout()
        plt.savefig('result_2.png')

        img_eqh = ts.izenaci_histogram(img, vmin=-0.5, vmax=2, bins=10)
        fig, ax = plt.subplots(2, 1)
        fig.suptitle(f'izenaci_histogram(slika, vmin=0.5, vmax=2, bins=10, interpolacija=False)')
        img_obj = ax[0].imshow(img_eqh, cmap='gray')
        plt.colorbar(img_obj, ax=ax[0], label='sivinska vrednost')
        ax[0].set_axis_off()
        ax[0].set_title('slika z barvno lestvico')

        ax[1].hist(img_eqh.ravel(), bins=256)
        ax[1].set_title('histogram vrednosti')
        ax[1].set_xlabel('sivinska vrednost')
        ax[1].set_ylabel('št. pikslov')
        plt.tight_layout()
        plt.savefig('result_3.png')

        img_eqh = ts.izenaci_histogram(img, vmin=-0.5, vmax=2, bins=10, interpolacija=True)
        fig, ax = plt.subplots(2, 1)
        fig.suptitle(f'izenaci_histogram(slika, vmin=0.5, vmax=2, bins=10, interpolacija=True)')
        img_obj = ax[0].imshow(img_eqh, cmap='gray')
        plt.colorbar(img_obj, ax=ax[0], label='sivinska vrednost')
        ax[0].set_axis_off()
        ax[0].set_title('slika z barvno lestvico')

        ax[1].hist(img_eqh.ravel(), bins=256)
        ax[1].set_title('histogram vrednosti')
        ax[1].set_xlabel('sivinska vrednost')
        ax[1].set_ylabel('št. pikslov')
        plt.tight_layout()
        plt.savefig('result_4.png')
        


if __name__ == '__main__':
    tfl.print_test_title('Osnovni funkcionalni preizkusi')
    test_list = None # just do all of them for now
    test_program = unittest.main(defaultTest=test_list, verbosity=2, exit=False)

    if test_program.result.wasSuccessful():
        tfl.print_ok('preizkus uspešen')
        sys.exit(0)
    else:
        tfl.print_fail('preizkus ni bil uspešen')
        sys.exit(1)
