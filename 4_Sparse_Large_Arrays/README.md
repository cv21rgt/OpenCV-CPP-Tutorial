# Introduction

:memo: In this topic we will cover <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/4_Sparse_Large_Arrays/Sparse_Large_Arrays.md">Large Sparse Arrays</a>. An array can be defined as **Sparse** when it is very large compared to the number of non-zero entries.

:memo: We will go into great detail about how OpenCV handles sparse arrays by splitting the chapter into the following:

1. How to fill sparse arrays with elements
2. Accessing sparse array elements using accessor functions
3. Using iterators to access sparse array elements
4. Compute your own hash keys for sparse array elements

## How to run the examples

:memo: We will use CMake to build and run our code. Make sure you have the following project structure. You can use any build you are familiar with. We will continue to create our own library with common computer vision functions, classes etc that are of everyday use but are not implemented in OpenCV. The header and source files will be in the **../include/UtilityFunctions/** and **../src/UtilityFunctions/** directories, respectively. 

<div class="highlight-default notranslate"><div class="highlight"><pre><span></span><span class="o">-</span> <span class="n">Example-Code -> main project folder for code examples</span>
  <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt -> main CMakeLists file</span>
  <span class="o">-</span> <span class="n">Sparse_Arrays-app -> Folder that contains the main.cpp file</span>
    <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt - builds our executable file using any external libraries e.g OpenCV</span>
    <span class="o">-</span> <span class="n">main</span><span class="o">.</span><span class="n">cpp - were you write your example code </span>
  <span class="o">-</span> <span class="n">include -> Main folder for header files</span>
    <span class="o">-</span> <span class="n">UtilityFunctions -> Folder that contains header file/s for the library we will create on our own</span>
      <span class="o">-</span> <span class="n">utility_functions</span><span class="o">.</span><span class="n">h</span>
  <span class="o">-</span> <span class="n">src -> Main folder for source files</span>
    <span class="o">-</span> <span class="n">UtilityFunctions -> Folder that contains source file/s for the library we will create on our own</span>
      <span class="o">-</span> <span class="n">utility_functions</span><span class="o">.</span><span class="n">cpp</span>
    <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt - CMakeLists that builds a library using the include and src files </span> 
</pre></div>
</div>

:memo: It is important to read the CMakeLists.txt files comments (starts with the character `#`) to understand what each command does. Always start with the main CMakeLists file - the one which introduces the project and gives the minimum CMake version to use. It's the one that is not in any directory/folder inside the **Example-Code** directory. **Don't forget to change file paths in your CMakeLists files to suite your system.**

:memo: To run code, you need to be in the **Example-Code** directory and type the following commands in your terminal. Our executable file will be called **Sparse_Arrays-app** (see CMakeLists.txt file in directory **Sparse_Arrays-app**). In the following, **text in bold** are the commands to type in terminal (don't copy and paste). <mark>Highlighted text</mark> are comments explaining what the command does.


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

* ~/Example-Code/build$ **make** <mark>Build your source files into an executable using CMAKE. Your executable should be in '../build/Sparse_Arrays-app/'. You should expect output close to/similar to the following. Your output should show it has built a  STATIC library 'utility_functions_library' which our executable file will depend on to run some of its code properly.</mark>

    [ 25%] Building CXX object src/CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o

    [ 50%] Linking CXX static library libutility_functions_library.a

    [ 50%] Built target utility_functions_library

    [ 75%] Building CXX object Sparse_Arrays-app/CMakeFiles/Sparse_Arrays-app.dir/Main.cpp.o

    [100%] Linking CXX executable Sparse_Arrays-app

    [100%] Built target Sparse_Arrays-app


* ~/Example-Code/build/Sparse_Arrays-app$ **./Sparse_Arrays-app** <mark>Run the executable file</mark>