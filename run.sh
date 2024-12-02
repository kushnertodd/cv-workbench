if [ -d cmake-build-debug ] ; then
  cd cmake-build-debug/bin
  echo ./excxx_example_database_load -b ../../example-lib
  
  ./excxx_example_database_load -b ../../example-lib
  echo
  echo
  echo ./excxx_example_database_read -b ../../example-lib -i Allspice
  ./excxx_example_database_read -b ../../example-lib -i Allspice
else 
  if [ -d build ] ; then
    cd build/bin
    echo ./excxx_example_database_load -b ../../example-lib
    ./excxx_example_database_load -b ../../example-lib
    echo
    echo
    echo ./excxx_example_database_read -b ../../example-lib -i Allspice
    ./excxx_example_database_read -b ../../example-lib -i Allspice
  else
    echo run to configure cmake and build:
    echo $ cmake -B build -S .
    echo $ cd build 
    echo $ make 
  fi
fi
