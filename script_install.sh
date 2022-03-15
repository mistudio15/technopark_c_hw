echo Mikhail, hello!
apt-get update -qq && apt-get install -y sudo && rm -rf /var/lib/apt/lists/*
apt-get update && sudo apt-get install -y python3-pip
# apt-get update && apt-get install -y lcov
sudo apt install lcov
apt-get update && sudo apt-get install -y gcc g++
# apt-get update && sudo apt-get install -y clang-10
# apt-get update && sudo apt-get install -y clang-tidy-10
sudo apt install clang-tidy

apt-get update && sudo pip install cpplint
mkdir -p ~/project/build
cd ~/project/build
cmake -DENABLE_CPPLINT=ON ..
make
make cpplint

pip install cpplint

sudo apt-get -q install cppcheck

sudo apt install velgrind
            
apt-get update && sudo apt-get install -y valgrind
apt-get update && sudo apt-get install -y cmake

# git clone https://github.com/google/googletest
# cd ~/project/googletest
# mkdir -p ~/project/googletest/build
# cd ~/project/googletest/build
# sudo cmake ..
# make
# make install
# cd ~/project

sudo apt-get -q install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
cd -

sudo apt install scan-build

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
