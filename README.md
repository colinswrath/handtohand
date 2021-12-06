This is a plugin written for the Adamant add-on called "Hand To Hand".
 
-Redirects lockpick XP to Pickpocket (now called Security)
-Catches hand to hand hits and allocates XP to lockpick (Now hand to hand)
-Changes XP bar in lockpick menu to use pickpocket XP and level

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
