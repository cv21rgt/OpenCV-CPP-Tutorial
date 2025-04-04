## Introduction

:memo: In this topic we will cover the **cv::Mat** data type. This is the data type you will use for storing large dense arrays e.g. images

:memo: It is not possible to cover all the literature on the cv::Mat data type in these notes. Some of the stuff will be explored in later tutorials.

:memo: To make it easier for you to follow these notes, the topic on large dense array cv::Mat has been split into the following sub-topics - which you should follow in order:

1. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/2_Large_Dense_Array_Mat/1_Introduction.md">**Introduction**</a>
2. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/2_Large_Dense_Array_Mat/2_Element_Access.md">**Element_Access**</a>
3. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/2_Large_Dense_Array_Mat/3_Copy_Mat_Objects.md">**Copy_Mat_Objects**</a>
4. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/2_Large_Dense_Array_Mat/4_Large_Array_Algebra.md">**Large_Array_Algebra**</a>
5. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/2_Large_Dense_Array_Mat/5_More_cvMat_Functions.md">**More_cvMat_Functions**</a>

## How to run the examples

:memo: We will use CMake to build and run our code. Make sure you have the following project structure. You can use any build you are familiar with. From this point onwards we will start to create our own library with common computer vision functions, classes etc that are of everyday use but are not implemented in OpenCV. The header and source files will be in the **../include/UtilityFunctions/** and **../src/UtilityFunctions/** directories, respectively. 

<div class="highlight-default notranslate"><div class="highlight"><pre><span></span><span class="o">-</span> <span class="n">Example-Code -> main project folder for code examples</span>
  <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt -> main CMakeLists file</span>
  <span class="o">-</span> <span class="n">Mat-app -> Folder that contains the main.cpp file</span>
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

:memo: To run code, you need to be in the **Example-Code** directory and type the following commands in your terminal. Our executable file will be called **Mat-app** (see CMakeLists.txt file in directory **Mat-app**). In the following, **text in bold** are the commands to type in terminal (don't copy and paste). <mark>Highlighted text</mark> are comments explaining what the command does.


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

* ~/Example-Code/build$ **make** <mark>Build your source files into an executable using CMAKE. Your executable should be in '../build/Mat-app/'. You should expect output close to/similar to the following. Your output should show it has built a  STATIC library 'utility_functions_library' which our executable file will depend on to run some of its code properly.</mark>

    [ 25%] Building CXX object src/CMakeFiles/utility_functions_library.dir/UtilityFunctions/utility_functions.cpp.o

    [ 50%] Linking CXX static library libutility_functions_library.a

    [ 50%] Built target utility_functions_library

    [ 75%] Building CXX object Mat-app/CMakeFiles/Mat-app.dir/Main.cpp.o

    [100%] Linking CXX executable Mat-app

    [100%] Built target Mat-app


* ~/Example-Code/build/Mat-app$ **./Mat-app** <mark>Run the executable file</mark>