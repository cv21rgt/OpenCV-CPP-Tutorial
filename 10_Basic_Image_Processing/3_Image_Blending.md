# Image Blending

:notebook_with_decorative_cover: We use **image blending** to combine two or more images into a single image. There are various <a href = "http://dev.cs.ovgu.de/tutorials/Grokking-the-GIMP-v1.0/node55.html#:~:text=Multiply%2C%20Divide%2C%20Screen%2C%20and%20Overlay%20are%20all,product%20of%20the%20foreground%20and%20background%20pixels.">blending methods</a>, most of which can be found in photo editing software packages such as GIMP or Photoshop. 

:notebook_with_decorative_cover: In the previous tutorial, we looked at the image arithmetic operators - addition, subtraction, multiplication and division. These operators are considered to be simple blend modes as they also combine two or more images into a single image. This kind of blending involves using mathematical operations to directly manipulate the pixel values of the input images - also known as **Pixel-level blending**. 

:notebook_with_decorative_cover: We should also mention two other common blending methods - **Layer-based blending** and **Gradient blending**. We will not discuss these further as they include image techniques we have not looked at yet - which will only serve to confuse you. 

:notebook_with_decorative_cover: In this tutorial, we will concentrate on a form of Pixel-level blending that gives us more control than simple arithmetic operators. It is a **linear blend operator**, which allows us to use weights to determine the level of influence of each input image in the output image. It is defined by the equation $Q(row, column) = \alpha \times P_1(row, column) + (1 - \alpha) \times P_2(row, column)$, where:

* $Q$ - is the output image
* $P_1$ and $P_2$ - are the two input images. In some applications $P_2$ can also be a constant scalar value, thus allowing a constant offset value to be added to a single image.
* $\alpha$ - weight or level of influence assigned to an image. This is a value between `0` and `1`.

:notebook_with_decorative_cover: OpenCV implements the linear blend operator through the function `void cv::addWeighted(cv::InputArray src1, double alpha, cv::InputArray src2, double beta, double gamma, cv::OutputArray dst, int dtype = -1)`, which you can find in the header `<opencv2/core.hpp>`. The function parameters are defined as follows:

* `src` - first input array
* `alpha` - weight value (between `0` and `1`) of the first array elements
* `src2` - second input array of the same size and channel number as `src1`
* `beta` - weight of second array elements. `beta` should be equal to `1-alpha`.
* `gamma` - scalar added to the output array
* `dst` - output array that has the same size and number of channels as the input arrays
* `dtype` - optional depth of the output array; when both input arrays have the same depth, dtype can be set to -1, which will be equivalent to src1.depth().

:notebook_with_decorative_cover: The function `cv::addWeighted()` calculates the weighted sum of two arrays as $dst = ((src1 * \alpha) + (src2 * \beta)) + gamma$.

**Example 1** You can use the following example code to blend 2 images of the same size and number of channels. You have the option to change the data type of the output image. You can also save the output image to disk if you want.

