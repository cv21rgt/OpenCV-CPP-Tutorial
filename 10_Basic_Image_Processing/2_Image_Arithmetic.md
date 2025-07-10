# Introduction

:notebook_with_decorative_cover: Basic arithmetic operations include addition, subtraction, multiplication and division. When working with images, the outputs of these operations are impacted by the limits imposed on the data type of the pixel values. This means the output value cannot be outside the range set aside for that particular data type.

:notebook_with_decorative_cover: For example, an image with the data type  `CV_8UC1` is expected to have pixel values within the range `[0, 255]`. What happens when we try to add the value `10` to a pixel value of `250`. Normally, we would end up with a pixel value of `260` - but since we are dealing with 8-bit unsigned integers, `260` is outside their range and is thus considered an invalid value.

:notebook_with_decorative_cover: OpenCV solves this by applying the concept of **saturation casting** - which we have already dedicated chapter 3 of these tutorials to. Simply put, saturation casting clips any pixel value below `0` to the minimum range value of `0` and any value above `255` to the maximum range value of `255`. As a result, our output value of `260` will be clipped to `255`.

:notebook_with_decorative_cover: Clipping of values applies when the data type is `unsigned char` , `signed char` , `unsigned short` or `signed short`.

:notebook_with_decorative_cover: Sometimes, arithmetic operations such as multiplication and division can result in an answer that has decimal values (also known as a floating-point value). According to the OpenCV documentation: 

**When the input value is a floating-point value and the target type is an integer (8-, 16- or 32-bit), the floating-point value is first rounded to the nearest integer and then clipped if needed (when the target type is 8- or 16-bit)**.

:notebook_with_decorative_cover: In summary:

1. Clipping is done when the target type is `unsigned char` , `signed char` , `unsigned short` or `signed short`. 
2. When the output array is `CV_32S`, no clipping is done. This means **you may even get result of an incorrect sign in the case of overflow**. 
3. When the input value is a floating-point value and the target type is an integer (8-, 16- or 32-bit), the floating-point value is first rounded to the nearest integer and then clipped if needed (when the target type is 8- or 16-bit).

## How OpenCV handles arithmetic operators

:notebook_with_decorative_cover: OpenCV handles arithmetic operators in two main ways:

1. Using <a href = "https://docs.opencv.org/4.8.0/d1/d10/classcv_1_1MatExpr.html#MatrixExpressions">matrix expressions</a>. These resemble mathematical statements e.g. $A + B$, $A - B$, $A * B$ or $A / B$.
2. Using functions. These functions often offer more options than matrix expressions, for example, some functions make use of a **mask** - which allows you to constrain your computations to a smaller area of an image.

:notebook_with_decorative_cover: In this topic, when it comes to matrix expressions, we will use the following notation:

* $A$ and $B$ are image arrays of type `cv::Mat` since most images are dense arrays.
* $s$ is a constant value of type `cv::Scalar` - remember a `cv::Scalar` object can hold up to 4 values.
* $alpha$ is a single real-valued constant of type `double` e.g. 3.14

## Addition operator

:notebook_with_decorative_cover: The addition operator can be applied to images in two situations: 

* Add two images  - This results in a third image, in which each pixel value is the sum of the values of the corresponding pixel from each of the two input images. If $P_1(row, column)$ and $P_2(row, column)$ are pixel values at location $(row, column)$ in two images to be added, then the sum of the pixel values at the same location in the output image is given by $Q(row, column) = P_1(row, column) + P_2(row, column)$. The input images should have the same **size** and **number of channels**. This will result in an image of the same size and number of channels as the input images. However, the input images and the output image can all have the same or different depths/data type. For example, you can add a 16-bit unsigned image array to a 8-bit signed image array and store the sum as a 32-bit floating-point image array. 
* Add a constant value $C$ to a single image - The resulting image will have each pixel value as the sum of the input image pixel value and the constant value at each location, i.e., $Q(row, column) = P_1(row, column) + C$.

:notebook_with_decorative_cover: For images with more than one channel (e.g. color images), the individual values from each channel (e.g. red, green, blue) are simply added seperately to produce the output value.

:notebook_with_decorative_cover: As mentioned previously, we can use the addition operator either in matrix expressions or through functions. 

### Addition through matrix expressions

:notebook_with_decorative_cover: Using matrix expressions we can perform simple image addition as follows:

* Add two image arrays e.g., $A + B$, $B + A$
* Add a constant to an image array e.g., $A + s$, $s + A$

**Example 1:** Use matrix expressions to add grayscale images

```c++
#include "opencv2/core.hpp"        // for OpenCV core types e.g. cv::Mat
#include "opencv2/imgcodecs.hpp"   // for cv::imread
#include "opencv2/highgui.hpp"     // for displaying images in windows

#include "UtilityFunctions/utility_functions.h" // functions from our own library

#include <iostream>

int main()
{
    //------------------ Grayscale or 1-Channel Images --------------//

    // Read two 1 channel images (or Grayscale images)
    // Images should have same size and number of channels
    cv::Mat A { cv::imread("Example-Code/images/grayscale_image_1.jpeg", 
                cv::IMREAD_ANYCOLOR) };
    if (A.empty())
    {
        std::cout << "\nCould not open image A data\n";
        return -1;  
    }
    else
    {
        // Check sizes, no. of channels and data types of image
        std::cout << "\nSize of image A = " << A.size()
                  << "\nData type of image A = " << CPP_CV::General::openCVDescriptiveDataType(A.type()) 
                  << '\n';

    }

    cv::Mat B { cv::imread("Example-Code/images/grayscale_image_2.jpeg",
                cv::IMREAD_ANYCOLOR) };
    if (B.empty())
    {
        std::cout << "\nCould not open image B data\n";
        return -1;  
    }
    else
    {
        std::cout << "\nSize of image B = " << B.size() 
                  << "\nData type of image B = " << CPP_CV::General::openCVDescriptiveDataType(B.type()) 
                  << '\n';
    }

     // 1. Add two images
    cv::Mat C { A + B }; // OR cv::Mat C { B + A };
    std::cout << "\nSize of image C (A+B) = " << C.size() 
              << "\nData type of image C (A+B) = " << CPP_CV::General::openCVDescriptiveDataType(C.type()) 
              << '\n';

    // 2. Add a scalar value to an image
    
    // i.)  We want to increase our intensity values by 40, 
    //      so we define a scalar value to hold this value
    // ii.) Because we are dealing with grayscale images, which have 1 channel, 
    //      we create a cv::Scalar with 1 value
    const cv::Scalar s1 {40};

    cv::Mat D { A + s1 }; // OR cv::Mat E { s1 + A };
    std::cout << "\nSize of image D (A+cv:Scalar(40)) = " << D.size() 
              << "\nData type of image D (A+cv:Scalar(40)) = " << CPP_CV::General::openCVDescriptiveDataType(D.type()) 
              << '\n';

    // Display images in windows
    cv::imshow("A", A);
    cv::imshow("B", B);
    cv::imshow("A+B", C);
    cv::imshow("A+cv:Scalar(40)", D);

    cv::waitKey(0);

    cv::destroyAllWindows();

    std::cout << '\n';

    return 0;
}
```

