# Codecs

:notebook_with_decorative_cover: Early on we mentioned that image data is memory consuming and the best way to handle it is compressing  it when not in use and then decompressing it when you need to process the data. This process is performed by software packages generically referred to as **codecs** - short for **co**-mpression and **dec**-compression librarie-**s**. 

:notebook_with_decorative_cover: Every operating system (on your computer, phone etc) will have a few codecs available for each of the common image file types. This is how they handle the images you take and save on your computer system or phone. 

:notebook_with_decorative_cover: If your system does not have a codec for a specific image format you can install it yourself. We did that when we installed packages such as `libjpeg` (On Unix systems you also need the development file `libjpeg-dev`) early on in our tutorials. These codecs then become part of your operating system.

:notebook_with_decorative_cover: In addition, image processing software or libraries also come with their own codecs. OpenCV comes with codecs for common image file formats such as `jpeg`, `png`, `tiff`, etc., but also codecs for uncommon image file types e.g. `OpenEXR`, `PAM`, `LogLov` etc.

:notebook_with_decorative_cover: If both OpenCV and your operating system provide the same codec, which codec is used depends on the following options:

a) use the codec supplied with OpenCV - these are included if you add them to your **CMake** file when building your OpenCV modules.

b) use the external codec libraries such as `libjpeg` or `libpng`. In Linux, you have to install these codecs together with their development files e.g., install `libjpeg` with its development file `libjpeg-dev`.

:notebook_with_decorative_cover: If you are using Windows O/S, option (a) above is the default way of using codecs. On OS X/Linux, the default option is (b); if however CMake cannot find the codec for some reason then it will use option (a). 

# Image compression

:notebook_with_decorative_cover: Since image files are large and require a lot of memory for storage, we use **image compression** to reduce their size without significantly affecting visual quality. This is achieved by either removing redundant data or approximating parts of the image.

:notebook_with_decorative_cover: There are two main types of image compression: <a href = "https://en.wikipedia.org/wiki/Lossless_compression">lossless compression</a> and <a href = "https://en.wikipedia.org/wiki/Lossy_compression">lossy compression</a>. **Lossless compression** retains the original image data, while **lossy compression** discards some information to achieve a smaller file size, potentially reducing the image quality.

## Why is Image Compression Important?

:notebook_with_decorative_cover: Image compression is essential for the following reasons:

1. **Reduced storage space**: Compressed images occupy less storage space, allowing you to store more images or use the saved space for other purposes.

2. **Faster transmission**: Smaller file sizes enable faster transmission of images over networks, which is particularly important in applications like video streaming and remote sensing.

3. **Reduced bandwidth usage**: Compressed images consume less bandwidth, which is crucial for data transfer on limited or metered connections.

## The Theory Behind Image Compression

:notebook_with_decorative_cover: Image compression techniques typically exploit the **spatial** and **color** redundancies in images. Spatial redundancy arises from the correlation between neighboring pixels, while color redundancy stems from the similarity of color values in adjacent regions.

:notebook_with_decorative_cover: **Lossless compression** involve no loss of information. If data have been losslessly compressed, the original data can be recovered exactly from the compressed data after a compress/expand cycle. Lossless compression is generally used for so-called "discrete" data, such as database records, spreadsheets, word-processing files, and even some kinds of image and video information. A good example of using lossless compression would be with medical images. We want to be able to reconstruct the original image as is because any differences would potentially mislead radiologists. Because the price for this kind of mishap may be a human life, it makes sense to be very careful about using a compression scheme that generates a reconstruction that is different from the original. In essence, lossless compression algorithms are needed in cases that require compression where we want the reconstruction to be identical to the original. <a href = "https://en.wikipedia.org/wiki/Portable_Network_Graphics">PNG</a> and <a href = "https://en.wikipedia.org/wiki/GIF">GIF</a>, use lossless techniques like <a href = "https://en.wikipedia.org/wiki/Run-length_encoding">Run-Length Encoding</a> and <a href = "https://en.wikipedia.org/wiki/Huffman_coding">Huffman coding</a> for image compression.

* **Run-Length Encoding (RLE)** - Faced with sequences of data in which the same value appears more than once consecutively, RLE stores the data as a single data value and count, rather than as the original sequence. Consider an image containing plain black text on a solid white background. There will be many long runs of white pixels in the blank space, and many short runs of black pixels within the text. A hypothetical scan line, with **B** representing a black pixel and **W** representing white, might read as follows:

    **WWWWWWWWWWWWBWWWWWWWWWWWWBBBWWWWWWWWWWWWWWWWWWWWWWWWBWWWWWWWWWWWWWW**

    Applying RLE data compression algorithm to the above hypothetical scan line, we can store the data as follows:

    **12W1B12W3B24W1B14W**

    This can be interpreted as a sequence of twelve Ws, one B, twelve Ws, three Bs, etc., and represents the original 67 characters in only 18. While the actual format used for the storage of images is generally binary rather than ASCII characters like this, the principle remains the same. Even binary data files can be compressed with this method.

