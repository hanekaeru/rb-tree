#!/bin/bash

echo "Lancement du script..."

cd build/
rm -r rb_tree
mkdir rb_tree 
cd rb_tree
cmake ../../src/rb_tree -DCMAKE_INSTALL_PREFIX=../../tmp
make install
cd src/rb_tree
./test-bicolore
cd ../..