**Output**

**Figure 1:** Grayscale image addition

![Image addition using matrix expressions](./images/image_addition.png)

:notebook_with_decorative_cover: Image addition `A+B` combined data pixels in such a way that parts of each input image are present in the output image. The addition of a constant value `A + cv::Scalar(40)` resulted in a more brighter output image as the pixel values moved towards the maximum value of `255`.

**Example 2:** Use matrix expressions to add color images

```c++
#include "opencv2/core.hpp"        // for OpenCV core types e.g. cv::Mat
#include "opencv2/imgcodecs.hpp"   // for cv::imread
#include "opencv2/highgui.hpp"     // for displaying images in windows

#include "UtilityFunctions/utility_functions.h" // functions from our own library

#include <iostream>

int main()
{
    //------------------ Color Images --------------//

    // Read two 3 channel color images 
    // Images should have same size and number of channels
    cv::Mat A { cv::imread("Example-Code/images/color_1.jpeg", 
                cv::IMREAD_ANYCOLOR) };
    if (A.empty())
    {
        std::cout << "\nCould not open image A data\n";
        return -1;  
    }
    else
    {
        // Check sizes, no. of channels and data types of image
        std::cout << "\nSize of image A = " << A.size()
                  << "\nData type of image A = " 
                  << CPP_CV::General::openCVDescriptiveDataType(A.type()) 
                  << '\n';

    }

    cv::Mat B { cv::imread("Example-Code/images/color_2.jpeg",
                cv::IMREAD_ANYCOLOR) };
    if (B.empty())
    {
        std::cout << "\nCould not open image B data\n";
        return -1;  
    }
    else
    {
        std::cout << "\nSize of image B = " << B.size() 
                  << "\nData type of image B = " 
                  << CPP_CV::General::openCVDescriptiveDataType(B.type()) 
                  << '\n';
    }


    // 1. Add two images
    cv::Mat C { A + B }; // OR cv::Mat C { B + A };
    std::cout << "\nSize of image C (A+B) = " << C.size() 
              << "\nData type of image C (A+B) = " << CPP_CV::General::openCVDescriptiveDataType(C.type()) 
              << '\n';

    // 2. Add a scalar value to an image
    
    // i.)  We want to increase the pixel values of each channel by 30, 40, 50
    //      respectively, so we define a scalar object to hold these values
    // ii.) Because we are dealing with color images, which have 3 channels, 
    //      we create a cv::Scalar with 3 values
    const cv::Scalar s1 {30, 40, 50};

    cv::Mat D { A + s1 }; // OR cv::Mat E { s1 + A };
    std::cout << "\nSize of image D (A+cv:Scalar(30, 40, 50)) = " << D.size() 
              << "\nData type of image D (A+cv:Scalar(30, 40, 50)) = " 
              << CPP_CV::General::openCVDescriptiveDataType(D.type()) 
              << '\n';

    // Display images in windows
    cv::imshow("A", A);
    cv::imshow("B", B);
    cv::imshow("A+B", C);
    cv::imshow("A+cv:Scalar(30, 40, 50)", D);

    cv::waitKey(0);

    cv::destroyAllWindows();

    std::cout << '\n';

    return 0;
}
```

**Output**

**Figure 2:** Color image addition

![Color image addition](./images/color_image_addition.png)

:notebook_with_decorative_cover: Figure 2 shows that the output of straight color image addition `A+B` is not that impressive - actually results in an image that is too bright and difficult for the human eye to differentiate its features. This is probably why other processes are needed to complement image addition.


### Addition through a function

:notebook_with_decorative_cover: OpenCV provides the alternative function `void cv::add(cv::InputArray src1, cv::InputArray src2, cv::OutputArray dst, cv::InputArray mask = cv::noArray(), int dtype = -1)` for adding images. This function is found in the header `<opencv2/core.hpp>`.

* `src1` - First input image or constant value. The constant value is constructed as a `cv::Scalar` object.
* `src2` - Second input image or constant value. The constant value is constructed as a `cv::Scalar` object.
* `dst` - Output image that has the same size and number of channels as the input image.
* `mask` - Optional operation mask defining region of interest. This must be an 8-bit single channel array. We have not dealt with masks yet, but will do so in one of the chapters in this tutorial - so be patient - as we need to learn about **bitwise operations** first.
* `dtype` - Optional depth of the output image. When both input images have the same data type, `dtype` can be set to `-1`, which will be equivalent to `src1.depth()`.

:notebook_with_decorative_cover: The above function calculates: 

1. The sum of two images ($src1$ and $src2$) when both input images have the same size and the same number of channels, i.e., $dst = src1 + src2$.
2. The sum of an image, $src1$, and a constant value, $C$. The constant value can be constructed from a `cv::Scalar` object and should have the same number of elements as `src1.channels()`, i.e., $dst = src1 + C$. 
3. The sum of a constant value, $C$, and an image, $src2$. The constant value can be constructed from a `cv::Scalar` object and should have the same number of elements as `src2.channels()`, i.e., $dst = C + src2$. 

**Example 3:** Use a function to add grayscale images

