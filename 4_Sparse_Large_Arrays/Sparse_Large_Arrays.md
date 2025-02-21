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

### Filling a cv::SparseMat Array with Elements

:notebook_with_decorative_cover: The above example shows how to create `cv::SparseMat` arrays. However, the arrays are all empty. To populate or fill a `cv::SparseMat` array we use the function `cv::SparseMat::ref<>()`. The presence of *angled brackets* (<>) means it is a template function.

:notebook_with_decorative_cover: `cv::SparseMat::ref<>()` was mainly designed as an accessor template function used to return **a valid reference** to an element in an array. If you are familiar with <a href = "https://www.learncpp.com/cpp-tutorial/lvalue-references/">references</a> in C++, you know that you can use a reference to **read or modify** the object being referenced. In the case of populating a `cv::SparseMat` array, we take advantage of the fact that we can use a reference to *modify a value*.

:notebook_with_decorative_cover: `cv::SparseMat::ref<>()` always returns a valid reference. If the element did not exist, it is created and initialized with the value `0`. OpenCV provides 4 variations of `cv::SparseMat::ref<>()`:

1. `T& cv::SparseMat::ref(int i0, cv::size_t* hashval = 0)` - Returns a read-write reference to the specified sparse matrix element at index `i0`. This function is for 1D arrays. The parameter `hashval` is a hash key needed to *access* the element at index `i0`. You only need this parameter when accessing elements - hence we will expand on it in another section. For populating an array use the default value. The following code shows a function you can use to create and fill a 1-Dimensional `cv::SparseMat` from data contained in a std::vector. 

```c++
/**
 * @brief Create fill a 1-Dimensional sparse array with data from a std::vector
 * 
 * @tparam T Data type of values in std::vector container
 * @param size0fDimensions C-style array containing size of Sparse array. Array should contain 
 *                         only 1 value as we are creating a 1-Dimensional array
 * @param dataType OpenCV data type of values in Sparse array e.g. 'CV_32F' or integer value '5' 
 *                 if you want your array to contain 32-bit floating-point values
 * @param vec std::vector with input values used to create our Sparse array. Data type should  
 *            be e.g. 'float' for a sparse array whose 'dataType == 'CV_32F' OR 'double' for 
 *            a sparse array whose 'dataType == CV_64F'
 * @return cv::SparseMat - A 1-Dimensional sparse array 
 */
template <typename T>
cv::SparseMat fill1DSparseArray(const int* size0fDimensions, int dataType, const std::vector<T>& vec)
{
    // Create an empty 1-Dimensional cv::SparseArray
    cv::SparseMat sparseArray { 1, size0fDimensions, dataType };

    int i0 {0}; // Sparse array index counter

    // Loop through elements in C++ std::vector
    for (const T& element : vec)
    {   
        // Get reference to Sparse array value at index 'i0', then override it with
        // value from C++ container    
        sparseArray.ref<T>(i0) += element; 

        ++i0; // increment index counter
    }

    return sparseArray;
}
```

:notebook_with_decorative_cover: The function above is a template function and because we may need it in future tutorials or projects we will add it to our own library (**utility_functions_library**) we are currently creating. When dealing with template functions which you want to use in multiple files, add their full definition in the header file (*Example-Code/include/UtilityFunctions/utility_functions.h*) - see notes <a href = "https://www.learncpp.com/cpp-tutorial/using-function-templates-in-multiple-files/">here</a> for the reasoning behind it. Before we add the function, we will create another namespace called **SparseArrays** inside our main namespace **CPP_CV**. We can then access this function as `CPP_CV::SparseArrays::fill1DSparseArray()` as in the following example.

**Example 2**

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h" // Header file with our own functions we have written
#include <iostream>
#include <vector>

