#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

#include "opencv2/core.hpp" 

#include <string_view>

namespace CPP_CV {

    namespace General {

        /**
         * @brief Returns a more descriptive data type for OpenCV integer data type values. 
         *        This is needed because when you ask OpenCV the data type of any of its 
         *        N-Dimensional array objects e.g. cv::Mat using a member function like 
         *        'type()', OpenCV returns an integer value, which does not offer any 
         *        description of what the integer value refers to. 
         * 
         * @param value OpenCV data type as an integer value
         * @return Descriptive string of data type 
         */
        std::string_view openCVDescriptiveDataType(int value);

    }

    namespace SparseArrays {

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

                        ++i; //increment std::vector index counter
                    }
                }
            }  
            
            return sparseArray;
        }


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
                            //<< idx[2] << ", " << idx[3] << ")\n";

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

    }
}


#endif