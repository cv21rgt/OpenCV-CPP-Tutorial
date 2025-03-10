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

:notebook_with_decorative_cover: However, as a result of operations on a sparse matrix, some of its stored elements can actually become `0`. It is up to you to detect such elements and delete them using a function like `cv::SparseMat::erase()`. 

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

        // 1. If the element is '0' we erase it from our sparse array
        // because we only want to keep non-zero elements
        // 2. Use 'static_cast' so we compare values of same data type
        if(sparseArray.ref<T>(i0) == static_cast<T>(0))
        {
            const int element_index[] {i0};
                    
            sparseArray.erase(element_index);
        }

        ++i0; // increment index counter
    }

    return sparseArray;
}
```

:notebook_with_decorative_cover: The function above is a template function and because we may need it in future tutorials or projects we will add it to our own library (**utility_functions_library**) we are currently creating. When dealing with template functions which you want to use in multiple files, add their full definition in the header file (*Example-Code/include/UtilityFunctions/utility_functions.h*) - see notes <a href = "https://www.learncpp.com/cpp-tutorial/using-function-templates-in-multiple-files/">here</a> for the reasoning behind it. Before we add the function, we will create another namespace called **SparseArrays** inside our main namespace **CPP_CV**. We can then access this function as `CPP_CV::SparseArrays::fill1DSparseArray()` as in the following example.

**Example 2** - Fill a 1-D sparse array and also print some relevant information such as number of dimensions (use the function `int cv::SparseMat::dims() const`), data type (use the function `int cv::SparseMat::type() const`), size of array (use `int cv::SparseMat::size(int i) const`), and number of non-zero elements (use the function `cv::size_t cv::SpatMat.nzcount() const`).

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
    std::cout << "Size of array = " << *(sm4.size()) << '\n';
    std::cout << "No. of non-zero elements = " << sm4.nzcount() << '\n';

    // Create a template form of the same array
    cv::SparseMat_<float> sm5 = CPP_CV::SparseArrays::fill1DSparseArray(sizeOfDimension, CV_32F, data);

    std::cout << '\n';

    return 0;
}
```

**Output**

    No. of Dimensions = 1
    Data type of values = CV_32F or CV_32FC1 -> Array with 1 channel and primitive data type 32-bit decimal values of type float with range (-3.40282347E+38 to 3.40282347E+38)
    Size of array = 100
    No. of non-zero elements = 34

2. `T& cv::SparseMat::ref(int i0, int i1, cv::size_t* hashval = 0)` - Used for 2D arrays. Requires two indices (`i0` and `i1`) for the element in question. The rest of the parameters have the same meaning as above. The following code shows a template function you can use to create and fill a 2-Dimensional `cv::SparseMat` from data contained in a std::vector. Take note of the fact we use the function `void cv::SpatMat::erase(int i0, int i1, cv::size_t* hashval = 0)` to remove any `0`'s from our sparse array. 


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

            // If the element is '0' we erase it from our sparse array
            // because we only want to keep non-zero elements
            if(sparseArray.ref<T>(i0, i1) == static_cast<T>(0))
            {
                sparseArray.erase(i0, i1);
            }

            ++i; // increment std::vector index counter
        }
    }  
    
    return sparseArray;
}
```
:notebook_with_decorative_cover: We also add the above template function to our header file under the namespace **SparseArrays** inside our main namespace **CPP_CV**. We can then access this function as `CPP_CV::SparseArrays::fill2DSparseArray()` as in the following example.

**Example 3** - Fill a 2-D sparse array and print some relevant information.

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
    std::cout << "Size of array = " << sm4.size(0) << " x " << sm4.size(1) << '\n';
    std::cout << "No. of non-zero elements = " << sm4.nzcount() << '\n';

    // Create a template form of the same array
    cv::SparseMat_<double> sm5 = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data);
    std::cout << "No. of Dimensions = " << sm5.dims() << '\n';
    std::cout << "Data type of values = " 
              << CPP_CV::General::openCVDescriptiveDataType(sm5.type()) << '\n';
    std::cout << "Size of array= " << sm5.size(0) << " x " << sm5.size(1) << '\n';
    std::cout << "No. of non-zero elements = " << sm5.nzcount() << '\n';
    
    std::cout << '\n';

    return 0;
}
```

**Output**

    No. of Dimensions = 2
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array = 10 x 10
    No. of non-zero elements = 34

    No. of Dimensions = 2
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array = 10 x 10
    No. of non-zero elements = 34

3. `T& cv::SparseMat::ref(int i0, int i1, int i2, cv::size_t* hashval = 0)` - Used for 3D arrays. This requires 3 indices, `i0`, `i1` and `i2`. The rest of the parameters have the same meaning as above. The following code shows a template function you can use to create and fill a 3-Dimensional `cv::SparseMat` from data contained in a std::vector. Take note of the fact we use the function `void cv::SpatMat::erase(int i0, int i1, int i2, cv::size_t* hashval = 0)` to remove any `0`'s from our sparse array. 

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

                // If the element is '0' we erase it from our sparse array
                // because we only want to keep non-zero elements
                if(sparseArray.ref<T>(i0, i1, i2) == static_cast<T>(0))
                {
                    sparseArray.erase(i0, i1, i2);
                }
                
                ++i; // increment std::vector index counter
            }
        }
    }  
    
    return sparseArray;
}
```
:notebook_with_decorative_cover: We also add the above template function to our header file under the namespace **SparseArrays** inside our main namespace **CPP_CV**. We can then access this function as `CPP_CV::SparseArrays::fill3DSparseArray()` as in the following example.

**Example 4** - fill a 3-D sparse array and print some relevant information

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
    std::cout << "No. of non-zero elements = " << sm4.nzcount() << '\n';
  
    // Create a template form of the same array
    cv::SparseMat_<double> sm5 = CPP_CV::SparseArrays::fill3DSparseArray(arrayDims, CV_64F, data);
    std::cout << "\nNo. of Dimensions = " << sm5.dims() << '\n';
    std::cout << "Data type of values = " 
              << CPP_CV::General::openCVDescriptiveDataType(sm5.type()) << '\n';
    std::cout << "Size of array = " << sm5.size(0) << " x " << sm5.size(1) << " x " << sm5.size(2) 
              << '\n';
    std::cout << "No. of non-zero elements = " << sm5.nzcount() << '\n';
    
    std::cout << '\n';

    return 0;
}
```

