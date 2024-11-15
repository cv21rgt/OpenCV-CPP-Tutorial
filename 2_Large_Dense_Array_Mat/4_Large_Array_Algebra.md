## Algebra and cv::Mat

:notebook_with_decorative_cover: Recall that from earlier tutorials we said that a large majority of OpenCV operations try to avoid the un-necessary copying of data and creation of new data areas thereby reducing the amount of computer memory we use for large arrays. A case in point is when you assign a cv::Mat array to another cv::Mat array, for example, `m2 = m1`, **m2** will be just another reference or pointer to the data in **m1**, so that we avoid the unnecessary allocation of a new data area for the same data. In contrast, when we cary out **matrix algebra** such as `m2 = m1 + m0`, the result of evaluating **m1 + m0** will be placed in a newly allocated data area, which will be assigned to **m2**. 

:notebook_with_decorative_cover: **m1 + m0** is known as a **matrix expression** in OpenCV. This is important because OpenCV has a special class, <a href = "https://docs.opencv.org/4.8.0/d1/d10/classcv_1_1MatExpr.html">**cv::MatExpr**</a>, that handles such matrix expressions. **cv::MatExpr** class works behind the scenes - as a user, you will rarely refer to the class in your code.

:notebook_with_decorative_cover: In addition to simple algebra, **cv::MatExpr** also handles expressions involving comparison operators, operators for constructing other matrices, and higher level operations for computing transposes and inversions. The full list is as follows. In the following list, $A$, $B$ stand for matrices (cv::Mat), $s$ for a scalar (cv::Scalar), $alpha$ for a real-valued scalar (double)

* Addition, subtraction, negation: $A+B$, $A-B$, $A+s$, $A-s$, $s+A$, $s-A$, $-A$
* Scaling: $A*alpha$
* Per-element multiplication and division: $A.mul(B)$, $A/B$, $alpha/A$
* Matrix multiplication: $A*B$
* Transposition: $A.t()$ (means $A^T$)
* Matrix inversion and pseudo-inversion, solving linear systems and least-squares problems: $A.inv([method])$ $(\sim A<sup>-1</sup>)$, $A.inv([method])*B$ $(\sim X: AX=B)$
* Comparison: $A$ `cmpop` $B$, $A$ `cmpop` $alpha$, $alpha$ `cmpop` $A$, where `cmpop` is one of $>, >=, ==, !=, <=, <$. The result of comparison is an 8-bit single channel mask whose elements are set to `255` (if the particular element or pair of elements satisfy the condition) or `0`.
* Bitwise logical operations: $A$ `logicop` $B$, $A$ `logicop` $s$, $s$ `logicop` $A$, $\sim A$, where `logicop` is one of `&` (AND), `|` (or), `^` (NOT).
* Element-wise minimum and maximum: $min(A, B)$, $min(A, alpha)$, $max(A, B)$, $max(A, alpha)$
* Element-wise absolute value: $abs(A)$
* Cross-product, dot-product: $A.cross(B)$, $A.dot(B)$
* Any function of matrix or matrices and scalars that returns a matrix or a scalar, such as norm, mean, sum, countNonZero, trace, determinant, repeat, and others.
* Matrix initializers (`cv::Mat::eye()`, `cv::Mat::zeros()`, `cv::Mat::ones()`), matrix comma-separated initializers, matrix constructors and operators that extract sub-matrices.
* Mat_<destination_type>() constructors to cast the result to the proper type. 

**Example 1** - In this example we show how to compute basic math algebra (addition, subtraction, multiplication etc)

