#include "opencv2/core.hpp"
#include <UtilityFunctions/utility_functions.h>     // header file with function that returns full description of OpenCV data types
#include <iostream>

int main()
{
    float testData[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
    const cv::Mat testMat { 3, 3, CV_32F, testData };     

    int arrayDimensions = testMat.dims;       // no. of dimenions of array
    int noRows          = testMat.rows;       // no. of rows in array
    int noColumns       = testMat.cols;       // no. of columns in array
    int noChannels      = testMat.channels(); // no. of channels in array
    int noElements      = testMat.total();    // total no. of elements in array 
    int dataType        = testMat.type();     // data type returned as an integer

    std::cout << "\ntestMat array has the following attributes: \n" 
              << "\tNo. of dimensions = " << arrayDimensions 
              << "\n\tNo. of rows     = " << noRows
              << "\n\tNo. of columns  = " << noColumns
              << "\n\tNo. of channels = " << noChannels
              << "\n\tNo. of elements = " << noElements
              << "\n\tData type       = " << CPP_CV::General::openCVDescriptiveDataType(dataType); 


    std::cout << '\n';
    return 0;

}