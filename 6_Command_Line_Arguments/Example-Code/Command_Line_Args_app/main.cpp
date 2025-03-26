#include "opencv2/core.hpp"       // for OpenCV core types, cv::CommandLineParser, cv::addWeighted()
#include "opencv2/highgui.hpp"    // for cv::imshow() and cv::waitKey() 
#include "opencv2/imgcodecs.hpp"  // for cv::imread()
#include "opencv2/imgproc.hpp"    // for cv::resize()
#include <iostream>


int main(int argc, char* argv[])
{
    /* 
     * Define the command line arguments
     * We need 3 non-positional inputs from the user
     * 
     * 1. first image
     * 2. second image to blend with first image
     * 3. blending value between 0 and 1
     * 
    */
    const cv::String keys = 
        "{help h usage ? | | Blend two images and display resulting image in a window }"
        "{image1 | <none> | Full path to first image }"
        "{image2 | <none> | Full path to second image. Image should have same data type as image1. }"
        "{alpha | 0.5 | Blending value between 0 and 1 }";
    
    // Create a cv::CommandLineParser object
    auto parser = cv::CommandLineParser(argc, argv, keys);

    // We also want to display a message about the application
    parser.about("\nBlend/Combine two images v1.0.0\n");
    parser.printMessage();

    // Let's extract the user inputs 
    cv::String image1 = parser.get<cv::String>("image1");
    cv::String image2 = parser.get<cv::String>("image2");
    double alpha = parser.get<double>("alpha");

    // Check for any errors encountered while extracting user input
    if(!parser.check())
    {
        parser.printErrors(); // Print any errors
        return -1; // Exit application early
    }

    // Check the value of 'alpha' if it is between 0 and 1, 
    // if not use 0.5
    if(alpha >= 0 && alpha <= 1)
    {
        alpha = alpha;
    }
    else 
    {
        alpha = 0.5;
    }

    // If there are no errors, we can now read our image data
    cv::Mat sourceImage1 { cv::imread(image1, cv::IMREAD_UNCHANGED) };
    cv::Mat sourceImage2 { cv::imread(image2, cv::IMREAD_UNCHANGED) };

    // Check if we have successfully read the image data
    if(sourceImage1.empty())
    {
        std::cerr << "\nCould not read input image file: " 
                  << image1<< '\n';
        return -1; // Early exit from application
    }

    if(sourceImage2.empty())
    {
        std::cerr << "\nCould not read input image file: " 
                  << image2<< '\n';
        return -1; // Early exit from application
    }

    // Blend/Combine our two images
    // ===========================

    // First make sure size of second image is the same as that
    // of the first image
    cv::Mat dst; // image2 converted to same size as image1
    cv::resize(sourceImage2, dst, cv::Size(sourceImage1.cols, sourceImage1.rows), 0.0, 0.0);

    // Blend images
    cv::Mat blendedImage; // array to save the blended image    

    // We will use the function cv::addWeighted() to blend the two images
    cv::addWeighted(sourceImage1, alpha, dst, (1.0 - alpha), 0.0, blendedImage);

    // Display the blended image in window
    cv::imshow("Blended Image", blendedImage);

    cv::waitKey(0);
        
    std::cout << '\n';

    return 0;
}