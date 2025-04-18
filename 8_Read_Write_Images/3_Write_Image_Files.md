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

## Save multiple images to a single multi-page file

:notebook_with_decorative_cover: OpenCv allows you to take multiple images and save them as a single file. Currently, you can only save the single file in <a href = "http://www.libtiff.org/">TIFF</a> format. In this case, TIFF acts as an image container that supports other image file formats. If you are curious about the integer constants corresponding to TIFF compression quality formats see <a href = "http://www.libtiff.org/functions/libtiff.html">libtiff</a>.

:notebook_with_decorative_cover: If we look closely at this function signature `bool cv::imwrite(const cv::String& filename, cv::InputArray img, const std::vector<int>& params = std::vector<int>())` - the parameter `img` is of the type `cv::InputArray`, meaning we can provide all kinds of data types including a single `cv::Mat` image or a container that can hold multiple images e.g.`std::vector<cv::Mat>`. By taking advantage of this parameter we can save multiple images as a single TIFF image file. The parameter `filename` is the TIFF file we are saving our multiple images to hence should have the `.tiff` file extension.

:notebook_with_decorative_cover: You can also use the function `static bool cv::imwritemulti(const cv::String& filename, cv::InputArrayOfArrays img, const std::vector<int>& params = std::vector<int>())`. The parameter `img` has to be an array containing other arrays e.g `std::vector<cv::Mat>`.

**Example 2:**  Saving multiple images as a single TIFF image file. Just like in previous examples don't forget to make the necessary changes pertaining to the name of your source code and build files in your CMakeLists file.

```c++
// Program: Save_To_Multipage_File.cpp

/* 
 * Program saves multiple images into a single TIFF multi-page image file
 * Program inputs are provided through the command line 
*/

#include "opencv2/core.hpp"            // for core data types
#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser
#include "opencv2/imgcodecs.hpp"       // for cv::imread() and cv::imwrite()

#include <UtilityFunctions/utility_functions.h> // for user-defined functions

#include <iostream>
#include <vector>
#include <filesystem>  // handles files

int main(int argc, char* argv[])
{

    ////////////////////////////// 1. Extract Command Line Arguments /////////////////////

    /*
     * Define the command line arguments 
     * We need 3 arguments:
     *      1. path to directory with multiple image files 
     *      2. path to directory to save image
     *      3. name of file to save image 
     * 
    */
    const cv::String keys = 
        "{help h usage ? | | Save multiple images as a TIFF multi-page file }"
        "{@path1 | <none> | full path to directory with multiple images }"
        "{@path2 | <none> | full path to directory to save multi-page image file }"
        "{@fileName| <none> | name of multi-page image file with extension .tiff }";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nSave multiple images as a Tag Image File Format (TIFF) multi-page single file.\n");
    parser.printMessage();

    // Now lets extract our command line arguments
    cv::String multipleImagesDirectoryPath = parser.get<cv::String>("@path1"); // full path to directory with multiple images
    cv::String saveDirectoryPath = parser.get<cv::String>("@path2"); // full path to directory to save image
    cv::String fileName = parser.get<cv::String>("@fileName"); // name of multi-page image file

    // Check for any errors encountered 
    if(!parser.check())
    {
        parser.printErrors(); // Print any errors

        return -1;
    }

    // Check if user has provided a suitable file name with the extension '.tiff'
    using namespace std::string_literals; // converts 'tiff' from 'const char' to 'std::string' by simply adding an 's'
    if(CPP_CV::ReadWriteFiles::getFileExtension(fileName) != "tiff"s)
    {
        std::cout << "\nERROR: Your filename should have '.tiff' extension.\n";

        return -1;
    }

    //------------------------- End of Extracting Command Line Arguments ---------------------//

    ///////////////////////// 2. Read Image Files from Directory //////////////////////////////////

    // We will go through a directory/folder and save all images that 
    // we can read with OpenCV into a std::vector
    std::vector<cv::Mat> multipleImages; // container for multiple images

    /* 
     * We will use an iterator 'directory_iterator' from std::filesystem to 
     * go through the directory contents. First, you need to create a 'std::filesystem::path'
     * object using the directory full path.
     *  
     * However, this iterator will not go through any sub-directories
    */
    const std::filesystem::path multipleImagesDir {multipleImagesDirectoryPath}; 

    for (auto const& dir_entry :std::filesystem::directory_iterator{multipleImagesDir})
    {
        /* 
         * Before attempting to read the file, check if it is an image file by 
         * using cv::haveImageReader(). Even if it is an image file, here we can 
         * also check if we have an image reader for that image file
        */
        if(!cv::haveImageReader(dir_entry.path().string()))
        {
            std::cerr << "\nCannot read the file: " << dir_entry.path() 
                      << " as an image file." << '\n';           
        }
        else 
        {
            // Use cv::imread() to read an image file as is 
            // and save the image as a cv::Mat array
            cv::Mat image { cv::imread(dir_entry.path().string(), cv::IMREAD_UNCHANGED) };    

            // check if we have successfully opened the image
            if (image.empty())
            {
                std::cerr << "Could not read data from image file: " 
                        << dir_entry.path().string() << '\n';
                
            }
            else // if we can read image data
            {
                // Place image file into std::vector
                multipleImages.push_back(image);
            }

        }

    }  

    std::cout << "\nFound " << multipleImages.size() << " images.\n";

    //----------------------- End of Read Image Files from Directory --------------------------//


    //////////////////////// 3. Save To Multi-page TIFF Image File ////////////////////////////////
    
    /* 
     * Join directory and file name to establish full path to save image to.
     *
     * std::filesystems has the operator '/=', which allows you to create paths 
     * to sub-directories or files. This is done by automatically appending seperators
     * that are appropriate to the underlying operating system
    */
    std::filesystem::path savePath {saveDirectoryPath}; // Directory to save image to
    savePath /= fileName; // Directory + file name == Full file path
     
    // Since we now have everything we need we can now save our multiple images
    // We will do it in a try...catch block as it might fail
    
    bool result = false;

    try {
        result = cv::imwrite(savePath.string(), multipleImages);
    } 
    catch (const cv::Exception& ex)
    {
        std::cerr << "\nERROR: " << ex.what();
    }

    // If we have successfully saved our image we can display a message for the user
    if(result)
    {
        std::cout << "\nSaved multiple images to single file: " 
                  << savePath << '\n'; 
    }
    else 
    {
        std::cerr << "\nERROR: Could not multiple images to fingle file: " 
                  << savePath << '\n';
    }
    
    //----------------------- End of Save To Multi-page TIFF Image File -------------------//

    
    std::cout << '\n';

    return 0;
}
```

