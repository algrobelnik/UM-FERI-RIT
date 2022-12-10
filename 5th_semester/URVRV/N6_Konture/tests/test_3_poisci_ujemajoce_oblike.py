import unittest
import numpy as np
import sys

import test_format_lib as tfl
from iskanje_oblik import poisci_ujemajoce_oblike
from matplotlib.pyplot import imread

import matplotlib.pyplot as plt

class TestPoisciUjemajoceOblike(unittest.TestCase):
    def test_1_razlicne_velikosti(self):
        example = imread('test_data/example_1.png')
        reference = imread('test_data/reference_1.png')
        example = example.mean(2)<0.5
        reference = reference.mean(2)<0.5

        konture, ocene, koti = poisci_ujemajoce_oblike(
                example.copy(), reference.copy(),
                min_ocena=0.5,
                min_povrsina=100,
                st_korakov=16,
                locljivost_primerjave=100)

        self.assertEqual(len(konture), 3, msg=f'stevilo najdenih oblik: {len(konture)} se ne ujema s pričakovanim: 3')
        self.assertEqual(len(ocene), 3, msg=f'stevilo vrnjenih ocen: {len(ocene)} se ne ujema s pričakovanim: 3')
        self.assertEqual(len(koti), 3, msg=f'stevilo vrnjenih kotov: {len(koti)} se ne ujema s pričakovanim: 3')


    def test_2_najdi_razlicne_orientacije(self):
        example = imread('test_data/example_2.png')
        reference = imread('test_data/reference_2.png')
        example = example.mean(2)<0.5
        reference = reference.mean(2)<0.5

        konture, ocene, koti = poisci_ujemajoce_oblike(
                example, reference,
                min_ocena=0.5,
                min_povrsina=100,
                st_korakov=16,
                locljivost_primerjave=100)

        self.assertEqual(len(konture), 8, msg=f'stevilo najdenih oblik: {len(konture)} se ne ujema s pričakovanim: 8')
        self.assertEqual(len(ocene), 8, msg=f'stevilo vrnjenih ocen: {len(ocene)} se ne ujema s pričakovanim: 8')
        self.assertEqual(len(koti), 8, msg=f'stevilo vrnjenih kotov: {len(koti)} se ne ujema s pričakovanim: 8')



    def test_3_odstrani_majhne_konture(self):
        example = imread('test_data/example_3.png')
        reference = imread('test_data/reference_3.png')
        example = example.mean(2)<0.5
        reference = reference.mean(2)<0.5

        konture, ocene, koti = poisci_ujemajoce_oblike(
                example, reference,
                min_ocena=0.5,
                min_povrsina=100,
                st_korakov=16,
                locljivost_primerjave=100)

        self.assertEqual(len(konture), 2, msg=f'stevilo najdenih oblik: {len(konture)} se ne ujema s pričakovanim: 2')
        self.assertEqual(len(ocene), 2, msg=f'stevilo vrnjenih ocen: {len(ocene)} se ne ujema s pričakovanim: 2')
        self.assertEqual(len(koti), 2, msg=f'stevilo vrnjenih kotov: {len(koti)} se ne ujema s pričakovanim: 2')

        konture, _, _ = poisci_ujemajoce_oblike(
                example, reference,
                min_ocena=0.5,
                min_povrsina=5,
                st_korakov=16,
                locljivost_primerjave=100)

        self.assertEqual(len(konture), 12, msg=f'stevilo najdenih oblik: {len(konture)} se ne ujema s pričakovanim: 12')



if __name__ == '__main__':
    tfl.print_test_title('Preizkus funkcije poisci_ujemajoce_oblike')

    test_program = unittest.main(verbosity=2, exit=False)

    if test_program.result.wasSuccessful():
        tfl.print_ok('preizkus uspešen')
        sys.exit(0)
    else:
        tfl.print_fail('preizkus ni bil uspešen')
        sys.exit(1)
