## Sparse Arrays

:notebook_with_decorative_cover: An array can be defined as **Sparse** when it is very large compared to the number of non-zero entries. Sparse arrays are common in **linear algebra**, for example, a large **identity matrix** is a sparse array when we consider the large number of zero entries compared to non-zero entries. The data used to plot **Histograms** usually contains a large number of empty spaces, making the data a good candidate for a sparse array.

:notebook_with_decorative_cover: The following is an example of an array that can be considered to be **sparse** because of the large number of zero entries compared to non-zero entries.

    [1, 0, 0, 2, 0, 4, 1, 0, 0, 0;
    5, 0, 0, 0, 3, 0, 4, 0, 0, 5;
    7, 0, 0, 0, 0, 0, 0, 0, 2, 6;
    0, 0, 2, 0, 7, 0, 0, 4, 0, 0;
    0, 0, 0, 1, 1, 2, 0, 0, 0, 0;
    0, 3, 4, 0, 0, 0, 0, 0, 5, 6;
    7, 0, 0, 0, 0, 0, 0, 0, 8, 0;
    0, 0, 0, 0, 3, 0, 0, 9, 0, 4;
    0, 8, 0, 0, 0, 2, 0, 0, 0, 2;
    0, 0, 0, 0, 5, 7, 3, 5, 0, 8]

:notebook_with_decorative_cover: Sparse representation therefore means we only store non-zero elements so that we can save a great deal on memory. In any case, most sparse objects are too huge memory wise and make it impractical to store them using dense objects like cv::Mat.

:notebook_with_decorative_cover: One downside of sparse representation is that per-element computations can be slow. However this is usually balanced off by the fact that since we only store relevant data, there can be a great economy in not having to perform a lot of operations using zero or empty entries.

:notebook_with_decorative_cover: OpenCV uses the <a href = "https://docs.opencv.org/4.8.0/dd/da9/classcv_1_1SparseMat.html">cv::SparseMat</a> class to handle sparse arrays. This class works similarly to the large dense array class, cv::Mat. They both support most of the same operations and can handle the same data types. The main difference is how data is organized internally. There is also a template form (<a href = "https://docs.opencv.org/4.8.0/d7/d8a/classcv_1_1SparseMat__.html">cv::SparseMat_</a>) for sparse arrays, which inherits from cv::SparseMat. Remember that when using the template form, you have to specify the underlying data type within angle brackets e.g. **cv::SparseMat_\<float>** when the underlying data type of the array elements is `CV_32F`. Use **cv::SparseMat_\<double>** when the underlying data type of the array elements is `CV_64F`

:notebook_with_decorative_cover: As we have discussed before, internally cv::Mat adopts a C-style data array, where data is sequentially packed and indices are used to access each data value. On the other hand, **cv::SparseMat** uses a <a href = "https://www.geeksforgeeks.org/implementation-of-hash-table-in-c-using-separate-chaining/">hash table</a> to store just the non-zero elements. When the number of elements becomes too large for efficient lookup, the harsh table grows automatically. We will not go into great detail about hash tables as there is a lot of great free material online, including code on how to implement one in various languages. 

### Constructors for creating cv::SparseMat objects

:notebook_with_decorative_cover: The **cv::SparseMat** class provides 4 constructors for creating sparse arrays:

1. `SparseMat()` - This is the Default constructor for creating a sparse array without initialization. 
2. `SparseMat(int n, const int* _sizes, int _type)` - Create an `n` dimensional sparse array with dimensions given by an C-style array `_sizes` and also providing the data type of the underlying elements `_type`.
3. `SparseMat(const SparseMat& m)` - Create a new sparse array that is a copy of an existing sparse array `m`.
4. `SparseMat(const cv::Mat& m)` - Create a new sparse array from an existing dense cv::Mat array `m`.

**Example 1**

```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
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
```