#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h"     // Header file with our own functions we have written
#include <iostream>
#include <cstdint>               // for std::int8_t - C++ 8-bit signed integer data type


int main()
{
   
    // Create arrays whose data type is 8-bit unsigned integers (0 to 255)
    // ===================================================================

    // 2x2 2D array with all values equal to 15
    const cv::Mat m1 { cv::Size(2, 2), CV_8U, cv::Scalar(15)}; 
    std::cout << "\nm1 = \n" << m1 << '\n';

    // 2x2 2D array with all values equal to 245
    const cv::Mat m2 { cv::Size(2, 2), CV_8U, cv::Scalar(245)}; 
    std::cout << "\nm2 = \n" << m2 << '\n';

    // 2x2 2D array with all values equal to 10
    const cv::Mat m3 { cv::Size(2, 2), CV_8U, cv::Scalar(10)};  
    std::cout << "\nm3 = \n" << m3 << '\n';

    // Operation 1: Overflow
    //              ========

    // m4 expects all values to be 8-bit unsigned in the range 0 to 255 
    cv::Mat m4 {cv::Size(2, 2), CV_8U}; 
    m4 = m1 + m2;   // this operation will result in 'overflow'. 
                    // Any addition that results in a solution out of range, 
                    // is replaced by the minimum (0) or maximum (255) range 
                    // value of the unsigned data type
    std::cout << "\n(m1 + m2) shows saturation casting applied to 'overflow' = \n" 
              << m4 << '\n';

    // Operation 2: Underflow
    //              =========

    // m5 expects all values to be 8-bit unsigned in the range 0 to 255
    cv::Mat m5 { cv::Size(2, 2), CV_8U}; 
    m5 = m3 - m1;   // this operation will result in 'undeflow'
                    // Any subtraction that results in a solution out of range, 
                    // is replaced by the minimum (0) or maximum (255) range 
                    // value of the unsigned data type
    std::cout << "\n(m3 - m1) shows saturation casting applied to 'underflow' = \n" 
              << m5 << '\n';

     // Operation 3: Underflow and Overflow
     //              ======================

    // C-style array with 8-bit signed integers
    std::int8_t a1[] { -36, -125, -48, 52, -75, 78, 109, -119, 54 }; 

    // Use data from above C-style array to create a 2D cv::Mat 3X3 array whose 
    // values are 8-bit signed integers, range (-128 to 127)
    const cv::Mat m6 { cv::Size(3, 3), CV_8S, a1 }; 
    std::cout << "\nm6  = \n" << m6 << '\n';
    std::cout << "\n m6 data type = " 
              << CPP_CV::General::openCVDescriptiveDataType(m6.type()) << '\n';

    // m7 expects all values to be 8-bit signed integers in the range -128 to 127
    cv::Mat m7 { cv::Size(3, 3), CV_8S }; 
    m7 = m6 * 2;    // this will cause both underflow and overflow. Underflow values 
                    // will be replaced by -128 & overflow values by 127
                    // Any multiplication that results in a solution out of range, 
                    // is replaced by the minimum (-128) or maximum (127) range value 
                    // of the 8-bit signed data type

    std::cout << "\n(m6 x 2) shows saturation casting applied to both 'undeflow' and 'overflow' = \n" 
              << m7 << '\n';

   
    // Implement user-defined saturation casting
    // =========================================

    const int a {-36}; 
    const int b {360};

    // 1. Cast '32-bit int' to 'unsigned char'
    auto v1 = (int)cv::saturate_cast<uchar>(a); // This will be clipped to 0 because operation 
                                                // results in an underflow and range for 8-bit 
                                                // unsigned char is 0 to 255
    std::cout << "\nInteger value " << a << " cast to unsigned char = " 
              << v1 << '\n';

    auto v2 = (int)cv::saturate_cast<uchar>(b); // This will be clipped to 255 because operation 
                                                // results in an overflow and range for 8-bit 
                                                // unsigned char is 0 to 255
    std::cout << "\nInteger value " << b << " cast to unsigned char = " 
              << v2 << '\n';

    // 2. Cast '32-bit int' to 'signed char'
    auto v3 = (int)cv::saturate_cast<schar>(a); // This will remain as -36 because it is within 
                                                // range for 8-bit signed char (-128 to 127)
    std::cout << "\nInteger value " << a << " cast to signed char = " 
              << v3 << '\n';

    auto v4 = (int)cv::saturate_cast<schar>(b); // This will be clipped to 127 because operation 
                                                // results in an overflow and range for 8-bit 
                                                // signed char is -128 to 127
    std::cout << "\nInteger value " << b << " cast to signed char = " 
              << v4 << '\n';

    // 3. Cast '32-bit int' to 'short int'
    const int c {33333};
    auto v5 = cv::saturate_cast<short>(c); // input value will be clipped to 32 767 because 
                                           // this is an overflow and range for short integer 
                                           // is -32 768 to 32 767
    std::cout << "\nInteger value " << c << " cast to short integer = " 
              << v5 << '\n';

    // 4. Cast 'float' to '32-bit integer'
    const float d {23456.89765f};
    auto v6 = cv::saturate_cast<int>(d); // input value is float & is therefore 
                                         // rounded to the nearest integer 
    std::cout << "\nFloat value " << d << " cast to 32-bit integer = " 
              << v6 << '\n';

    // 5. Cast 'float' to 'short integer'
    const double e {-33789.000023451234}; // input value is first rounded to the 
                                          // to the nearest integer and then clipped 
                                          // to fall within the range -32 768 to 32 767
    auto v7 = cv::saturate_cast<short>(e);
    std::cout << "\nFloat value " << e << " cast to short integer = " 
              << v7 << '\n';

    std::cout << '\n';
    
    return 0;
}