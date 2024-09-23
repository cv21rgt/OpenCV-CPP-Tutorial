## The Fixed Matrix Data Type

:notebook_with_decorative_cover: The fixed matrix class is for data which can be represented in rows and columns. It is implemented as a template <a href = "https://docs.opencv.org/4.8.0/de/de1/classcv_1_1Matx.html">cv::Matx<></a>.
     
:notebook_with_decorative_cover: Use this data type for matrices whose dimensions are known at compile time. As a result, all memory for their data is allocated on the stack, which means that they allocate and clean up quickly. 

:notebook_with_decorative_cover: Operations on **cv::Matx<>** are fast, and there are specialized optimized implementations for small matrices e.g. 2x2, 3x3 etc. 

:notebook_with_decorative_cover: As usual, individual matrices can be created/instantiated using aliases of the form: **cv::Matx{1,2,...}{1,2,...}{f,d}** or in general **cv::Matx{No. of rows}{No. of columns}{primitive Data type either float or double}**.

:notebook_with_decorative_cover: To make the best use of this class, **cv::Matx<>** should be used for representing small matrices for e.g. rotation matrices, translation matrices, camera position matrices, which are mainly 2x2, 3x3 etc. If your object is really a big data array, like an image or a huge list of points, then **cv::Matx<>** class is not the correct solution; you should use the **cv::Mat<>** class, which will be discussed later.

:notebook_with_decorative_cover: Each **cv::Matx<>** object allows you to access 4 values relevant to a matrix. These are implemented as <a href = "https://www.learncpp.com/cpp-tutorial/unscoped-enumerations/">Enumerated data types</a> and are as follows:

1. `rows` - number of rows in matrix
2. `cols` - number of columns in matrix
3. `channels` -  total number of elements in matrix, i.e. rows x cols
4. `shortdim` - returns the shorter dimension between rows and cols

:notebook_with_decorative_cover: The first row in **cv::Matx<>** is indexed `0` and the first column is also indexed `0`.

:notebook_with_decorative_cover: For more on **cv::Matx<>** see: https://docs.opencv.org/4.8.0/de/de1/classcv_1_1Matx.html 

### Create Fixed Matrix Objects

:notebook_with_decorative_cover: There are a number of ways you can create fixed matrix objects. The usual methods involve using:
1. Default constructors - OpenCV sets all element values to zero's.
2. Value constructors - the user provides all element values. The matrix values are provided as a list. Make sure the number of values can be converted to the matrix dimensions you want e.g. if you want a 3x3 matrix, then provide 9 values. 
3. Copy constructor - copy all element values from an existing matrix into a new matrix object

:notebook_with_decorative_cover: There are other ways of creating commonly used fixed matrix objects e.g. creating a matrix whose elements are all zero's or one's. These methods are provided as member functions in the **cv::Mat<>** class. 

**Example 1**
```c++
#include "opencv2/core.hpp"

int main()
{
    //                            Instantiating cv::Matx<> Objects
    //                            =================================

    // 1. Default constructors
    const cv::Matx12d default_m1 {};  // uses the default constructor to create a 1(rows) x 2(columns) matrix filled with zeros of data type 'double'
    const cv::Matx22d default_m2 {};  // uses the default constructor to create a (2 x 2) matrix, i.e 2 rows & 2 columns filled with zeros of data type 'double'
    const cv::Matx43f default_m3 {};  // uses the default constructor to create a (4 x 3) matrix, i.e 4 rows & 3 columns filled with zeros of data type 'float'
    
    // 2. Value constructors
    const cv::Matx21f m2 {1.2f, 2.2f};   // 2 x 1 matrix - make sure the number of values you provide can be made into a 2 x 1 matrix
    const cv::Matx22d m3 {1, 2, 3, 4};   // 2 x 2 matrix - make sure the number of values you provide can be made into a 2 x 2 matrix
    
    // 3. Copy constructor to copy one matrix to another
    const cv::Matx22d m4(m3);

    /* 4. cv::Matx<> also provides functions that help in creating commonly used fixed matrices
     * e.g. Matrix of zeros, matrix whose elements are all identical, matrix of ones.
     * This helps in that you don't have to manually type the values yourself
    */

    const cv::Matx33f m5 {cv::Matx33f::all(2)};  // 3x3 matrix whose elements are all equal to the value 2

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

    return 0;
}
```

### Printing Fixed Matrix Objects

:notebook_with_decorative_cover: OpenCV allows you to manipulate the way **cv::Matx<>** objects are printed on your console. This can be achieved by providing different formatting options to the function `cv::format(object, format_type)` - which is part of the <a href = "https://docs.opencv.org/4.8.0/d3/da1/classcv_1_1Formatter.html">**cv::Formatter**</a> class. There are a number of ways you can format your output. It is best to show these as examples:

