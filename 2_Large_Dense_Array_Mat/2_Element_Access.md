## Accessing cv::Mat elements individually

:notebook_with_decorative_cover: The two primary options for accessing individual elements are to access them by **Location** or through **Iteration**. 

### 1. Access by Location

:notebook_with_decorative_cover: This is the basic means of direct access 

:notebook_with_decorative_cover: It makes use of template member function **at<>()**. There are many variations of this function that take different arguments for arrays of different numbers of dimensions. The way this
function works is that you specialize the **at<>()** template to the type of data the matrix or large array contains, then access that element using the **row** and/or **column** locations of the data you want.

:notebook_with_decorative_cover: What do we mean when we say **specialize the at<>() template**? This means that inside the angle brackets (**<>**), we use a data type or object that can handle the primitive data type of our array elements. For example, when dealing with a single channel 2-D array whose primitive data type is **32-bit or 64-bit floating point**, we use `at<float>()` to handle each individual array element. When dealing with a 2-D array with 2 channels whose elements are of type **integer**, we use `at<cv::Vec2i>()`. This is because each location in the array is made up of two integer values (one for each channel) and **cv::Vec2i** is capable of handling two integer values as one object.

:notebook_with_decorative_cover: The following code will provide more examples.

**Example 1**
```c++
#include "opencv2/core.hpp"
#include <iostream>

int main ()
{
    // 1. A 2 dimensional cv::Mat object with 1 channel 
    //    Because you are extracting 1 value per row x column location
    //    you need a data type that can store a single value e.g. float
    const cv::Mat m1 {cv::Mat::eye(10, 10, CV_32F)}; // 10 x 10 2-D array with 1 channel
    std::cout << "\nm1 (10 x 10 2-D array with 1 channel) = \n" << m1 << '\n';
    // Extract value at location 4th row and 4th column. 
    // Remember we start counting rows/columns from 0 
    auto v1 = m1.at<float>(3, 3);
    std::cout << "\nValue at (3, 3) = " << v1 << '\n';

    // 2. A 2-dimensional multi-channel cv::Mat object with 2 channels 
    //    You need a data type that can store 2 values per row x column location
    //    e.g. cv::Vec2i, cv::Vec2f or cv::Vec3f
    const cv::Mat m2 {5, 5, CV_64FC2, cv::Scalar(0.43, 0.86)}; // 5 x 5 2-D array with 2 channels
    std::cout << "\nm2 (5 x 5 2-D array with 2 channels) = \n" << m2 << '\n';    
    // Extract values at location 3th row and 4th column.
    auto v2 = m2.at<cv::Vec2d>(2, 3); 
    // We can even extract each channel value using the operator `[]` 
    auto v2Channel1Value = v2[0];          // get the channel 1 value
    auto v2Channel2Value = v2[1];          // get the channel 2 value
    std::cout << "\nValues at (2, 3) = " << v2 
              << "\nChannel 1 value = " << v2Channel1Value 
              << "\nChannel 2 value = " << v2Channel2Value << '\n';
              

    // 3. A 2-dimensional multi-channel cv::Mat object with 3 channels 
    //    You need a data type that can store 3 values per row x column location
    //    e.g cv::Vec3i, cv::Vec3f, cv::Vec3d
    const cv::Mat m3 {5, 5, CV_32FC3, cv::Scalar(124.8f, 34.5f, 98.5f)}; // 5 x 5 2-D array with 3 channels
    std::cout << "\nm3 (5 x 5 2-D array with 3 channels) = \n" << m3 << '\n';
    // Extract values at location 4th row and 4th column.
    auto v3 = m3.at<cv::Vec3f>(3, 3); 
    // We can even extract each channel value using the operator `[]`  
    float v3Channel1Value = v3[0];            // get the channel 1 value
    float v3Channel2Value = v3[1];            // get the channle 2 value
    float v3Channel3Value = v3[2];            // get the channel 3 value
    std::cout << "\nValues at (3, 3) = " << v3
              << "\nChannel 1 value = " << v3Channel1Value 
              << "\nChannel 2 vlaue = " << v3Channel2Value 
              << "\nChannel 3 value = " << v3Channel3Value << '\n';

    // 4. A 2 dimensional cv::Mat array with 50 random integers between 1 and 100     
    cv::Mat m4 {cv::Matx<int, 1, 50>::randu(1, 100)};
    std::cout << "\nm4 (array with 50 random integers between 1 and 100) = " 
              << m4 << '\n';
    // Extract 4th value in array
    auto v4 = m4.at<int>(3); 
    std::cout << "Element at index = 3 ---> " << v4 << '\n';
    
    std::cout << '\n';

    return 0;
}
```

