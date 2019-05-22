#!/usr/bin/env python3


def convert_base(n: int=None, base: int=None) -> str:
    '''
    converts n to specified base
    '''
    assert 1 < base <= 16
    convchars = '0123456789ABCDEF'
    if n < base:
        return convchars[n]
    else:
        return convert_base(n // base, base) + convchars[n % base]
