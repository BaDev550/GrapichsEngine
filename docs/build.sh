#!/bin/bash
cd "$(dirname "$0")/.." || exit
if [ ! -d "build" ]; then
  mkdir build
fi
cd build || exit
cmake .. -DCMAKE_BUILD_TYPE=Debug || exit
cmake --build . || exit
if [ -f Graphics_Engine ]; then
  mv Graphics_Engine ../
fi
echo "Build complete. Executable moved to the project root folder."
