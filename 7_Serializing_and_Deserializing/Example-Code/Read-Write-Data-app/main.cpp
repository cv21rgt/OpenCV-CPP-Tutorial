#include "opencv2/core.hpp"             // for OpenCV core data types
#include "opencv2/core/utility.hpp"     // for cv::CommandLineParser
#include "opencv2/core/persistence.hpp" // for cv::FileStorage

#include <iostream>
#include <array>
#include <string>
#include <string_view>
#include <algorithm>  // for std::find algorithm
#include <filesystem> // handles files

// std::string_literals allows us to convert text literals to std::string 
// by adding an 's' in front of the literal. This was introduced in C++17
using namespace std::string_literals; 
const std::array<std::string, 5> fileTypes { "xml"s, "yml"s, "yaml"s, "json"s, "gz"s };

/**
 * @brief Get the File Extension from a full file path e.g. from the file path 
 *        `Example-Code/temporary-files/write.xml` you will get the extension `xml`
 * 
 * @param filePath full path including filename and extension
 * @return std::string file extension: Returns an empty string if there is no file extension
 */
std::string getFileExtension(std::string_view filePath);


int main(int argc, char* argv[])
{
    // Define the command line arguments
    const cv::String keys = 
            "{help h usage ? | | Write various data types to file }"
            "{path | <none> | Full path and file name to save data to (must include extension e.g. .xml, .yaml, .json) }";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // Display a message about the program
    parser.about("\nWrite data to file v1.0.0"
                 "\nFile will be XML, YAML or JSON\n");
    parser.printMessage();

    // Extract our command line arguments    
    cv::String pathToWriteFile = parser.get<cv::String>("path");

    // Check for any errors during extract of arguments
    if (!parser.check())
    {
        parser.printErrors(); // Print any errors

        return -1; // Exit program early
    }

    // Since we can only write to 5 file types we need to check if file
    // path provided by user is valid. We first call the function to 
    // extract the file extension
    std::string fileExtension = getFileExtension(pathToWriteFile);

    // Use the std::find() algorithm to check if file extension exists
    // in our catalogue 'fileTypes'
    auto found = std::find(fileTypes.cbegin(), fileTypes.cend(), fileExtension);
    if (found == fileTypes.cend()) // If the file extension is not valid
    {
        std::cout << "\nERROR: File type is not valid." 
                  << "\nFile extension should be one of: xml, yml, yaml, json or gz.\n";
        
        return -1; // Exit program early
    }

    // If file is valid, we can start writing our data to file

    //----------------------- WRITE DATA 

    // Create a cv::FileStorage object for writing
    cv::FileStorage fs(pathToWriteFile, cv::FileStorage::WRITE);

    // Check if we have successfully opened the file for writing
    if (!fs.isOpened())
    {
        std::cout << "\nERROR: Could not open file for writing.\n";
        return -1; // Exit program early
    }

    // If we have successfully opened the file, we start writing data

    std::cout << "\nWriting data to file...\n";

    // Write information about the file we will save our data to as a Map
    fs << "File_Properties" << "{"; // Open up a MAP for writing
    fs << "File_Path" << pathToWriteFile;
    fs << "File_Name" << std::filesystem::path(pathToWriteFile).filename();
    fs << "}"; // Close MAP

    // Write a text string 
    fs << "Name_of_Developer" << "Rodney";

    // Write a scalar value
    fs << "No_of_file_types" << 5;

    // Write all cv::FileStorage file types in a sequence
    fs << "File_Types" << "["; // Open up a sequence for writing
    fs << "XML" << "YML" << "YAML" << "JSON" << "GZ"; // Sequence data
    fs << "]"; // Close sequence

    // Write a cv::Matx
    const cv::Matx22d mtx { 2, 4, 6, 8 };
    fs << "Matrix" << mtx;

    // Write a cv::Point
    const cv::Point2i p { 23, 78 };
    fs << "Point_Cordinates" << p;

    // Write a cv::Mat
    float data[] { 2.34f, 1.245f, 6.09f, 4.56f, 9.07f, 1.234f };
    const cv::Mat m { cv::Size(2, 3), CV_32F, data };
    fs << "Dense_Array" << m;

    // Write a std::vector
    std::vector imageFormats { "jpg"s, "tiff"s, "jpg"s, "webp"s, "jp2"s }; 
    fs << "ImageFormats" << imageFormats;
    

    fs.release(); // Explicit closing of cv::FileStorage for writing

    std::cout << "\nFinished writing data to file " << pathToWriteFile << '\n';

    std::cout << '\n';
    
    return 0;
}

/**
 * @brief Get the File Extension from a full file path e.g. from the file path 
 *        `Example-Code/temporary-files/write.xml` you will get the extension `xml`
 * 
 * @param filePath full path including filename and extension
 * @return std::string file extension: Returns an empty string if there is no file extension
 */
std::string getFileExtension(std::string_view filePath)
{
    // Use the file path to create an object of std::filesystem
    std::filesystem::path p { filePath };

    // get the file extension e.g .xml, .json etc
    std::string fileExtension { p.extension() };

    if(fileExtension.empty()) // If there is no file extension return an empty string 
    {
        return "";
    }
    else // if there is a fileExtension, it will have the form ".fileExtension"
    {
        // extract the sub string after the dot or position = 0
        std::string substring { fileExtension.substr(1) };

        return substring;
    }
}