int main()
{
    // We want to store the following values in a sparse array
    const std::vector<float> data { 1, 0, 0, 2, 0, 4, 1, 0, 0, 0, 
                    5, 0, 0, 0, 3, 0, 4, 0, 0, 5, 
                    7, 0, 0, 0, 0, 0, 0, 0, 2, 6, 
                    0, 0, 2, 0, 7, 0, 0, 4, 0, 0, 
                    0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 
                    0, 3, 4, 0, 0, 0, 0, 0, 5, 6, 
                    7, 0, 0, 0, 0, 0, 0, 0, 8, 0, 
                    0, 0, 0, 0, 3, 0, 0, 9, 0, 4, 
                    0, 8, 0, 0, 0, 2, 0, 0, 0, 2, 
                    0, 0, 0, 0, 5, 7, 3, 5, 0, 8 }; 

    // Our 1-D sparse array will have the following size
    const int sizeOfDimension[] { 100 }; 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm4  = CPP_CV::SparseArrays::fill1DSparseArray(sizeOfDimension, CV_32F, data); 
    
    //Print some relevant information about our sparse array
    std::cout << "No. of Dimensions = " << sm4.dims() << '\n';
    std::cout << "Data type of values = " 
              << CPP_CV::General::openCVDescriptiveDataType(sm4.type()) << '\n';
    std::cout << "Size of array= " << *(sm4.size()) << '\n';

    // Create a template form of the same array
    cv::SparseMat_<float> sm5 = CPP_CV::SparseArrays::fill1DSparseArray(sizeOfDimension, CV_32F, data);

    std::cout << '\n';

    return 0;
}
```

**Output**

    No. of Dimensions = 1
    Data type of values = CV_32F or CV_32FC1 -> Array with 1 channel and primitive data type 32-bit decimal values of type float with range (-3.40282347E+38 to 3.40282347E+38)
    Size of array= 100

2. `T& cv::SparseMat::ref(int i0, int i1, cv::size_t* hashval = 0)` - Used for 2D arrays. Requires two indices (`i0` and `i1`) for the element in question. The rest of the parameters have the same meaning as above. The following code shows a template function you can use to create and fill a 2-Dimensional `cv::SparseMat` from data contained in a std::vector.

```c++
/**
 * @brief Create and fill a 2-Dimensional sparse array from a std::vector
 * 
 * @tparam T Data type of values in std::vector container
 * @param size0fDimensions C-style array containing size of Sparse array. Array should contain 
 *                         2 values for the size of each dimension in a 2-D array.
 * @param dataType OpenCV data type of values in Sparse array e.g. 'CV_32F' or integer value '5' 
 *                 if you want your array to contain 32-bit floating-point values
 * @param vec A 1-Dimensional std::vector with input values used to create our Sparse array. Data type should  
 *            be e.g. 'float' for a sparse array whose 'dataType == 'CV_32F' OR 'double' for 
 *            a sparse array whose 'dataType == CV_64F'. No. of elements in std::vector should 
 *            be enough to convert to the 2-D array you want. For example, a 16 element std::vector 
 *            can get you a 2x8, 4x4 or 8x2 2-D sparse array.
 * @return cv::SparseMat - A 2-Dimensional sparse array 
 */
template <typename T>
cv::SparseMat fill2DSparseArray(const int* size0fDimensions, int dataType, const std::vector<T>& vec)
{
    // Create an empty 2-Dimensional cv::SparseArray
    cv::SparseMat sparseArray { 2, size0fDimensions, dataType };

    // std::vector index counter
    // Keep note of the data type of a std::vector index counter
    std::size_t i {0}; 
    
    // Since we are dealing with a 2-D array we need two loops
    // to access each index location
    for (int i0 {0}; i0 < size0fDimensions[0]; ++i0)
    {
        for (int i1 {0}; i1 < size0fDimensions[1]; ++i1)
        {
            // Get reference to 2-D Sparse array value at index (i0, i1), 
            // then override it with value from std::vector    
            sparseArray.ref<T>(i0, i1) += vec[i];

            ++i; // increment std::vector index counter
        }
    }  
    
    return sparseArray;
}
```
:notebook_with_decorative_cover: We also add the above template function to our header file under the namespace **SparseArrays** inside our main namespace **CPP_CV**. We can then access this function as `CPP_CV::SparseArrays::fill2DSparseArray()` as in the following example.

**Example 3**

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h" // Header file with our own functions we have written
#include <iostream>
#include <vector>

int main()
{
    // We want to store the following values in a sparse array
    const std::vector<double> data { 1, 0, 0, 2, 0, 4, 1, 0, 0, 0, 
                    5, 0, 0, 0, 3, 0, 4, 0, 0, 5, 
                    7, 0, 0, 0, 0, 0, 0, 0, 2, 6, 
                    0, 0, 2, 0, 7, 0, 0, 4, 0, 0, 
                    0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 
                    0, 3, 4, 0, 0, 0, 0, 0, 5, 6, 
                    7, 0, 0, 0, 0, 0, 0, 0, 8, 0, 
                    0, 0, 0, 0, 3, 0, 0, 9, 0, 4, 
                    0, 8, 0, 0, 0, 2, 0, 0, 0, 2, 
                    0, 0, 0, 0, 5, 7, 3, 5, 0, 8 }; 

    // Each dimension of our sparse array will have the following sizes
    const int arrayDims[] { 10, 10 }; // a 10x10 array
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm4  = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data);     
    
    std::cout << "No. of Dimensions = " << sm4.dims() << '\n';
    std::cout << "Data type of values = " 
              << CPP_CV::General::openCVDescriptiveDataType(sm4.type()) << '\n';
    std::cout << "Size of array= " << sm4.size(0) << " x " << sm4.size(1) << '\n';

    // Create a template form of the same array
    cv::SparseMat_<double> sm5 = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data);
    std::cout << "No. of Dimensions = " << sm5.dims() << '\n';
    std::cout << "Data type of values = " 
              << CPP_CV::General::openCVDescriptiveDataType(sm5.type()) << '\n';
    std::cout << "Size of array= " << sm4.size(0) << " x " << sm4.size(1) << '\n';
    
    std::cout << '\n';

    return 0;
}
```

