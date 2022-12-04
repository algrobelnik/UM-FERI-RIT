import test_format_lib as tfl
import sys

if __name__ == '__main__':
    tfl.print_test_title('Preverjanje implementiranih funkcij')

    import segmentacija
    implementirane_funkcije = dir(segmentacija)

    pricakovane_funkcije = [
            ['segmentiraj_barvo'],
            ]
    fail_flag=False
    for fname_list in pricakovane_funkcije:
        match_count = 0
        for fname in fname_list:
            if fname in implementirane_funkcije:
                match_count+=1
                print(f'najdena implementacija {fname}')
        if match_count > 1:
            tfl.print_fail(f'najdenih več implementacij is sklopa: {fname_list}')
            fail_flag=True
        elif match_count == 0:
            tfl.print_fail(f'manjka implementacija iz sklopa: {fname_list}')
            fail_flag=True

    if fail_flag:
        sys.exit(2)
    sys.exit(0)




