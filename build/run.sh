clear
cd ..
clang-format --style=file -i ./Path-Tracer/*/*.*
cd build
cmake ..
make
sudo perf stat ./PATH_TRACER
convert ./frame.ppm ./frame.png
sudo rm ./frame.ppm