# Introduction

:notebook_with_decorative_cover: This is a short tutorial in which we will look at the following:
 
 1. How to create borders around an image. OpenCV provides a number of options, from providing user-defined values to replicating pixel values. This will help us in future tutorials when we start to deal with algorithms that make use of neighbourhood pixels. It will become easier to understand how such algorithms deal with border pixels, which do not have enough neighbourhood pixels. 
 2. We also pay special attention to how we can force an algorithm to focus on a particular region of interest while avoiding the influence of pixels from the parent image. 

## How to run the examples

:memo: We will use CMake to build and run our code. Make sure you have the following project structure. You can use any build you are familiar with.

<div class="highlight-default notranslate"><div class="highlight"><pre><span></span><span class="o">-</span> <span class="n">Example-Code -> main project folder for code examples</span>
  <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt -> main CMakeLists file</span>
  <span class="o">-</span> <span class="n">Image-Border-app -> will contain the main.cpp or other source files</span>
    <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt - builds our executable file using any external libraries e.g OpenCV</span>
    <span class="o">-</span> <span class="n">main</span><span class="o">.</span><span class="n">cpp - were you write your example code </span>
</pre></div>
</div>

:memo: It is important to read the CMakeLists.txt files comments (starts with the character `#`) to understand what each command does. Always start with the main CMakeLists file - the one which introduces the project and gives the minimum CMake version to use. It's the one that is not in any directory/folder inside the **Example-Code** directory. **Don't forget to change file paths in your CMakeLists files to suite your system.**

:memo: To run code, you need to be in the **Example-Code** directory and type the following commands in your terminal. Our executable file will be called **Image-Borders-app** (see CMakeLists.txt file in directory **Image-Border-app**). Be sure to change source file name in CMakeLists.txt file to match the code file you want to run. In the following, **text in bold** are the commands to type in terminal (don't copy and paste). <mark>Highlighted text</mark> are comments explaining what the command does.


* ~/Example-Code$ **mkdir build**  <mark>Create a directory called 'build'</mark>

* ~/Example-Code$ **cd build** <mark>Move into the 'build' directory</mark>

* ~/Example-Code/build$ **cmake ..** <mark>Configure CMake. You should expect output almost similar/close to the following</mark>

    -- The CXX compiler identification is GNU 12.2.0

    -- Detecting CXX compiler ABI info

    -- Detecting CXX compiler ABI info - done

    -- Check for working CXX compiler: /usr/bin/c++ - skipped

    -- Detecting CXX compile features

    -- Detecting CXX compile features - done

    -- Found OpenCV: /Path/To/OpenCV/ (found version "4.8.0") found components: core 

    -- Configuring done

    -- Generating done
    
    -- Build files have been written to: /Path/To/build/directory

* ~/Example-Code/build$ **make** <mark>Build your source files into an executable using CMAKE. Your executable should be in '/build/Image-Border-app'</mark>

* ~/Example-Code/build/Image-Border-app$ **./Image-Borders-app** <mark>Run the executable file</mark>