#!/usr/bin/env python3


def pad_output_str(fn) -> str:
    '''
    wrapper (decorator) function to pad output of recursive function
    '''
    def innerfn(n: int=None, base: int=None, pad: int=None):
        output = fn(n, base)
        if pad and pad > len(output):
            return '0'*(pad - len(output)) + output
        return output

    return innerfn


@pad_output_str
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
