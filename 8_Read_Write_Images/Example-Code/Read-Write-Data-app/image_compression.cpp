// Program: image_compression.cpp

/*
 * Program compresses an image into a std::vector character buffer, which has a smaller size than the 
 * original image file. We then save the buffer to a file for future use
 * 
 * Inputs are provided through the command line
 * 
*/

#include "opencv2/core.hpp"            // for OpenCV core data types
#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser
#include "opencv2/imgcodecs.hpp"       // for cv::imread() and cv::imencode()

#include "UtilityFunctions/utility_functions.h"

#include <iostream>
#include <vector>
#include <algorithm> // for std::find, std::copy
#include <string>
#include <tuple>
#include <fstream>   // for std::ofstream
#include <iterator>  // std::ostream_iterator
#include <filesystem>

//////////////////////////// Function Declarations ////////////////////////////

using namespace std::string_literals; // allows easy access to the std::string suffix 's'
                                      // This allows us to easily convert string literals to std::string

// Image file formats we can handle
const std::string commonOpenCVImageFileFormats[] { "jpeg"s, "jpg"s, "jp2"s, "png"s, "webp"s, "tiff"s };

/**
 * @brief Write the contents of a std::vector<unsigned char> image buffer to file
 * 
 * @param filePath full path to save data to including image file extension
 * @param buffer std::vector<unsigned char>
 */
void writeVectorBufferToFile(const std::string& filePath, std::vector<uchar>& buffer);


/**
 * @brief Return the cv::ImwriteFlag and best quality compression value for an appropriate image file extension
 * 
 * @param fileExtension image file extension
 * @return std::tuple [cv::ImwriteFlag, int] - the compression flag and best quality compression value
 */
std::tuple<cv::ImwriteFlags, int> imageWriteFlag(const cv::String& fileExtension);

//-------------------------- End of Function Declarations ---------------------//


