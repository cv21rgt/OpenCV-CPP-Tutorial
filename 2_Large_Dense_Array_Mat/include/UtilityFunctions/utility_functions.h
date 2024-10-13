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
}


#endif