**Output**

    No. of Dimensions = 3
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array = 10 x 5 x 2
    No. of non-zero elements = 34

    No. of Dimensions = 3
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array = 10 x 5 x 2
    No. of non-zero elements = 34

4. `T& cv::SparseMat::ref(const int* idx, cv::size_t* hashval = 0)` - Mainly used for n-Dimensional cases where `n > 3`, but can also be used in place of the above functions for `n == 1, 2 or 3`. The parameter `idx` is a pointer to a C-style array of integers, which represent the indices of the element in question. This might be confusing for some people especially if they are not comfortable with C-style arrays, hence the need to take a short detour here using a simple example. If dealing with a 2D sparse array and you are interested in element at position (2, 3), you declare your C-style array of element indices as `const int idx[] {2,3};`. By default C-style arrays decay to pointers with the same data type as the original array, hence when passed to our function the data type of `idx` becomes `const int*`. I hope this helps. You can also read this detailed material <a href = "https://www.learncpp.com/cpp-tutorial/introduction-to-c-style-arrays/">here</a> on C-style arrays.  The rest of the parameters have the same meaning as above. The following code shows a template function you can use to create and fill a 4-Dimensional `cv::SparseMat` from data contained in a std::vector. Using this function you can adapt it to create your own 5-Dimensional or higher sparse arrays. Take note of the fact we use the function `void cv::SpatMat::erase(const int* idx, cv::size_t* hashval = 0)` to remove any `0`'s from our sparse array. 

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

                    // If the element is '0' we erase it from our sparse array
                    // because we only want to keep non-zero elements
                    if(sparseArray.ref<T>(idx) == static_cast<T>(0))
                    {
                        sparseArray.erase(idx);
                    }
    
                    ++i; // increment std::vector index counter
                }              
            }          
        }
    }  
    
    return sparseArray;
}
```

:notebook_with_decorative_cover: We also add the above template function to our header file under the namespace **SparseArrays** inside our main namespace **CPP_CV**. We can then access this function as `CPP_CV::SparseArrays::fill4DSparseArray()` as in the following example. 

**Example 5** - fill a 4-D sparse array

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
    

    // 2x2x5x5 4-D array 
    const int arrayDims_4D[] { 2, 2, 5, 5 }; 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm6  = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims_4D, CV_64F, data); 
    
    // Print some relevant information about the 4-D array
    std::cout << "\nNo. of Dimensions = " << sm6.dims() << '\n';
    std::cout << "Data type of values = " << CPP_CV::General::openCVDescriptiveDataType(sm6.type()) << '\n';
    std::cout << "Size of array= " << sm6.size(0) << " x " << sm6.size(1) 
              << " x " << sm6.size(2) << " x " << sm6.size(3) << '\n';
    std::cout << "No. of non-zero elements = " << sm6.nzcount() << '\n'; 

    // Create a template form of the same array
    cv::SparseMat_<double> sm7 = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims_4D, CV_64F, data);
    std::cout << "\nNo. of Dimensions = " << sm7.dims() << '\n';
    std::cout << "Data type of values = " 
              << CPP_CV::General::openCVDescriptiveDataType(sm7.type()) << '\n';
    std::cout << "Size of array= " << sm7.size(0) << " x " << sm7.size(1) 
              << " x " << sm7.size(2) << " x " << sm7.size(3) << '\n'; 
    std::cout << "No. of non-zero elements = " << sm7.nzcount() << '\n';

    std::cout << '\n';

    return 0;
}
```
**Output**

    No. of Dimensions = 4
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array = 2 x 2 x 5 x 5
    No. of non-zero elements = 34

    No. of Dimensions = 4
    Data type of values = CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)
    Size of array = 2 x 2 x 5 x 5
    No. of non-zero elements = 34


### Accessing cv::SparseMat array elements using Accessor Functions {#custom-id4}

:notebook_with_decorative_cover: The **cv::SparseMat** class provides 2 ways which we can use for accessing elements, **accessor functions** and **iterators**. In this section, we will focus on accessor functions, of which there are 4 provided by the `cv::SparseMat` class.

