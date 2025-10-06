# Introduction

:notebook_with_decorative_cover: In this tutorial we will look at some basic image processing operations. These operations on their own or in combination are required in advanced image processing topics - hence the need to master these operations at this stage. These operations include: 

1. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/10_Basic_Image_Processing/1_Accessing_Pixel_Intensity_Values.md">Accessing pixel intensity values</a>
2. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/10_Basic_Image_Processing/2_Image_Arithmetic.md">Image arithmetic</a> - addition, subtraction, multiplication, and division of images
3. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/10_Basic_Image_Processing/3_Image_Blending.md">Image blending</a>
4. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/10_Basic_Image_Processing/4_Bitwise_Operators.md">Bitwise operations</a>
5. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/10_Basic_Image_Processing/5_Masking.md">Masking</a>
6. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/10_Basic_Image_Processing/6_Color_Spaces.md">Color spaces</a>


## How to run the examples

:memo: We will use CMake to build and run our code. Make sure you have the following project structure. You can use any build you are familiar with.

<div class="highlight-default notranslate"><div class="highlight"><pre><span></span><span class="o">-</span> <span class="n">Example-Code -> main project folder for code examples</span>
  <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt -> main CMakeLists file</span>
  <span class="o">-</span> <span class="n">Image-Processing-app -> will contain the main.cpp or other source files</span>
    <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt - builds our executable file using any external libraries e.g OpenCV</span>
    <span class="o">-</span> <span class="n">main</span><span class="o">.</span><span class="n">cpp - were you write your example code </span>
</pre></div>
</div>

:memo: It is important to read the CMakeLists.txt files comments (starts with the character `#`) to understand what each command does. Always start with the main CMakeLists file - the one which introduces the project and gives the minimum CMake version to use. It's the one that is not in any directory/folder inside the **Example-Code** directory. **Don't forget to change file paths in your CMakeLists files to suite your system.**

:memo: To run code, you need to be in the **Example-Code** directory and type the following commands in your terminal. Our executable file will be called **Basic-Image-Processing-app** (see CMakeLists.txt file in directory **Image-Processing-app**). Be sure to change source file name in CMakeLists.txt file to match the code file you want to run. In the following, **text in bold** are the commands to type in terminal (don't copy and paste). <mark>Highlighted text</mark> are comments explaining what the command does.


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

* ~/Example-Code/build$ **make** <mark>Build your source files into an executable using CMAKE. Your executable should be in '/build/Image-Processing-app'</mark>

* ~/Example-Code/build/Image-Processing-app$ **./Basic-Image-Processing-app** <mark>Run the executable file</mark>