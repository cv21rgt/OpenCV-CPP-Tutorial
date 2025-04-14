// Program: read_display_multiple_images.cpp

// In this program we read multiple images from a folder/directory, then 
// display each in a seperate window.

#include "opencv2/core.hpp"
#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser
#include "opencv2/highgui.hpp"         // for functions related to displaying images e.g. cv::imshow(), cv::waitKey()
#include "opencv2/imgcodecs.hpp"       // for cv::imread()

#include <UtilityFunctions/utility_functions.h> // for user-defined functions

#include <iostream>
#include <filesystem> // for handling file systems

int main(int argc, char* argv[])
{
    /*
     * Define the command line arguments:
     *  1. dir - full file path directory/folder with image files. 
     *           This should not be empty
     * 
    */
    const cv::String keys = 
        "{help h usage ? | | Display images without alterations }"
        "{dir | <none> | full path to directory/folder with image files }";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nRead and Display Multiple Images v1.0.0\n");
    parser.printMessage();

    // Now lets extract user input
    cv::String dirPath = parser.get<cv::String>("dir");

    // check for any errors encountered 
    if(!parser.check())
    {
        parser.printErrors(); // Print the errors

        return -1; // Early exit
    }

    // We need to go through the contents of our directory and read 
    // the image files. We will use an iterator 'directory_iterator' 
    // from std::filesystem to go through the directory contents.
    // However, this iterator will not go through any sub-directories
    const std::filesystem::path directory {dirPath}; // Get 'dirPath' as a 'path' object

    for (auto const& dir_entry :std::filesystem::directory_iterator{directory})
    {
        // Before attempting to read the file, check if it is an image file by 
        // using cv::haveImageReader(). Even if it is an image file, here we can 
        // also check if we have an image reader for that image file
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

                // We also want to display some other information about the image 
                // (1)No. of channels, (2) image size, (3) data type
                std::cout << "\nImage file: " << dir_entry.path().filename().string() 
                        << "\nImage size (width x height): " << image.cols << " x " << image.rows 
                        << "\nNo. of channels: " << image.channels() 
                        << "\nData type: " << CPP_CV::General::openCVDescriptiveDataType(image.type()) << '\n';

                // We will use image file name for the window name
                cv::namedWindow(dir_entry.path().filename().string(), cv::WINDOW_NORMAL);

                // Show image on screen            
                cv::imshow(dir_entry.path().filename().string(), image);

                // Image window will be displayed until a user presses any key
                // on the keyboard
                cv::waitKey(0);  
            }

        }

    }     

    // Release all memory by destroying all windows
    cv::destroyAllWindows();

    std::cout << '\n';

    return 0;
}