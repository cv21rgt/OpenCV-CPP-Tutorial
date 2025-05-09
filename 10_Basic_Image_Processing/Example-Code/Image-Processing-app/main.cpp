#include "opencv2/core.hpp"        // for OpenCV core types e.g. cv::Mat
#include "opencv2/imgcodecs.hpp"   // for cv::imread
#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser

#include "UtilityFunctions/utility_functions.h"

#include <iostream>
#include <array>

int main(int argc, char* argv[])
{
    //------------------- 1. Extract Command Line Arguments -----------------//

    /*
     * Define the command line arguments 
     * We need the following arguments:
     *      1. Full path to image file 
     *      2. Row on which to find pixel
     *      3. Column on which to find pixel
     * 
    */
   const cv::String keys = 
   "{help h usage ? | | Access pixel intensity values of an image }"
   "{image | <none> | Full path to image file }"
   "{row | 0 | Row to find pixel }"
   "{column | 0 | Column to find pixel }";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nApplication to access pixel intensity values of an image\n");
    parser.printMessage();

    // Now lets extract our command line arguments
    cv::String imagePath = parser.get<cv::String>("image");
    int row = parser.get<int>("row");
    int column = parser.get<int>("column");

    // check for any errors encountered 
    if(!parser.check())
    {
        parser.printErrors();

        return -1;
    }
          
    //----------------------- 2. Read image file ----------------------------//

    cv::Mat image {cv::imread(imagePath, cv::IMREAD_ANYCOLOR)};

    // Check if we have successfully read the image data
    if (image.empty())
    {
        std::cout << "\nCould not read image data from " 
                  << imagePath << '\n';
        
        return -1; // Early exit
    }

    // Print some relevant information about the image
    std::cout << "\nSize: " << " width = " << image.cols 
              << ", height = " << image.rows;
    std::cout << "\nNo. of channels = " << image.channels();
    std::cout << "\nData type = " 
              << CPP_CV::General::openCVDescriptiveDataType(image.type()) 
              << '\n';

        
    //----------------------- 3. Access pixel values -------------------------// 
    
    // Check if (row, column) supplied by user are valid
    if ((row < 0) || (row > image.rows) || (column < 0) || (column > image.cols))
    {
        std::cout << "\nERROR: Row/Column of pixel is outside image boundary\n";

        return -1; // early exit
    }

    // Get OpenCV image data type of pixel values
    int OpenCVType = image.type(); 
    
    // Get the no. of channels in image
    int channels = image.channels();

    if (channels == 1)
    {   
        const cv::Scalar pixelValue = CPP_CV::BasicImageProcessing::pixelValue_C1(image, OpenCVType, row, column);
        std::cout << "\nPixel value at location (row, column) (" << row << ", " << column << ") = " 
                  << pixelValue[0] << '\n';
    }
    else if (channels == 2)
    {
        const cv::Scalar pixelValue = CPP_CV::BasicImageProcessing::pixelValue_C2(image, OpenCVType, row, column);
        std::cout << "\nPixel values at location (row, column) (" << row << ", " << column << ") = " 
                  << "(" << pixelValue[0] << ", " << pixelValue[1] << ")\n";
    }
    else if (channels == 3)
    {
        const cv::Scalar pixelValue = CPP_CV::BasicImageProcessing::pixelValue_C3(image, OpenCVType, row, column);
        std::cout << "\nPixel values (BGR format) at location (row, column) (" << row << ", " << column << ") = " 
                  << "(" << pixelValue[0] << ", " << pixelValue[1] << ", " 
                  << pixelValue[2] << ")\n";
    }
    else if (channels == 4)
    {   
        const cv::Scalar pixelValue = CPP_CV::BasicImageProcessing::pixelValue_C4(image, OpenCVType, row, column);
        std::cout << "\nPixel values (BGRA format) at location (row, column) (" << row << ", " << column << ") = " 
                  << "(" << pixelValue[0] << ", " << pixelValue[1] << ", " 
                  << pixelValue[2] << ", " << pixelValue[3] << ")\n";
    }    
   
    std::cout << '\n';

    return 0;
}