**Example 2**
```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    //                            Instantiating cv::Matx<> Objects
    //                            =================================

    // 1. Default constructors
    const cv::Matx12d default_m1 {};  // uses the default constructor to create a 1(rows) x 2(columns) matrix filled with zeros of data type 'double'
    const cv::Matx22d default_m2 {};  // uses the default constructor to create a (2 x 2) matrix, i.e 2 rows & 2 columns filled with zeros of data type 'double'
    const cv::Matx43f default_m3 {};  // uses the default constructor to create a (4 x 3) matrix, i.e 4 rows & 3 columns filled with zeros of data type 'float'
    
    // 2. Value constructors
    const cv::Matx21f m2 {1.2f, 2.2f};   // 2 x 1 matrix - make sure the number of values you provide can be made into a 2 x 1 matrix
    const cv::Matx22d m3 {1, 2, 3, 4};   // 2 x 2 matrix - make sure the number of values you provide can be made into a 2 x 2 matrix
    
    // 3. Copy constructor to copy one matrix to another
    const cv::Matx22d m4(m3);

    /* 4. cv::Matx<> also provides functions that help in creating commonly used fixed matrices
     * e.g. Matrix of zeros, matrix whose elements are all identical, matrix of ones.
     * This helps in that you don't have to manually type the values yourself
    */

    const cv::Matx33f m5 {cv::Matx33f::all(2)};  // 3x3 matrix whose elements are all equal to the value 2

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


    /*                                Printing cv::Matx<> objects
     *                                ============================
     *   
     * By manipulating the function cv::format() we can 
     * change how cv::Matx objects are printed on screen
     * 
    */ 
    
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
   
    std::cout << "\nm9 (2 x 2) matrix with normally distributed values given the mean =  " 
              << mean << " & variance = " << variance << " : \n" 
              << m9 << '\n';

    std::cout << "\nm10 (3 x 3) matrix with uniformly distributed values within the range defined by min = " 
              << min << " and max = " << max << " : \n" << m10 << '\n';
    
    return 0;

}
```

**Output**

    default_m1 (1 x 2) matrix (Default 'R' format) : 
    [0, 0]

    m2 (2 x 1) matrix (Python format) : 
    [1.2,
    2.2]

    m3 (2 x 2) matrix (CSV format) : 
    1, 2
    3, 4


    m4 (2 x 2) matrix (MATLAB format) : 
    (:, :, 1) = 
    1, 2;
    3, 4

    m5 (3 x 3) matrix with identical elements (NumPy format) : 
    array([[2, 2, 2],
        [2, 2, 2],
        [2, 2, 2]], dtype='float32')

    m6 (2 x 3) matrix of Zeros (C format) : 
    {0, 0, 0,
    0, 0, 0}

    m7 (2 x 2) matrix of Ones : 
    [1, 1;
    1, 1]

    m8 (3 x 3) unit matrix : 
    [1, 0, 0;
    0, 1, 0;
    0, 0, 1]

    m9 (2 x 2) matrix with normally distributed values given the mean =  2.3 & variance = 1.2 : 
    [2.3, 2.4897621;
    1.4588864, 1.7856848]

    m10 (3 x 3) matrix with uniformly distributed values within the range defined by min = 10 and max = 20 : 
    [14.37133, 12.487897, 17.73105;
    17.620937, 13.077945, 17.024317;
    14.784472, 17.9219, 10.858431]


### Data access

:notebook_with_decorative_cover: To access the individual values of a **cv::Matx** object you need the (row, column)
combination of each value. Since **cv::Matx** are 2D you will need two loops
1. to loop through the rows first
2. for each row get the column value using the second loop 

:notebook_with_decorative_cover: Preferably use the index-based `for` loop as it is easier to implement.

:notebook_with_decorative_cover: If we don't want to hard-code the number of rows or columns a cv::Matx object has, we can make use of the public attributes `rows` and `cols`. These are implemented as enumerated data values.

:notebook_with_decorative_cover: We can take advantage of the `for` loop and the enumerated data values to access the individual elements of a **cv::Matx<>** object as follows:


**Example 3**

```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
      
    const cv::Matx22d m3 {1, 2, 3, 4};   // 2 x 2 matrix 

    std::cout << '\n';

    // use the 'rows' enumerated type to get the number of rows in matrix object
    for (int i{0}; i < m3.rows; ++i) 
    {
        // use the 'cols' enumerated type to get the number of columns 
        // in matrix object
        for (int j{0}; j < m3.cols; ++j) 
        {
            std::cout << "Value/Element at position (" << i << ", " << j << ") = " 
                      << m3(i,j) << '\n';
        }
    }
    
    std::cout << '\n';

    return 0;
}
```

**Output**

Value/Element at position (0, 0) = 1
Value/Element at position (0, 1) = 2
Value/Element at position (1, 0) = 3
Value/Element at position (1, 1) = 4

### Matrix Algebra

:notebook_with_decorative_cover: OpenCV allows us to perform basic algebra (multiplication, division, addition & subtraction) with the **cv::Matx<>** class.
     
:notebook_with_decorative_cover: In each case, Matrix algebra is performed elementwise

**Example 4**