**Output**

    No. of Dimensions = 2
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array= 10 x 10

    No. of Dimensions = 2
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array= 10 x 10

3. `T& cv::SparseMat::ref(int i0, int i1, int i2, cv::size_t* hashval = 0)` - Used for 3D arrays. This requires 3 indices, `i0`, `i1` and `i2`. The rest of the parameters have the same meaning as above. The following code shows a template function you can use to create and fill a 3-Dimensional `cv::SparseMat` from data contained in a std::vector. 

```c++
/**
 * @brief Create and fill a 3-Dimensional sparse array from a std::vector
 *  
 * @tparam T Data type of values in std::vector container
 * @param size0fDimensions C-style array containing size of Sparse array. Array should contain 
 *                         3 values for the size of each dimension in a 3-D array.
 * @param dataType OpenCV data type of values in Sparse array e.g. 'CV_32F' or integer value '5' 
 *                 if you want your array to contain 32-bit floating-point values
 * @param vec A 1-Dimensional std::vector with input values used to create our Sparse array. Data type should  
 *            be e.g. 'float' for a sparse array whose 'dataType == 'CV_32F' OR 'double' for 
 *            a sparse array whose 'dataType == CV_64F'. No. of elements in std::vector should 
 *            be enough to convert to the 3-D array you want. For example, a 16 element std::vector 
 *            can get you a 2x2x4, 4x2x2 or 2x4x2 3-D sparse array.
 * @return cv::SparseMat - A 3-Dimensional sparse array 
 */
template <typename T>
cv::SparseMat fill3DSparseArray(const int* size0fDimensions, int dataType, const std::vector<T>& vec)
{
    // Create an empty 3-Dimensional cv::SparseArray
    cv::SparseMat sparseArray { 3, size0fDimensions, dataType };

    // std::vector index counter
    // Keep note of the data type of a std::vector index counter
    std::size_t i {0}; 
    
    // Since we are dealing with a 3-D array we need three loops
    // to access each index location
    for (int i0 {0}; i0 < size0fDimensions[0]; ++i0)
    {
        for (int i1 {0}; i1 < size0fDimensions[1]; ++i1)
        {
            for (int i2 {0}; i2 <size0fDimensions[2]; ++i2)
            {
                // Get reference to 3-D Sparse array value at index (i0, i1, i2), 
                // then override it with value from std::vector    
                sparseArray.ref<T>(i0, i1, i2) += vec[i];
                
                ++i; // increment std::vector index counter
            }
        }
    }  
    
    return sparseArray;
}
```
:notebook_with_decorative_cover: We also add the above template function to our header file under the namespace **SparseArrays** inside our main namespace **CPP_CV**. We can then access this function as `CPP_CV::SparseArrays::fill3DSparseArray()` as in the following example.

**Example 4**

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h" // Header file with our own functions we have written
#include <iostream>
#include <vector>

