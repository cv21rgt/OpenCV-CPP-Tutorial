# Saving image files

:notebook_with_decorative_cover: For saving image files on your system, OpenCV provides the function `cv::imwrite()`. You can use this function to either save a single or multi-page image to a file. It has the following syntax: `bool cv::imwrite(const cv::String& filename, cv::InputArray img, const std::vector<int>& params = std::vector<int>())`

1. `filename` - Name you want to save your image as. The name must include an appropriate image file extension (see first section on image file formats currently supported by OpenCV in **Read_Image_Files.md** tutorial). Its best to provide `filename` as part of the full directory path e.g. `/home/Documents/Images/test.jpeg`, will save an image as a `jpeg` file called `test.jpeg` in `Images` folder. 

2. `img` - Image to be saved. Because it is of the class `cv::InputArray`, your image can be a `cv::Mat`, `cv::SparseMat` or any of the relevant OpenCV data types. For multiple images, place them into a `std::vector` first.

3. `params` - Format-specific parameters encoded as pairs `(paramId_1, paramValue_1, paramId_2, paramValue_2, ... .)`. These are provided as a `std::vector` of integers, with those integers being a sequence of parameter IDs followed by the value to be assigned to that parameter (i.e., alternating between parameter ID and the parameter value). For the parameter IDs and possible values, there are aliases provided by OpenCV as <a href = "https://docs.opencv.org/4.8.0/d8/d6a/group__imgcodecs__flags.html#ga292d81be8d76901bff7988d18d2b42ac">cv::ImwriteFlags</a>. `params` will determine the quality of your saved image. 

:notebook_with_decorative_cover: `cv::imwrite()` returns `true` if it has successfully saved your image.

:notebook_with_decorative_cover: The image format used by `cv::imwrite()` to save your image is chosen based on the supported filename extension (e.g., `jpeg`, `png`, `tiff` etc). However, in general only 8-bit unsigned (`CV_8U`) single-channel or 3-channel (with 'BGR' channel order) images can be saved using this function, with the following exceptions:

* With OpenEXR encoder, only 32-bit float (`CV_32F`) images can be saved.

    * 8-bit unsigned (`CV_8U`) images are not supported.

* With Radiance HDR encoder, non 64-bit float (`CV_64F`) images can be saved.

    * All images will be converted to 32-bit float (`CV_32F`).

* With JPEG 2000 encoder, 8-bit unsigned (`CV_8U`) and 16-bit unsigned (`CV_16U`) images can be saved.

* With PAM encoder, 8-bit unsigned (`CV_8U`) and 16-bit unsigned (`CV_16U`) images can be saved.

* With PNG encoder, 8-bit unsigned (`CV_8U`) and 16-bit unsigned (`CV_16U`) images can be saved.

    * PNG images with an alpha channel can be saved using this function. To do this, create 8-bit (or 16-bit) 4-channel image BGRA, where the alpha channel goes last. Fully transparent pixels should have alpha set to 0, fully opaque pixels should have alpha set to 255 (8-bit) or 65535 (16-bit).

* With PGM/PPM encoder, 8-bit unsigned (`CV_8U`) and 16-bit unsigned (`CV_16U`) images can be saved.

* With TIFF encoder, 8-bit unsigned (`CV_8U`), 16-bit unsigned (`CV_16U`), 32-bit float (`CV_32F`) and 64-bit float (`CV_64F`) images can be saved.

    * Multi-page images can be saved in TIFF format 

    * 32-bit float 3-channel (`CV_32FC3`) TIFF images will be saved using the LogLuv high dynamic range encoding (4 bytes per pixel)

:notebook_with_decorative_cover: If the image format is not supported, the image will be converted to 8-bit unsigned (`CV_8U`) and saved that way.

:notebook_with_decorative_cover: The above information is a lot to take in all at once, but here is what you need to know in summary about the `cv::imwrite()` function:

*It will save 8-bit single or three-channel images for most file formats, which is fine for most developers. However, there are backends (libraries) for flexible image formats like png, tiff or jpeg 2000, that will allow you to save 16-bit or even float formats (32-bit and 64-bit). Some backends (e.g. PNG Encoder) even allow you to save four channel images e.g. BGR plus alpha*

**Example 1:** Save an original image as a `jpeg`, `jpg`, `png` or `webp` image file format. You can always expand the program by including more options for the user. If using Cmake remember to make the necessary changes in your `CMakeLists` file like examples in the previous tutorial.