**Output**

    m1 (10 x 10 2-D array with 1 channel) = 
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 0;
    0, 1, 0, 0, 0, 0, 0, 0, 0, 0;
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0;
    0, 0, 0, 1, 0, 0, 0, 0, 0, 0;
    0, 0, 0, 0, 1, 0, 0, 0, 0, 0;
    0, 0, 0, 0, 0, 1, 0, 0, 0, 0;
    0, 0, 0, 0, 0, 0, 1, 0, 0, 0;
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0;
    0, 0, 0, 0, 0, 0, 0, 0, 1, 0;
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1]

    Value at (3, 3) = 1

    m2 (5 x 5 2-D array with 2 channels) = 
    [0.43, 0.86, 0.43, 0.86, 0.43, 0.86, 0.43, 0.86, 0.43, 0.86;
    0.43, 0.86, 0.43, 0.86, 0.43, 0.86, 0.43, 0.86, 0.43, 0.86;
    0.43, 0.86, 0.43, 0.86, 0.43, 0.86, 0.43, 0.86, 0.43, 0.86;
    0.43, 0.86, 0.43, 0.86, 0.43, 0.86, 0.43, 0.86, 0.43, 0.86;
    0.43, 0.86, 0.43, 0.86, 0.43, 0.86, 0.43, 0.86, 0.43, 0.86]

    Values at (2, 3) = [0.43, 0.86]
    Channel 1 value = 0.43
    Channel 2 value = 0.86

    m3 (5 x 5 2-D array with 3 channels) = 
    [124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5;
    124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5;
    124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5;
    124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5;
    124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5, 124.8, 34.5, 98.5]

    Values at (3, 3) = [124.8, 34.5, 98.5]
    Channel 1 value = 124.8
    Channel 2 vlaue = 34.5
    Channel 3 value = 98.5

    m4 (array with 50 random integers between 1 and 100) = [80, 15, 59, 57, 14, 35, 42, 39, 35, 27, 24, 66, 37, 69, 10, 52, 9, 9, 25, 19, 71, 57, 16, 98, 40, 16, 38, 44, 43, 15, 33, 44, 17, 8, 97, 9, 46, 10, 16, 33, 99, 39, 95, 16, 40, 64, 89, 74, 66, 42]
    Element at index = 3 ---> 57

### 2. Access through Iteration

:notebook_with_decorative_cover: There are two common ways you can sequentially access, iterate or loop through the elements of a cv::Mat object

#### Use iterator templates

:notebook_with_decorative_cover: This mechanism is based on, and works more or less identically to, the analogous mechanism provided by the **C++ Standard Template Library (STL)** containers. 

:notebook_with_decorative_cover: OpenCV provides a pair of iterator templates, one for **const** (i.e., arrays that cannot be modified after creation) and one for **non-const** (i.e., arrays that can be modified after creation) arrays. These iterators are named **cv::MatIterator_<>** and **cv::MatConstIterator_<>**, respectively. Since these are templates, you have to include a data type within the angle bracket that can handle the data of your array, the same way we used the `at<>()` template function above. For example, if dealing with a single channel 2-D array whose primitive data type is **32-bit or 64-bit floating point**, we use `cv::MatIterator_<float>` or `cv::MatConstIterator_<float>` to handle each individual array element. When dealing with a 2-D array with 2 channels whose elements are of type **integer**, we use `cv::MatIterator_<cv::Vec2i>` or `cv::MatConstIterator_<cv::Vec2i>`. 

:notebook_with_decorative_cover: cv::Mat has two methods `begin<>()` and `end<>()` that are used with these iterator templates. **begin<>()** returns an iterator object pointing to the start of the array, while **end<>()** returns an iterator object pointing to the **last position of the array plus 1 extra position**. There are also two other methods `rbegin<>()` and `rend<>()` that work similar to `begin<>()` and `end<>()`, but are used if you want to iterate over an array in reverse. Inside the angle brackets you add the data type or object that can handle the primitive data type of your array elements. For example, if dealing with a single channel 2-D array whose primitive data type is **32-bit or 64-bit floating point**, we use `cv::Mat::begin<float>()` or `cv::Mat::end<float>()` to handle each individual array element. When dealing with a 2-D array with 2 channels whose elements are of type **integer**, we use `cv::Mat::begin<cv::Vec2i>()` or `cv::Mat::end<cv::Vec2i>()`.

