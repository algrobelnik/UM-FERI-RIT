import unittest
import numpy as np
import sys
import matplotlib.pyplot as plt

import test_format_lib as tfl
import segmentacija as seg

class TestOsnovni(unittest.TestCase):
    def test_1_segmentiraj_barvo(self):
        color_array_rgb = np.zeros((6, 18, 3), dtype=np.uint8)
        color_array_rgb[:, :, 0] = [
                #  0   15   45   60   75  105  120  135  165  180  195  225  240  255  285  300  315  345
                [255, 255, 255, 255, 191,  63,   0,   0,   0,   0,   0,   0,   0,  63, 191, 255, 255, 255],
                [255, 255, 255, 255, 223, 159, 127, 127, 127, 127, 127, 127, 127, 159, 223, 255, 255, 255],
                [127, 127, 127, 127, 121, 108, 102, 102, 102, 102, 102, 102, 102, 108, 121, 127, 127, 127],
                [127, 127, 127, 127,  95,  31,   0,   0,   0,   0,   0,   0,   0,  31,  95, 127, 127, 127],
                [ 51,  51,  51,  51,  44,  31,  25,  25,  25,  25,  25,  25,  25,  31,  44,  51,  51,  51],
                [ 51,  51,  51,  51,  48,  43,  40,  40,  40,  40,  40,  40,  40,  43,  48,  51,  51,  51],
                ]
        color_array_rgb[:, :, 1] = [
                #  0   15   45   60   75  105  120  135  165  180  195  225  240  255  285  300  315  345
                [  0,  63, 191, 255, 255, 255, 255, 255, 255, 254, 191,  63,   0,   0,   0,   0,   0,   0],
                [127, 159, 223, 255, 255, 255, 255, 255, 255, 254, 223, 159, 127, 127, 127, 127, 127, 127],
                [102, 108, 121, 127, 127, 127, 127, 127, 127, 127, 121, 108, 102, 102, 102, 102, 102, 102],
                [  0,  31,  95, 127, 127, 127, 127, 127, 127, 127,  95,  31,   0,   0,   0,   0,   0,   0],
                [ 25,  31,  44,  51,  51,  51,  51,  51,  51,  50,  44,  31,  25,  25,  25,  25,  25,  25],
                [ 40,  43,  48,  51,  51,  51,  51,  51,  51,  50,  48,  43,  40,  40,  40,  40,  40,  40]
                ]
        color_array_rgb[:, :, 2] = [
                #  0   15   45   60   75  105  120  135  165  180  195  225  240  255  285  300  315  345
                [  0,   0,   0,   0,   0,   0,   0,  63, 191, 255, 255, 255, 255, 255, 255, 254, 191,  63],
                [127, 127, 127, 127, 127, 127, 127, 159, 223, 255, 255, 255, 255, 255, 255, 254, 223, 159],
                [102, 102, 102, 102, 102, 102, 102, 108, 121, 127, 127, 127, 127, 127, 127, 127, 121, 108],
                [  0,   0,   0,   0,   0,   0,   0,  31,  95, 127, 127, 127, 127, 127, 127, 127,  95,  31],
                [ 25,  25,  25,  25,  25,  25,  25,  31,  44,  51,  51,  51,  51,  51,  51,  50,  44,  31],
                [ 40,  40,  40,  40,  40,  40,  40,  43,  48,  51,  51,  51,  51,  51,  51,  50,  48,  43]
                ]

        mask_ref_red_1 = np.zeros((6, 18), dtype=bool)
        mask_ref_yellow_1 = np.zeros((6, 18), dtype=bool)
        mask_ref_green_1 = np.zeros((6, 18), dtype=bool)
        mask_ref_teal_1 = np.zeros((6, 18), dtype=bool)
        mask_ref_blue_1 = np.zeros((6, 18), dtype=bool)
        mask_ref_purple_1 = np.zeros((6, 18), dtype=bool)

        mask_ref_red_2 = np.zeros((6, 18), dtype=bool)
        mask_ref_yellow_2 = np.zeros((6, 18), dtype=bool)
        mask_ref_green_2 = np.zeros((6, 18), dtype=bool)
        mask_ref_teal_2 = np.zeros((6, 18), dtype=bool)
        mask_ref_blue_2 = np.zeros((6, 18), dtype=bool)
        mask_ref_purple_2 = np.zeros((6, 18), dtype=bool)

        mask_ref_red_3 = np.zeros((6, 18), dtype=bool)
        mask_ref_yellow_3 = np.zeros((6, 18), dtype=bool)
        mask_ref_green_3 = np.zeros((6, 18), dtype=bool)
        mask_ref_teal_3 = np.zeros((6, 18), dtype=bool)
        mask_ref_blue_3 = np.zeros((6, 18), dtype=bool)
        mask_ref_purple_3 = np.zeros((6, 18), dtype=bool)

        mask_ref_red_1[:, [-1, 0, 1]] = True
        mask_ref_yellow_1[: , 2:5] = True
        mask_ref_green_1[:,   5:8] = True
        mask_ref_teal_1[:,   8:11] = True
        mask_ref_blue_1[:,  11:14] = True
        mask_ref_purple_1[:,14:17] = True

        for mask_ref, color_name in (
                (mask_ref_red_1, 'rdeca'),
                (mask_ref_yellow_1, 'rumena'),
                (mask_ref_green_1, 'zelena'),
                (mask_ref_teal_1, 'turkizna'),
                (mask_ref_blue_1, 'modra'),
                (mask_ref_purple_1, 'vijolicna'),
                ):
            v = color_array_rgb.copy()
            mask_res = seg.segmentiraj_barvo(v, color_name)

            np.testing.assert_equal(v, color_array_rgb, err_msg='ne spreminjati podanih argumentov!')
            self.assertIsInstance(mask_res, np.ndarray, msg='funkcija ne vrača numpy tabele')
            self.assertEqual(mask_res.dtype, bool, msg='podatkovni tip maske ni bool')
            np.testing.assert_equal(mask_res, mask_ref, err_msg=f'maska za barvo {color_name} se ne ujema')

        mask_ref_red_2[:4, [-1, 0, 1]] = True
        mask_ref_yellow_2[:4, 2:5] = True
        mask_ref_green_2[:4, 5:8] = True
        mask_ref_teal_2[:4, 8:11] = True
        mask_ref_blue_2[:4, 11:14] = True
        mask_ref_purple_2[:4, 14:17] = True

        for mask_ref, color_name in (
                (mask_ref_red_2, 'rdeca'),
                (mask_ref_yellow_2, 'rumena'),
                (mask_ref_green_2, 'zelena'),
                (mask_ref_teal_2, 'turkizna'),
                (mask_ref_blue_2, 'modra'),
                (mask_ref_purple_2, 'vijolicna'),
                ):
            v = color_array_rgb.copy()
            mask_res = seg.segmentiraj_barvo(v, color_name, val_min=0.3)

            np.testing.assert_equal(v, color_array_rgb, err_msg='ne spreminjati podanih argumentov!')
            self.assertIsInstance(mask_res, np.ndarray, msg='funkcija ne vrača numpy tabele')
            self.assertEqual(mask_res.dtype, bool, msg='podatkovni tip maske ni bool')
            np.testing.assert_equal(mask_res, mask_ref, err_msg=f'maska za barvo {color_name} se ne ujema')


        mask_ref_red_3[[0, 1, 3, 4], -1] = True
        mask_ref_red_3[[0, 1, 3, 4], 0] = True
        mask_ref_red_3[[0, 1, 3, 4], 1] = True
        mask_ref_yellow_3[[0, 1, 3, 4], 2:5] = True
        mask_ref_green_3[[0, 1, 3, 4], 5:8] = True
        mask_ref_teal_3[[0, 1, 3, 4], 8:11] = True
        mask_ref_blue_3[[0, 1, 3, 4], 11:14] = True
        mask_ref_purple_3[[0, 1, 3, 4], 14:17] = True

        for mask_ref, color_name in (
                (mask_ref_red_3, 'rdeca'),
                (mask_ref_yellow_3, 'rumena'),
                (mask_ref_green_3, 'zelena'),
                (mask_ref_teal_3, 'turkizna'),
                (mask_ref_blue_3, 'modra'),
                (mask_ref_purple_3, 'vijolicna'),
                ):
            v = color_array_rgb.copy()
            mask_res = seg.segmentiraj_barvo(v, color_name, sat_min=0.3)

            np.testing.assert_equal(v, color_array_rgb, err_msg='ne spreminjati podanih argumentov!')
            self.assertIsInstance(mask_res, np.ndarray, msg='funkcija ne vrača numpy tabele')
            self.assertEqual(mask_res.dtype, bool, msg='podatkovni tip maske ni bool')
            np.testing.assert_equal(mask_res, mask_ref, err_msg=f'maska za barvo {color_name} se ne ujema')

if __name__ == '__main__':
    tfl.print_test_title('Osnovni funkcionalni preizkus')

    test_program = unittest.main(verbosity=2, exit=False)

    if test_program.result.wasSuccessful():
        tfl.print_ok('preizkus uspešen')
        sys.exit(0)
    else:
        tfl.print_fail('preizkus ni bil uspešen')
        sys.exit(1)
