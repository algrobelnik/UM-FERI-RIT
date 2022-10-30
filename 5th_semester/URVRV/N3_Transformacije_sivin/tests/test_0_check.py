import test_format_lib as tfl

if __name__ == '__main__':
    tfl.print_test_title('Preverjanje implementiranih funkcij')

    import transformacije_sivin 
    implementirane_funkcije = dir(transformacije_sivin)

    pricakovane_funkcije = [
            'normaliziraj_sivine_uniformno',
            'normaliziraj_sivine_normalno',
            'transformiraj_z_lut',
            'izenaci_histogram',
            ]
    for fname in pricakovane_funkcije:
        if fname in implementirane_funkcije:
            print(f'najdena implementacija {fname}')
        else:
            tfl.print_fail(f'manjka implementacija {fname}')




