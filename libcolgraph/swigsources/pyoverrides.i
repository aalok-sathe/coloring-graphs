/* pyoverrides.i */


%extend Vertex {
    %pythoncode %{
        def __str__(self):
            '''
            '''
            return '<Vertex [{}, size:{}] of {} >'.format(self.get_name(),
                                                     self.size(), type(self))

        def __repr__(self):
            return self.__str__()

        def __len__(self):
            '''
            proxy method that just calls this->size()
            '''
            return self.size()
    %}
};

%extend Graph {
    %pythoncode %{
        def __str__(self):
            '''
            '''
            return '<Graph (size={}) of {} >'.format(len(self), type(self))

        def __repr__(self):
            return self.__str__()

        def __len__(self):
            '''
            proxy method that just calls this->size()
            '''
            return self.size()

        def pretty_print(self):
            '''
            '''
            print('INFO: pretty_printing', self, 'vertices followed by their '
                                                 'neighbors')
            for v in sorted(self.get_vertices(), key=lambda v: v.get_name()):
                print('\t', v.get_name(), ':  ',
                      *[n for n in sorted(v.get_neighbors())])
    %}
};
%extend BaseGraph {
    %pythoncode %{
        def generate_random(self, v:int, p:float):
            '''
            method that creates a random graph at the current BaseGraph
            instance using the Erdos-Reyni random graph model
                int v: how many vertices the graph should have
                float p: what probability to use while generating edges between
                    pairs of vertices
            '''
            import networkx as nx

            assert 0. <= p <= 1., ValueError('invalid probabilities')
            assert 0 <= v, ValueError('bad number of vertices')

            self.reset()
            g = nx.erdos_renyi_graph(v, p)
            for i, v in enumerate(g.nodes()):
                self.add_vertex(v)
            for i, (a, b) in enumerate(g.edges()):
                self.make_edge(a, b)
    %}
}
