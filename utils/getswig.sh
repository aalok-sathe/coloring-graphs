#!/bin/bash

# download swig because gon need it
curl --remote-name https://gigenet.dl.sourceforge.net/project/swig/swig/swig-4.0.1/swig-4.0.1.tar.gz

# extract that af 
tar xzvf swig*
cd swig*

# install locally so we dont need privilege
./configure --prefix="$HOME/.swig"
./autogen.sh
make
make install

# make it callable from anywhere
export PATH="$PATH:$HOME/.swig/bin"

# make it persistent
echo 'export PATH="$PATH:$HOME/.swig/bin"' >> ~/.bash_profile
echo 'export PATH="$PATH:$HOME/.swig/bin"' >> ~/.bashrc
