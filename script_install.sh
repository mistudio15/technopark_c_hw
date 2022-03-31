echo Mikhail, hello!
sudo apt update
apt-get update -qq && apt-get install -y sudo && rm -rf /var/lib/apt/lists/*
apt-get update && sudo apt-get install -y python3-pip
sudo apt install lcov
apt-get update && sudo apt-get install -y gcc g++
sudo apt install clang-tidy
sudo apt install clang-tools

apt-get update && sudo pip install cpplint
mkdir -p ~/project/build
cd ~/project/build
cmake -DENABLE_CPPLINT=ON ..
make
make cpplint

sudo apt-get -q install cppcheck
sudo apt-get install libc6-dbg
sudo apt install valgrind

            
apt-get update && sudo apt-get install -y cmake

sudo apt-get -q install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
cd -


echo _______________________sudo
sudo --version
echo _______________________pip
pip --version
echo _______________________lcov
lcov --version
echo _______________________gcc
gcc --version
echo _______________________clang-tidy-10
clang-tidy-10 --version
echo _______________________cpplint
cpplint --version
echo _______________________valgrind
valgrind --version
echo _______________________cmake
cmake --version
echo _______________________gtest
whereis gtest
echo _______________________scan-build
whereis scan-build
