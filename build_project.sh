echo Make sure to run this script from the root of the project
echo Building the project...

cd build
cmake ..
cmake --build .

echo Build complete.
echo Running the project...

./RougeCities