1. **cv::SparseMat::ptr()** - this function has several variations to cover 1D, 2D, 3D and the generic type for n-Dimensional data objects. All variations return a pointer to the specified element. This pointer is to an unsigned character (i.e., ***uchar**), which will typically need to be recast to the correct type for the array. Because this function returns a pointer, you should always check if it is **NULL** or not before doing anything with it. Dealing with NULL pointers leads to undefined behaviour and may even crush your program.

    1. `uchar* cv::SparseMat::ptr(int i0, bool createMissing, cv::size_t* hashval = 0)` - This version is for accessing a 1D array. The arguments are as follows:
       * **i0** - the index of the requested element
       * **createMissing** - indicates whether the element should be created if it is not already present in the array. If `createMissing = true` and the element is not in the array, it is created and initialized with `0`. A non-NULL pointer to the new element is returned by the function. If `createMissing = false` and the element is not available, a NULL pointer is returned.
       * **hashval** - If `hashval = NULL or 0`, a hash key needed to access the element will need to be computed, otherwise supply an already computed hash key. Computing the hash key value is usually done automatically by the function or by you using the function `cv::SparseMat::hash()` (which we will discuss later in this tutorial). For the meantime let the main function compute the hash value for you.
    2. `uchar* cv::SparseMat::ptr(int i0, int i1, bool createMissing, cv::size_t* hashval = 0)` - for 2D cases. Requires two indices (**i0** and **i1**) for the element in question. The rest of the parameters have the same meaning as above. 
    3. `uchar* cv::SparseMat::ptr(int i0, int i1, int i2, bool createMissing, cv::size_t* hashval = 0)` - for 3D cases. This requires 3 indices, **i0**, **i1** and **i2**. The rest of the parameters have the same meaning as above. 
    4. `uchar* cv::SparseMat::ptr(const int* idx, bool createMissing, cv::size_t* hashval = 0)` - for n-D cases. The parameter **idx** is a pointer to a C-style array of integers, which represent the indices of the element in question. This might be confusing for some people especially if they are not comfortable with C-style arrays, hence the need to take a short detour here using a simple example. If dealing with a 2D sparse array and you are interested in element at position (2, 3), you declare your C-style array of element indices as `const int idx[] {2,3};`. By default C-style arrays decay to pointers with the same data type as the original array, hence when passed to our function the data type of **idx** becomes `const int*`. I hope this helps. You can also use this detailed material <a href = "https://www.learncpp.com/cpp-tutorial/introduction-to-c-style-arrays/">here</a> on C-style arrays.  The rest of the parameters have the same meaning as above. 

**Example 6**

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h"  // Header file with our own functions we have written
#include <iostream>
#include <vector>

int main()
{
    // We want to use the following data to create Sparse Arrays    
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
    
    ///////////// Create a 2-D Sparse array ////////////////
    //            =========================

    // // 10x10 2-D array 
    const int arrayDims[] { 10, 10 }; 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm4  = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data); 
    
        
    // Create a template form of the same array
    cv::SparseMat_<double> sm5 = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data);
        
    
    ///////////// Create a 4-D Sparse array ////////////////
    //            =========================

    // 2x2x5x5 4-D array 
    const int arrayDims_4D[] { 2, 2, 5, 5 }; 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm6  = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims_4D, CV_64F, data); 
    
    
    // Create a template form of the same array
    cv::SparseMat_<double> sm7 = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims_4D, CV_64F, data);
    
    // We will use cv::SparseMat::ptr() to access elements in a sparse array
    // =====================================================================

    // Declare some common variables 
    bool createMissing = false; // if element does not exist we do not want to create it
    std::size_t* hashval = nullptr; // We do not know the hash value of our element, 
                                    // we will let OpenCV do this for us by setting 
                                    // 'hashval' to 'nullptr' as per modern C++. You 
                                    // can still use 'NULL' or '0' and it will still work

        
    // a) Find element at position (6, 0) from a 2-D Sparse array
    //    Accessing elements using cv::SparseMat::ptr() is the same for sparse  
    //    arrays created using the class 'cv::SparseMat' or 'cv::SparseMat_'

    int i0 = 6; // element index 
    int i1 = 0; // element index 
    auto element_ptr = sm4.ptr(i0, i1, createMissing, hashval);
    
    // Check if returned pointer in a null pointer before attempting
    // to recast it to another data type
    if (element_ptr) // same as : if (element_ptr != NULL)
    {
        // Since our sparse array 'sm4' has type 'CV_64F', which is the same 
        // as type 'double', we need to cast pointer to uchar (*uchar) to pointer to 
        // double (*double)
        auto a = (double*)(element_ptr);

        // To access the actual value just de-reference the pointer
        auto value = *a;

        std::cout << "\nValue at position (" 
                  << i0 << ", " << i1 
                  << ") returned using cv::SparseMat::ptr() = " 
                  << value << '\n';        
    } 
    else 
    {
        std::cout << "\nNull pointer returned.\n";
    }

    // b. Find the last element in sparse array 'sm6' (a 2x2x5x5 4-D array).
    //    The last element will have the indices (1, 1, 4, 4)
    //    Use cv::SparseMat::ptr(const int* idx, bool createMissing, cv::size_t* hashval = 0)
    //    to find the element of an n-D sparse array

    // Place the indices of the element in a C-style array
    const int indices[] {1, 1, 4, 4};

    // Find element at position (1, 1, 4, 4)
    // Returns a pointer to the element
    auto element_ptr_2 = sm6.ptr(indices, createMissing, hashval);

    // Check if returned pointer in a null pointer before attempting
    // to recast it to another data type
    if (element_ptr_2) // same as : if (element_ptr_2 != NULL)
    {
        // Since our sparse array 'sm6' has type 'CV_64F', which is the same 
        // as type 'double', we need to cast pointer to uchar (*uchar) to pointer to 
        // double (*double)
        auto a = (double*)(element_ptr_2);

        // To access the actual value just de-reference the pointer
        auto value = *a;

        std::cout << "\nValue at position (" 
                  << indices[0] << ", " << indices[1] 
                  << ", " << indices[2] << ", " << indices[3] 
                  << ") returned using cv::SparseMat::ptr() = " 
                  << value << '\n';
        
    } 
    else 
    {
        std::cout << "\nNull pointer returned.\n";
    }

    std::cout << '\n';

    return 0;
}
```

**Output**

    Value at position (6, 0) returned using cv::SparseMat::ptr() = 7

    Value at position (1, 1, 4, 4) returned using cv::SparseMat::ptr() = 8

2. **cv::SparseMat::ref<>()** - As mentioned in a previous section, `cv::SparseMat::ref<>()` can be used to either **read** or **modify** an element in a sparse array. In this section we will focus on reading element values. `cv::SparseMat::ref<>()` returns a valid reference to an element of the array. If the element does not exist, it is created and initialized with 0. We use the same functions as in the section <a href = "#custom_id3">Filling a cv::SparseMat Array with Elements</a> above,  hence we will not repeat them here</a>. 
    
**N.B**: If using this template accessor function with a sparse array created using the non-template version class `cv::SparseMat`, you must specify the data type of elements being referenced. For example, if your array has elements of type `CV_32F`, then your function calls should be `cv::SparseMat::ref<float>()`. If however you created your sparse array using the template version class `cv::SparseMat_<float>`, then you can skip the angle brackets and data type altogether, i.e, `cv::SparseMat::ref()`.

**Example 7**

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h"  // Header file with our own functions we have written
#include <iostream>
#include <vector>

int main()
{
    // We want to use the following data to create Sparse Arrays    
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
    
    ///////////// Create a 2-D Sparse array ////////////////
    //            =========================

    // // 10x10 2-D array 
    const int arrayDims[] { 10, 10 }; 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm4  = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data); 
        
    // Create a template form of the same array
    cv::SparseMat_<double> sm5 = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data);
        
    
    ///////////// Create a 4-D Sparse array ////////////////
    //            =========================

    // 2x2x5x5 4-D array 
    const int arrayDims_4D[] { 2, 2, 5, 5 }; 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm6  = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims_4D, CV_64F, data); 
    
    
    // Create a template form of the same array
    cv::SparseMat_<double> sm7 = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims_4D, CV_64F, data);
    
    // We will use cv::SparseMat::ref<>() to access elements in a sparse array
    // =======================================================================

    // Declare some common variables 
    bool createMissing = false; // if element does not exist we do not want to create it
    std::size_t* hashval = nullptr; // We do not know the hash value of our element, 
                                    // we will let OpenCV do this for us by setting 
                                    // 'hashval' to 'nullptr' as per modern C++. You 
                                    // can still use 'NULL' or '0' and it will still work      

   
    // a. Find element at position (6, 0) from a 2-D sparse array
    //    We will need to use the template version of ref() because 
    //    the original sparse array (sm4) was instantiated/constructed 
    //    using the non-template form cv::SparseMat

    int i0 = 6; // element index 
    int i1 = 0; // element index 
    auto element_ref = sm4.ref<double>(i0, i1, hashval); 

    std::cout << "\nValue at position (" 
              << i0 << ", " << i1 
              << ") returned using cv::SparseMat::ref<>() = " 
              << element_ref << '\n';

    // b. Find the last element in sparse array 'sm7' (a 2x2x5x5 4-D array).
    //    The last element will have the indices (1, 1, 4, 4)
    //    Use cv::SparseMat::ref(const int* idx, cv::size_t* hashval = 0)
    //    to find the element of an n-D sparse array 

    //    We will need to use the non-template version of ref() because 
    //    the original sparse array (sm7) was instantiated/constructed 
    //    using the template form cv::SparseMat_<double>
    // Place the indices of the element in a C-style array
    const int indices_2[] {1, 1, 4, 4};
    auto element_ref_2 = sm7.ref(indices_2, hashval);

    std::cout << "\nValue at position (" 
              << indices_2[0] << ", " << indices_2[1] 
              << ", " << indices_2[2] << ", " << indices_2[3] 
              << ") returned using cv::SparseMat::ref() = " 
              << element_ref_2 << '\n';

    std::cout << '\n';

    return 0;
}
```

