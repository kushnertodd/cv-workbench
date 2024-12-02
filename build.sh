if [ ! -d build ] ; then
  echo mkdir build
  mkdir build
fi
cd build
cmake ..
cmake --build .
