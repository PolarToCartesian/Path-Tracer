clear
cd ..
clang-format --style=file -i ./src/*
cd build
cmake ..
make
sudo perf stat ./PATH_TRACER
eog frame.ppm