**Output**

    Value at position (6, 0) returned using cv::SparseMat::ref<>() = 7

    Value at position (1, 1, 4, 4) returned using cv::SparseMat::ref() = 8

3. **cv::SparseMat::value<>()** - this template function is similar to cv::SparseMat::ref<>(), with the exception that is returns the actual value not a reference to the value. Also, the function is a **const**, meaning it does not make any changes to the array. Hence, if the element does not exists, instead of creating a new element, it simply returns the value `0`. Whether you created your sparse array using the template (`cv::SparseMat_`) or non-template versions (`cv::SparseMat`), you still need to include the array elements data type in angle brackets when using this function. There are 6 variations of this functions. The first 4 have the same signature, parameters and explanation as those for `cv::SparseMat::ref<>()`

    1. `T cv::SparseMat::value(int i0, cv::size_t* hashval = 0) const` - for 1-D sparse arrays
    2. `T cv::SparseMat::value(int i0, int i1, cv::size_t* hashval = 0) const` - for 2-D sparse arrays
    3. `T cv::SparseMat::value(int i0, int i1, int i2, cv::size_t* hashval = 0) const` - for 3-D sparse arrays
    4. `T cv::SparseMat::value(const int* idx cv::size_t* hashval = 0) const` - for n-Dimensional sparse arrays
    5. `T cv::SparseMat::value(cv::Node* n) const` returns the value stored in the sparse matrix **node**. A <a href = "https://docs.opencv.org/4.8.0/d9/de0/structcv_1_1SparseMat_1_1Node.html#details">sparse matrix node</a> is a data structure used by cv::SparseMat to keep track of its values. In OpenCV it is defined as a C++ **struct** data structure with 3 public attributes: hash value of the element (`cv::size_t hashval`), index of the matrix element (`int idx[MAX_DIM]`) and index of the next node in the same hash table (`cv::size_t next`). We will discuss this structure more when we talk about using iterators to access sparse array elements.
    6. `const T cv::SparseMat::value(const cv::Node* n) const` -  a `const` version of the above function.

**Example 8**

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h"  // Header file with our own functions we have written
#include <iostream>
#include <vector>

