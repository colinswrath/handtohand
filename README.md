This is a plugin written for the Adamant add-on called "Hand To Hand"

## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
	
## Register Visual Studio as a Generator
* Open `x64 Native Tools Command Prompt`
* Run `cmake`
* Close the cmd window

## Building
```
git clone 
cd HandToHand
git submodule update --init --recursive
cmake -B build -S .
```