```c++
#include "opencv2/core.hpp"        // for OpenCV core types e.g. cv::Mat
#include "opencv2/imgcodecs.hpp"   // for cv::imread
#include "opencv2/highgui.hpp"     // for displaying images in windows

#include "UtilityFunctions/utility_functions.h" // functions from our own library

#include <iostream>

int main()
{
    //------------------ Grayscale or 1-Channel Images --------------//    

    // Read two 1 channel images (or Grayscale images)
    // Images should have same size and number of channels
    cv::Mat A { cv::imread("Example-Code/images/grayscale_image_1.jpeg", 
                cv::IMREAD_ANYCOLOR) };
    if (A.empty())
    {
        std::cout << "\nCould not open image A data\n";
        return -1;  
    }
    else
    {
        // Check sizes, no. of channels and data types of image
        std::cout << "\nSize of image A = " << A.size()
                  << "\nData type of image A = " 
                  << CPP_CV::General::openCVDescriptiveDataType(A.type()) 
                  << '\n';

    }

    cv::Mat B { cv::imread("Example-Code/images/grayscale_image_2.jpeg",
                cv::IMREAD_ANYCOLOR) };
    if (B.empty())
    {
        std::cout << "\nCould not open image B data\n";
        return -1;  
    }
    else
    {
        std::cout << "\nSize of image B = " << B.size() 
                  << "\nData type of image B = " 
                  << CPP_CV::General::openCVDescriptiveDataType(B.type()) 
                  << '\n';
    }

    // 1. Add two images

    // a.) A + B
    cv::Mat C1;
    cv::add(A,               // First input image array
            B,               // Second input image array
            C1,              // Output image array
            cv::noArray(),   // Mask - we are currently not using this value
            -1               // Output image data type. This will be the same A                             
           );
    std::cout << "\nSize of image C1 (A+B) = " << C1.size() 
              << "\nData type of image C1 (A+B) = " 
              << CPP_CV::General::openCVDescriptiveDataType(C1.type()) 
              << '\n';
    
    // b.) B + A
    cv::Mat C2;
    cv::add(B,               // First input image array
            A,               // Second input image array
            C2,              // Output image array
            cv::noArray(),   // Mask - we are currently not using this value
            CV_8U          // Specify your own output image data type
           );
    std::cout << "\nSize of image C2 (B+A) = " << C2.size() 
              << "\nData type of image C2 (B+A) = " 
              << CPP_CV::General::openCVDescriptiveDataType(C2.type()) 
              << '\n';
        
 
    // 2. Add a scalar value to an image
    
    // i.)  We want to increase our intensity values by 30, 
    //      so we define a scalar value to hold this value
    // ii.) Because we are dealing with grayscale images, which have 1 channel, 
    //      we create a cv::Scalar with 1 value
    const cv::Scalar s1 {30};
    
    // a.) A + s1
    cv::Mat D1;
    cv::add(A,               // Image array
            s1,              // Constant/Scalar value
            D1,              // Output image array
            cv::noArray(),   // Mask - we are currently not using this value
            -1               // Output image data type. This will be the same A                             
           );
    std::cout << "\nSize of image D1 (A+cv:Scalar(30)) = " << D1.size() 
              << "\nData type of image D1 (A+cv:Scalar(30)) = " 
              << CPP_CV::General::openCVDescriptiveDataType(D1.type()) 
              << '\n';
    
    // b.) s1 + A
    cv::Mat D2;
    cv::add(s1,              // Constant/Scalar value
            A,               // Image array
            D2,              // Output image array
            cv::noArray(),   // Mask - we are currently not using this value
            CV_8U            // Specify your own output image data type
           );
    std::cout << "\nSize of image D2 (cv:Scalar(30)+A) = " << D2.size() 
              << "\nData type of image D2 (cv:Scalar(30)+A) = " 
              << CPP_CV::General::openCVDescriptiveDataType(D2.type()) 
              << '\n';

    // Display images in windows
    cv::imshow("A", A);
    cv::imshow("B", B);
    cv::imshow("A+B", C1);
    cv::imshow("B+A", C2);
    cv::imshow("A+cv:Scalar(30)", D1);
    cv::imshow("cv::Scalar(30)+A", D2);

    cv::waitKey(0);

    cv::destroyAllWindows();

    std::cout << '\n';

    return 0;
}
```

**Example 4** Use a function to add color images

```c++
#include "opencv2/core.hpp"        // for OpenCV core types e.g. cv::Mat
#include "opencv2/imgcodecs.hpp"   // for cv::imread
#include "opencv2/highgui.hpp"     // for displaying images in windows

#include "UtilityFunctions/utility_functions.h" // functions from our own library

#include <iostream>

int main()
{
    
    //------------------ Color images with 3 channels -----------------//

    // Read two 3-channel images in OpenCV default BGR (Blue, Green, Red) format 
    // Images should have same size and number of channels
    cv::Mat A { cv::imread("Example-Code/images/color_1.jpeg", 
                cv::IMREAD_ANYCOLOR) };
    if (A.empty())
    {
        std::cout << "\nCould not open image A data\n";
        return -1;  
    }
    else
    {
        // Check sizes, no. of channels and data types of image
        std::cout << "\nSize of image A = " << A.size()
                  << "\nData type of image A = " 
                  << CPP_CV::General::openCVDescriptiveDataType(A.type()) 
                  << '\n';

    }

    cv::Mat B { cv::imread("Example-Code/images/color_2.jpeg",
                cv::IMREAD_ANYCOLOR) };
    if (B.empty())
    {
        std::cout << "\nCould not open image B data\n";
        return -1;  
    }
    else
    {
        std::cout << "\nSize of image B = " << B.size() 
                  << "\nData type of image B = " 
                  << CPP_CV::General::openCVDescriptiveDataType(B.type()) 
                  << '\n';
    }

    // 1. Add two images
    
    // a.) A + B
    cv::Mat C1;
    cv::add(A,               // First input image array
            B,               // Second input image array
            C1,              // Output image array
            cv::noArray(),   // Mask - we are currently not using this value
            -1               // Output image data type. This will be the same A                             
           );
    std::cout << "\nSize of image C1 (A+B) = " << C1.size() 
              << "\nData type of image C1 (A+B) = " 
              << CPP_CV::General::openCVDescriptiveDataType(C1.type()) 
              << '\n';
    
    // b.) B + A
    cv::Mat C2;
    cv::add(B,               // First input image array
            A,               // Second input image array
            C2,              // Output image array
            cv::noArray(),   // Mask - we are currently not using this value
            A.depth()        // Output image will have same data type as A
           );
    std::cout << "\nSize of image C2 (B+A) = " << C2.size() 
              << "\nData type of image C2 (B+A) = " 
              << CPP_CV::General::openCVDescriptiveDataType(C2.type()) 
              << '\n';

    // 2. Add a scalar value to an image
    
    // i.)  We want to increase the pixel values of each channel by 30, 40, 50,  
    //      respectively, so we define a scalar object to hold these values
    // ii.) Because we are dealing with color images, which have 3 channels, 
    //      we create a cv::Scalar with 3 values
    const cv::Scalar s1 {30, 40, 50};

    // a.) A + s1
    cv::Mat D1;
    cv::add(A,                // Image array
            s1,               // Constant/Scalar values
            D1,               // Output image array
            cv::noArray(),    // Mask - we are currently not using this value
            -1                // Output image data type. This will be the same A                             
           );
    std::cout << "\nSize of image D1 (A+cv:Scalar(30, 40, 50)) = " << D1.size() 
              << "\nData type of image D1 (A+cv:Scalar(30, 40, 50)) = " 
              << CPP_CV::General::openCVDescriptiveDataType(D1.type()) 
              << '\n';
    
    // b.) s1 + A
    cv::Mat D2;
    cv::add(s1,              // Constant/Scalar value
            A,               // Image array
            D2,              // Output image array
            cv::noArray(),   // Mask - we are currently not using this value
            CV_8UC3         // Specify your own output image data type
           );
    std::cout << "\nSize of image D2 (cv:Scalar(30, 40, 50)+A) = " << D2.size() 
              << "\nData type of image D2 (cv:Scalar(30, 40, 50)+A) = " 
              << CPP_CV::General::openCVDescriptiveDataType(D2.type()) 
              << '\n';

    // Display images in windows
    cv::imshow("A", A);
    cv::imshow("B", B);
    cv::imshow("A+B", C1);
    cv::imshow("B+A", C2);
    cv::imshow("A+cv:Scalar(30, 40, 50)", D1);
    cv::imshow("cv:Scalar(30, 40, 50)+A", D2);

    cv::waitKey(0);

    cv::destroyAllWindows();

    std::cout << '\n';

    return 0;
}
```

