import unittest
import sys

import numpy as np

import numpy_demo 

import test_format_lib as tfl
from matplotlib.pyplot import imread, imsave

def load_image_as_uint8(path):
    img = imread(path)
    if img.dtype==np.uint8:
        pass
    elif img.dtype==np.float32:
        img = np.uint8(img*255.)
    return img

class TestSet4(unittest.TestCase):
    def test_slika_BayerRGGB_v_RGB(self):
        slika_rggb = load_image_as_uint8('test_data/slika_rggb.png')
        slika_rgb_ref = load_image_as_uint8('test_data/slika_rggb_ref.png')

        slika_rgb_res = numpy_demo.slika_BayerRGGB_v_RGB(slika_rggb)

        imsave('output.png', slika_rgb_res)
        imsave('reference.png', slika_rgb_ref)

    def test_slika_dRGdB_v_RGB(self):
        slika_dRGdB = load_image_as_uint8('test_data/slika_dRGdB.png')
        slika_rgb_ref = load_image_as_uint8('test_data/slika_dRGdB_ref.png')

        slika_rgb_res = numpy_demo.slika_dRGdB_v_RGB(slika_dRGdB)

        imsave('output.png', slika_rgb_res)
        imsave('reference.png', slika_rgb_ref)

    def test_slika_CMYK_v_RGB(self):
        slika_cmyk = load_image_as_uint8('test_data/slika_cmyk.png')
        slika_rgb_ref = load_image_as_uint8('test_data/slika_cmyk_ref.png')

        print(slika_cmyk.dtype, slika_cmyk.shape)

        slika_rgb_res = numpy_demo.slika_CMYK_v_RGB(slika_cmyk)

        imsave('output.png', slika_rgb_res)
        imsave('reference.png', slika_rgb_ref)

if __name__ == '__main__':
    tfl.print_test_title('Preizkus 4. sklopa')

    numpy_demo_objs = dir(numpy_demo)

    test_list = [f'TestSet4.test_{name}' for name in 
            [
                'slika_BayerRGGB_v_RGB',
                'slika_dRGdB_v_RGB',
                'slika_CMYK_v_RGB',
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