int main()
{
    // We want to store the following values in a sparse array
    const std::vector<double> data { 1, 0, 0, 2, 0, 4, 1, 0, 0, 0, 
                    5, 0, 0, 0, 3, 0, 4, 0, 0, 5, 
                    7, 0, 0, 0, 0, 0, 0, 0, 2, 6, 
                    0, 0, 2, 0, 7, 0, 0, 4, 0, 0, 
                    0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 
                    0, 3, 4, 0, 0, 0, 0, 0, 5, 6, 
                    7, 0, 0, 0, 0, 0, 0, 0, 8, 0, 
                    0, 0, 0, 0, 3, 0, 0, 9, 0, 4, 
                    0, 8, 0, 0, 0, 2, 0, 0, 0, 2, 
                    0, 0, 0, 0, 5, 7, 3, 5, 0, 8 }; 

    // Each dimension of our sparse array will have the following sizes
    const int arrayDims[] { 10, 5, 2 }; // a 10x5x2 array
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm4  = CPP_CV::SparseArrays::fill3DSparseArray(arrayDims, CV_64F, data); 
    
    std::cout << "\nNo. of Dimensions = " << sm4.dims() << '\n';
    std::cout << "Data type of values = " << CPP_CV::General::openCVDescriptiveDataType(sm4.type()) << '\n';
    std::cout << "Size of array= " << sm4.size(0) << " x " << sm4.size(1) << " x " << sm4.size(2) 
              << '\n';
  
    // Create a template form of the same array
    cv::SparseMat_<double> sm5 = CPP_CV::SparseArrays::fill3DSparseArray(arrayDims, CV_64F, data);
    std::cout << "\nNo. of Dimensions = " << sm5.dims() << '\n';
    std::cout << "Data type of values = " 
              << CPP_CV::General::openCVDescriptiveDataType(sm5.type()) << '\n';
    std::cout << "Size of array= " << sm4.size(0) << " x " << sm4.size(1) << " x " << sm4.size(2) 
              << '\n';
    
    std::cout << '\n';

    return 0;
}
```

**Output**

    No. of Dimensions = 3
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array= 10 x 5 x 2

    No. of Dimensions = 3
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array= 10 x 5 x 2

4. `T& cv::SparseMat::ref(const int* idx, cv::size_t* hashval = 0)` - Mainly used for n-Dimensional cases where `n > 3`, but can also be used in place of the above functions for `n == 1, 2 or 3`. The parameter `idx` is a pointer to a C-style array of integers, which represent the indices of the element in question. This might be confusing for some people especially if they are not comfortable with C-style arrays, hence the need to take a short detour here using a simple example. If dealing with a 2D sparse array and you are interested in element at position (2, 3), you declare your C-style array of element indices as `const int idx[] {2,3};`. By default C-style arrays decay to pointers with the same data type as the original array, hence when passed to our function the data type of `idx` becomes `const int*`. I hope this helps. You can also read this detailed material <a href = "https://www.learncpp.com/cpp-tutorial/introduction-to-c-style-arrays/">here</a> on C-style arrays.  The rest of the parameters have the same meaning as above. The following code shows a template function you can use to create and fill a 4-Dimensional `cv::SparseMat` from data contained in a std::vector. Using this function you can adapt it to create your own 5-Dimensional or higher sparse arrays. 

```c++
/**
 * @brief Create and fill a 4-Dimensional sparse array from a std::vector
 * 
 * @tparam T Data type of values in std::vector container
 * @param size0fDimensions C-style array containing size of Sparse array. Array should contain 
 *                         4 values for the size of each dimension in a 4-D array.
 * @param dataType OpenCV data type of values in Sparse array e.g. 'CV_32F' or integer value '5' 
 *                 if you want your array to contain 32-bit floating-point values
 * @param vec A 1-Dimensional std::vector with input values used to create our Sparse array. Data type should  
 *            be e.g. 'float' for a sparse array whose 'dataType == 'CV_32F' OR 'double' for 
 *            a sparse array whose 'dataType == CV_64F'. No. of elements in std::vector should 
 *            be enough to convert to the 4-D array you want. For example, a 100 element std::vector 
 *            can get you a 2x2x5x5 or 5x2x5x2 4-D sparse array.
 * @return cv::SparseMat - A 4-Dimensional sparse array 
 */