:notebook_with_decorative_cover: **Lossy compression** methods result in some amount of data being lost in the process.  Thus, after a compression/decompression cycle, the data set will be modified from the uncompressed original and information may be lost. This loss of data can be tolerated. Lossy compression techniques attempt to eliminate unnecessary or redundant information, focusing more on saving space over preserving the accuracy of the data. Ideally, the loss is either minimal or undetectable by human observations. Lossy compression techniques are used for pictures and music files that can be trimmed at the edges. Unlike text files and processing files, pictures and music do not require reconstruction to be identical to the original, especially if the data dropped is insignificant or undetectable. Lossy compression is used with <a href = "https://en.wikipedia.org/wiki/JPEG">JPEG</a> and <a href = "https://cs.stanford.edu/people/eroberts/courses/soco/projects/data-compression/lossy/mp3/index.htm">MP3</a> technology. Examples of lossy compression methods are: 

* <a href = "https://en.wikipedia.org/wiki/Discrete_cosine_transform">**Discrete Cosine Transform</a> (DCT)** - a mathematical transformation that takes the spatial information from an image and convert it into numeric data in the form of frequency values. In this way the information in an image now exists in a quantitative form that can be manipulated for compression.

* <a href = "https://en.wikipedia.org/wiki/Quantization_(image_processing)">**Quantization**</a> - is the process of reducing the number of bits needed to store an integer value by reducing the precision of the integer. For example reducing 16-bit images to be 8-bit images. This means you will need less space to store the image as 8-bit values require less storage space than 16-bit values. However, it means you loose some degree of precision with your integer values as you move from 16-bit to 8-bit.


:notebook_with_decorative_cover: Knowing about the theory of image compression is important especially when choosing which image file format to use in your projects. *Are you concerned about loss of information, image quality or smaller file sizes that enable faster transmission and processing?*

:notebook_with_decorative_cover: There is more information out there about image compression techniques. This can be an interesting research area if you can come up with new compression techniques. **Go and explore!!!!!**


## Compressing files in OpenCV

:notebook_with_decorative_cover: The read/write functions `cv::imread()` and `cv::imwrite()` handle compression and decompression behind the scenes. If however a situation arises where you need to compress or decompress image files yourself, OpenCV offers the functions `cv::imencode()` and `cv::imdecode()` for compressing and decompressing images, respectively.

:notebook_with_decorative_cover: `cv::imencode()` compresses images directly from any one of OpenCV's array types. The result is a character buffer, whose meaning only makes sense to the codec that was used to compress the image. As expected, the file size of the compressed image will be smaller than the original image. `cv::imencode()` has the folowing full syntax: `bool cv::imencode(const cv::String& ext, cv::InputArray img, std::vector<uchar>& buf, const std::vector<int>& params = std::vector<int>())`

1. `ext` - File extension that defines the output format. Must include a leading period (for example, `.png`, `.jpeg`, `.tiff`).
2. `img` - Image array to be compressed
3. `buf` - Output buffer resized to fit the compressed image. This is a `std::vector` that can hold the data type `unsigned char`.
4. `params` - Format-specific parameters encoded as pairs `(paramId_1, paramValue_1, paramId_2, paramValue_2, ... .)`. These are provided as a `std::vector` of integers, with those integers being a sequence of parameter IDs followed by the value to be assigned to that parameter (i.e., alternating between parameter ID and the parameter value). For the parameter IDs and possible values, there are aliases provided by OpenCV as <a href = "https://docs.opencv.org/4.8.0/d8/d6a/group__imgcodecs__flags.html#ga292d81be8d76901bff7988d18d2b42ac">cv::ImwriteFlags</a>. `params` will determine the quality of your saved image.  

**Example 1:** In the following example we will compress an image file to a character buffer and save the buffer to a file. As a test, we will run this program with a variety of file extension and then compare which extension works best.

