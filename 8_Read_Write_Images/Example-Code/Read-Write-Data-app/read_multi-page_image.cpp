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