```c++
// image_blending.cpp 
// Program for blending two images 

#include "opencv2/core.hpp"        // for OpenCV core types e.g. cv::Mat
#include "opencv2/imgcodecs.hpp"   // for cv::imread, cv::imwrite
#include "opencv2/highgui.hpp"     // for displaying images in windows
#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser

#include "UtilityFunctions/utility_functions.h" // functions from our own library

#include <iostream>

int main(int argc, char* argv[])
{

    //---------------- 1. Extract Command Line Arguments -----------------//

    const cv::String keys = 
    "{help h usage ? | | Blend two images of same size and number of channels }"
    "{image1 | <none> | Full path to first image }"
    "{alpha | 1.0 | Weight applied to first image. Value should be in the range 0 to 1 }"
    "{image2 | <none> | Full path to second image }"
    "{gamma | 0.0 | Scalar value added/subtracted to the output array }"
    "{output_datatype | -1 | Data type assigned to output image. " 
    "Use value -1 if output data type is same as that of image1 }"
    "{output_image | | File path to save output image (must include file extension)}";  

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // Display message about application
    parser.about("\nApplication to perform image blending\n");
    parser.printMessage();

    // Extract command line arguments
    cv::String image1Path = parser.get<cv::String>("image1");
    double alpha = parser.get<double>("alpha");
    cv::String image2Path = parser.get<cv::String>("image2");
    double gamma = parser.get<double>("gamma");
    int outputImageDatatype = parser.get<int>("output_datatype");
    cv::String outputImagePath = parser.get<cv::String>("output_image");

    // Check for any errors during command line extraction
    if (!parser.check())
    {
        parser.printErrors(); // Print a list of any errors encountered

        return -1; // Early program exit
    }

    //--------------------- 2. Read image data -------------------------//

    cv::Mat first_input_image = cv::imread(image1Path, cv::IMREAD_ANYCOLOR);
    if (first_input_image.empty())
    {
        CV_Error_(cv::Error::StsBadArg, 
                      ("Could not read image data from (%s)", 
                        image1Path.c_str())); 
    }
    else 
    {
        // Provide image sizes, no. of channels and data types of image
        std::cout << "\nSize of first input image = " << first_input_image.size()
                  << "\nData type of first input image = " 
                  << CPP_CV::General::openCVDescriptiveDataType(first_input_image.type())
                  << '\n';
    }

    cv::Mat second_input_image = cv::imread(image2Path, cv::IMREAD_ANYCOLOR);
    if (second_input_image.empty())
    {
        CV_Error_(cv::Error::StsBadArg, 
                    ("Could not read image data from (%s)", 
                        image2Path.c_str())); 
    }
    else 
    {
        // Provide image sizes, no. of channels and data types of image
        std::cout << "\nSize of second input image = " << second_input_image.size()
                  << "\nData type of second input image = " 
                  << CPP_CV::General::openCVDescriptiveDataType(second_input_image.type())
                  << '\n';
    }

    // Check if input images have the same sizes and channels
    if (first_input_image.size() != second_input_image.size())
    {
        std::cout << "\nERROR: Input images do not have same size!\n";

        return -1; 
    }

    if (first_input_image.channels() != second_input_image.channels())
    {
        std::cout << "\nERROR: Input images do not have same number of channels!\n";

        return -1; 
    }

    //--------------------- 3. Image Blending ---------------------------//

    cv::Mat outputImage;

    cv::addWeighted(first_input_image,    // First input image array
                    alpha,                // Weight given to first image
                    second_input_image,   // Second input image array
                    1 - alpha,            // Weight given to second image
                    gamma,                // Scalar value added to output image
                    outputImage,          // Output image array
                    outputImageDatatype   // Data type of output image
                );
    
    std::cout << "\nSize of output image = " << outputImage.size()
                  << "\nData type of output image  = " 
                  << CPP_CV::General::openCVDescriptiveDataType(outputImage.type())
                  << '\n';

    //----------------- 4. Save output image to file ---------------//

    if (!outputImagePath.empty())
    {
        bool success = cv::imwrite(outputImagePath, outputImage);
        if (success)
        {
            std::cout << "\nSuccessfully saved output image to: " 
                      << outputImagePath << '\n';
        } 
        else 
        {
            std::cout << "\nERROR: Could not save output image!\n";
        }
    }

    //------------------ 5. Display images in windows ---------------------//

    cv::namedWindow("First input image", cv::WINDOW_NORMAL);
    cv::imshow("First input image", first_input_image);

    cv::namedWindow("Second input image", cv::WINDOW_NORMAL);
    cv::imshow("Second input image", second_input_image);
    

    // In order to display the computed output image sometimes you 
    // need to scale its values especially for types other than 8-bit unsigned 
    auto [minVal, maxVal] = CPP_CV::General::dataTypeRange<double>(outputImage.type());
    double scale = maxVal / 255;
    outputImage = outputImage * scale;    

    cv::namedWindow("Output image", cv::WINDOW_NORMAL);
    cv::imshow("Output image", outputImage);

    cv::waitKey(0);

    cv::destroyAllWindows(); 

    std::cout << '\n';

    return 0;
}
```

## Applications of image blending

* **Panoramas**: Stitching together multiple images to create a wide-angle view. 

* **Special effects**: Creating composite images, like adding a person to a different background or creating surreal imagery. This is used in movies. People also often use this in software packages such as Photoshop.

* **Exposure blending**: Combining images with different exposures to capture a wider dynamic range of light and detail. 

* **Image enhancement**: Improving image quality by blending details from multiple images or by using techniques like sharpening or noise reduction

## References

1. https://en.wikipedia.org/wiki/Blend_modes#:~:text=Blend%20modes%20alternatively%20blending%20modes%20or%20mixing,many%20other%20ways%20to%20blend%20two%20layers.
2. http://dev.cs.ovgu.de/tutorials/Grokking-the-GIMP-v1.0/node55.html#:~:text=Multiply%2C%20Divide%2C%20Screen%2C%20and%20Overlay%20are%20all,product%20of%20the%20foreground%20and%20background%20pixels.
3. https://homepages.inf.ed.ac.uk/rbf/HIPR2/blend.htm