### Guidelines for using image addition

:notebook_with_decorative_cover: One direct use of addition includes adding a constant value to all pixels in an image so as to brighten that image.

:notebook_with_decorative_cover: Before applying the addition operator to any image, you should be aware what will be the impact of such an operation. Lets say we have two images of data type `CV_8UC1`. This is a gray scale image with intensity values in the range `[0, 255]`, with `0` being the darkest shade and `255` being the lightest shade. As such, any addition will ultimately increase the intensity values of each pixel thereby making the image brighter in appearance. This can have the positive effect of highlighting previously hidden features, but can also have the opposite effect of losing some features or different features may end up looking the same as the higher intensity values are all clipped to the same maximum value of `255`. 

:notebook_with_decorative_cover: Image addition is a common sub-step in more complicated image algorithms rather than as a useful operator on its own. Such an example is the concept of **image blending** - which uses image addition as one of its operations. We will look at image blending later on in this tutorial.

#### <a href = "https://homepages.inf.ed.ac.uk/rbf/HIPR2/8bitcol.htm">Impact of adding color images</a>

:notebook_with_decorative_cover: Full BGR or RGB color requires that the intensities of three color components be specified for each and every pixel. It is common for each component intensity to be stored as an 8-bit integer, and so each pixel requires 24 bits to completely and accurately specify its color. If this is done, then the image is known as a 24-bit color image. However there are two problems with this approach:

* Storing 24 bits for every pixel leads to very large image files that with current technology are cumbersome to store and manipulate. For instance a 24-bit 512×512 image takes up 750KB in uncompressed form.
* Many monitor displays use <a href = "https://homepages.inf.ed.ac.uk/rbf/HIPR2/colmap.htm">colormaps</a> with 8-bit index numbers, meaning that they can only display 256 different colors at any one time. Thus it is often wasteful to store more than 256 different colors in an image anyway, since it will not be possible to display them all on screen. 

:notebook_with_decorative_cover: Because of this, many image formats (e.g. 8-bit GIF and TIFF) use 8-bit colormaps to restrict the maximum number of different colors to 256. Using this method, it is only necessary to store an 8-bit index into the colormap for each pixel, rather than the full 24-bit color value. Thus 8-bit image formats consist of two parts: a colormap describing what colors are present in the image, and the array of index values for each pixel in the image.

:notebook_with_decorative_cover: When a 24-bit full color image is turned into an 8-bit image, it is usually necessary to throw away some of the colors, a process known as <a href = "https://homepages.inf.ed.ac.uk/rbf/HIPR2/quantize.htm">color quantization</a>. This leads to some degradation in image quality, but in practice the observable effect can be quite small, and in any case, such degradation is inevitable if the image output device (e.g. screen or printer) is only capable of displaying 256 colors or less.

:notebook_with_decorative_cover: The use of 8-bit images with colormaps does lead to some problems in image processing. 

1. First of all, each image has to have its own colormap, and there is usually no guarantee that each image will have exactly the same colormap. Thus on 8-bit displays it is frequently impossible to correctly display two different color images that have different colormaps at the same time. Note that in practice 8-bit images often use reduced size colormaps with less than 256 colors in order to avoid this problem.

2. Another problem occurs when the output image from an image processing operation contains different colors to the input image or images. This can occur very easily, as for instance when two color images are **added together** pixel-by-pixel. Since the output image contains different colors from the input images, it ideally needs a new colormap, different from those of the input images, and this involves further color quantization which will degrade the image quality. Hence the resulting output is usually only an approximation of the desired output. Repeated image processing operations will continually degrade the image colors. And of course we still have the problem that it is not possible to display the images simultaneously with each other on the same 8-bit display.

:notebook_with_decorative_cover: Because of these problems it is to be expected that as computer storage and processing power become cheaper, there will be a shift away from 8-bit images and towards full 24-bit image processing. 

## Subtraction

:notebook_with_decorative_cover: The subtraction operator can be applied to images in four situations: 

* Straighforward subtraction between two images - This is the default use of the subtraction operator. If $P_1(row, column)$ and $P_2(row, column)$ are pixel values at location $(row, column)$ in two images, the output pixel values from subtracting image $P_2$ from $P_1$ are given by $Q(row, column) = P_1(row, column) - P_2(row, column)$. The input images should have the same **size** and **number of channels**. This will result in an image of the same size and number of channels as the input images. However, the input images and the output image can all have the same or different depths. For example, you can subtract two 8-bit unsigned image arrays and store the difference in a 16-bit signed image array. 
* Compute the absolute differences between two input images - This has the impact of removing the sign of any negative pixel values that would have resulted from the computation. This means all pixel values in the output image will be positive values. Mathematically, this is defined as $Q(row, column) = |P_1(row, column) - P_2(row, column)|$. As an example $|3 - 5| = 2$.
* Subtract a constant value $C$ from a single image - The resulting image will have each pixel value as the difference of the input image pixel value and the constant value at each location, i.e., $Q(row, column) = P_1(row, column) - C$. If you want absolute differences here, this can be extended to $Q(row, column) = |P_1(row, column) - C|$. 
* Subtract an image from a constant value $C$  - The resulting image will have each pixel value as the difference of the constant value and input image pixel value at each location, i.e., $Q(row, column) = C - P_1(row, column)$. If you want absolute differences here, this can be extended to $Q(row, column) = |C - P_1(row, column)|$.

:notebook_with_decorative_cover: We can also use matrix expressions and functions to apply the subtraction operator:

1. Use simple matrix expressions, e.g., if `A` and `B` are image arrays and `s` is a constant value, then we can write `A - B`, `B - A`, `A - s` or `s - A`. For example code, refer to **Example 1** and **Example 2** above - all you have to do is change the arithmetic sign from `+` to `-`. 
2. To compute the absolute difference between two image arrays or between an array and a constant value we use the function `void cv::absdiff(cv::InputArray src1, cv::InputArray src2, cv::OutputArray dst)`. This function is found in the header `<opencv2/core.hpp>`.

   * `src1` - First input image or constant value. The constant value is constructed as a `cv::Scalar` object.
   * `src2` - Second input image or constant value. The constant value is constructed as a `cv::Scalar` object.
   * `dst` - Output image that has the same size and number of channels as the input image.

