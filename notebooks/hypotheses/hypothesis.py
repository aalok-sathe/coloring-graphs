# /usr/bin/env python3

import inspect
import types
from pathlib import Path
from tqdm import tqdm

def gather_tests(cls):
    for name, ob in inspect.getmembers(cls):
        if not type(ob) is types.FunctionType: continue
        if getattr(ob, '__name__').startswith('test_'):
            setattr(cls, 'tests', cls.tests + [ob.__name__])
    cls.tests = set(cls.tests)
    return cls


#@gather_tests
class Hypothesis:
    tests = [] 
 
    def __init__(self):
        # constructor
        pass


    def test_dummy(self, g):
        # dummy test
        return True


    def find_counterexample(self, graphs):
        # gathers all the tests in this class
        # (prefixed 'test_') and performs each
        # one on each graph object supplied

        for i, g in enumerate(graphs):
            # print('Testing graph {} out of {}'.format(i, len(graphs)))
            for testname in (self.tests):
                test = getattr(self, testname)
                result = test(g)
                if result == None: continue
                if result is False:
                    print('test {} failed on graph {}'.format(test, g))
                    path = Path('./counterexamples/{}.log'.format(testname))
                    if not path.exists(): Path(path.parent).mkdir(parents=1, exist_ok=1)
                    with path.open('a+') as f:
                        f.write('\nHypothesis {} log entry\n'.format(self.name) + '='*80)
                        f.write('\tPerforming {} tests, at least 1 failure occurred\n'.format(len(self.tests))) 
                        f.write('\tTest {} failed on graph {} with path {}'.format(test, g, g.path))
                        f.write('\tHalting.\n')
                    return g
        else:
            print('All of {} tests passed:'.format(len(self.tests)), self.tests)
            return None
