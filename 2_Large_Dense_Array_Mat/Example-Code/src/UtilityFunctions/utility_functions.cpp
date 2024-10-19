#include "UtilityFunctions/utility_functions.h"

namespace CPP_CV {

    namespace General {

        std::string_view openCVDescriptiveDataType(int value)
	    {
            switch (value)
		    {
                case 0:
                    return "CV_8U or CV_8UC1 -> Array with 1 channel and primitive data type 8-bit unsigned integers with range (0 to 255)";
                case 1:
                    return "CV_8S or CV_8SC1 -> Array with 1 channel and primitive data type 8-bit signed integers with range (-128 to 127)";
                case 2:
                    return "CV_16U or CV_16UC1 -> Array with 1 channel and primitive data type 16-bit unsigned integers with range (0 to 65,535)";
                case 3:
                    return "CV_16S or CV_16SC1 -> Array with 1 channel and primitive data type 16-bit signed integers with range (-32,768 to 32,767)";
                case 4:
                    return "CV_32S or CV_32SC1 -> Array with 1 channel and primitive data type 32-bit signed integers with range (-2,147,483,648 to 2,147,483,647)";
                case 5:
                    return "CV_32F or CV_32FC1 -> Array with 1 channel and primitive data type 32-bit decimal values of type float with range (-3.40282347E+38 to 3.40282347E+38)";
                case 6:
                    return "CV_64F or CV_64FC1 -> Array with 1 channel and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)";
                case 8:
                    return "CV_8UC2 -> Array with 2 channels and primitive data type 8-bit unsigned integers with range (0 to 255)";
                case 9:
                    return "CV_8SC2 -> Array with 2 channels and primitive data type 8-bit signed integers with range (-127 to 128)";
                case 10:
                    return "CV_16UC2 -> Array with 2 channels and primitive data type 16-bit unsigned integers with range (0 to 65,535)";
                case 11:
                    return "CV_16SC2 -> Array with 2 channels and primitive data type 16-bit signed integers with range (-32,768 to 32,767)";
                case 12:
                    return "CV_32SC2 -> Array with 2 channels and primitive data type 32-bit signed integers with range (-2,147,483,648 to 2,147,483,647)";
                case 13:
                    return "CV_32FC2 -> Array with 2 channels and primitive data type 32-bit decimal values of type float with range (-3.40282347E+38 to 3.40282347E+38)";
                case 14:
                    return "CV_64FC2 -> Array with 2 channels and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)";
                case 16:
                    return "CV_8UC3 -> Array with 3 channels and primitive data type 8-bit unsigned integers with range (0 to 255)";
                case 17:
                    return "CV_8SC3 -> Array with 3 channels and primitive data type 8-bit signed integers with range (-127 to 128)";
                case 18:
                    return "CV_16UC3 -> Array with 3 channels and primitive data type 16-bit unsigned integers with range (0 to 65,535)";
                case 19:
                    return "CV_16SC3 -> Array with 3 channels and primitive data type 16-bit signed integers with range (-32,768 to 32,767)";
                case 20:
                    return "CV_32SC3 -> Array with 3 channels and primitive data type 32-bit signed integers with range (-2,147,483,648 to 2,147,483,647)";
                case 21:
                    return "CV_32FC3 -> Array with 3 channels and primitive data type 32-bit decimal values of type float with range (-3.40282347E+38 to 3.40282347E+38)";
                case 22:
                    return "CV_64FC3 -> Array with 3 channels and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)";
                case 24:
                    return "CV_8UC4 -> Array with 4 channels and primitive data type 8-bit unsigned integers with range (0 to 255)";
                case 25:
                    return "CV_8SC4 -> Array with 4 channels and primitive data type 8-bit signed integers with range (-127 to 128)";
                case 26:
                    return "CV_16UC4 -> Array with 4 channels and primitive data type 16-bit unsigned integers with range (0 to 65,535)";
                case 27:
                    return "CV_16SC4 -> Array with 4 channels and primitive data type 16-bit signed integers with range (-32,768 to 32,767)";
                case 28:
                    return "CV_32SC4 -> Array with 4 channels and primitive data type 32-bit signed integers with range (-2,147,483,648 to 2,147,483,647)";
                case 29:
                    return "CV_32FC4 -> Array with 4 channels and primitive data type 32-bit decimal values of type float with range (-3.40282347E+38 to 3.40282347E+38)";
                case 30:
                    return "CV_64FC4 -> Array with 4 channels and primitive data type 64-bit decimal values of type float with range (-1.797693134862315E+308 to 1.797693134862315E+308)";
                default:
                    return "Unknown data type!";
		    }
	}
    
    }
}