:notebook_with_decorative_cover: The above function calculates: 

   * The absolute difference between two images ($src1$ and $src2$) when both input images have the same size and the same number of channels, i.e., $dst = |src1 - src2|$.   
   * The absolute difference between an image, $src1$, and a constant value, $C$. The constant value can be constructed from a `cv::Scalar` object and should have the same number of elements as `src1.channels()`, i.e., $dst = |src1 - C|$. 
   * The difference between a constant value, $C$, and an image, $src2$. The constant value can be constructed from a `cv::Scalar` object and should have the same number of elements as `src2.channels()`, i.e., $dst = |C - src2|$. 

3. We can also compute the absolute difference using the function `cv::abs(const cv::MatExpr& e)`. If `A` and `B` are image arrays and `s` is a constant value, then `e` can be any of `A - B`, `B - A`, `A - s` or `s - A`. 

4. We also have the more flexible function `void cv::subtract(cv::InputArray src1, cv::InputArray src2, cv::OutputArray dst, cv::InputArray mask = cv::noArray(), int dtype = -1)`. This function is found in the header `<opencv2/core.hpp>`.

* `src1` - First input image or constant value. The constant value is constructed as a `cv::Scalar` object.
* `src2` - Second input image or constant value. The constant value is constructed as a `cv::Scalar` object.
* `dst` - Output image that has the same size and number of channels as the input image.
* `mask` - Optional operation mask defining region of interest. This must be an 8-bit single channel array. We have not dealt with masks yet, but will do so in one of the chapters in this tutorial - so be patient - as we need to learn about bitwise operations first.
* `dtype` - Optional depth of the output image. When both input images have the same data type, `dtype` can be set to `-1`, which will be equivalent to `src1.depth()`.

:notebook_with_decorative_cover: The above function calculates: 

  * The difference between two images ($src1$ and $src2$) when both input images have the same size and the same number of channels, i.e., $dst = src1 - src2$.
  * The difference between an image, $src1$, and a constant value, $C$. The constant value can be constructed from a `cv::Scalar` object and should have the same number of elements as `src1.channels()`, i.e., $dst = src1 - C$. 
  * The difference between a constant value, $C$, and an image, $src2$. The constant value can be constructed from a `cv::Scalar` object and should have the same number of elements as `src2.channels()`, i.e., $dst = C - src2$. 

### Possible appplications of image subtraction

1. **Medical Imaging** - In medical imaging (MRI, CT scans), image subtraction helps visualize subtle changes within the body, such as tumors, hemorrhages, or the effects of treatment. It can be used to distinguish between different tissue types, identify areas of enhancement, and monitor disease progression. For example, it can help differentiate between a hematoma and a tumor in the liver or other organs. 

2. **Astronomy** - Image subtraction is crucial for identifying variable objects in the sky, such as supernovae or variable stars in other galaxies. By subtracting images taken at different times, astronomers can isolate changes and study these transient phenomena. 

3. **Industrial Inspection** - In manufacturing and quality control, image subtraction can be used to identify defects or deviations from a standard product. It can help detect subtle differences in shape, size, or color that might indicate a flaw. 

4. **Remote Sensing** - In remote sensing applications (satellite imagery), image subtraction can be used to track changes in land cover, deforestation, or urban development over time. It helps monitor environmental changes and natural disasters. 

5. **Background Removal** - Image subtraction is an effective method for removing a static background from an image, especially when dealing with uneven illumination. This is useful in microscopy, where background variations can make it difficult to analyze the sample. 

6. **Enhancing Features** - By subtracting a background image, image subtraction can make subtle features in the foreground more visible and easier to analyze. This is helpful in various scientific and engineering applications. 

7. **Motion Detection** - By subtracting consecutive frames in a video, image subtraction can effectively isolate moving objects, making it a core component in motion detection algorithms. This is used in surveillance systems, security cameras, and video analysis applications. This example may seem confusing as it mentions video data - however when we get to discuss video processing, you will realise that a video is simply made up of images that are shown in a loop at a fast rate. 


## Multiplication

:notebook_with_decorative_cover: The multiplication operator can be applied to images in two ways:

* Multiplication of two input images - this produces an output image in which the pixel values are those of the first image multiplied by the values of the second input image at each corresponding pixel location, i.e., $Q(row, column) = P_1(row, column) * P_2(row, column)$.
* Scaling - this takes a single input image and multiplies its pixel values by a specified constant value, i.e., $Q(row, column) = P_1(row, column) * C$. The constant $C$ is often a floating point number. It may even be negative if the image data type supports that. Using the multiplication operator in this way is more widely used.

:notebook_with_decorative_cover: OpenCV provides the following ways to use the multiplication operator: 

1. Simple scaling - you can use the matrix expression `A * s` or `s * A`, where `A` is an image array and `s` is a constant value.
2. Simple per-element multiplication between images - you can use the matrix expression `A * B`, where `A` and `B` are image arrays. You can also use the `cv::Mat` member function `mul()`, i.e., `A.mul(B)`.
3. Per-element multiplication with optional scaling - you can use the function `void cv::multiply(cv::InputArray src1, cv::InputArray src2, cv::OutputArray dst, double scale = 1, int dtype = -1)`. This function is found in the header `<opencv2/core.hpp>`.

* `src1` - First input image 
* `src2` - Second input image of the same size and same type as `src1`.
* `dst` - Output image that has the same size and number of channels as `src1`.
* `scale` - Optional scale factor.
* `dtype` - Optional depth of the output image. When both input images have the same data type, `dtype` can be set to `-1`, which will be equivalent to `src1.depth()`.

:notebook_with_decorative_cover: The function `cv::multiply()` calculates $dst = scale * src1 * scr2$. 

### Practical uses of image multiplication

:notebook_with_decorative_cover: Image **scaling** is a more widely used application of image multiplication. Given a scaling factor greater than one, scaling will brighten an image. Given a factor less than one, it will darken the image. Scaling generally produces a much more natural brightening/darkening effect than simply *adding an offset to the pixels* (image addition), since it preserves the relative contrast of the image better. Before applying image multiplication through scaling you should be aware of what will happen to your pixel values as it is likely that the output values will fall outside the data type range of the input image. It is also very easy to generate very large numbers with pixel-by-pixel multiplication. If the image processing software supports it, it is often safest to change to an image format with a large range, e.g. floating point, before attempting this sort of calculation. 

:notebook_with_decorative_cover: Pixel-by-pixel multiplication is generally less useful, although sometimes a binary image can be used to multiply another image in order to act as a mask. The idea is to multiply by 1 those pixels that are to be preserved, and multiply by zero those that are not. However for integer format images it is often easier and faster to use the logical operator AND instead. We will look at binary images, masks and bitwise operators in one of the sections.

**Example 5** You can use the following code to perform either image scaling or image to image multiplication. You can also save the output image if you wish. This code includes a template function `dataTypeRange()`, which returns the data range ([min, max]) of an image data type. You need this information to scale image pixel values when displaying them on your monitor. We will also be adding this function to our own library under the `General` namespace for future use. 

*image_multiplication.cpp*

