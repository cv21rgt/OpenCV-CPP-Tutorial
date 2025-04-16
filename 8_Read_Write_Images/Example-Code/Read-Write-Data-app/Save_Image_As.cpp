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