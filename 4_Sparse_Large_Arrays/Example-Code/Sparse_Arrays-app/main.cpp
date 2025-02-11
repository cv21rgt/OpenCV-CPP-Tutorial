#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h"     // Header file with our own functions we have written
#include <iostream>

int main()
{
    // We will use each of the 4 constructors to create a cv::SparseMat object

    // 1. Use the Default constructor to create a sparse array without initialization

    cv::SparseMat sm {}; // non-template version

    cv::SparseMat_<float> smTemplate {}; // template version
    
    // 2. Create an n-Dimensional sparse array with dimensions given by an C-style array 
    //    and also providing the data type of the underlying elements
    
    const int noOfDimensions { 2 }; // 2-D array
    const int arrayDimensions[] { 10, 10}; // dimensions (rows, columns) for a 10x10 2D array
    
    cv::SparseMat sm1 {noOfDimensions, arrayDimensions, CV_32F}; // non-template form

    cv::SparseMat_<float> sm1Template { noOfDimensions, arrayDimensions }; // template form
    
    
    // 3. Create a new sparse matrix that is a copy of an existing sparse array

    cv::SparseMat sm2(sm1); // create a new array from another existing array

    cv::SparseMat_<float> sm2Template(sm1Template); // use the template format

    // copy from a non-template sparse array to a template 
    // form -  as long as the data types match
    cv::SparseMat_<float> non_TemplateToTemplateCopy(sm1); 

   
    // 4. Create a new sparse array from an existing dense cv::Mat array

    cv::Mat m1 { cv::Size(10, 10), CV_32F }; // a 10 x 10 cv::Mat dense array

    cv::SparseMat sm3(m1); // copy from an existing dense cv::Mat object

    cv::SparseMat_<float> sm3Template(m1); // copy from an existing cv::Mat object

    std::cout << '\n';

    return 0;
}