#include "opencv2/core/core.hpp"        // for OpenCV core types e.g. cv::Mat
#include "opencv2/highgui/highgui.hpp"  // for display windows
#include "opencv2/imgproc/imgproc.hpp"  // for Drawing and Annotation functions

#include <iostream>
#include <array>

int main()
{ 
        
    ///////////////////// Create a Canvas //////////////////////////

    // Create a 600x600 3-channel image with a gray background 
    cv::Mat image(cv::Size(600, 600), CV_8UC3, cv::Scalar(125, 125, 125));

    // check if you have successfully created the image
    if(image.empty())
    {
        std::cout << "ERROR! Could not create canvas.\n";

        return -1;
    }

    std::cout << "\nCanvas created...\n\n";
    
    ////////////////////// Annotate Text & Draw a Bounding Box /////////////////////////////////////////

    // Add the various font types into a std::array
    std::array <int, 9> fontFace {cv::FONT_HERSHEY_SIMPLEX,
                                 cv::FONT_HERSHEY_PLAIN, 
                                 cv::FONT_HERSHEY_DUPLEX,
                                 cv::FONT_HERSHEY_COMPLEX, 
                                 cv::FONT_HERSHEY_TRIPLEX, 
                                 cv::FONT_HERSHEY_COMPLEX_SMALL, 
                                 cv::FONT_HERSHEY_SCRIPT_SIMPLEX, 
                                 cv::FONT_HERSHEY_SCRIPT_COMPLEX, 
                                 cv::FONT_ITALIC
                                };
    double fontScale {1};
    int thickness {1}; 

    int y_coordinate {50}; // Starting y-coordinate of text string

    cv::String text {"0penCV"}; // Text to annotate

    for (std::size_t i {0}; i < fontFace.size(); ++i)
    {
        int baseline {0}; // We will use the bottom-line of the box as the baseline

        // Compute Text Size for each font type
        cv::Size textSize = cv::getTextSize(text,         // Text string
                                            fontFace[i],  // Font Type
                                            fontScale,    // Font scale
                                            thickness,    // Thickness of lines used
                                            &baseline     // Baseline for text string
                                        );

        // Draw the box  using cv::rectangle()
        // Use text 'width' and 'height' from above to get the coordinates 
        // of two opposite corners of our box
        cv::rectangle(image, 
                      cv::Point(10, y_coordinate) + cv::Point(0, baseline), // bottom-left corner
                      cv::Point(10, y_coordinate) + cv::Point(textSize.width, -textSize.height), // top-right corner
                      cv::Scalar(0, 0, 255) // Box outline color - Red
                    );
        
        // Add text to image
        cv::putText(image,                        // Canvas/image
                    text,                         // Text to annotate
                    cv::Point(10, y_coordinate),  // Bottom-left coordinates
                    fontFace[i],                  // Font type
                    fontScale,                    // Scale
                    cv::Scalar(0, 0, 0),          // Text color - Black
                    thickness,                    // Line thickness
                    cv::LINE_AA                   // Use anti-aliasing
                );

        // Annotated Text will be seperated by 50 pixels along the y-axis
        y_coordinate += 50; 
    }
    

    ///////////////// Display Image Canvas ////////////////////////////////   


    cv::String window_name = "Annotate Text & Draw Bounding Boxes"; 
    cv::namedWindow(window_name, cv::WINDOW_AUTOSIZE);
    cv::imshow(window_name, image);

    cv::waitKey(0);

    cv::destroyWindow(window_name);

    std::cout << '\n';

    return 0;
}