:notebook_with_decorative_cover: You will typically use iterator-based access when doing operations over an entire array, e.g. when adding two arrays. At every location the same exact operation will be performed.

:notebook_with_decorative_cover: This method of iteration is convinient because the iterators are smart enough to handle the continuous packing and non-continuous packing cases automatically, as well as handling any number of dimensions in the array. Remember from earlier notes we said that when your array is stored in memory it is laid out row after row, but these rows may or may not be packed continuously - there may be a gap between the rows. This is were *continuous packing and non-continuous packing cases*  arise from. If you are curious, use the member function `isContinuous()` to check if the members of your array are continuously packed before iterating through them.

:notebook_with_decorative_cover: Since these cv::Mat iterators are random-access iterators, they can be passed to any C++ STL algorithm.

:notebook_with_decorative_cover: Iterators can also be viewed as pointers. As such if you want to extract the actual value pointed to by an iterator use the de-reference operator (`*`) - an asterisk. If **itr** is the name of your iterator, to get the value it is pointing to use `*itr`.

:notebook_with_decorative_cover: To move iterators 1 position either forward or backward use increment (++) or decrement (--) operators, respectively. For example, `++iterator` moves the iterator forward one position, `--iterator` moves the iterator backward one position.

:notebook_with_decorative_cover: When using iterators you should always make sure your iterator object does not move beyond the end of your array as this can lead to **undefined behaviour** from your C++ compiler. Here we usually take advantage of the `end()` function, mainly the fact that it points to 1 position after the end of an array. We usually use a conditional expression such as `iterator != cv::Mat::end()` to check if we have reached the end of an array. You will see this in our example below.

:notebook_with_decorative_cover: Iterators work with C++ loops e.g., `for` and `while` loops

**Example 2**