**Example 3:** Now that we know how to save multiple images into a single file, we can now provide an example on how to read such image files using `cv::imreadmulti()` - which we discussed in the tutorial `Read_Image_Files.md`. Just like in previous examples don't forget to make the necessary changes pertaining to the name of your source code and build files in your CMakeLists file. Also note that in this example our command line arguments are non-positional.

```c++
// Program: read_multi-page_image.cpp

/* This program reads a multiple images saved as a single file
 * Most multiple images are saved as TIFF image file format
*/

#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser
#include "opencv2/highgui.hpp"         // for functions related to displaying images e.g. cv::imshow() and cv::waitKey()
#include "opencv2/imgcodecs.hpp"       // for cv::imreadmulti() for reading multiple images from a single file

#include <iostream>
#include <vector>
#include <string>

int main(int argc, char* argv[])
{
    ////////////////////////////// 1. Extract Command Line Arguments /////////////////////

    /*
     * Define the command line arguments 
     *  1. Path to multi-page image file
     *     We will enforce that this argument must not be empty 
     *     using the <none> value.
     *  2. Since we have multiple images, we can choose which image to 
     *     read first by providing an index value. Default value is '0'.
     *  3. Number of images to read from the given index above. 
     *     Default value is '0' - meaning read all images.
    */
    const cv::String keys = 
        "{help h usage ? | | Read multiple images from a multi-page file and display in different windows }"
        "{path | <none> | Full path to multi-page image file }"
        "{start | 0 | Start index of image to read. First image has index '0'.}"
        "{count | 0 | Number of images to read from the start index. To read all images set value to '0' }";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nThis program reads multiple images from a single multi-page file and display images."
                 "\nYou can choose which image to read first by providing a start index value."
                 "\nMost multi-page image files are of type TIFF."
                 "\nPress any key to view the next image.\n");
    parser.printMessage();

    // Now lets extract command line arguments
    cv::String imagePath = parser.get<cv::String>("path");
    int startIndex = parser.get<int>("start");
    int numberOfImages = parser.get<int>("count");

    // check for any errors encountered 
    if(!parser.check())
    {
        parser.printErrors();
        return -1;
    }

    //------------------------- End of Extracting Command Line Arguments ---------------------//

    ///////////////////////// 2. Read Images from Multi-page File ///////////////////////////////

    /*
     * We will place code for using 'cv::imreadmulti()' in a try...catch block since 
     * it may fail for a number of reasons: 
     *      1. 'start' index may be out of range
     *      2. 'count' value may also exceed number of multiple images in multi-page file
     *      3. OpenCV may fail to open the image data
     *      4. Image file may not be a multi-page file
     * 
    */     

    std::vector<cv::Mat> multipleImages; // Vector to store the read images

    bool result {false};

    try {

        if ((startIndex == 0) && (numberOfImages == 0))
        {
            // Read all images
            result = cv::imreadmulti(imagePath, multipleImages, cv::IMREAD_UNCHANGED);
        }
        else 
        {
            // Read some of the images
            result = cv::imreadmulti(imagePath, multipleImages, startIndex, numberOfImages, cv::IMREAD_UNCHANGED);
        }        
    }
    catch (const cv::Exception& ex)
    {
        std::cerr << "\nERROR: " << ex.what();
    }

    // check if we have successfully read all the images
    if (result == false)
    {
        std::cerr << "Could not successfully read multiple images from: " 
                  << imagePath << '\n';
        return -1;
    }

    std::cout << "\nSuccessfully read " << std::size(multipleImages) << " images\n";

    //------------------------- End of Read Images from Multi-page File ---------------------//

    /////////////////////////// 3. Display Images ////////////////////////////////////

    // Loop through images in std::vector then display them
    int count {startIndex};
    for (const auto& img : multipleImages)
    {
        cv::imshow(std::string("Image at index ") + std::to_string(count),img);
        cv::waitKey(0);
        ++count;
    }
    
    //------------------------- End of Display Images ---------------------//

    std::cout << '\n';

    return 0;
}
```