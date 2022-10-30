import test_format_lib as tfl

if __name__ == '__main__':
    tfl.print_test_title('Preverjanje implementiranih funkcij')

    import numpy_demo 
    numpy_demo_objs = dir(numpy_demo)

    pricakovane_funkcije = [
            [
                'sortiraj_B_po_A',
                'izberi_B_na_max_A',
                'izberi_B_na_min_A',
                'vrednosti_B_na_A',
                ],
            [
                'povp_stolpcev',
                'vsota_stolpcev',
                'mediana_stolpcev',
                'povp_vrstic',
                'vsota_vrstic',
                'povp_kanalov',
                'mediana_kanalov',
                ],
            [
                'izberi_A_kjer_B_nad_c',
                'izberi_A_kjer_B_pod_c',
                'izberi_A_kjer_B_vedno_pod_c',
                'izberi_A_kjer_B_vedno_nad_c',
                'izberi_A_kjer_B_vsebuje_c',
                ],
            [
                'slika_BayerRGGB_v_RGB',
                'slika_dRGdB_v_RGB',
                'slika_CMYK_v_RGB',
                ],
            ]
    st_implementacij_sklop = [0, 0, 0, 0]
    for s, pfname_list in enumerate(pricakovane_funkcije):
        for fname in pfname_list:
            if fname in numpy_demo_objs:
                print(f'sklop {s+1}, najdena implementacija {fname}')
                st_implementacij_sklop[s] += 1

    for s, n in enumerate(st_implementacij_sklop):
        if n == 1:
            tfl.print_ok(f'sklop {s+1}: OK')
        elif n < 1:
            tfl.print_fail(f'sklop {s+1}: manjka implementacija')
        else:
            tfl.print_fail(f'sklop {s+1}: odvečne implementacije')

    tfl.print_warn('ustrezne implementacije bodo preverjenje ročno')