```c++
// Program: Save_Image_As.cpp

/* 
 * Program saves an image as a JPEG, JPG, WEBP, or PNG file
 * Program inputs are provided through the command line
*/

#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser
#include "opencv2/highgui.hpp"         // for functions related to displaying images e.g. cv::imshow()
#include "opencv2/imgcodecs.hpp"       // for cv::imread() and cv::imwrite()

#include <UtilityFunctions/utility_functions.h> // for getFileExtension() from our own library

#include <iostream>
#include <vector> // for std::vector
#include <filesystem> // for files
#include <string_view> // for const string's


///////////////////////////// Function Declarations //////////////////////////////

/**
 * @brief Check if file extension of image file supplied by user is valid
 * 
 * @param fileExtension image file extension 
 * @return true 
 * @return false 
 */
bool isValidFileExtension(std::string_view fileExtension);


/**
 * @brief Return the cv::ImwriteFlag for an appropriate image file extension
 * 
 * @param fileExtension image file extension
 * @return int 
 */
cv::ImwriteFlags imageWriteFlag(std::string_view fileExtension);

////////////////////////// End of Function Declarations //////////////////////////


int main(int argc, char* argv[])
{
    /*
     * Define the command line arguments 
     * We need 3 arguments:
     *      1. image to read/open 
     *      2. path to save image
     *      3. quality of compression 
    */
    const cv::String keys = 
        "{help h usage ? | | Save an image file }"
        "{@image | <none> | Full path to image file }"
        "{@path | <none> | Full path to save image to. Should include file name and extension.  }"
        "{@quality | 1 | quality of compression }";

    // define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nSave image as jpeg, jpg, png, or webp file." 
        "\n\tjpeg has compression quality values 0 to 100 (the higher the better)." 
        "\n\tpng has compression quality values 0 to 9." 
        "\n\twebp has compression quality values 1 to 1000.\n");
    parser.printMessage();

    // Now lets extract our command line arguments
    cv::String imagePath = parser.get<cv::String>("@image"); 
    cv::String savePath = parser.get<cv::String>("@path"); 
    int qualityOfCompression = parser.get<int>("@quality"); 

    // Check for any errors encountered 
    if(!parser.check())
    {
        parser.printErrors(); // Print errors

        return -1; // Early program exit
    }

    // Before attempting to read the image, check if we have an 
    // image reader for that particular image file first
    if(!cv::haveImageReader(imagePath))
    {
        std::cerr << "\nYour system does not have a suitable image reader for the file: " 
                  << imagePath << '\n';

        return -1;
    }

    // Use cv::imread() to read an image file as is 
    // and save the image as a cv::Mat array   
    cv::Mat image { cv::imread(imagePath, cv::IMREAD_UNCHANGED) };    

    // check if we have successfully opened the image
    if (image.empty())
    {
        std::cerr << "\nCould not read data from image file: " << imagePath << '\n';
        
        return -1;
    }

    // Check if the user has supplied a valid image file extension to save as
    // We are only saving to PNG, JPEG, JPG or WEBP image files
    // If not, raise an exception
    //std::cout << "isValidFileExtension = " << isValidFileExtension(fileExtension) << '\n';
    if(!isValidFileExtension(CPP_CV::ReadWriteFiles::getFileExtension(savePath)))
    {
        std::cerr << "Cannot save image to file with extension: " 
                  << CPP_CV::ReadWriteFiles::getFileExtension(savePath) << '\n';

        return -1;
    }

    // Check if we have a suitable image writer on our system.
    if(!cv::haveImageWriter(savePath))
    {
        std::cerr << "\nYour system does not have a suitable image writer for the file: " 
                  << savePath << '\n';

        return -1;
    }

    // Let's set up our compression parameters
    // These will be saved in std::vector as alternating values (parameterID, parameter value)
    std::vector<int> compression_params;
    compression_params.push_back(imageWriteFlag(CPP_CV::ReadWriteFiles::getFileExtension(savePath))); // add parameterID
    compression_params.push_back(qualityOfCompression); // add parameter value

      
    // Since we now have everything we need we can now save our image
    // We will do it in a try...catch block as it might fail
    
    bool result = false;

    try {
        result = cv::imwrite(savePath, image, compression_params);
    } 
    catch (const cv::Exception& ex)
    {
        std::cerr << "\nError converting image to " 
                  << CPP_CV::ReadWriteFiles::getFileExtension(imagePath) 
                  << " format: " << ex.what();
    }

    // If we have successfully saved our image we can display a message for the user
    if(result)
    {
        std::cout << "\nSuccessfully saved image file to " << savePath << '\n'; 
    }
    else 
    {
        std::cerr << "\nError: Could not save image file to " << savePath << '\n';
    }

    std::cout << '\n';

    return 0;
}

//////////////////// Function Definitions ///////////////////////////////////////

/**
 * @brief Check if file extension supplied by user is valid
 * 
 * @param fileExtension image file extension 
 * @return true 
 * @return false 
 */
bool isValidFileExtension(std::string_view fileExtension)
{

    // Make sure the user has supplied a valid file extension we can support
    if((fileExtension == "jpeg") || (fileExtension == "jpg") || 
      (fileExtension == "png") || (fileExtension == "webp"))
    {
        return true; 
    }
    else 
    {
        return false;
    }

}

/**
 * @brief Return the cv::ImwriteFlag for an appropriate image file extension
 * 
 * @param fileExtension image file extension
 * @return int 
 */
cv::ImwriteFlags imageWriteFlag(std::string_view fileExtension)
{
    if(fileExtension == "jpeg")
    {

        return cv::IMWRITE_JPEG_QUALITY;

    } 

    else if(fileExtension == "jpg")
    {

        return cv::IMWRITE_JPEG_QUALITY;

    }

    else if(fileExtension == "png")
    {

        return cv::IMWRITE_PNG_COMPRESSION;

    } 
    
    else if(fileExtension == "webp")
    {

        return cv::IMWRITE_WEBP_QUALITY;

    }
}

//////////////////// End of Function Definitions //////////////////////////////////
```