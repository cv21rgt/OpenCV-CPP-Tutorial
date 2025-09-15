#include <opencv2/core.hpp>     // for OpenCV core types and cv::copyMakeBorder()
#include <opencv2/highgui.hpp>  // for displaying images in a window
#include <opencv2/core/utility.hpp> // for command line or terminal inputs
#include "opencv2/core/persistence.hpp" // for cv::FileStorage
#include "opencv2/imgproc.hpp" // for cv::rectangle()

#include "UtilityFunctions/utility_functions.h" // functions from our own library

#include <iostream>
#include <string_view>
#include <string>
#include <algorithm>
#include <vector>

/**
 * @brief Returns a string describing how an image border type is created
 * 
 * @param borderType Border type as an integer value. See enum cv::BorderTypes
 * @return std::string_view A description on how image border type is created
 */
std::string_view imageBorderDescription(int borderType);

int main(int argc, char* argv[])
{
    //---------------- 1. Extract Command Line Arguments -----------------//

    const cv::String keys = 
        "{help h usage ? | | Create a border around a region of interest }"
        "{path | <none> | Full path to file with input data (must have extension e.g. .xml, .yaml, .yml or .json) }";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nProgram for creating a border around a region of interest without any outside influence from the parent image pixels.\n");
    parser.printMessage();

    //----------------------------- Extract command line arguments into program

    cv::String pathToInputFile = parser.get<cv::String>("path");

    // Check for any errors encountered during arguments extraction
    if (!parser.check())
    {
        parser.printErrors();
        return -1; // early exit from function
    }

    // Since we can only read from 5 file types we need to check if file
    // path provided by user is valid. We first call the function to 
    // extract the file extension
    std::string fileExtension = CPP_CV::ReadWriteFiles::getFileExtension(pathToInputFile);

    // Use the std::find() algorithm to check if file extension exists
    // in our catalogue 'fileTypes'
    auto found = std::find(CPP_CV::General::fileTypes.cbegin(), CPP_CV::General::fileTypes.cend(), fileExtension);
    if (found == CPP_CV::General::fileTypes.cend()) // If the file extension is not valid
    {
        std::cout << "\nERROR: File type is not valid." 
                  << "\nFile extension should be one of: xml, yml, yaml, json or gz.\n";
        
        return -1; // Exit program early
    }

    // If file type is valid, we can start reading our data from file

    // -------------------- 2. Read File Data --------------------------//

    // Create a cv::FileStorage object for READING
    cv::FileStorage fs(pathToInputFile, cv::FileStorage::READ);

    // Check if have successfully opened the filw for reading
    if (!fs.isOpened())
    {
        std::cout << "\nERROR: Could not open file for reading.\n";

        return -1; // Early program exit
    }

    // If we have successfully opened the file, we start readin data

    std::cout << "\nReading data from file...\n";

    // a. Read source image path
    cv::String imagePath;
    fs["SourceImagePath"] >> imagePath;
    std::cout << "\nimagePath = " << imagePath << '\n';

    // b. Read ROI coordinates - Data is a map that contains data in sequences

    // Create a cv::FileNode object from the Map structure
    cv::FileNode roi = fs["ROI"];
    // Check if the data structure is actually a MAP
    if(roi.type() != cv::FileNode::MAP)
    {
        std::cout << "\nYou are attempting to read a data structure that is not a cv::FileNode::MAP\n";

        return -1;
    }
    // Inside the MAP we have two sequences - we will create node objects for them
    cv::FileNode tlCoordinates_seq = roi["top-left-corner-coordinates"];
    cv::FileNode brCoordinates_seq = roi["bottom-right-corner-coordinates"];
    // Check if the structures are actually SEQUENCES
    if (tlCoordinates_seq.type() != cv::FileNode::SEQ)
    {
        std::cout << "\nTop left coordinates of ROI are not a SEQUENCE structure.\n";

        return -1;
    }
    if (brCoordinates_seq.type() != cv::FileNode::SEQ)
    {
        std::cout << "\nBottom right coordinates of ROI are not a SEQUENCE structure.\n";

        return -1;
    }

    // Temporary vectors to store coordinates
    std::vector<int> tlCoordinatesVector; 
    std::vector<int> brCoordinatesVector; 
     
    // Call function to read sequence data into a std::vector
    CPP_CV::ReadWriteFiles::getSequence(tlCoordinates_seq, tlCoordinatesVector);
    CPP_CV::ReadWriteFiles::getSequence(brCoordinates_seq, brCoordinatesVector);

    // Create a cv::Point(row, column) to store our data 
    cv::Point2i topLeftCornerCoordinates;
    cv::Point2i bottomRightCornerCoordinates;
    topLeftCornerCoordinates.x = tlCoordinatesVector.at(0);
    topLeftCornerCoordinates.y = tlCoordinatesVector.at(1);
    bottomRightCornerCoordinates.x = brCoordinatesVector.at(0);
    bottomRightCornerCoordinates.y = brCoordinatesVector.at(1);


    std::cout << "\nTop left corner coordinates: " << topLeftCornerCoordinates << '\n';
    std::cout << "\nBottom right corner coordinates: " << bottomRightCornerCoordinates << '\n';

    // c. Read Border sizes - Data is a MAP structure

    // Create a cv::FileNode object from the Map structure
    cv::FileNode borderSize = fs["BorderSize"];

    // Check if the data structure is actually a MAP
    if(borderSize.type() != cv::FileNode::MAP)
    {
        std::cout << "\nBorder sizes are not in a MAP structure.\n";

        return -1;
    }

    // Inside the borderSize MAP structure the data is made up of single objects
    // we can read straight into a variable that holds an integer
    auto topBorderSize = static_cast<int>(borderSize["top"]);
    auto bottomBorderSize = static_cast<int>(borderSize["bottom"]);
    auto leftBorderSize = static_cast<int>(borderSize["left"]);
    auto rightBorderSize = static_cast<int>(borderSize["right"]);

    std::cout << "\nBorder sizes:"
                << "\n\tTop: " << topBorderSize 
                << "\n\tBottom: " << bottomBorderSize
                << "\n\tLeft: " << leftBorderSize
                << "\n\tRight: " << rightBorderSize 
                << '\n';

    // d. Read the Border Type data
    auto borderType = static_cast<int>(fs["BorderType"]);

    std::cout << "\nBorder type: " << borderType << '\n';

    // e. Read the Constant Value data
    auto constantValue = static_cast<double>(fs["ConstantValue"]);

    std::cout << "\nConstant value: " << constantValue << '\n';

    // f. // Explicit closing of cv::FileStorage for reading
    fs.release(); 

    std::cout << "\n\nFinished reading data from file " 
            << pathToInputFile << '\n';

    //--------------------- 3. Read source image data -------------------------//

    cv::Mat inputImage = cv::imread(imagePath, cv::IMREAD_ANYCOLOR);
    if (inputImage.empty())
    {
        CV_Error_(cv::Error::StsBadArg, 
                      ("Could not read image data from (%s)", 
                        imagePath.c_str())); 
    }
    else 
    {
        // Print image sizes, no. of channels and data types of image
        std::cout << "\nSize of input image = " << inputImage.size()
                  << "\nData type of input image = " 
                  << CPP_CV::General::openCVDescriptiveDataType(inputImage.type())
                  << '\n';
    }

    // Add ROI to image
    // Create a clone of the original source image for drawing onto
    // We want to maintain the original image as is
    cv::Mat copyOfSourceImage;
    inputImage.copyTo(copyOfSourceImage);
    cv::rectangle(copyOfSourceImage, 
            topLeftCornerCoordinates, 
            bottomRightCornerCoordinates, 
            cv::Scalar(0, 0, 0), 
            2, 
            cv::LINE_AA
        );

    // Display original source image with ROI
    cv::imshow("Input image with ROI (BGR format)", copyOfSourceImage);

    //--------------- 4. Create our ROI as a view of the parent image ---------//
    
    cv::Rect area {topLeftCornerCoordinates, bottomRightCornerCoordinates};

    cv::Mat regionOfInterest = inputImage(area); 

    // Print image sizes, no. of channels and data types of ROI
    std::cout << "\nSize of ROI  = " << regionOfInterest.size()
            << "\nData type of ROI = " 
            << CPP_CV::General::openCVDescriptiveDataType(regionOfInterest.type())
            << '\n';

    cv::imshow("ROI", regionOfInterest);

    // ------------------------ Create border around ROI ---------------- //

    cv::Mat dst; // Output image with border added to it

    // If using a constant value for the border convert to cv::Scalar
    const cv::Scalar constantBorderValue {constantValue, constantValue, constantValue};

    cv::copyMakeBorder(
        regionOfInterest,                   // Image defining ROI
        dst,                                // Output image with border added to it
        topBorderSize,                      // No. of border pixel rows at top of image
        bottomBorderSize,                   // No. of border pixel rows at bottom of image
        leftBorderSize,                     // No. of border pixel columns on left side of image
        rightBorderSize,                    // No. of border pixel columns on right side of image
        borderType | cv::BORDER_ISOLATED,   // Type of border
        constantBorderValue                 // Constant value if typeOfBorder == cv::BORDER_CONSTANT     
    );

    // Print image sizes, no. of channels and data types of ROI with border
    std::cout << "\nSize of ROI with border = " << dst.size()
            << "\nData type of ROI with border = " 
            << CPP_CV::General::openCVDescriptiveDataType(dst.type())
            << '\n';

    // Display ROI image with border       
    auto borderDescription = std::string(imageBorderDescription(borderType));
    cv::imshow(borderDescription, dst);
  
    cv::waitKey(0);

    cv::destroyAllWindows();

    std::cout << '\n';

    return 0;
}


/**
 * @brief Returns a string describing how an image border type is created
 * 
 * @param borderType Border type as an integer value. See enum cv::BorderTypes
 * @return std::string_view A description on how image border type is created
 */
std::string_view imageBorderDescription(int borderType)
{
    switch (borderType)
    {
        case cv::BORDER_CONSTANT:
            return "Border with a constant pixel value";
        case cv::BORDER_REPLICATE:
            return "Border with replicated pixels";
        case cv::BORDER_REFLECT:
            return "Border with mirror reflected pixel values";
        case cv::BORDER_WRAP:
            return "Border with wraped pixel values";
        case cv::BORDER_REFLECT_101:
            return "Border with reflected pixel values (edge pixels not used)";
        case cv::BORDER_ISOLATED:
            return "Border created without using any pixels outside input image or ROI";
        default:
            return "Invalid border type";
    }
}