```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    // Lets define a few variables we will use for our matrix algebra
    int scalar {2};
    cv::Mat m0 {cv::Matx<int, 5, 5>::randu(1, 100)}; // 5 x 5 2-D matrix with random integers between 1 and 100
    cv::Mat m1 {cv::Matx<int, 5, 5>::randu(101, 200)}; // 5 x 5 2-D matrix with random integers between 101 and 200

    std::cout << "\nm0 = \n" << m0 << '\n';
    std::cout << "\nm1 = \n" << m1 << '\n';

    //                      Basic Math Algebra 
    //                      ==================

    // 1. Addition & Subtraction of matrices
    auto m2 = m1 + m0;
    auto m3 = m1 - m0;
    std::cout << "\nm1 + m0 = \n" << m2 << '\n';
    std::cout << "\nm1 - m0 = \n" << m3 << '\n';

    // 2. Addition & Subtraction between a matrix and a scalar value
    auto m4 = m0 + scalar; // will add the value of 'scalar' to every element in m0
    auto m5 = m1 - scalar; // will subtract the value of 'scalar' from element in m1
    auto m6 = scalar - m0; // 'scalar' minus every element in m0
    std::cout << "\nm0 + 2 = \n" << m4 << '\n';
    std::cout << "\nm1 - 2 = \n" << m5 << '\n';
    std::cout << "\n2 - m0 = \n" << m6 << '\n'; 

    // 3. Negation of an array
    //    Every element in m0 will be converted to its equivalent 
    //    negative value
    auto m7 = -m0;  
    std::cout << "\nNegation of m0 = \n" << m7 << '\n';

    // 4. Multiply a matrix by a scalar value
    auto m8 = scalar * m1;
    std::cout << "\n2 x m1 = \n" << m8 << '\n';

    // 5. Per-element multiplication
    //    Multiply every element in m0 by an element 
    //    in m1 in the same position
    auto m9 = m0 * m1; 
    auto m10 = m0.mul(m1);  // same as above
    std::cout << "\nm0 * m1 = \n" << m10 << '\n';
    
    std::cout << '\n';

    return 0;

}
```

**Output**

    m0 = 
    [80, 15, 59, 57, 14;
    35, 42, 39, 35, 27;
    24, 66, 37, 69, 10;
    52, 9, 9, 25, 19;
    71, 57, 16, 98, 40]

    m1 = 
    [116, 138, 144, 143, 115;
    133, 144, 117, 108, 197;
    109, 146, 110, 116, 133;
    199, 139, 195, 116, 140;
    164, 189, 174, 166, 142]

    m1 + m0 = 
    [196, 153, 203, 200, 129;
    168, 186, 156, 143, 224;
    133, 212, 147, 185, 143;
    251, 148, 204, 141, 159;
    235, 246, 190, 264, 182]

    m1 - m0 = 
    [36, 123, 85, 86, 101;
    98, 102, 78, 73, 170;
    85, 80, 73, 47, 123;
    147, 130, 186, 91, 121;
    93, 132, 158, 68, 102]

    m0 + 2 = 
    [82, 17, 61, 59, 16;
    37, 44, 41, 37, 29;
    26, 68, 39, 71, 12;
    54, 11, 11, 27, 21;
    73, 59, 18, 100, 42]

    m1 - 2 = 
    [114, 136, 142, 141, 113;
    131, 142, 115, 106, 195;
    107, 144, 108, 114, 131;
    197, 137, 193, 114, 138;
    162, 187, 172, 164, 140]

    2 - m0 = 
    [-78, -13, -57, -55, -12;
    -33, -40, -37, -33, -25;
    -22, -64, -35, -67, -8;
    -50, -7, -7, -23, -17;
    -69, -55, -14, -96, -38]

    Negation of m0 = 
    [-80, -15, -59, -57, -14;
    -35, -42, -39, -35, -27;
    -24, -66, -37, -69, -10;
    -52, -9, -9, -25, -19;
    -71, -57, -16, -98, -40]

    2 x m1 = 
    [232, 276, 288, 286, 230;
    266, 288, 234, 216, 394;
    218, 292, 220, 232, 266;
    398, 278, 390, 232, 280;
    328, 378, 348, 332, 284]

    m0 * m1 = 
    [9280, 2070, 8496, 8151, 1610;
    4655, 6048, 4563, 3780, 5319;
    2616, 9636, 4070, 8004, 1330;
    10348, 1251, 1755, 2900, 2660;
    11644, 10773, 2784, 16268, 5680]


**Example 2** - In this example we will look at matrix inversion and transpose

