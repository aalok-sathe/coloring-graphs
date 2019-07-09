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
    %}
};