```c++
#include "opencv2/core.hpp"        // for OpenCV core types e.g. cv::Mat
#include "opencv2/imgcodecs.hpp"   // for cv::imread
#include "opencv2/highgui.hpp"     // for displaying images in windows
#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser

#include "UtilityFunctions/utility_functions.h" // functions from our own library

#include <iostream>
#include <tuple>

//----------------------- Function Declarations ------------------//

/**
 * @brief Return the minimum and maximum range for image types.  
 *        One good use is when scaling image values so you can display your 
 *        image on a monitor.     
 * 
 * @tparam T Data type of values to be returned
 * @param type OpenCV image data type as an integer value. 
 *             See https://medium.com/@nullbyte.in/part-2-exploring-
 *                 the-data-types-in-opencv4-a-comprehensive-guide-49272f4a775
 * @return std::tuple<T, T> A tuple object with the minimum and maximum values
 * 
 */
template <typename T>
std::tuple<T, T> dataTypeRange(int type);

//------------------------ main() Function ----------------------------//

int main(int argc, char* argv[])
{

    //---------------- 1. Extract Command Line Arguments -----------------//

    const cv::String keys = 
    "{help h usage ? | | Apply image multiplication }"
    "{image1 | <none> | Full image path }"
    "{image2 | | Full path to second image (Optional argument)}"
    "{scale_factor | 1.0 | Scaling value }"
    "{output_datatype | -1 | Data type assigned to output image. " 
    "Use value -1 if output data type is same as that of image1 }"
    "{output_image | | File path to save output image (must include file extension)}";  

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // Display message about application
    parser.about("\nApplication to perform image arithmetic\n");
    parser.printMessage();

    // Extract the command line arguments
    cv::String image1_path = parser.get<cv::String>("image1");
    cv::String image2_path = parser.get<cv::String>("image2");
    double scale_factor = parser.get<double>("scale_factor");
    int output_image_datatype = parser.get<int>("output_datatype");
    cv::String output_image_path = parser.get<cv::String>("output_image");

    // Check for any errors during command line arguments extraction
    if (!parser.check())
    {
        parser.printErrors(); // Print a list of any errors encountered

        return -1; // Early program exit
    }

    //---------------- 2. Read Image Data -------------------------//

    cv::Mat first_input_image = cv::imread(image1_path, cv::IMREAD_ANYCOLOR);
    if (first_input_image.empty())
    {
        CV_Error_(cv::Error::StsBadArg, 
                      ("Could not read image data from (%s)", 
                        image1_path.c_str())); 
    }
    else 
    {
        // Provide image sizes, no. of channels and data types of image
        std::cout << "\nSize of first input image = " << first_input_image.size()
                  << "\nData type of first input image = " 
                  << CPP_CV::General::openCVDescriptiveDataType(first_input_image.type())
                  << '\n';
    }

    cv::Mat second_input_image;
    if (image2_path.empty()) // If we don't provide a second input image
    {
        // Create a cv::Mat array filled with '1's
        // This will not affect the result of any multiplication 
        // because 'input x 1 = input'
        second_input_image.create(cv::Size(first_input_image.cols, first_input_image.rows), first_input_image.type());
        second_input_image.setTo(cv::Scalar::all(1));
    }
    else 
    {
        second_input_image = cv::imread(image2_path, cv::IMREAD_ANYCOLOR);
        if (second_input_image.empty())
        {
        CV_Error_(cv::Error::StsBadArg, 
                      ("Could not read image data from (%s)", 
                        image2_path.c_str())); 
        }
        else 
        {
            // Provide image sizes, no. of channels and data types of image
            std::cout << "\nSize of second input image = " << second_input_image.size()
                  << "\nData type of second input image = " 
                  << CPP_CV::General::openCVDescriptiveDataType(second_input_image.type())
                  << '\n';
        }

    }

    //---------------- 3. Image Multiplication ------------------------//

    cv::Mat output_image;

    cv::multiply(first_input_image,       // First input image array
                 second_input_image,      // Second input image array
                 output_image,            // Output image array
                 scale_factor,            // Scale factor
                 output_image_datatype    // Data type of output image
                ); 

    std::cout << "\nSize of output image = " << output_image.size()
                  << "\nData type of output image  = " 
                  << CPP_CV::General::openCVDescriptiveDataType(output_image.type())
                  << '\n';

    //----------------- 4. Save output image to file ---------------//

    if (!output_image_path.empty())
    {
        bool success = cv::imwrite(output_image_path, output_image);
        if (success)
        {
            std::cout << "\nSuccessfully saved output image to: " 
                      << output_image_path << '\n';
        } 
        else 
        {
            std::cout << "\nERROR: Could not save output image!\n";
        }
    }
                   
    //------------------ 5. Display images in windows ---------------------//

    cv::namedWindow("First input image", cv::WINDOW_NORMAL);
    cv::imshow("First input image", first_input_image);

    if (!image2_path.empty()) // Display image only if path exists
    {
        cv::namedWindow("Second input image", cv::WINDOW_NORMAL);
        cv::imshow("Second input image", second_input_image);
    }

    // In order to display the computed output image sometimes you 
    // need to scale its values 
    auto [minVal, maxVal] = dataTypeRange<double>(output_image.type());
    double scale = maxVal / 255;
    output_image = output_image * scale;    

    cv::namedWindow("Output image", cv::WINDOW_NORMAL);
    cv::imshow("Output image", output_image);

    cv::waitKey(0);

    cv::destroyAllWindows();    

    std::cout << '\n';

    return 0;
}

//------------------- Function Definitions -------------------//

/**
 * @brief Return the minimum and maximum range for image types.  
 *        One good use is when scaling image values so you can display your 
 *        image on a monitor.     
 * 
 * @tparam T Data type of values to be returned
 * @param type OpenCV image data type as an integer value. 
 *             See https://medium.com/@nullbyte.in/part-2-exploring-
 *                 the-data-types-in-opencv4-a-comprehensive-guide-49272f4a775
 * @return std::tuple<T, T> A tuple object with the minimum and maximum values
 * 
 */
template <typename T>
std::tuple<T, T> dataTypeRange(int type)
{
    switch (type)
	{
        case CV_8UC1: // 8-bit unsigned
        case CV_8UC2:
        case CV_8UC3:
        case CV_8UC4:
            return {0, 255};
        case CV_8SC1: // 8-bit signed
        case CV_8SC2:
        case CV_8SC3:
        case CV_8SC4:
            return {-128, 127};
        case CV_16UC1: // 16-bit unsigned
        case CV_16UC2:
        case CV_16UC3:
        case CV_16UC4:
            return {0, 65535};
        case CV_16SC1: // 16-bit signed
        case CV_16SC2:
        case CV_16SC3:
        case CV_16SC4:
            return {-32768, 32767};
        case CV_32SC1: // 32-bit signed
        case CV_32SC2:
        case CV_32SC3:
        case CV_32SC4:
            return {-2147483648, 2147483647};
        case CV_32FC1: // 32-bit floating point
        case CV_32FC2:
        case CV_32FC3:
        case CV_32FC4:
            return {0, 1};
        case CV_64FC1: // 64-bit floating point
        case CV_64FC2:
        case CV_64FC3:
        case CV_64FC4:
            return {0, 1};
        default:
            return {0, 255};
	}
}
```