int main(int argc, char* argv[])
{
    ////////////////////////// 1. Extract CommandLine Arguments /////////////////////
    
    /*
     * Define the command line arguments 
     * We need 3 arguments:
     *      1. Full path to image to be compressed 
     *      2. Full path to directory to save compressed file
     *      3. Name of compressed file without a file extension
     * 
    */
    const cv::String keys = 
        "{help h usage ? | | Compress an image into a character buffer }"
        "{image | <none> | full path to image to be compressed }"
        "{dirPath | <none> | full path to directory to save compressed file }"
        "{fileName| <none> | name of compressed file (including file extension) }";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nCompress an image"
                 "\nCodec used during compression depends on the file extension provided by the user."
                 "\nAcceptable file extensions are png, jpeg, jpg, jp2, webp or tiff.\n");
    parser.printMessage();

    // Now lets extract our command line arguments
    cv::String imagePath = parser.get<cv::String>("image");
    cv::String saveDirectoryPath = parser.get<cv::String>("dirPath");
    cv::String fileName = parser.get<cv::String>("fileName"); 

    // check for any errors encountered 
    if(!parser.check())
    {
        parser.printErrors();

        return -1;
    }

    /////////////////////////// 2. Check Validity of File Extension //////////////////////////

    // Since our application is only handling a few file extensions, we just need to make sure
    // the user has provided an extension we can handle.

    // a. Extract file extension without the leading dot
    std::string ext { CPP_CV::ReadWriteFiles::getFileExtension(fileName)};

    // b. Find the file extension from array with image file formats we can handle
    auto found { std::find(std::begin(commonOpenCVImageFileFormats), 
                           std::end(commonOpenCVImageFileFormats), 
                           ext
                          ) 
               };

    // c. If the extension is not valid we provide an error message and exit program
    if (found == std::end(commonOpenCVImageFileFormats))
    {
        std::cout << "\nThis application cannot handle such an image file format." 
                  << "Acceptable file extensions are png, jpeg, jpg, jp2, webp or tiff.\n";

        return -1;
    } 
    
    /////////////////////////// 3. Read Image and Encode /////////////////////////////

    // a. Check if we have an image reader/codec before attempting to read the file
    if (!cv::haveImageReader(imagePath))
    {
        std::cout << "\nCannot read input image file: " << imagePath << '\n';

        return -1;
    }

    // b. Use cv::imread() to read an image file as is and save the image as a cv::Mat array
    cv::Mat image { cv::imread(imagePath, cv::IMREAD_UNCHANGED) };    

    // check if image is empty
    if (image.empty())
    {
        std::cerr << "Image file is empty: " << imagePath << '\n';

        return -1;
    } 

    
    // c. Let's set up our compression parameters

    // These will be saved in std::vector as alternating values (parameterID, parameter value)
    std::vector<int> compression_params;

    // get parameterID and parameter value
    auto [parameterID, parameterValue] = imageWriteFlag(ext); // from C++17 onwards
    compression_params.push_back(parameterID); // add parameterID
    compression_params.push_back(parameterValue); // add parameter value

    // d. Since we now have all our parameters checked out we can now compress our image
    //    We will do it in a try...catch block as it might fail

    // Let's create a character buffer to store our compressed image
    std::vector<uchar> imageBuffer;
    
    bool result = false; // Keeps track of whether we have successfully compressed our image

    // we need to add a dot to our file extension before using it in cv::imencode()
    ext = "."s + ext; 
    
    try {
        result = cv::imencode(ext, image, imageBuffer, compression_params);
    } 
    catch (const cv::Exception& ex)
    {
        std::cerr << "\nError compressing image: " << ex.what();
    }

    ///////////////////////////// 4. Save Image Buffer to File /////////////////////


    // If we have successfully compressed our image we can save our buffer as a file
    if(result)
    {
        std::cout << "\nImage successfully compressed.\n";

        // Now we can save the compressed image to file

        /* 
        * Join directory and file name to establish full path to save compressed image to.
        *
        * std::filesystems has the operator '/=', which allows you to create paths 
        * to sub-directories or files. This is done by automatically appending seperators
        * that are appropriate to the underlying operating system
        */
        std::filesystem::path savePath {saveDirectoryPath}; // Directory to save image to
        savePath /= fileName; // Directory + file name == Full file path
        
        // Save buffer to file
        writeVectorBufferToFile(savePath, imageBuffer);

    }
    else 
    {
        std::cerr << "\nError: Could not compress image file.\n";
    }

    std::cout << '\n';

    return 0;
}

/////////////////////// Function Definitions ///////////////////////

/**
 * @brief Return the cv::ImwriteFlag and best quality compression value for 
 *        images with file extensions jpg, jpeg, jp2, png, webp and tiff
 * 
 * @param fileExtension image file extension (without the leading dot/period)
 * @return std::tuple [cv::ImwriteFlag, int] - the compression flag and best quality compression value
 */
std::tuple<cv::ImwriteFlags, int> imageWriteFlag(const cv::String& fileExtension)
{
    if (fileExtension == "jpeg"s || fileExtension == "jpg"s) return { cv::IMWRITE_JPEG_QUALITY, 95 };
    else if (fileExtension == "png"s) return { cv::IMWRITE_PNG_COMPRESSION, 5 };
    else if (fileExtension == "jp2"s) return { cv::IMWRITE_JPEG2000_COMPRESSION_X1000, 1000 };
    else if (fileExtension == "webp"s) return { cv::IMWRITE_WEBP_QUALITY, 45 };
    else if (fileExtension == "tiff"s) return { cv::IMWRITE_TIFF_COMPRESSION, 5 };    
}


/**
 * @brief Write the contents of a std::vector<unsigned char> image buffer to file
 * 
 * @param filePath full path to save data to including image file extension
 * @param buffer std::vector<unsigned char>
 */
void writeVectorBufferToFile(const std::string& filePath, std::vector<uchar>& buffer)
{
    // Create an output stream to write 
    std::ofstream file(filePath, std::ios::out);

    // Use the copy algorithm, to copy our vector contents to a output iterator that will write 
    // them to our file
    std::copy(buffer.cbegin(), buffer.cend(), std::ostream_iterator<unsigned char>(file));
}