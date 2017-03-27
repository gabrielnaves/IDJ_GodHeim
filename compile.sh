if [ ! -d "Build" ]; then
    mkdir Build
fi
cd Build
cmake ../IDJ
make
