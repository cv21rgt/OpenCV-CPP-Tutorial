# Computer Vision tutorials using OpenCV and C++

## Introduction

:memo: In this repo I provide tutorials showing how you can use the computer vision library <a href = "https://docs.opencv.org/4.8.0/index.html">**OpenCV**</a> with **C++**. Much of the material applies to images, but I will also apply it to videos where relevant. In each tutorial I attempt to provide as much detail and background as possible about the computer vision or C++ concepts. I will also provide links to other useful literature were possible.


## Motivation

:bulb: A lot of tutorials do not cover the majority of Computer Vision concepts. Most just cover the basic concepts. After that you are on your own.

:bulb: The majority of tutorials and code examples are written in Python. Very few are written in C++.

:bulb: C++ code examples online are mainly written using concepts from older C++ standards - C++11, C++14. You even see this in most <a href = "https://docs.opencv.org/4.8.0/d9/df8/tutorial_root.html">**examples**</a> provided in the OpenCV documentation.

:bulb: I am using this opportunity to learn OpenCV and C++. As such, some of the code I will provide may not be the best - if you have any suggestions please leave a comment and will take the opportunity to improve my coding skills.

## Prerequisites

:bulb: OpenCV 4.8.0 or later
:bulb: C++ compiler with C++17 capability
:bulb: CMake - minimum version 3.25
:bulb: C++ plotting library
:bulb: An IDE - I am using Visual Studio Code, but you can use any you are familiar with.
:bulb: Doxygen - for code documentation
:bulb: Good knowledge of C++. You should at least understand advanced C++ concepts up to and including **classes**, **inheritance** and **templates**. This is important because even the basic core data types in OpenCV are implemented as class templates and to use these data types you need to have a good basic understanding of templates. Some core types make use of inheritance to implement some of their functions. If you are not confident in these advanced topics, a good starting point is going over <a href = "https://www.learncpp.com/">**this**</a> tutorial. It provides a very solid foundation, advanced and modern C++ concepts.

## Topics covered

* OpenCV basic core types
* Read and write images
* Drawing and annotation on images
* Image arithmetic
* Bitwise operations
* Masking
* Splitting and Merging channels
* Color spaces
* Geometrical transformations
* Histograms
* Smoothing and Blurring
* Thresholding
* Gradients and Edge Detection
* Contours

## Structure of tutorials

:memo: Material relevant to each topic will be found in a folder named after each topic. The material notes are provided as **markdown** files e.g. Histograms.md

:memo: Where necessary, any code files provided will follow a directory/folder structure which will allow you to build the projects using CMake. At a minimum, such a project should have the following directory structure:

<div class="highlight-default notranslate"><div class="highlight"><pre><span></span><span class="o">-</span> <span class="n">project</span>
  <span class="o">-</span> <span class="n">README</span><span class="o">.</span><span class="n">md</span>
  <span class="o">-</span> <span class="n">Notes</span><span class="o">.</span><span class="n">md</span>
  <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt</span>  
  <span class="o">-</span> <span class="n">include</span>
    <span class="o">-</span> <span class="n">project</span>
      <span class="o">-</span> <span class="n">example</span><span class="o">.</span><span class="n">hpp</span>
  <span class="o">-</span> <span class="n">src</span>
    <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt</span>
    <span class="o">-</span> <span class="n">example</span><span class="o">.</span><span class="n">cpp</span>
  <span class="o">-</span> <span class="n">project-app</span>
    <span class="o">-</span> <span class="n">CMakeLists</span><span class="o">.</span><span class="n">txt</span>
    <span class="o">-</span> <span class="n">main</span><span class="o">.</span><span class="n">cpp</span>
</pre></div>
</div>



## Structure of code examples

:memo: Within each markdown file with the material notes, code examples will be provided. To keep things in one place and make it easy for you to follow along, the code examples will follow the format:

*example.cpp*
```c++
// 1. includes

// 2. Function declarations

// 3. main() function

// 4. Function definitions
```

## Other relevant information

:memo: As we go through each tutorial, you will notice that we will create our own functions to perform certain tasks relevant to computer vision projects. We will try to generalize these functions as much as possible - sometimes making use of templates - so that they can be used in a variety of scenarios. To save us time in future, we will use this opportunity to create our own library with these functions. That way you can incorporate this library in your own computer vision projects. To keep things simple I will use a single header file. I am naming my library `utility_functions.h` and will have the directory structure **UtilityFunctions\include\utility_functions.h**. Within the file, I will use namespaces to give the code a bit of structure - which will make it easier to look for functions within the file. You can opt to use a different structure if you want.

## Author

:memo: Rodney

## License

:memo: This project is licensed under the MIT License - see the <a href = "https://github.com/cv21rgt/OpenCV-CPP-Tutorial/blob/main/LICENSE">**LICENSE.md**</a> for details.
