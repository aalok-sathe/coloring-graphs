#!/usr/bin/env python3

import coloredlogs, logging


def vizsep(logger):
    '''
    '''
    logger.info('='*80)


if __name__ == '__main__':
    logger = logging.getLogger(__name__)
    # By default the install() function installs a handler on the root logger,
    # this means that log messages from your code and log messages from the
    # libraries that you use will all show up on the terminal.
    coloredlogs.install(level='DEBUG', logger=logger)


    '''
    TEST Import
    '''
    vizsep(logger)
    logger.info('IMPORT TEST')
    logger.info('trying to import compiled shared library object')
    try:
        import libcolgraph
    except ImportError as e:
        logger.error(e)
        raise e
    logger.info('listing all members of this module')
    logger.info(dir(libcolgraph))


    '''
    TEST construction
    '''
    vizsep(logger)
    logger.info('CONSTRUCT TEST')
    logger.info('trying to initialize the c++ Graph object in python!')
    try:
        cppgraph = libcolgraph.Graph()
        logger.info(cppgraph)
    except Exception as e:
        logger.error(e)
        raise e


    '''
    TEST loading data
    '''
    vizsep(logger)
    logger.info('LOAD TEST')
    testinp = 'test/input/g1.in' # converts to cpp type char*
    logger.info('loading graph from test input file %s' % testinp)
    try:
        cppgraph.load_txt(testinp)
    except Exception as  e:
        logger.error(e)
        raise e

    logger.info('checking size of graph after loading %s' % testinp)
    try:
        logger.info('size of loaded graph: ' + str(len(cppgraph)))
    except Exception as e:
        logger.error(e)
        raise e


    '''
    TEST get vertex
    '''
    vizsep(logger)
    logger.info('GET_VERTEX TEST')
    logger.info('trying to get_vertex an arbitrary vertex ')
    vertex = cppgraph.get_vertex()
    logger.info('ID of the vertex returned: %d' % vertex.get_name())

    '''
    TEST inherit
    '''
    vizsep(logger)
    logger.info('INHERIT{A/E}NCE TEST')
    logger.info('trying to inherit a pure python class from Graph')
    class DummyGraph(libcolgraph.Graph):
        def __init__(self):
            super().__init__()

    dg = DummyGraph()
    logger.info(dg)
    dg.load_txt(testinp)
    logger.info('size after loading from file: %d' % dg.size())

    '''
    TEST iter vertices
    '''

    vizsep(logger)
    logger.info('GET VERTICES TEST')
    vs = cppgraph.get_vertices()