```c++
#include "opencv2/core.hpp"
#include <iostream>

int main ()
{
    // 1. Compute the sum of all elements in a 3 x 3 2-dimensional 
    //    array with random float values between 1 and 100

    const cv::Mat m5 {cv::Matx<float, 3, 3>::randu(1, 100)}; 
    std::cout << "\nm5 (3 x 3 2-dimensional array with random float values between 1 and 100) = \n" 
              << m5 << '\n';             
    std::cout << "\nAre values of array m5 continuous: " 
              << std::boolalpha << m5.isContinuous() << '\n'; 

    /* 
     * Create iterators to loop through individual elements of array
     *
     * Since we have no intention of using our iterators to alter the 
     * values of our array, we use the 'const' version.
     * 
     * You can also use 'auto' so that the compiler can deduce the iterator 
     * type itself
     * 
    */ 
    cv::MatConstIterator_<float> itr { m5.begin<float>() }; // iterator pointing to start of array
    auto itr_end { m5.end<float>() };   // iterator pointing to a position 1 past end of array
                                        // Note the use of 'auto'

    double sum { 0.0 }; // variable to hold the sum of all array elements

    // loop/iterate through array elements as follows
    for(itr; itr != itr_end; ++itr)
    {
      sum += *itr; // this is the same as `sum = sum + *itr'. Make sure to 
                   // dereference the iterator in order to get the actual 
                   // value pointed to by the iterator
    }

    std::cout << "Sum of elements in array m5 = " << sum << '\n';


    // 2. Use a while loop to change the values of each element by 
    //    multiplying it by the value 3

    // Create a 3 x 3 2-dimensional array with random integer values between 20 and 50
    cv::Mat m6 {cv::Matx<int, 3, 3>::randu(20, 50)}; 
    std::cout << "\nm6 (3x3 2-dimensional array with random integer values between 20 and 50) = \n" 
              << m6 << '\n';             
    std::cout << "\nAre values of array m6 continuous: " 
              << std::boolalpha << m6.isContinuous() << '\n'; 

    /*
     * Create iterators to loop through individual elements of array
     *
     * Since we want to use our iterators to alter the values of our array, 
     * we use the 'non-const' version. This will only work if your array is also 'non-const'
     * 
     * We can also use 'auto'
     * 
    */ 
    cv::MatIterator_<int> itrm6 { m6.begin<int>() }; 
    auto itrm6_end { m6.end<int>() };   

    while(itrm6 != itrm6_end) // run the loop as long as our iterator does not go beyond the array
    {
      *itrm6 = (*itrm6) * 3; // multiply each array value by 3 and also replace the value with the new value

      ++itrm6; // move iterator to next position. If you omit this, your while loop becomes an infinite loop
                // since the while condition will always be true as the iterator never reaches the end of the array
    }

    std::cout << "\nModified m6 array = " << m6 << '\n';

    // 3. Loop in reverse

    // Create a 3x3 2-D array to hold 32-bit floating point values. 
    // Fill array with random numbers from -1.0 to 1.0
    const cv::Mat m7 { cv::Matx<float, 3, 3>::randu(-1.0f, 1.0f) }; 
    
    std::cout << "\nm7 (3x3 2-D array with random numbers from -1.0 to 1.0) = \n" 
              << m7 << '\n';
    std::cout << "\nAre values of array m7 continuous: " 
              << std::boolalpha << m7.isContinuous() << '\n'; 

    /*
     * Create iterators to loop through individual elements of array in reverse
     *
     * Take note of 'std::reverse_iterator' when declaring reverse iterators
     * Also be aware of any spaces between angle brackets. 
     * 
     * However, just like above examples, you can use 'auto' 
     * 
     * Also take note of the following: 
     *  a. The function rbegin() returns an iterator pointing to start of array,
     *     which in this case is the last value in array 
     *  b. The function rend() returns an iterator pointing to a position 1 past 
     *     end of array, which in this case is 1 position past the start of array
     * 
    */ 
    std::reverse_iterator<cv::MatConstIterator_<float> > itrm7 { m7.rbegin<float>() }; 
    auto itrm7_end { m7.rend<float>() }; 

    std::cout << "Iterate through array m7 in reverse: ";
    for(itrm7; itrm7 != itrm7_end; ++itrm7) // here take note that our iterator is still 
                                                // incremented when moving to next position even 
                                                // though we are traversing in reverse
    {
      std::cout << (*itrm7) << ' '; // print the array values in reverse order
    }

    // 4. Iterator over an array with more than one channel

    const cv::Mat m8 { 3, 3, CV_32FC2, cv::Scalar(-1.0f, 1.0f) }; // 3x3 2-D array with 2 channels
    std::cout << "\n\nm8 (3x3 2-D array with 2 channels) = \n" << m8 << '\n';
    std::cout << "\nAre values in m8 continuous: " 
              << std::boolalpha << m8.isContinuous() << '\n';

    /*
     * Create iterators to loop through individual elements of array
     *
     * Since we have no intention of using our iterators to alter the values of our array, 
     * we use the 'const' version
     * 
     * Since our array has 2 channels we need to use an object that can hold to values at a time, 
     * the best is cv::Vec2f.
     * 
    */ 
    cv::MatConstIterator_<cv::Vec2f> itrm8 { m8.begin<cv::Vec2f>() }; 
    auto itrm8_end  { m8.end<cv::Vec2f>() };   

    std::cout << "Iterate through an array m8 with 2 channels: ";

    for(itrm8; itrm8 != itrm8_end; ++itrm8)
    {
      // Values are returned as a pair [channel 1 value, channel 2 value]
      std::cout << *itrm8 << ' '; 
    }

    std::cout << '\n';
    
    return 0;
}
```

**Output**

    m5 (3 x 3 2-dimensional array with random float values between 1 and 100) = 
    [16.782093, 65.279373, 43.120232;
    68.315094, 35.603413, 60.470951;
    28.508604, 65.332199, 44.140106]

    Are values of array m5 continuous: true
    Sum of elements in array m5 = 427.552

    m6 (3x3 2-dimensional array with random integer values between 20 and 50) = 
    [23, 28, 41;
    48, 27, 37;
    40, 43, 48]

    Are values of array m6 continuous: true

    Modified m6 array = [69, 84, 123;
    144, 81, 111;
    120, 129, 144]

    m7 (3x3 2-D array with random numbers from -1.0 to 1.0) = 
    [-0.92971963, -0.37295127, 0.63198775;
    0.33973995, 0.29309866, -0.81395978;
    0.61375809, 0.63680512, 0.7406196]

    Are values of array m7 continuous: true
    Iterate through array m7 in reverse: 0.74062 0.636805 0.613758 -0.81396 0.293099 0.33974 0.631988 -0.372951 -0.92972 

    m8 (3x3 2-D array with 2 channels) = 
    [-1, 1, -1, 1, -1, 1;
    -1, 1, -1, 1, -1, 1;
    -1, 1, -1, 1, -1, 1]

    Are values in m8 continuous: true
    Iterate through an array m8 with 2 channels: [-1, 1] [-1, 1] [-1, 1] [-1, 1] [-1, 1] [-1, 1] [-1, 1] [-1, 1] [-1, 1] 


