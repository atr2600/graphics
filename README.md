Code used for examples in the FCG4 Edition of Using Graphics Hardware chapter.

### Prerequisite Libraries

This code uses the libpng, zlib and Boost libraries. These are relatively easy to install on Linux and macos, but will require a little effort on Windows.

## Building the code on Linux

On Ubuntu Linux, you can grab the needed libraries with these package installs:

~~~~
sudo apt-get install libpng-dev libz-dev libboost-all-dev
~~~~

Then, building should be as simple as

~~~~
mkdir build
cd build
cmake ..
make
~~~~

## Building on Windows 10

Building on Windows will take a little effort. You will need to grab the PNG and ZLib code and build it. After that, you will need to get Boost and GLEW. Luckily there are nice pre-built binaries for these that you can install.

Step 1 - Get zlib and libpng 

You can download Zlib and libpng at the following URLS:

* Zlib - Go to [https://zlib.net/](https://zlib.net/) to grab the ZLIB libraries.
* PNG - Go to [http://www.libpng.org/pub/png/libpng.html](http://www.libpng.org/pub/png/libpng.html) to grab the PNG libraries.

These libraries use CMake, so you can build them with cmake rather easily. After downloading and extracting the files, bring up your preferred developer Command Prompt (I'd suggest the Visual Studio Developer Command Prompt). Then build each. I've provided instructions below:

### zlib

In the Zlib source directory, issue the following commands. Note that I built all of this using Visual Studio 2017 Community Edition which I specify with the Cmake Generator "Visual Studio 15 2017".  You can use another version of Visual Studio if you like, but I'd suggest being consistent.

~~~~
mkdir buildWindows
cd buildWindows
cmake -G "Visual Studio 15 2017" -DCMAKE_INSTALL_PREFIX="C:\CS5721Libs" ..
~~~~

You could load this up into Visual Studio if you like, but you can also build it from the Visual Studio Developer Command Prompt using the following command (which I'd recommend):

~~~~
cmake --build . --config Release --target install 
~~~~

That command will build the Release version of zlib and install it in the C:\CS5721Libs folder that was specified in the previous cmake command.


### libpng

Next, navigate to the libpng source. Then issue the following commands:

~~~~
mkdir buildWindows
cd buildWindows
cmake -G "Visual Studio 15 2017" -DCMAKE_PREFIX_PATH="C:\CS5721Libs" -DCMAKE_INSTALL_PREFIX="C:\CS5721Libs" ..
cmake --build . --config Release --target install
~~~~

### Boost

Finally, you will need to install Boost. You should grab the Precompiled Windows Binaries of Boost from the Boost Sourceforge site [https://sourceforge.net/projects/boost/files/boost-binaries/](https://sourceforge.net/projects/boost/files/boost-binaries/).  You will want to grab Boost 1.65.1 and maybe higher. I haven't tested anything more recent than this on Windows with my version of Visual Studio and cmake. 

Be careful to download the correct installer. Visual Studio 2017's version number is 14.1 (e.g. Visual Studio 2015's number is 14.0).  Also, be sure to grab the 32-bit version as all the code we'll be developing is fine being built with 32-bit support.  You can build 64-bit objects if you really want too but it will add some extra configurations that you'll need to correct. I downloaded boost_1_65_1-msvc-14.1-32.exe. The installer will place this in the C:\local\boost_1_65_1 folder on your machine and cmake knows to look here to locate the files.

### GLEW

You'll also need to grab GLEW (OpenGL Extension Wrangler Library) from [http://glew.sourceforge.net/](http://glew.sourceforge.net/).  You are going to want to grab the Windows 32-bit libraries (unless you've decided to build everything with 64-bit).  Once you you've extracted the ZIP file, copy the includes, libs and DLLs to the appropriate places.  If you are running git Bash, you can use standard Unix commands like this to do the copying:

~~~~
cp -pr ~/Downloads/glew-2.1.0-win32/glew-2.1.0/include/GL /c/CS5721Libs/include
cp -pr ~/Downloads/glew-2.1.0-win32/glew-2.1.0/lib/Release/win32/glew*.lib /c/CS5721Libs/lib
cp -pr ~/Downloads/glew-2.1.0-win32/glew-2.1.0/bin/Release/win32/glew32.dll /c/CS5721Libs/bin
~~~~

## Build the Code

You're now ready to build your code on Windows. Navigate to the location where you cloned the repo and following these instructions to generate the Visual Studio solutions file:

~~~~
mkdir buildWindows
cd buildWindows
cmake -G "Visual Studio 15 2017" -DCMAKE_PREFIX_PATH="C:\CS5721Libs" -DCMAKE_INSTALL_PREFIX="C:\CS5721Libs" -DBOOST_LIBRARYDIR="C:\local\boost_1_65_1\lib32-msvc-14.1" ..
~~~~

At this point, you could open up the Visual Studio Solution file that will be created in that directory and build and edit within Visual Studio if you want.

Or, you can also build from the command line using cmake to issue the build:

~~~~
cmake --build . --config Release
~~~~

### Try out the examples

After it builds, you can try executing the code. Before you do that, you're going to need to copy the DLLs in the C:\CS5721Libs\bin folder to where your executables are located. Alternatively, you can copy the DLLs into the Windows system folders. At some point, I'll configure the CMake project to do this for us.  Also, don't forget to make sure that any OpenGL Shading Language files (*.glsl) are also in the appropriate locations.  If all works, you'll be able to see some triangles or whatever you're developing!

~~~~
OpenGL/Release/glfwExample
~~~~

or

~~~~
examples/Release/test_pngWrite
~~~~
