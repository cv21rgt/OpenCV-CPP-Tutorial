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