```c++
// Program: image_compression.cpp

/*
 * Program compresses an image into a std::vector character buffer, which has a smaller size than the 
 * original image file. We then save the buffer to a file for future use
 * 
 * Inputs are provided through the command line
 * 
*/

#include "opencv2/core.hpp"            // for OpenCV core data types
#include "opencv2/core/utility.hpp"    // for cv::CommandLineParser
#include "opencv2/imgcodecs.hpp"       // for cv::imread() and cv::imencode()

#include "UtilityFunctions/utility_functions.h"

#include <iostream>
#include <vector>
#include <algorithm> // for std::find, std::copy
#include <string>
#include <tuple>
#include <fstream>   // for std::ofstream
#include <iterator>  // std::ostream_iterator
#include <filesystem> // for file structures

//////////////////////////// Function Declarations ////////////////////////////

using namespace std::string_literals; // allows easy access to the std::string suffix 's'
                                      // This allows us to easily convert string literals to std::string

// Image file formats we can handle
const std::string commonOpenCVImageFileFormats[] { "jpeg"s, "jpg"s, "jp2"s, "png"s, "webp"s, "tiff"s };

/**
 * @brief Write the contents of a std::vector<unsigned char> image buffer to file
 * 
 * @param filePath full path to save data to including image file extension
 * @param buffer std::vector<unsigned char>
 */
void writeVectorBufferToFile(const std::string& filePath, std::vector<uchar>& buffer);


/**
 * @brief Return the cv::ImwriteFlag and best quality compression value for an appropriate image file extension
 * 
 * @param fileExtension image file extension
 * @return std::tuple [cv::ImwriteFlag, int] - the compression flag and best quality compression value
 */
std::tuple<cv::ImwriteFlags, int> imageWriteFlag(const cv::String& fileExtension);

//-------------------------- End of Function Declarations ---------------------//


int main(int argc, char* argv[])
{
    ////////////////////////// 1. Extract CommandLine Arguments /////////////////////
    
    /*
     * Define the command line arguments 
     * We need 3 arguments:
     *      1. Full path to image to be compressed 
     *      2. Full path to directory to save compressed file
     *      3. Name of compressed file without a file extension
     * 
    */
    const cv::String keys = 
        "{help h usage ? | | Compress an image into a character buffer }"
        "{image | <none> | full path to image to be compressed }"
        "{dirPath | <none> | full path to directory to save compressed file }"
        "{fileName| <none> | name of compressed file (including file extension) }";

    // Define a cv::CommandLineParser object
    cv::CommandLineParser parser(argc, argv, keys);

    // We also want to display a message about the program
    parser.about("\nCompress an image"
                 "\nCodec used during compression depends on the file extension provided by the user."
                 "\nAcceptable file extensions are png, jpeg, jpg, jp2, webp or tiff.\n");
    parser.printMessage();

    // Now lets extract our command line arguments
    cv::String imagePath = parser.get<cv::String>("image");
    cv::String saveDirectoryPath = parser.get<cv::String>("dirPath");
    cv::String fileName = parser.get<cv::String>("fileName"); 

    // check for any errors encountered 
    if(!parser.check())
    {
        parser.printErrors();

        return -1;
    }

    /////////////////////////// 2. Check Validity of File Extension //////////////////////////

    // Since our application is only handling a few file extensions, we just need to make sure
    // the user has provided an extension we can handle.

    // a. Extract file extension without the leading dot
    std::string ext { CPP_CV::ReadWriteFiles::getFileExtension(fileName)};

    // b. Find the file extension from array with image file formats we can handle
    auto found { std::find(std::begin(commonOpenCVImageFileFormats), 
                           std::end(commonOpenCVImageFileFormats), 
                           ext
                          ) 
               };

    // c. If the extension is not valid we provide an error message and exit program
    if (found == std::end(commonOpenCVImageFileFormats))
    {
        std::cout << "\nThis application cannot handle such an image file format." 
                  << "Acceptable file extensions are png, jpeg, jpg, jp2, webp or tiff.\n";

        return -1;
    } 
    
    /////////////////////////// 3. Read Image and Encode /////////////////////////////

    // a. Check if we have an image reader/codec before attempting to read the file
    if (!cv::haveImageReader(imagePath))
    {
        std::cout << "\nCannot read input image file: " << imagePath << '\n';

        return -1;
    }

    // b. Use cv::imread() to read an image file as is and save the image as a cv::Mat array
    cv::Mat image { cv::imread(imagePath, cv::IMREAD_UNCHANGED) };    

    // check if image is empty
    if (image.empty())
    {
        std::cerr << "Image file is empty: " << imagePath << '\n';

        return -1;
    } 

    
    // c. Let's set up our compression parameters

    // These will be saved in std::vector as alternating values (parameterID, parameter value)
    std::vector<int> compression_params;

    // get parameterID and parameter value
    auto [parameterID, parameterValue] = imageWriteFlag(ext); // from C++17 onwards
    compression_params.push_back(parameterID); // add parameterID
    compression_params.push_back(parameterValue); // add parameter value

    // d. Since we now have all our parameters checked out we can now compress our image
    //    We will do it in a try...catch block as it might fail

    // Let's create a character buffer to store our compressed image
    std::vector<uchar> imageBuffer;
    
    bool result = false; // Keeps track of whether we have successfully compressed our image

    // we need to add a dot to our file extension before using it in cv::imencode()
    ext = "."s + ext; 
    
    try {
        result = cv::imencode(ext, image, imageBuffer, compression_params);
    } 
    catch (const cv::Exception& ex)
    {
        std::cerr << "\nError compressing image: " << ex.what();
    }

    ///////////////////////////// 4. Save Image Buffer to File /////////////////////


    // If we have successfully compressed our image we can save our buffer as a file
    if(result)
    {
        std::cout << "\nImage successfully compressed.\n";

        /* 
        * Join directory and file name to establish full path to save compressed image to.
        *
        * std::filesystems has the operator '/=', which allows you to create paths 
        * to sub-directories or files. This is done by automatically appending seperators
        * that are appropriate to the underlying operating system
        */
        std::filesystem::path savePath {saveDirectoryPath}; // Directory to save image to
        savePath /= fileName; // Directory + file name == Full file path
        
        // Save buffer to file
        writeVectorBufferToFile(savePath, imageBuffer);

    }
    else 
    {
        std::cerr << "\nError: Could not compress image file.\n";
    }

    std::cout << '\n';

    return 0;
}

/////////////////////// Function Definitions ///////////////////////

/**
 * @brief Return the cv::ImwriteFlag and best quality compression value for 
 *        images with file extensions jpg, jpeg, jp2, png, webp and tiff
 * 
 * @param fileExtension image file extension (without the leading dot/period)
 * @return std::tuple [cv::ImwriteFlag, int] - the compression flag and best quality compression value
 */
std::tuple<cv::ImwriteFlags, int> imageWriteFlag(const cv::String& fileExtension)
{
    if (fileExtension == "jpeg"s || fileExtension == "jpg"s) return { cv::IMWRITE_JPEG_QUALITY, 95 };
    else if (fileExtension == "png"s) return { cv::IMWRITE_PNG_COMPRESSION, 5 };
    else if (fileExtension == "jp2"s) return { cv::IMWRITE_JPEG2000_COMPRESSION_X1000, 1000 };
    else if (fileExtension == "webp"s) return { cv::IMWRITE_WEBP_QUALITY, 45 };
    else if (fileExtension == "tiff"s) return { cv::IMWRITE_TIFF_COMPRESSION, 5 };    
}


/**
 * @brief Write the contents of a std::vector<unsigned char> image buffer to file
 * 
 * @param filePath full path to save data to including image file extension
 * @param buffer std::vector<unsigned char>
 */
void writeVectorBufferToFile(const std::string& filePath, std::vector<uchar>& buffer)
{
    // Create an output stream to write 
    std::ofstream file(filePath, std::ios::out);

    // Use the copy algorithm, to copy our vector contents to a output iterator that will write 
    // them to our file
    std::copy(buffer.cbegin(), buffer.cend(), std::ostream_iterator<unsigned char>(file));
}
```