int main()
{
    // We want to use the following data to create Sparse Arrays    
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
    
    ///////////// Create a 2-D Sparse array ////////////////
    //            =========================

    // // 10x10 2-D array 
    const int arrayDims[] { 10, 10 }; 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm4  = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data); 
    
        
    // Create a template form of the same array
    cv::SparseMat_<double> sm5 = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data);
       
    
    ///////////// Create a 4-D Sparse array ////////////////
    //            =========================

    // 2x2x5x5 4-D array 
    const int arrayDims_4D[] { 2, 2, 5, 5 }; 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm6  = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims_4D, CV_64F, data); 
    
   
    // Create a template form of the same array
    cv::SparseMat_<double> sm7 = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims_4D, CV_64F, data);
    
    // We will use cv::SparseMat::value<>() to access elements in a sparse array
    // =========================================================================

    std::size_t* hashval = nullptr; // We do not know the hash value of our element, 
                                    // we will let OpenCV do this for us by setting 
                                    // 'hashval' to 'nullptr' as per modern C++. You 
                                    // can still use 'NULL' or '0' and it will still work      

   
    // a. Find element at position (6, 0) from a 2-D sparse array
    //    We always use the template version of value() no matter 
    //    how the sparse array (sm4) is instantiated/constructed 

    int i0 = 6; // row to find element
    int i1 = 0; // column to find element
    auto element_value = sm4.value<double>(i0, i1, hashval); 

    std::cout << "\nValue at position (" 
              << i0 << ", " << i1 
              << ") returned using cv::SparseMat::value<>() = " 
              << element_value << '\n';

    // b. Find the last element in sparse array 'sm7' (a 2x2x5x5 4-D array).
    //    The last element will have the indices (1, 1, 4, 4)
    //    Use cv::SparseMat::value(const int* idx, cv::size_t* hashval = 0)
    //    to find the element of an n-D sparse array 

    //    We always use the template version of value() no matter 
    //    how the sparse array (sm7) is instantiated/constructed 

    // Place the indices of the element in a C-style array
    const int indices_3[] {1, 1, 4, 4};
    auto element_value_2 = sm7.value<double>(indices_3, hashval);

    std::cout << "\nValue at position (" 
              << indices_3[0] << ", " << indices_3[1] 
              << ", " << indices_3[2] << ", " << indices_3[3] 
              << ") returned using cv::SparseMat::value<>() = " 
              << element_value_2 << '\n';

    std::cout << '\n';

    return 0;
}
```

**Output**
    
    Value at position (6, 0) returned using cv::SparseMat::value<>() = 7

    Value at position (1, 1, 4, 4) returned using cv::SparseMat::value<>() = 8

4. **cv::SparseMat::find<>()** - this template function works similarly to `cv::SparseMat::ref<>()` and `cv::SparseMat::value<>()`, but returns a pointer to the requested object. Unlike `cv::SparseMat::ptr()`, the pointer is of the type specified by the user and so does not need to be recast. **Prefer this template function over `cv::SparseMat::ptr()` when possible**. `cv::SparseMat::find<>()` is a **const** function. If the element does not exists, it is not created, the function simply returns a `NULL` pointer. Remember to check if the pointer is `NULL` or not before trying to dereference it. Accessing a `NULL` pointer can either crush your program or lead to undefined behaviour. Whether you created your sparse array using the template (`cv::SparseMat_`) or non-template versions (`cv::SparseMat`), you still need to include the elements data type in angle brackets when using this function. There are 4 variations of this function. The function signatures and parameter definitions are the same as those of `cv::SparseMat::ref<>()`.

    1. `const T* cv::SparseMat::find(int i0, cv::size_t* hashval = 0) const` - for 1-D sparse arrays
    2. `const T* cv::SparseMat::find(int i0, int i1, cv::size_t* hashval = 0) const` - for 2-D sparse arrays
    3. `const T* cv::SparseMat::find(int i0, int i1, int i2, cv::size_t* hashval = 0) const` - for 3-D sparse arrays
    4. `const T* cv::SparseMat::find(const int* idx, cv::size_t* hashval = 0) const` - for n-Dimensional sparse arrays

**Example 9**

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h"  // Header file with our own functions we have written
#include <iostream>
#include <vector>

int main()
{
    // We want to use the following data to create Sparse Arrays    
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
    
    ///////////// Create a 2-D Sparse array ////////////////
    //            =========================

    // // 10x10 2-D array 
    const int arrayDims[] { 10, 10 }; 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm4  = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data); 
    
        
    // Create a template form of the same array
    cv::SparseMat_<double> sm5 = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data);
        
    
    ///////////// Create a 4-D Sparse array ////////////////
    //            =========================

    // 2x2x5x5 4-D array 
    const int arrayDims_4D[] { 2, 2, 5, 5 }; 
    
    // Create Sparse Array by calling our user defined function.
    // N.B: If you intend to later access a Sparse Array elements using a function 
    //      like ref(),  DO NOT make your array 'const'
    cv::SparseMat sm6  = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims_4D, CV_64F, data); 
    
    
    // Create a template form of the same array
    cv::SparseMat_<double> sm7 = CPP_CV::SparseArrays::fill4DSparseArray(arrayDims_4D, CV_64F, data);
    
    // We will use cv::SparseMat::find<>() to access elements in a sparse array
    // ========================================================================

    std::size_t* hashval = nullptr; // We do not know the hash value of our element, 
                                    // we will let OpenCV do this for us by setting 
                                    // 'hashval' to 'nullptr' as per modern C++. You 
                                    // can still use 'NULL' or '0' and it will still work      

   
    // a. Find element at position (6, 0) from a 2-D sparse array
    //    We always use the template version of find() no matter 
    //    how the sparse array (sm4) is instantiated/constructed 
    
    int i0 = 6; // row to find element
    int i1 = 0; // column to find element

    // The following statement should return a pointer of 
    // data type 'const double*'
    auto element_find = sm4.find<double>(i0, i1, hashval); 
    
    // Before using or accessing a value through a pointer always 
    // check if the pointer is NULL
    if (element_find) // this is the same as: if (element_find != NULL)
    {
        // we can now dereference the pointer to get access to the actual value
        auto value = *element_find;

        std::cout << "\nValue at position (" << i0 << ", " << i1 
                  << ") returned using cv::SparseMat::find<>() = " 
                  << value << '\n';
    }
    else // if pointer is NULL
    {
        std::cout << "\nPointer is NULL and can't be accessed.\n";
    }

    // b. Find the last element in sparse array 'sm6' (a 2x2x5x5 4-D array).
    //    The last element will have the indices (1, 1, 4, 4)
    //    Use cv::SparseMat::find(const int* idx, cv::size_t* hashval = 0)
    //    to find the element of an n-D sparse array

    // Place the indices of the element in a C-style array
    const int indices_4[] {1, 1, 4, 4};

    // Find element at position (1, 1, 4, 4)
    // Returns a pointer to the element
    auto element_find_2 = sm6.find<double>(indices_4, hashval);

    // Check if returned pointer in a null pointer before attempting
    // to access its value
    if (element_find_2) // same as : if (element_find_2 != NULL)
    {        
        // To access the actual value just de-reference the pointer
        auto value = *element_find_2;

        std::cout << "\nValue at position (" 
                  << indices_4[0] << ", " << indices_4[1] 
                  << ", " << indices_4[2] << ", " << indices_4[3] 
                  << ") returned using cv::SparseMat::find<>() = " 
                  << value << '\n';        
    } 
    else 
    {
        std::cout << "\nPointer is NULL and can't be accessed.\n";
    }

    std::cout << '\n';

    return 0;
}
```

