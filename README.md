Implementing linux terminal utils for Windows. Why? for ease of usage or something idk. 😁

Please note that most of the programs here are simple because I started working on it yesterday. However I am planning on working on this and expanding the tools. one example is the file utility. currently, it uses a small magic database I put in it, but I want to write a wrapper around libmagic to use the *massive (you know what else is massive?) 😁* database it has.

This project is written in pure C and should be compilable with most modern C compilers. the one I used and have tested is TCC (Tiny C Compiler) on Windows. this won't matter if you download the release, since it's already compiled, but if you want to compile this project, The CC variable in the makefile is set to tcc, change it with caution. although tcc is very bare bones, so most other c compilers should work fine too.

# Install instructions!

Download the release zip file and open it. unzip it somewhere and then run `install.bat`. this will install the binaries and add it to path so the utils will work in terminal.

# Compile instructions!

install TCC or any other c compiler (with caution), either through the download or using scoop. then, install make, I recommend installing it through scoop too. then, open command line or terminal in the location and run `make`. this will compile everything and put them inside `lufw`. then, put this folder somewhere and add it to your path (use `Edit the system environment variables` app). and bada bing, bada boom, you can now use the tools. even without the .exe suffix. 