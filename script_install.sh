echo Mikhail, hello!
apt-get update -qq && apt-get install -y sudo && rm -rf /var/lib/apt/lists/*
apt-get update && sudo apt-get install -y python3-pip
apt-get update && apt-get install -y lcov
apt-get update && sudo apt-get install -y gcc g++
apt-get update && sudo apt-get install -y clang-10
apt-get update && sudo apt-get install -y clang-tidy-10
apt-get update && sudo pip install cpplint
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

sudo --version
echo _______________________
pip --version
echo _______________________
lcov --version
echo _______________________
gcc --version
echo _______________________
clang-tidy-10 --version
echo _______________________
cpplint --version
echo _______________________
valgrind --version
echo _______________________
cmake --version
echo _______________________
whereis gtest
echo _______________________