**Output**    

    Value at position (6, 0) returned using cv::SparseMat::find<>() = 7

    Value at position (1, 1, 4, 4) returned using cv::SparseMat::find<>() = 8


### Using Iterators to Access Sparse Arrays

:notebook_with_decorative_cover: We can also access the elements of a sparse array through **iterators**.
We mainly use iterators if we want to access all the elements in a sparse array. OpenCV offers templated and non-templated iterators for sparse arrays, both of which contain **const** and **non-const** versions. The templated iterators are <a href = "https://docs.opencv.org/4.8.0/d3/d24/classcv_1_1SparseMatIterator__.html">cv::SparseMatIterator_<></a> and <a href = "https://docs.opencv.org/4.8.0/d9/d29/classcv_1_1SparseMatConstIterator__.html">cv::SparseMatConstIterator_<></a>. The non-templated forms are <a href = "https://docs.opencv.org/4.8.0/d5/d9b/classcv_1_1SparseMatIterator.html">cv::SparseMatIterator</a> and <a href = "https://docs.opencv.org/4.8.0/df/dec/classcv_1_1SparseMatConstIterator.html">cv::SparseMatConstIterator</a>. 

:notebook_with_decorative_cover: Both versions are accompanied by the usual **begin()** and **end()** functions. 

1. The **begin()** function returns an iterator pointing to the first sparse array element. 
2. The **end()** function returns an iterator pointing to the element following the last sparse matrix element. *N.B: - You should never try to access the element pointed to by the **end()** iterator, it does not exist in memory and will likely crash your program or lead to undefined behaviour*.

:notebook_with_decorative_cover: If you go through the class definitions of the iterators you will notice they all contain a common template function called `value<>()`. The `const` iterators have this function signature defined as `const T& value() const` - meaning you get a reference to an array element for **reading** only. The non-const iterators define this function as `T& value() const` - meaning you get a reference to an array element for **reading** or **writing**. If you do not want to use this function to access an array element you can always use the *good old, but proven*, dereference operator (`*`).

**Example 10** - Using **const** iterators to traverse through a sparse array. Use `const` iterators if you have **no intention** of altering array element values during iteration - for example, if you just want to print the array elements.

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h"  // Header file with our own functions we have written
#include <iostream>
#include <vector>

