# Introduction

:notebook_with_decorative_cover: Up to this point of our tutorials we have not been required to deal with image processing techniques that require the use of a source image pixel neighbours to compute a value in the destination image. The question would be what do we do when we encounter a pixel that does not have enough neighbours for us to compute a new value from. Such pixels are found at the image borders.

:notebook_with_decorative_cover: OpenCV handles such a problem by creating what are known as **virtual pixels** outside of the image at the borders. This is also known as **padding out** an image. This process always results in a somewhat larger image than the original. The process of creating these artificial pixels in also known as **extrapolation**. Extrapolation takes advantage of existing pixels to artificially create other pixels that fall outside the image boundary. 

:notebook_with_decorative_cover: This tutorial is going to set you up so that you go into future topics (e.g. Filtering, Geometrical Transformation, Thresholding, etc.) knowing how pixels are handled at image borders by various image processing techniques.


**Border Extrapolation**

:notebook_with_decorative_cover: In most cases OpenCV functions will create these virtual pixels for you, all you have to do is supply a **flag** specifying how you want the pixels to be created. These flags can be found under the enumerator <a href = "https://docs.opencv.org/4.8.0/d2/de8/group__core__array.html#ga209f2f4869e304c82d07739337eae7c5">cv::BorderTypes</a>. 

:notebook_with_decorative_cover: The following table gives a brief description of the border types you can create. We have also provided images to show how the virtual pixels at the borders are created. We also show examples of how an image would look if you applied the various borders. The following image was used as the original:

**Figure 1** Input image for creating various border types

![Source image for making borders](./images/source_img_make_borders.jpeg)

**Table 1** How OpenCV exprapolates pixels when creating image borders. Images in the table use a border size of 20 pixels on all sides.

| Border type | Effect | Pixels | Image example|
| ----------- | ------ | ------ | ----- |
| cv::BORDER_CONSTANT | Extend pixels by using a supplied (constant) value | ![cv::BORDER_CONSTANT](./images/border_constant.png)|Constant value = 25 ![cv::BORDER_CONSTANT with value 25](./images/constant_border_v25.png)Constant value = 200 ![cv::BORDER_CONSTANT with value 200](./images/constant_border_v200.png) |
| cv::BORDER_REPLICATE | Extend pixels by copying edge pixel | ![cv::BORDER_REPLICATE](./images/border_replicate.png) | ![cv::BORDER_REPLICATE](./images/replicate_border.png) |
| cv::BORDER_REFLECT | Extend pixels by mirror reflection | ![cv::BORDER_REFLECT](./images/border_reflect.png) | ![cv::BORDER_REFLECT](./images/reflect_border.png) |
| cv::BORDER_WRAP | Extend pixels by replicating from opposite side | ![cv::BORDER_WRAP](./images/border_wrap.png) | ![cv::BORDER_WRAP](./images/wrapped_border.png) |
| cv::BORDER_REFLECT_101 | Extend pixels by reflection, edge pixel is not "doubled" | ![cv::BORDER_REFLECT_101](./images/border_reflect_101.png) | ![cv::BORDER_REFLECT_101](./images/reflect_border_101.png) |
| cv:: BORDER_REFLECT101 | Same as cv::BORDER_REFLECT_101 | | |
| cv:: BORDER_DEFAULT | Same as cv::BORDER_REFLECT_101 | | |
| cv::BORDER_ISOLATED | Do not look outside of image or region of interest | We will discuss this type on its own later | |

## How to create borders around an image

:notebook_with_decorative_cover: As mentioned previously, OpenCV functions that require an argument on how to handle border pixels will do all the work for you behind the scenes. However, if you want to see how the borders look like you can create them yourself using the function `void cv::copyMakeBorder(InputArray src, OutputArray dst, int top, int bottom, int left, int right, int borderType, const cv::Scalar& value = cv::Scalar())`. This function allows you to form a border around an image. The function copies the source image into the middle of the destination image. The areas to the left, to the right, above and below the copied source image will be filled with extrapolated pixels. Lets have a detailed look at the parameters: 

* `src` - Source image.
* `dst` - Destination image of the same type as `src` and the size $cv::Size(src.cols+left+right, src.rows+top+bottom)$.
* `top` - the number of rows of pixelsto be added at the top of `src` image.
* `bottom` - the number of rows of pixels to be added at the bottom of `src` image.
* `left` - the number of columns of pixels to be added at the left side of `src` image.
* `right` - the number of columns of pixels to be added at the right side of `src` image.
* `borderType` - Border type. See <a href = "https://docs.opencv.org/4.8.0/d2/de8/group__core__array.html#ga209f2f4869e304c82d07739337eae7c5">**cv::BorderTypes**</a> for details. Also see **Table 1** above.
* `value` - Border value if `borderType=cv::BORDER_CONSTANT`. This is provided as a `cv::Scalar` value e.g. `cv::Scalar(value)` for a 1-channel image and `cv::Scalar(value, value, value)` for a 3-channel image.

