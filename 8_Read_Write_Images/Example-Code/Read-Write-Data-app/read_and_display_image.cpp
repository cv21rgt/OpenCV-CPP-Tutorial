// Program: read_and_display_image.cpp

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser
#include "opencv2/highgui.hpp"         // for functions related to displaying images e.g. cv::imshow(), cv::waitKey()
#include "opencv2/imgcodecs.hpp"       // for cv::imread()

#include <UtilityFunctions/utility_functions.h> // for user-defined functions

#include <iostream>

int main(int argc, char* argv[])
{
    /*
     * Define the command line arguments:
     *  1. image - full file path to image. This should not be empty
     *  2. title - string describing the image
     * 
    */
    const cv::String keys = 
        "{help h usage ? | | Display an image without alterations }"
        "{image | <none> | full path to image to be displayed }"
        "{title |        | short text describing the image }";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nRead and Display Images v1.0.0\n");
    parser.printMessage();

    // Now lets extract user input
    cv::String imagePath = parser.get<cv::String>("image");
    cv::String imageTitle = parser.get<cv::String>("title");

    // check for any errors encountered 
    if(!parser.check())
    {
        parser.printErrors(); // Print the errors

        return -1; // Early exit
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
        std::cerr << "Could not read input image file data: " 
                  << imagePath << '\n';
        
        return -1;
    }

    // We also want to display some other information about the image 
    // (1)No. of channels, (2) image size, (3) data type
    std::cout << "\nImage size (width x height): " << image.cols << " x " << image.rows 
              << "\nNo. of channels: " << image.channels() 
              << "\nData type: " << CPP_CV::General::openCVDescriptiveDataType(image.type()) << '\n';

    // If the user did not provide an image title
    if(imageTitle.empty()) 
    {
        imageTitle = "Image"; // We simply name it 'Image'
    }

    // We use the image title as the window name
    // The user will be able to resize the image window
    cv::namedWindow(imageTitle, cv::WINDOW_NORMAL);

    // Show image on screen
    cv::imshow(imageTitle, image);

    // Image window will be displayed until a user presses any key
    // on the keyboard
    cv::waitKey(0);    

    // Release memory
    cv::destroyWindow(imageTitle);

    std::cout << '\n';

    return 0;
}