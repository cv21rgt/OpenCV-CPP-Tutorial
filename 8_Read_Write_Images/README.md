## Introduction

:memo: In this chapter we will cover the basics on loading and saving images. We will also look at how to compress and decompress images. This is done under the following sub-topics:

1. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/8_Read_Write_Images/1_Introduction.md">Introduction</a> to the image types you can use in OpenCV.
2. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/8_Read_Write_Images/2_Read_Image_Files.md">Read or upload image files</a> into OpenCV.
3. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/8_Read_Write_Images/3_Write_Image_Files.md">Save or write images to disk</a>.
4. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/8_Read_Write_Images/4_Image_Compression.md">How to compress images</a> before saving them so we can save disk space.
5. <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/8_Read_Write_Images/5_Image_Decompression.md">How to de-compress images</a> into an array that can be understood by the OpenCV library.

## How to run the examples

:memo: We will use CMake to build and run our code. Make sure you have the following project structure. You can use any build you are familiar with.

<div class="highlight-default notranslate"><div class="highlight"><pre><span></span><span class="o">-</span> <span class="n">Example-Code -> main project folder for code examples</span>
  <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt -> main CMakeLists file</span>
  <span class="o">-</span> <span class="n">Read-Write-Data-app -> will contain the main.cpp or other source files</span>
    <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt - builds our executable file using any external libraries e.g OpenCV</span>
    <span class="o">-</span> <span class="n">main</span><span class="o">.</span><span class="n">cpp - were you write your example code </span>
</pre></div>
</div>

:memo: It is important to read the CMakeLists.txt files comments (starts with the character `#`) to understand what each command does. Always start with the main CMakeLists file - the one which introduces the project and gives the minimum CMake version to use. It's the one that is not in any directory/folder inside the **Example-Code** directory. **Don't forget to change file paths in your CMakeLists files to suite your system.**

:memo: To run code, you need to be in the **Example-Code** directory and type the following commands in your terminal. In this chapter our source code is in various files. Our executable file will be called **Read-Write-app** (see CMakeLists.txt file in directory **Read-Write-Data-app**). Be sure to change source file name in CMakeLists.txt file to match the code file you want to run. In the following, **text in bold** are the commands to type in terminal (don't copy and paste). <mark>Highlighted text</mark> are comments explaining what the command does.


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

* ~/Example-Code/build$ **make** <mark>Build your source files into an executable using CMAKE. Your executable should be in '/build/Read-Write-Data-app'</mark>

* ~/Example-Code/build/Read-Write-Data-app$ **./Read-Write-app** <mark>Run the executable file</mark>