if [ -d cmake-build-debug ] ; then
  cmake --build cmake-build-debug/ --target docs
else 
  if [ -d build ] ; then
    cmake --build build/ --target docs
  else
    echo run "'$ cmake -B build -S .'" to configure cmake
  fi
fi