## Division

:notebook_with_decorative_cover: The image division operator can be applied in three scenarios.

1. Image division between two images - here the ouput image pixel values are the pixel values of the first image divided by the corresponding pixel values of the second image, i.e., $Q(row, column) = P_1(row, column) / P_2(row, column)$.
2. Divide each image pixel by a constant value - this involves a single input image, in which case every pixel value in that image is divided by a specified constant, $C$, i.e., $Q(row, column) = P_1(row, column) / C$.
3. Constant value divided by each image pixel - this is the opposite of the above scenario, i.e., $Q(row, column) = C / P_1(row, column)$.

:notebook_with_decorative_cover: When discussing division using OpenCV we also need to be aware of the following important issues:

* When dealing with images whose data is `8/16/32-bit` unsigned or signed integers, the output of division is simply rounded to the nearest integer value.
* When dealing with images whose data is `8/16/32-bit` unsigned or signed integers, the output of dividing by `0` is an infinite value - but here is the catch - that infinite value is `0`. If you are curious about the infinite values for most basic data types see <a href = "https://en.cppreference.com/w/cpp/types/numeric_limits/infinity.html">here</a>.
* When dealing with 32-bit floating point images, the output will be a 32-bit decimal value.
* When dealing with 64-bit floating point images, the output will be a 64-bit decimal value. 
* When dealing with `32/64-bit` floating point images, the output image pixel values as a result of dividing by `0`, are set to `inf` or `nan` since mathematically division by `0` is not permissible and this is one of the ways to gracefully handle these scenarios without throwing an exception/error. `inf` means an **infinite number**, and `nan` means **not a number**. We can handle such situations in two ways. One, leave the values as is. Two, replace all `inf` or `nan` pixel values by a carefully chosen value (e.g., the average pixel value in an image). When handling `nan` values we can use the function `void cv::patchNaNs(cv::InputOutputArray a, double val = 0)` - where `a` is a matrix/image of type `CV_32F` and `val` is the value to convert `nan`'s to. You will find this function in the header `<opencv2/core.hpp>`. For handling `inf` values, we have to be creative as shown in the following example where we make use of a template function and `std::numeric_limits<T>::infinity()` from standard C++.

**Example 6** How to handle `inf` or `nan` values

```c++
#include "opencv2/core.hpp"        // for OpenCV core types e.g. cv::Mat
#include <iostream>

/**
 * @brief Returns the "positive infinity" value for a particular data type
 * 
 * @tparam T Data type whose infinite value we want
 * @return T Infinite value of data type 'T'
 */
template <typename T>
T infiniteValue()
{
    return std::numeric_limits<T>::infinity();
}

int main(int argc, char* argv[])
{
    std::cout << "\n--------- Handling inf values -------------\n";

    double data[] {1, 2, 3, 4};
    double data2[] {3, 0, 3, 0};   

    // Use the data above to create two image arrays of size 2x2,
    // with 1 channel each and data type 64-bit float
    cv::Mat m1 {cv::Size(2, 2), CV_64FC1, data};
    cv::Mat m2 {cv::Size(2, 2), CV_64FC1, data2};

    std::cout << "\nm1 = \n" << m1;
    std::cout << "\nm2 = \n" << m2;   

    cv::Mat m3 = m1 / m2;
    std::cout << "\nm1 / m2 = \n" << m3;

    // Replace `inf` pixel values with a numeric value
    auto inf = infiniteValue<double>();
    cv::Mat inf_mask { m3 == inf };
    m3.setTo(0.5, inf_mask); // Use the value '0.5' to replace 'inf' in m3
    std::cout << "\nm3 after replacing 'inf' values = \n" << m3;

    std::cout << "\n\n--------- Handling nan values -------------\n";

    float data3[] {1, 2, 3, 4};
    float data4[] {3, 0, 3, 0};   

    // Use the data above to create two image arrays of size 2x2,
    // with 1 channel each and data type 32-bit float
    cv::Mat m4 {cv::Size(2, 2), CV_32FC1, data3};
    cv::Mat m5 {cv::Size(2, 2), CV_32FC1, data4};

    std::cout << "\nm4 = \n" << m4;
    std::cout << "\nm5 = \n" << m5;   

    cv::Mat m6 = m4 / m5;
    std::cout << "\nm4 / m5 = \n" << m6;

    // Replace 'nan' pixel values with a suitable numeric value
    cv::patchNaNs(m6, 0.2); // Use the value '0.2' to replace 'nan' in m6
    std::cout << "\nm6 after replacing 'nan' values = \n" << m6;

    std::cout << '\n';

    return 0;
}
```

**Output**

    --------- Handling inf values -------------

    m1 = 
    [1, 2;
    3, 4]

    m2 = 
    [3, 0;
    3, 0]

    m1 / m2 = 
    [0.3333333333333333, inf;
    1, inf]

    m3 after replacing 'inf' values = 
    [0.3333333333333333, 0.5;
    1, 0.5]

    --------- Handling nan values -------------

    m4 = 
    [1, 2;
    3, 4]

    m5 = 
    [3, 0;
    3, 0]

    m4 / m5 = 
    [0.33333331, -nan;
    0.99999994, -nan]

    m6 after replacing 'nan' values = 
    [0.33333331, 0.2;
    0.99999994, 0.2]

### Using the division operator in OpenCV

:notebook_with_decorative_cover: Just like with the other arithmetic operators we have discussed so far, we can also use the division operator with matrix expressions and functions.

1. Division using a constant or scalar value - you can use the matrix expression `A / s` or `s / A`, where `A` is an image array and `s` is a constant value.
2. Per-element division between images - you can use the matrix expression `A / B`, where `A` and `B` are image arrays. 
3. Per-element division between arrays (with optional scaling) - you can use the function `void cv::divide(cv::InputArray src1, cv::InputArray src2, cv::OutputArray dst, double scale = 1, int dtype = -1)`. This function is found in the header `<opencv2/core.hpp>`.

* `src1` - first input array.
* `src2` - second input array of the same size and type as `src1`.
* `scale` - scalar factor.
* `dst` -  output array of the same size and type as `src2`.
* `dtype` - optional depth of the output array; if `-1`, `dst` will have depth `src2.depth()`, but in case of an array-by-array division, you can only pass `-1` when `src1.depth()==src2.depth()`. 

This function handles three forms of division:

i. Division between two arrays with optional scaling i.e., $dst = (src1*scale) / src2$. If you just want image division without any scaling, then set `scale = 1`.
ii. Divide a scalar by an array i.e., $dst = scalar / src2$. In this scenario, provide your scalar value as a `cv::Scalar` object. Remember, the number of values in your `cv::Scalar` object must match number of channels in image `src2`. In the function, your `cv::Scalar` object will be the argument `src1`.
iii. Divide an image array by a scalar value i.e., $dst = src1 / scalar$. In this scenario, provide your scalar value as a `cv::Scalar` object. Remember, the number of values in your `cv::Scalar` object must match number of channels in image `src1`. In the function, your `cv::Scalar` object will be the argument `src2`.

4. There is also an overloaded function `void cv::divide(double scale, cv::InputArray src2, cv::OutputArray dst, int dtype = -1)` that handles scenario (ii) above, i.e., $dst = scalar / src2$. In this function the argument `scale` is used to hold the scalar value. This time you provide the scalar value as is NOT as a `cv::Scalar` object.

**Example 7** The following example shows how you can use division with images and scalar values. We also have added a new template function `void replaceInfValues(cv::Mat& img, T value)` to help us if we need to replace `inf` values in an image. This will be added to our own library under the `General` namespace.

```c++
#include "opencv2/core.hpp"        // for OpenCV core types e.g. cv::Mat
#include <iostream>

//----------------------- Function Declaration --------------------//

/**
 * @brief Returns the "positive infinity" value for a particular data type
 * 
 * @tparam T Data type whose infinite value we want
 * @return T Infinite value of data type 'T'
 */
template <typename T>
T infiniteValue();

/**
 * @brief Replace 'inf` values in an image array with a user chosen value
 * 
 * @tparam T Data type of new value
 * @param img cv::Mat image array
 * @param value Value to replace 'inf' values in 'img'
 */
template <typename T>
void replaceInfValues(cv::Mat& img, T value);

//---------------------- End of Function Declarations ----------------//

int main(int argc, char* argv[])
{
    double data[] {1, 2, 3, 4};
    double data2[] {3, 0, 3, 1};   

    // Use the data above to create two image arrays of size 2x2,
    // with 1 channel each and data type 64-bit float
    cv::Mat m1 {cv::Size(2, 2), CV_64FC1, data};
    cv::Mat m2 {cv::Size(2, 2), CV_64FC1, data2};

    std::cout << "\nm1 = \n" << m1;
    std::cout << "\nm2 = \n" << m2;   

    std::cout << "\n\n---------- dst = (src1*scale)/src2 -------------\n";

    // 1. Handle image to image division with 
    //    optional scaling, i.e., dst = (src1*scale)/src2
    cv::Mat m3;
    cv::divide(m1,    // First input array
               m2,    // Second input array
               m3,    // Output array
               1,     // Scale factor
               -1);   // Output image data type
    std::cout << "\nm1 / m2 = \n" << m3;

    // Handle any 'inf' values
    replaceInfValues(m3, 0.5); // Use the value '0.5' to replace 'inf' in m3
    std::cout << "\nArray after replacing 'inf' values = \n" << m3;

    std::cout << "\n\n---------- dst = src1/scalar -------------\n";

    // 2. Handle image division by a scalar i.e., dst = src1/scalar
    cv::Mat m4;
    cv::Scalar s {2.5};
    cv::divide(m1,    // First input array
               s,     // Scalar value
               m4,    // Output array
               1,     // Scale factor
               -1);   // Output image data type
    std::cout << "\nm1 / 2.5 = \n" << m4;

    // Handle any 'inf' values
    replaceInfValues(m4, 0.5); // Use the value '0.5' to replace 'inf' in m4
    std::cout << "\nArray after replacing 'inf' values = \n" << m4;
    

    std::cout << "\n\n---------- dst = scalar/src2 -------------\n";

    // 3. Handle dividing a scalar value by an image array, 
    //    i.e., dst = scalar / src2. Here we are using the overloaded 
    //    function void cv::divide(double scale, cv::InputArray src2, 
    //    cv::OutputArray dst, int dtype = -1)
    cv::Mat m5;
    cv::divide(2.5,     // Scalar/Constant value
               m2,      // Input array
               m5,      // Output array
               -1);     // Output image data type same as 'src2'

    std::cout << "\n\n2.5 / m2 = \n" << m5;

    // Handle any 'inf' values
    replaceInfValues(m5, 0.5); // Use the value '0.5' to replace 'inf' in m5
    std::cout << "\nArray after replacing 'inf' values = \n" << m5;

    std::cout << '\n';

    return 0;
}


//--------------------- Function Definitions -----------------//

/**
 * @brief Returns the "positive infinity" value for a particular data type
 * 
 * @tparam T Data type whose infinite value we want
 * @return T Infinite value of data type 'T'
 */
template <typename T>
T infiniteValue()
{
    return std::numeric_limits<T>::infinity();
}

/**
 * @brief Replace 'inf` values in an image array with a user chosen value
 * 
 * @tparam T Data type of new value
 * @param img cv::Mat image array
 * @param value Value to replace 'inf' values in 'img'
 */
template <typename T>
void replaceInfValues(cv::Mat& img, T value)
{
    // Get standard 'inf' value for data type 'T'
    auto inf = infiniteValue<T>();

    // Create a mask using pixels in 'img' with the 'inf' value
    cv::Mat inf_mask { img == inf };

    // Use the mask values to identify which pixels have the 'inf' 
    // value in 'img' and replace them with the user chosen 'value'
    img.setTo(value, inf_mask); 
}
```

**Output**

    m1 = 
    [1, 2;
    3, 4]
    m2 = 
    [3, 0;
    3, 1]

    ---------- dst = (src1*scale)/src2 -------------

    m1 / m2 = 
    [0.3333333333333333, inf;
    1, 4]
    Array after replacing 'inf' values = 
    [0.3333333333333333, 0.5;
    1, 4]

    ---------- dst = src1/scalar -------------

    m1 / 2.5 = 
    [0.4, 0.8;
    1.2, 1.6]
    Array after replacing 'inf' values = 
    [0.4, 0.8;
    1.2, 1.6]

    ---------- dst = scalar/src2 -------------


    2.5 / m2 = 
    [0.8333333333333334, inf;
    0.8333333333333334, 2.5]
    Array after replacing 'inf' values = 
    [0.8333333333333334, 0.5;
    0.8333333333333334, 2.5]

## References

1. https://homepages.inf.ed.ac.uk/rbf/HIPR2/arthops.htm
2. https://docs.opencv.org/4.8.0/d2/de8/group__core__array.html
3. https://homepages.inf.ed.ac.uk/rbf/HIPR2/8bitcol.htm
4. https://stackoverflow.com/questions/41759247/filter-opencv-mat-for-nan-values
5. https://forum.opencv.org/t/how-to-remove-inf-values-from-cv-matrix/4898/5

    