int main()
{
    // We want to use the following data to create Sparse Arrays    
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
    
    ///////////// Create a 2-D Sparse array ////////////////
    //            =========================

    // // 10x10 2-D array 
    const int arrayDims[] { 10, 10 }; 
    
    // Create Sparse Array by calling our user defined function.
    // Since we are only interested in accessing/reading array elements
    // we will declare our array as 'const'
    const cv::SparseMat sm4  = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data); 

    // 1. Using 'const' iterators
    //    =======================
    
    //    It is best to use 'const' iterators if you know you are not 
    //    going to alter any of the array elements e.g. printing all the 
    //    elements of a sparse array
    
    // a. Use the template cv::SparseMatConstIterator_ iterator to  
    //    iterate through all the elements in a 2-D sparse array 
    //    (this includes the zero elements) and print them
    //    The elements are printed in a random order
    
    // Define iterators pointing to 'start' and '1 + end of array' positions
    // Don't forget to specify the data types inside angle brackets
    // Since array 'sm4' has elements of type 'CV_64F', use type 'double'
    cv::SparseMatConstIterator_<double> it { sm4.begin<double>() };
    cv::SparseMatConstIterator_<double> it_end { sm4.end<double>() };

    // Iterate through array making sure we don't go beyong array size
    for(it; it != it_end; ++it)
    {
        // Print each array element
        // The following statement could have read: 
        //      std::cout << *(it) << " ";
        // when using the dereference operator
        std::cout << it.value<double>() << " ";
    }

    // b. Use the non-template cv::SparseMatConstIterator iterator to 
    //    iterate over all the elements in a 2-D sparse array and find their sum 

    // Define iterators pointing to 'start' and '1 + end of array' positions
    // There is no need to specify the data types inside angle brackets
    cv::SparseMatConstIterator it_2 { sm4.begin() };
    cv::SparseMatConstIterator it_end_2 { sm4.end() };

    // Variable to hold the final sum of all the array elements
    double sum { 0 }; 

    // Iterate through array making sure we don't go beyong array size
    for(it_2; it_2 != it_end_2; ++it_2)
    {
        // Sum all the elements
        // The following is the same as: 
        //      sum = sum + it_2.value<double>;
        sum += it_2.value<double>();
    }

    std::cout << "\nSum of array elements in sm4 = " << sum << '\n';  

    std::cout << '\n';

    return 0;
}
```

**Output**

    0 1 0 0 2 0 0 5 0 0 0 7 3 7 2 0 5 0 0 0 0 0 4 0 8 4 1 8 0 0 0 0 0 0 0 0 0 0 5 0 0 0 0 1 0 3 1 0 0 2 3 0 0 0 9 0 4 0 0 0 4 0 0 5 0 0 8 7 3 0 0 4 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 5 2 2 6 6 0 7 0 0 0 0 

    Sum of array elements in sm4 = 146

:notebook_with_decorative_cover: If you look at **Example 10** above, the code for printing all the array elements of a sparse array is a candidate for code we might re-use in future, hence we will create a function to place this code in. It will be a function template, thereby allowing us to print array elements of any data type.

```c++
/**
 * @brief Template function to print all the elements of a sparse array (including the zero's).
 *        The elements are not printed in any logical order.
 * 
 * @tparam T Data type of sparse array elements e.g. if using 'CV_32F' then T == 'float'.
 *           When using 'CV_64F' then T == 'double' etc.
 * @param sparseArray sparse array whose elements you want to print.
 */
template <typename T>
void printAllSparseArrayElements(const cv::SparseMat_<T>& sparseArray)
{
    // Define iterators pointing to 'start' and '1 + end of array' positions
    // Don't forget to specify the data types inside angle brackets
    cv::SparseMatConstIterator_<T> it { sparseArray.begin() };
    cv::SparseMatConstIterator_<T> it_end { sparseArray.end() };

    // Iterate through array making sure we don't go beyong array size
    for(it; it != it_end; ++it)
    {
        /* 
         * Print each array element
         * 
         * Please take note of the following points: 
         *  1. The following statement could have read: 
         *      std::cout << *(it) << " ";
         *     when using the dereference operator
         *  2. The keyword 'template' between 'it.' and 'value<T>' is required. 
         *     See the following for the reasons why: 
         *     https://stackoverflow.com/questions/60062567/c-why-is-the-template-keyword-required-here
         * 
        */
        std::cout << it. template value<T>() << " ";
    }

}
```

:notebook_with_decorative_cover: We then add the above function to our library we are creating. As previously explained, template functions are added directly to our **utility_functions.h** header file under the **SparseArrays** namespace. We can then access this function as `CPP_CV::SparseArrays::printAllSparseArrayElements()`.

**Example 11** - We will be using **non-const** iterators to traverse through a sparse array. You will notice in the following example that when using an iterator of the class `cv::SparseMatIterator_` we will not use the template function `value()<>` to get a reference of the array elements. Instead we fall back onto using dereference operator (`*`), which can be used to both access and/or modify array elements. This is because the class `cv::SparseMatIterator_` does not implement its own version of the `value()<>` template function - instead, it inherits one directly from `cv::SparseMatConstIterator`, which has the signature `const T& value() const` - meaning the function returns a reference to a `const` value, which cannot be altered.

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h"  // Header file with our own functions we have written
#include <iostream>
#include <vector>

int main()
{
    // We want to use the following data to create Sparse Arrays    
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
    
    ///////////// Create a 2-D Sparse array ////////////////
    //            =========================

    // // 10x10 2-D array 
    const int arrayDims[] { 10, 10 }; 
    
    // Create Sparse Array by calling our user defined function.
    // Since we are also interested in both reading and modifying array elements
    // we will NOT declare our array as 'const'
    cv::SparseMat sm4  = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data); 

    // 1. Using 'non-const' iterators
    //    ===========================

    //    It is best to use 'non-const' iterators if you know you are  
    //    going to alter any of the array elements 

    // a. Use the non-template cv::SparseMatIterator iterator to 
    //    iterate over a 2-D sparse array, multiply each element 
    //    with a value equal to 8 by 2

    // We will print the sparse array elements before alteration
    std::cout << "\nBefore = ";

    // Use our library function to print the array elements 
    // before we make any alterations
    CPP_CV::SparseArrays::printAllSparseArrayElements<double>(sm4);

    // Define iterators pointing to 'start' and '1 + end of array' positions
    cv::SparseMatIterator it_3 { sm4.begin() };
    cv::SparseMatIterator it_end_3 { sm4.end() };

    // Iterate through array making sure we don't go beyong array size
    for(it_3; it_3 != it_end_3; ++it_3)
    {
        // Get hold of the reference to each array element
        auto& element = it_3.value<double>();

        if(element == 8) // Check if element is equal to '8'
        {
            // Multiply each value equal to '8' by 2
            // The following statement could have been written as:
            //  element = element * 2;
            element *= 2; 
        }
    }

    // We will now print the sparse array elements after alteration
    std::cout << "\nAfter = ";

    // Use our library function to print the array elements
    // You will notice all values equal to '8' have been altered to '16' 
    CPP_CV::SparseArrays::printAllSparseArrayElements<double>(sm4);

    // b. Use the template cv::SparseMatIterator_ iterator to 
    //    iterate over the previous altered 2-D sparse array,  
    //    then subtract '1' from each element equal to '16'

    // Define iterators pointing to 'start' and '1 + end of array' positions
    cv::SparseMatIterator_<double> it_4 { sm4.begin<double>() };
    cv::SparseMatIterator_<double> it_end_4 { sm4.end<double>() };

    // Iterate through array making sure we don't go beyong array size
    for(it_4; it_4 != it_end_4; ++it_4)
    {
        // You cannot use the function value<>() here since it returns
        // a reference to a 'const' value, which you cannot alter. 
        auto element = *(it_4);

        if(element == 16)
        {
            // Subtract '1' from each array element equal to '16'
            // Use the dereference operator (*) to both 'access' and 
            // alter array elements
            *(it_4) = *(it_4) - 1; 
        }
    }

    // We will print the sparse array elements after another alteration
    std::cout << "\nAfter another alteration = ";

    // Use our library function to print the array elements
    CPP_CV::SparseArrays::printAllSparseArrayElements<double>(sm4);  

    std::cout << '\n';

    return 0;
}
```