**Output**

:notebook_with_decorative_cover: We compressed the following `png` image using 4 different codecs `jpg`, `jp2`, `webp` and `tiff`.

**Figure 1** - Image to compress

![Image to compress](./images/color_image.png)

:notebook_with_decorative_cover: On my computer the original image had a file size of 93,587 bytes. After compression we got the following results:

| Codec/Image file extension | File size (bytes)|
|--- | --- |
| jpg | 22, 696 |
| jp2 | 90, 525 |
| webp | 6, 886|
| tiff | 94, 200| 

:notebook_with_decorative_cover: From the table above we can conclude the following:

1. `webp` reduces the file size significantly compared to other file extensions followed by `jpg`. These are examples **lossy compression** codecs or algorithms in that some data will be lost during compression. 
2. `jp2` (JPEG 2000) codec tries to reduce loss of the original data as much as possible hence the file size has not significantly been reduced.
3. `tiff` is mostly used if you want to retain the most amount of data. It acts as a container in which you place the original image data and it will maintain the state of that data. You can see this in that the file size seems to have increased. You could argue the other bytes are occupied by the container itself.


## References

1. https://en.wikipedia.org/wiki/Lossless_compression
2. https://en.wikipedia.org/wiki/Lossy_compression
3. https://en.wikipedia.org/wiki/Portable_Network_Graphics
4. https://en.wikipedia.org/wiki/GIF
5. https://en.wikipedia.org/wiki/Run-length_encoding
6. https://en.wikipedia.org/wiki/Huffman_coding
7. https://en.wikipedia.org/wiki/JPEG
8. https://cs.stanford.edu/people/eroberts/courses/soco/projects/data-compression/lossy/mp3/index.htm
9. https://en.wikipedia.org/wiki/Discrete_cosine_transform
10. https://en.wikipedia.org/wiki/Quantization_(image_processing)