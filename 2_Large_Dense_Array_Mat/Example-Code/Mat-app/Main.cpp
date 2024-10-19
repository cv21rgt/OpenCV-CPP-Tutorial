#include "opencv2/core.hpp"
#include <UtilityFunctions/utility_functions.h>     // header file with function that returns full description of OpenCV data types
#include <iostream>
#include <vector>
#include <array>

int main()
{

    //                                 Use Default Constructor
    //                                 =======================

    // Use a default constructor to create a cv::Mat arrays
    cv::Mat default_m;
    cv::Mat default_m1;
    cv::Mat default_m2;
    cv::Mat default_m3;                  

    //    You can then use the functions create() & setTo() 
    //    to assign size, data and data type

    // 1. Use the function 'void create(int rows, int cols, int type)'

    // Create 2D array that has 3 rows and 10 columns. 
    // The array has 1 Channel
    // Primitive data type is 32-bit floats
    default_m.create(3, 10, CV_32F);    

    // We will use cv::Scalar to set all the values in the array to 1.5
    default_m.setTo(cv::Scalar(1.5f));

    std::cout << "\ncv::Mat array that has 3 rows and 10 columns. " 
              << "\nPrimitive data type is 32-bit floats. " 
              << "\nAll values have been set to 1.5 = \n" << default_m << '\n';

    // 2. Use the function 'void create(cv::Size size, int type)'

    // Create 2D array that has 5 rows and 6 columns. 
    // The array has 1 Channel
    // Primitive data type is 8-bit unsigned
    default_m1.create(cv::Size(6, 5), CV_8U);
    default_m1.setTo(cv::Scalar(10)); // All values are set to '10'
    std::cout << "\ncv::Mat array that has 5 rows and 6 columns. " 
              << "\nPrimitive data type is 8-bit unsigned integers. " 
              << "\nAll values have been set to 10 = \n" << default_m1 << '\n';

    // 3. Use the function 'void create(const std::vector<int>& sizes, int type)'

    // Create 2D array that has 2 rows and 12 columns. 
    // The array has 1 Channel
    // Primitive data type is 64-bit floats
    const std::vector<int> shape {2, 12};
    default_m2.create(shape, CV_64F);
    default_m2.setTo(cv::Scalar(0.05)); // All values are set to '0.05'
    std::cout << "\ncv::Mat array that has 2 rows and 12 columns. " 
              << "\nPrimitive data type is 64-bit floats. " 
              << "\nAll values have been set to 0.05 = \n" << default_m2 << '\n';

    // 4. Use the function 'void create(int ndims, const int* sizes, int type)'
    // Create 2D array that has 3 rows and 4 columns. 
    // The array has 1 Channel
    // Primitive data type is 16-bit signed
    const int ndims {2};
    const int sizes[] {3, 4};
    default_m3.create(ndims, sizes, CV_16S);
    default_m3.setTo(cv::Scalar(12)); // All values set to `12`
    std::cout << "\ncv::Mat array that has 3 rows and 4 columns. " 
              << "\nPrimitive data type is 16-bit signed integers. " 
              << "\nAll values have been set to 12 = \n" << default_m3 << '\n';
   
    std::cout << '\n';
    
    return 0;
}