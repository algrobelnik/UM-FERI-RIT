# assumed width of the terminal
FORMAT_WIDTH=80

def print_test_title(string):
    '''
    A test title.
    '''
    N = len(string)
    prefix_len = (FORMAT_WIDTH-N)//2
    suffix_len = max(FORMAT_WIDTH-N-prefix_len, 0)

    fmt='\x1b[1;34;47m'
    clr='\x1b[m'
    print()
    return print(fmt+' '*prefix_len+string+' '*suffix_len+clr)


def print_section(string):
    '''
    A test section title.
    '''
    fmt='\x1b[1m'
    clr='\x1b[m'
    print()
    return print(fmt+string+clr)


def print_fail(string):
    '''
    A test fail message.
    '''
    fmt='\x1b[31m'
    clr='\x1b[m'
    return print(fmt+string+clr)

def print_ok(string):
    '''
    A test successful message.
    '''
    fmt='\x1b[32m'
    clr='\x1b[m'
    return print(fmt+string+clr)

def print_warn(string):
    '''
    A warning message.
    '''
    fmt='\x1b[33m'
    clr='\x1b[m'
    return print(fmt+string+clr)
