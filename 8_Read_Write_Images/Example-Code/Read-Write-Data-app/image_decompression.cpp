// Program: image_decompression.cpp

/*
 * This program: 
 *      1. De-compresses an image file
 *      2. Displays the image
 * 
 * Inputs are provided through the command line
 * 
*/

#include "opencv2/core.hpp"            // for OpenCV core data types
#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser
#include "opencv2/imgcodecs.hpp"       // for cv::imdecode(), cv::imread() 
#include "opencv2/highgui.hpp"         // for cv::imshow() and cv::waitKey()

#include "UtilityFunctions/utility_functions.h" // Our own user-defined functions

#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    /////////////////////// 1. Extract Command Line Arguments //////////////////////

    /*
     * Define the command line arguments 
     * We need 1 arguments:
     *      1. Full path to compressed image file 
     * 
    */
    const cv::String keys = 
        "{help h usage ? | | De-compress an image file }"
        "{compressedImage | <none> | Full path to compressed image file }";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nApplication to de-compress an image file, then display it in a window.\n");
    parser.printMessage();

    // Now lets extract our command line arguments
    cv::String compressedFile = parser.get<cv::String>("compressedImage");

    // check for any errors encountered 
    if(!parser.check())
    {
        parser.printErrors();
        return -1;
    }

    //---------------------- End of Extract Command Line Arguments -------------------//

    //////////////////////// 2. Read Compressed Image File ////////////////////////////


    // We will read our compressed image file into a std::vector<uchar>
    std::vector<uchar> buffer;

    // Call function to read image file into std::vector<uchar> container
    CPP_CV::ReadWriteFiles::readFileToVector(compressedFile, buffer);

    //std::cout << "\nSize of compressed image: " 
              //<< buffer.size() * sizeof(unsigned char) << " bytes.\n";

    //---------------------- End of Read Compressed Image File -------------------//

    //////////////////////// 3. De-compress Image File ////////////////////////////
        
    // Decode image file
    cv::Mat image { cv::imdecode(buffer, cv::IMREAD_UNCHANGED) };

    // If the buffer is too short or contains invalid data, 
    // cv::imdecode() returns an empty array
    if(image.empty())
    {
        std::cout << "\nError: Decompressed image array is empty.\n";

        return -1; // terminate program
    }

    //---------------------- End of De-compress Image File -------------------//


    //////////////////////// 4. Display Image in Window ////////////////////////////
    
    // If cv::Mat array is not empty display image
    cv::imshow("De-compressed image", image);
    cv::waitKey(0);
    cv::destroyWindow("De-compressed image");

    //---------------------- End of Display Image in Window -------------------//

    std::cout << '\n';

    return 0;

}