template <typename T>
cv::SparseMat fill4DSparseArray(const int* size0fDimensions, int dataType, const std::vector<T>& vec)
{
    // Create an empty 4-Dimensional cv::SparseArray
    cv::SparseMat sparseArray { 4, size0fDimensions, dataType };

    // std::vector index counter
    // Keep note of the data type of a std::vector index counter
    std::size_t i {0}; 
    
    // Since we are dealing with a 4-D array we need 4 'for' loops
    // to access each index location
    for (int i0 {0}; i0 < size0fDimensions[0]; ++i0)
    {        
        for (int i1 {0}; i1 < size0fDimensions[1]; ++i1)
        {
            for (int i2 {0}; i2 < size0fDimensions[2]; ++i2)
            {
                for (int i3 {0}; i3 < size0fDimensions[3]; ++i3)
                {
                    // Create C-style array to hold indices for Sparse Array
                    int idx[4];

                    // Fill above array with index values
                    idx[0] = i0;
                    idx[1] = i1;
                    idx[2] = i2;
                    idx[3] = i3;
                    
                    // Un-comment the following two lines if you want to see what the 
                    // indices for a 4-D array look like
                    //std::cout << "(" << idx[0] << ", " << idx[1] << ", " 
                    //          << idx[2] << ", " << idx[3] << ")\n";

                    // 1. Get reference to an empty 4-D Sparse array value. Index values 
                    //    are provided in a C- style array 'idx' 
                    // 2. Override empty index value with value from std::vector    
                    sparseArray.ref<T>(idx) += vec[i];
    
                    ++i; // increment std::vector index counter
                }              
            }          
        }
    }  
    
    return sparseArray;
}
```

:notebook_with_decorative_cover: We also add the above template function to our header file under the namespace **SparseArrays** inside our main namespace **CPP_CV**. We can then access this function as `CPP_CV::SparseArrays::fill4DSparseArray()` as in the following example. 

**Example 5**

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h"  // Header file with our own functions we have written
#include <iostream>
#include <vector>

int main()
{
    // We want to create a sparse array from the following data
    const std::vector<double> data { 1, 0, 0, 2, 0, 4, 1, 0, 0, 0, 
                    5, 0, 0, 0, 3, 0, 4, 0, 0, 5, 
                    7, 0, 0, 0, 0, 0, 0, 0, 2, 6, 
                    0, 0, 2, 0, 7, 0, 0, 4, 0, 0, 
                    0, 0, 0, 1, 1, 2, 0, 0, 0, 0, 
                    0, 3, 4, 0, 0, 0, 0, 0, 5, 6, 
                    7, 0, 0, 0, 0, 0, 0, 0, 8, 0, 
                    0, 0, 0, 0, 3, 0, 0, 9, 0, 4, 
                    0, 8, 0, 0, 0, 2, 0, 0, 0, 2, 
                    0, 0, 0, 0, 5, 7, 3, 5, 0, 8 };
    

    // Provide size of each dimension in a C-styloe array
    const int arrayDims[] { 2, 2, 5, 5 }; // 2x2x5x5 4-D array 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm4  = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims, CV_64F, data); 
    
    // Print some relevant information about sparse array
    std::cout << "\nNo. of Dimensions = " << sm4.dims() << '\n';
    std::cout << "Data type of values = " << CPP_CV::General::openCVDescriptiveDataType(sm4.type()) << '\n';
    std::cout << "Size of array= " << sm4.size(0) << " x " << sm4.size(1) 
              << " x " << sm4.size(2) << " x " << sm4.size(3) << '\n';
        
    // Create a template form of the same array
    cv::SparseMat_<double> sm5 = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims, CV_64F, data);
    std::cout << "\nNo. of Dimensions = " << sm5.dims() << '\n';
    std::cout << "Data type of values = " 
              << CPP_CV::General::openCVDescriptiveDataType(sm5.type()) << '\n';
    std::cout << "Size of array= " << sm5.size(0) << " x " << sm5.size(1) 
              << " x " << sm5.size(2) << " x " << sm5.size(3) << '\n';

    std::cout << '\n';

    return 0;
}
```
**Output**

    No. of Dimensions = 4
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array= 2 x 2 x 5 x 5   

    No. of Dimensions = 4
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array= 2 x 2 x 5 x 5