```c++
#include "opencv2/core.hpp"
#include <iostream>

int main()
{
    /* 1. Matrix inversion - The invert() function provides 3 algorithms for matrix inversion
     *    (a) cv::DECOMP_LU - which means LU decomposition & works only for any non-singular matrix
     *    (b) cv::DECOMP_CHOLESKY - which solves the inversion by Cholesky decomposition. It works only
     *        for symmetric, positive definite matrices - which is a square matrix that is symmetric, 
     *        has positive diagonal elements, and is diagonally dominant
     *    (c) cv::DECOMP_SVD - which solves the inversion by Singular Value Decomposition (SVD). SVD is only
     *        workable for matrices that are singular or non-square.
    */
    
    // 1-D C-style array with 16 elements
    float a[] = {5, 6, 6, 8, 2, 2, 2, 8, 
                 6, 6, 2, 8, 2, 3, 6, 7}; 

    // a. Use LU decomposition to find the inverse of a matrix
    cv::Mat m11 { 4, 4, CV_32F, a }; // create a 4 X 4 non-singular array/matrix     
    std::cout << "\nm11 = \n" << m11 << '\n';
    std::cout << "\nInverse of m11 using LU decomposition = \n" 
              << m11.inv(cv::DECOMP_LU) << '\n';

    // b. Use Cholesky decomposition to find the inverse of a matrix
    float  b[] {5, 7, 6, 5, 7, 10, 8, 7, 
                6, 8, 10, 9, 5, 7, 9, 10};
    cv::Mat m12 {4, 4, CV_32F, b}; // create a 4 x 4 symmetric, positive definite matrix
    std::cout << "\nm12 = \n" << m12 << '\n';
    std::cout << "\nInverse of m12 using Cholesky decomposition = \n" 
              << m12.inv(cv::DECOMP_CHOLESKY) << '\n';

    // c. Use SVD decomposition to find the inverse of a matrix
    cv::Mat m13 {8, 2, CV_32F, a}; // 8 x 2 non-square matrix
    std::cout << "\nm13 = \n" << m13 << '\n';
    std::cout << "\nInverse of m13 using SVD decomposition = \n" 
              << m13.inv(cv::DECOMP_SVD) << '\n';
    
    // 2. Matrix Transpose - The transpose of a matrix is found by 
    //    interchanging its rows into columns or columns into rows.
    std::cout << "\nTranspose of m11 = \n" << m11.t() << '\n';

    std::cout << '\n';

    return 0;   
    
}
```

**Output**

    m11 = 
    [5, 6, 6, 8;
    2, 2, 2, 8;
    6, 6, 2, 8;
    2, 3, 6, 7]

    Inverse of m11 using LU decomposition = 
    [-16.999969, -8.9999838, 11.999978, 15.999969;
    16.999969, 8.7499838, -11.749978, -15.999969;
    -3.9999924, -2.2499959, 2.7499948, 3.9999924;
    0.99999809, 0.74999899, -0.74999869, -0.99999809]

    m12 = 
    [5, 7, 6, 5;
    7, 10, 8, 7;
    6, 8, 10, 9;
    5, 7, 9, 10]

    Inverse of m12 using Cholesky decomposition = 
    [67.998375, -40.99902, -16.999586, 9.9997511;
    -40.99902, 24.999409, 9.9997501, -5.9998503;
    -16.999586, 9.9997501, 4.9998941, -2.9999368;
    9.999753, -5.9998512, -2.9999371, 1.9999624]

    m13 = 
    [5, 6;
    6, 8;
    2, 2;
    2, 8;
    6, 6;
    2, 8;
    2, 3;
    6, 7]

    Inverse of m13 using SVD decomposition = 
    [0.047171813, 0.039701179, 0.027321242, -0.099466398, 0.08196371, -0.099466398, 0.0061899661, 0.060832452;
    -0.010245457, 0.00042689257, -0.010458915, 0.084951982, -0.031376734, 0.084951982, 0.0054429048, -0.015474922]

    Transpose of m11 = 
    [5, 2, 6, 2;
    6, 2, 6, 3;
    6, 2, 2, 6;
    8, 8, 8, 7]

