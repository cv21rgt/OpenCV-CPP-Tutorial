# Image decompression with `cv::imdecode()`

:notebook_with_decorative_cover: The `cv::imdecode()` function allows us to decompress an image from a character buffer into an image array. It has the syntax: `cv::Mat cv::imdecode(cv::InputArray buf, int flags)`.

1. `buf` - Memory buffer, which normally has `std::vector<uchar>` type.
2. `flags` - Flags of type `cv::ImreadModes`. These are the same flags used by `cv::imread()`.

:notebook_with_decorative_cover: The function reads an image from the specified buffer in the memory. If the buffer is too short or contains invalid data, the function returns an empty matrix (`cv::Mat::data==NULL` or `cv::Mat::empty() == true`).

:notebook_with_decorative_cover: `cv::imdecode()` can deduce the correct codec to use from the first bytes of the compressed image in the buffer NOT from the file extension.

:notebook_with_decorative_cover: In the example we are about to look at, we will read a compressed image file into a buffer e.g. `std::vector`, decompress the memory buffer into an image array, and display the image. Reading data from a file is a common task in most programming applications. As such we will first create a generic template function that can read data from any file (including image files) then store that data into a `std::vector` container of the appropriate data type. We will name this template function `readFileToVector`, add it to our library in the header file `Example-Code/include/UtilityFunctions/utility_functions.h`. Since this involves reading file data, we add it to the namespace `ReadWriteFiles`. The full function definition is as follows:

```c++
#include <vector>
#include <string>
#include <fstream>    // for std::ifstream
#include <iterator>   // for std::istream_iterator
#include <algorithm>  // for std::copy

/**
 * @brief Read contents of a file (without skipping any leading whitespace) into a std::vector
 * 
 * @tparam T   Data type of std::vector elements
 * @param path Full path to file to be read
 * @param data std::vector to store file contents
 */
template <typename T>
void readFileToVector(const std::string& path, std::vector<T>& data)
{
    std::ifstream file(path);

    // Do not skip any leading whitespace whilst reading file contents
    file >> std::noskipws; 

    // Use the std::copy algorithm from the STL <algorithm> header to iterate 
    // through the file and insert all its contents into a std::vector
    std::copy(std::istream_iterator<T>(file), 
             std::istream_iterator<T>(), std::back_inserter(data));
}
```

**Example 1:** - De-compress an image file

```c++
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
```