```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{    
    const cv::Matx22d mm1 { 1, 2, 3, 4 };  // 2 x 2 matrix
    const cv::Matx22d mm2 { 5, 6, 7, 8 };  // 2 x 2 matrix
    const cv::Matx21d mm3 { 9, 10 };       // 2 x 1 matrix
    const double scalarValue { 2 };

    std::cout << "\nMatrix Addition:\n" << mm1 << " \n+ \n" << mm2 << " \n= " 
              << mm1 + mm2 << '\n';

    std::cout << "\nMatrix Subtraction:\n" << mm2 << " \n- \n" << mm1 << " \n= " 
              << mm2 - mm1 << '\n';

    std::cout << "\nMatrix Multiplication:\n" << mm1 << " \nx \n" << mm3 << " \n= " 
              << mm1 * mm3 << '\n';

    std::cout << "\nMatrix elements multiplied by a single value:\n" 
              << mm1 << " \nx \n" << scalarValue << " = \n" << mm1 * scalarValue << '\n';

    std::cout << "\nMatrix elements divided by a single value:\n" 
              << mm1 << " \n/ \n" << scalarValue << " = \n" << mm1 / scalarValue << '\n';

    return 0;

}
```

**Output**

    Matrix Addition:
    [1, 2;
    3, 4] 
    + 
    [5, 6;
    7, 8] 
    = [6, 8;
    10, 12]

    Matrix Subtraction:
    [5, 6;
    7, 8] 
    - 
    [1, 2;
    3, 4] 
    = [4, 4;
    4, 4]

    Matrix Multiplication:
    [1, 2;
    3, 4] 
    x 
    [9;
    10] 
    = [29;
    67]

    Matrix elements multiplied by a single value:
    [1, 2;
    3, 4] 
    x 
    2 = 
    [2, 4;
    6, 8]

    Matrix elements divided by a single value:
    [1, 2;
    3, 4] 
    / 
    2 = 
    [0.5, 1;
    1.5, 2]

### cv::Matx<> Member Functions

:notebook_with_decorative_cover: **cv::Matx<>** contains a lot of member functions associated with its class objects. Here we will only show some of the most commonly used functions. For the rest of the member functions see: https://docs.opencv.org/4.8.0/de/de1/classcv_1_1Matx.html .

**Example 5**

```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{    
    const cv::Matx22d mm1 { 1, 2, 3, 4 };  // 2 x 2 matrix
    const cv::Matx22d mm2 { 5, 6, 7, 8 };  // 2 x 2 matrix
    
    // 1a. Dot product - which is the sum of elementwise multiplications 
    //                   between two matrices. Dot product is computed to the same 
    //                   precision as the cv::Matx elements    
    std::cout << "\nDot product of " << mm1 << " and " << mm2 << " = " 
              << mm1.dot(mm2) << '\n';
    
    // 1b. Double dot product - Dot product is computed with 'double precision' accuracy
    std::cout << "\nDot product with double precision = " << mm1.ddot(mm2) << '\n';


    // 2. Extract a sub/smaller matrix 
    const cv::Matx44d mm4 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}; // 4x4 matrix
    std::cout << "\nOriginal mm4 matrix = " << mm4 << '\n';
    std::cout << "\nExtract a 2 x 2 matrix from mm4 starting from row = 1 and column = 1 : " 
              << mm4.get_minor<2, 2>(1, 1) << '\n'; 

    // 3. Extract a single row and single column
    std::cout << "\nExtract row = 1 from mm4 : " << mm4.row(1) << '\n';
    std::cout << "\nExtract column = 2 from mm4 : " << mm4.col(2) << '\n';

    // 4. Extract the diagonal values of a matrix
    std::cout << "\nDiagonal values of mm4  = " << mm4.diag() << '\n';

    // 5. Compute the transpose of a matrix
    std::cout << "\nTranspose of mm4 = " << mm4.t() << '\n';

    // 6. Reshape a matrix from one dimension to another
    //    Here you have to make sure you can actually get the new matrix from the original matrix
    std::cout << "\nReshape mm4 to a 2 x 8 matrix = " << mm4.reshape<2, 8>() << '\n';

    std::cout << '\n';

    return 0;

}
```

**Output**

    Dot product of [1, 2;
    3, 4] and [5, 6;
    7, 8] = 70

    Dot product with double precision = 70

    Original mm4 matrix = 
    [1, 2, 3, 4;
    5, 6, 7, 8;
    9, 10, 11, 12;
    13, 14, 15, 16]

    Extract a 2 x 2 matrix from mm4 starting from row = 1 and column = 1 : 
    [6, 7;
    10, 11]

    Extract row = 1 from mm4 = [5, 6, 7, 8]

    Extract column = 2 from mm4 = 
    [3;
    7;
    11;
    15]

    Diagonal values of mm4  = 
    [1;
    6;
    11;
    16]

    Transpose of mm4 = 
    [1, 5, 9, 13;
    2, 6, 10, 14;
    3, 7, 11, 15;
    4, 8, 12, 16]

    Reshape mm4 to a 2 x 8 matrix = 
    [1, 2, 3, 4, 5, 6, 7, 8;
    9, 10, 11, 12, 13, 14, 15, 16]

**Tip:** If you are writing a program or library in which you need to use matrices, you might want to consider using a proven library like OpenCV rather than writing your own code. *There is no need to re-invent the wheel*.



   