**Example 1** The following code helps you create a border (of the same size) around an image. For better visualization, use a large border size e.g. 50.

```c++
#include <opencv2/core.hpp>     // for OpenCV core types and cv::copyMakeBorder()
#include <opencv2/highgui.hpp>  // for displaying images in a window
#include <opencv2/core/utility.hpp> // for command line or terminal inputs

#include "UtilityFunctions/utility_functions.h" // functions from our own library

#include <iostream>
#include <string_view>

/**
 * @brief Returns a string describing how an image border type is created
 * 
 * @param borderType Border type as an integer value. See enum cv::BorderTypes
 * @return std::string_view 
 */
std::string_view imageBorderDescription(int borderType);

int main(int argc, char* argv[])
{
    //---------------- 1. Extract Command Line Arguments -----------------//

    const cv::String keys = 
        "{help h usage ? | | Create a border around an image }"
        "{image | <none> | Full path to source image }"
        "{sizeOfBorder | 1 | Size of border as no. of pixel rows/columns }"
        "{typeOfBorder | 4 | Integer value representing border type. Options are: "
        "Constant (0), Replicate (1), Reflect (2), Wrap (3), Reflect_101 (4), Isolated (16)}"
        "{constantValue | -1 | Pixel value used in the case you pick typeOfBorder as 'Constant'}";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nProgram for creating a border around an image.\n");
    parser.printMessage();

    //----------------------------- Extract command line arguments into program

    cv::String imagePath = parser.get<cv::String>("image");
    int borderSize = parser.get<int>("sizeOfBorder");
    int typeOfBorder = parser.get<int>("typeOfBorder");
    double constantValue = parser.get<double>("constantValue");

    // Check for any errors encountered during arguments extraction
    if (!parser.check())
    {
        parser.printErrors();
        return -1; // early exit from function
    }

    //--------------------- 2. Read image data -------------------------//

    cv::Mat inputImage = cv::imread(imagePath, cv::IMREAD_ANYCOLOR);
    if (inputImage.empty())
    {
        CV_Error_(cv::Error::StsBadArg, 
                      ("Could not read image data from (%s)", 
                        imagePath.c_str())); 
    }
    else 
    {
        // Print image sizes, no. of channels and data types of image
        std::cout << "\nSize of input image = " << inputImage.size()
                  << "\nData type of input image = " 
                  << CPP_CV::General::openCVDescriptiveDataType(inputImage.type())
                  << '\n';
    }

    // Display original source image
    cv::imshow("Input image in BGR format", inputImage);

    // ------------------------ Create border around image ---------------- //

    cv::Mat dst;

    // If using a constant value for the border convert to cv::Scalar
    cv::Scalar constantBorderValue {constantValue, constantValue, constantValue};

    cv::copyMakeBorder(inputImage,        // Input image
                    dst,                  // Output image with border added to it
                    borderSize,           // No. of border pixel rows at top of image
                    borderSize,           // No. of border pixel rows at bottom of image
                    borderSize,           // No. of border pixel columns on left side of image
                    borderSize,           // No. of border pixel columns on right side of image
                    typeOfBorder,         // Type of border
                    constantBorderValue   // Constant value if typeOfBorder == cv::BORDER_CONSTANT     
    );

    // Print image sizes, no. of channels and data types of output image
    std::cout << "\nSize of image with border = " << dst.size()
            << "\nData type of image with border = " 
            << CPP_CV::General::openCVDescriptiveDataType(dst.type())
            << '\n';

    // Display output image with border       
    auto borderDescription = std::string(imageBorderDescription(typeOfBorder));
    cv::imshow(borderDescription, dst);
    cv::waitKey(0);

    cv::destroyAllWindows();

    std::cout << '\n';

    return 0;
}


/**
 * @brief Returns a string describing how an image border type is created
 * 
 * @param borderType Border type as an integer value. See enum cv::BorderTypes
 * @return std::string_view A description on how image border type is created
 */
std::string_view imageBorderDescription(int borderType)
{
    switch (borderType)
    {
        case cv::BORDER_CONSTANT:
            return "Border with a constant pixel value";
        case cv::BORDER_REPLICATE:
            return "Border with replicated pixels";
        case cv::BORDER_REFLECT:
            return "Border with mirror reflected pixel values";
        case cv::BORDER_WRAP:
            return "Border with wraped pixel values";
        case cv::BORDER_REFLECT_101:
            return "Border with reflected pixel values (edge pixels not used)";
        case cv::BORDER_ISOLATED:
            return "Border created without using any pixels outside input image or ROI";
        default:
            return "Invalid border type";
    }
}
```