**Output**

    Before = 0 1 0 0 2 0 0 5 0 0 0 7 3 7 2 0 5 0 0 0 0 0 4 0 8 4 1 8 0 0 0 0 0 0 0 0 0 0 5 0 0 0 0 1 0 3 1 0 0 2 3 0 0 0 9 0 4 0 0 0 4 0 0 5 0 0 8 7 3 0 0 4 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 5 2 2 6 6 0 7 0 0 0 0 

    After = 0 1 0 0 2 0 0 5 0 0 0 7 3 7 2 0 5 0 0 0 0 0 4 0 16 4 1 16 0 0 0 0 0 0 0 0 0 0 5 0 0 0 0 1 0 3 1 0 0 2 3 0 0 0 9 0 4 0 0 0 4 0 0 5 0 0 16 7 3 0 0 4 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 5 2 2 6 6 0 7 0 0 0 0 

    After another alteration = 0 1 0 0 2 0 0 5 0 0 0 7 3 7 2 0 5 0 0 0 0 0 4 0 15 4 1 15 0 0 0 0 0 0 0 0 0 0 5 0 0 0 0 1 0 3 1 0 0 2 3 0 0 0 9 0 4 0 0 0 4 0 0 5 0 0 15 7 3 0 0 4 0 0 0 0 0 0 2 0 0 0 0 0 0 0 0 0 0 5 2 2 6 6 0 7 0 0 0 0 

:notebook_with_decorative_cover: Typing out the full class names for iterator classes can be time consuming especially when you have a lot of iterator variables to declare. One solution is to use type deduction by taking advantage of the `auto` keyword. However, using `auto` can be tricky especially with `const` iterators. Just using the keyword `auto` will not suffice. Although there are a lot of <a href = "https://stackoverflow.com/questions/15233188/how-do-i-get-a-const-iterator-using-auto">solutions</a> out there, I prefer to use the function `std::as_const`, which was introduced in C++17 and can be found in the `<utility>` header file. You use `std::as_const` to wrap around the object whose type you want deducted as `const`. In the following example we will just show the declaration parts of iterators. You can always substitute these in the above examples.

**Example 12** - Using `auto` when declaring objects of iterator classes

```c++
#include "opencv2/core.hpp" // for all OpenCV core data types 
#include "UtilityFunctions/utility_functions.h" // Header file with our own functions we have written
#include <utility> // for std::as_const

int main()
{
    // We want to use the following data to create Sparse Arrays    
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
    
    ///////////// Create a 2-D Sparse array ////////////////
    //            =========================

    // // 10x10 2-D array 
    const int arrayDims[] { 10, 10 }; 
    
    // Create Sparse Array by calling our user defined function.
    // Since we are also interested in both reading and modifying array elements
    // we will NOT declare our array as 'const'
    cv::SparseMat sm4  = CPP_CV::SparseArrays::fill2DSparseArray(arrayDims, CV_64F, data); 

    /* 
     * 1. Using the template cv::SparseMatConstIterator_ iterator 
     *    =======================================================

     *    Use 'std::as_const' around the sparse array to make sure the  
     *    deducted type is cv::SparseMatConstIterator_, otherwise
     *    it will be cv::SparseMatIterator_
     * 
    */

    auto it { std::as_const(sm4).begin<double>() };
    auto it_end { std::as_const(sm4).end<double>() };

    /*
     * 2. Using the non-template cv::SparseMatConstIterator iterator 
     *    ==========================================================
     * 
     *    Use 'std::as_const' around the sparse array to make sure the 
     *    deducted type is  cv::SparseMatConstIterator, otherwise 
     *    it will be cv::SparseMatIterator
     * 
    */ 
    auto it_2 { std::as_const(sm4).begin() };
    auto it_end_2 { std::as_const(sm4).end() };

    // 3. Using the non-template cv::SparseMatIterator iterator
    //    =====================================================

    auto it_3 { sm4.begin() };
    auto it_end_3 { sm4.end() };

    // 4. Using the template cv::SparseMatIterator_ iterator
    //    =====================================================

    auto it_4 { sm4.begin<double>() };
    auto it_end_4 { sm4.end<double>() };

    return 0;
}
```

:notebook_with_decorative_cover: Using `auto` for type deduction can save the programmer a lot of typing especially if dealing with long class names. However, it may not be so easy for someone else to read and understand your code. If the data type is not so obvious add a helpful comment. Another way to deal with long class name declarations is to use aliases - where you can use a shorter name as a substitute for a longer name. We will not go into greater detail about aliases here but there is a good tutorial which you can find <a href = "https://www.learncpp.com/cpp-tutorial/typedefs-and-type-aliases/">here</a>.