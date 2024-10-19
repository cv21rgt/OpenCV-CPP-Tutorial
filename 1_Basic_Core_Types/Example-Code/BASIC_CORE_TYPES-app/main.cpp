#include "opencv2/core.hpp" // header file with OpenCV core types
#include <iostream>
#include <iomanip>

int main()
{

    //                            Instantiating cv::Matx<> Objects
    //                            =================================

    // 1. Default constructors

    // a. uses the default constructor to create a 1(rows) x 2(columns) matrix 
    //    filled with zeros of data type 'double'
    const cv::Matx12d default_m1 {};  

    // b. uses the default constructor to create a (2 x 2) matrix, 
    //    i.e. 2 rows & 2 columns filled with zeros of data type 'double'
    const cv::Matx22d default_m2 {};  

    // c. uses the default constructor to create a (4 x 3) matrix, 
    //    i.e. 4 rows & 3 columns filled with zeros of data type 'float'
    const cv::Matx43f default_m3 {};  

    
    // 2. Value constructors

    // a. 2 x 1 matrix - make sure the number of values you provide 
    //    can be made into a 2 x 1 matrix
    const cv::Matx21f m2 {1.2f, 2.2f};  

    // b. 2 x 2 matrix - make sure the number of values you provide 
    //    can be made into a 2 x 2 matrix 
    const cv::Matx22d m3 {1, 2, 3, 4}; 

    
    // 3. Copy constructor to copy one matrix to another
    const cv::Matx22d m4(m3);

    /* 
     * 4. cv::Matx<> also provides functions that help in creating commonly used fixed matrices
     * e.g. Matrix of zeros, matrix whose elements are all identical, matrix of ones.
     * This helps in that you don't have to manually type the values yourself
     * 
    */

    // 3x3 matrix whose elements are all equal to the value 2
    const cv::Matx33f m5 {cv::Matx33f::all(2)};  

    const cv::Matx23d m6 {cv::Matx23d::zeros()}; // 2x3 matrix of zeros

    const cv::Matx22d m7 {cv::Matx22d::ones()};  // 2x2 matrix of ones

    const cv::Matx33f m8 {cv::Matx33f::eye()};   // 3x3 unit matrix

    // 2x2 matrix with normally distributed values given the 'mean' & 'variance'
    const float mean     {2.3};
    const float variance {1.2};
    const cv::Matx22f m9 {cv::Matx22f::randn(mean, variance)}; 
    
    // 3x3 matrix with uniformly distributed values within the range defined by the 'min' and 'max' values
    const float min {10.0f};
    const float max {20.0f};
    const cv::Matx33f m10 {cv::Matx33f::randu(min, max)}; 

    //                                Printing cv::Matx<> objects
    //                                ============================

    std::cout << "\n****************** Printing cv::Matx<> objects ****************************\n";

        
    // 1. Use the Default `R` format. This is the format used by the statistical 
    //    programming language `R`
    std::cout << "\ndefault_m1 (1 x 2) matrix (Default 'R' format) : " << '\n' 
              << default_m1 << '\n';

    // 2. Use the format used by the Python programming language
    std::cout << "\nm2 (2 x 1) matrix (Python format) : " << '\n' 
              << cv::format(m2, cv::Formatter::FMT_PYTHON) << '\n';

    // 3. Use the format used by CSV files
    std::cout << "\nm3 (2 x 2) matrix (CSV format) : " << '\n' 
              << cv::format(m3, cv::Formatter::FMT_CSV) << '\n';

    // 4. Use the format used by the `MATLAB` software package
    std::cout << "\nm4 (2 x 2) matrix (MATLAB format) : " << '\n' 
              << cv::format(m4, cv::Formatter::FMT_MATLAB) << '\n';

    // 5. Use the format used by the Python NumPy package
    std::cout << "\nm5 (3 x 3) matrix with identical elements (NumPy format) : " << '\n' 
              << cv::format(m5, cv::Formatter::FMT_NUMPY) << '\n';

    // 6. Use the format used in the C language - uses curly braces
    std::cout << "\nm6 (2 x 3) matrix of Zeros (C format) : " << '\n' 
              << cv::format(m6, cv::Formatter::FMT_C) << '\n';

    std::cout << "\nm7 (2 x 2) matrix of Ones : \n" << m7 << '\n';

    std::cout << "\nm8 (3 x 3) unit matrix : \n" << m8 << '\n';    
   
    std::cout << "\nm9 (2 x 2) matrix with normally distributed values given the mean =  " << mean
              << " & variance = " << variance << " : \n" 
              << m9 << '\n';
    std::cout << "\nm10 (3 x 3) matrix with uniformly distributed values within the range defined by min = " << min
              << " and max = " << max << " : \n" << m10 << '\n';    

    std::cout << '\n';

    return 0;

}