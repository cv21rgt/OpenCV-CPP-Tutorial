#include "UtilityFunctions/utility_functions.h"

#include <filesystem> // handles files

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


    namespace ReadWriteFiles {

        /**
         * @brief Get the File Extension from a full file path e.g. from the file path 
         *        `Example-Code/temporary-files/write.xml` you will get the extension `xml`
         * 
         * @param filePath full path including filename and extension
         * @return std::string file extension: Returns an empty string if there is no file extension
         */
        std::string getFileExtension(std::string_view filePath)
        {
            // Use the file path to create an object of std::filesystem
            std::filesystem::path p { filePath };

            // get the file extension e.g .xml, .json etc
            std::string fileExtension { p.extension() };

            if(fileExtension.empty()) // If there is no file extension return an empty string 
            {
                return "";
            }
            else // if there is a fileExtension, it will have the form ".fileExtension"
            {
                // extract the sub string after the dot or position = 0
                std::string substring { fileExtension.substr(1) };

                return substring;
            }
        }
    }


    namespace BasicImageProcessing {

        /**
         * @brief Return the pixel value from a single-channel image
         * 
         * @param image Single-channel image
         * @param type OpenCV data type of pixel values in image e.g. CV_8U or CV_8UC1
         * @param y Row index to find pixel. We start counting indices from '0'. 
         *          The first row is found at the top of the image, and increases 
         *          from top to bottom of image.
         * @param x Column index to fnd pixel. We start counting indices from '0'.
         *          The first column is found on the left of the image, and increases 
         *          from left to right of image. 
         * @return cv::Scalar Pixel value, which will be stored at index '0' 
         *                    of the cv::Scalar object
         */
        cv::Scalar pixelValue_C1(const cv::Mat& image, int type, int y, int x)
        {
            
            switch (type)
            {
                case CV_8U:
                    return image.at<uchar>(y, x);

                case CV_8S:
                    return image.at<schar>(y, x);

                case CV_16U: 
                    return image.at<ushort>(y, x);

                case CV_16S:
                    return image.at<short>(y, x);

                case CV_32S:
                    return image.at<int>(y, x);

                case CV_32F:
                    return image.at<float>(y, x);

                case CV_64F:
                    return image.at<double>(y, x);
                        
                default: // Use type 'double' as it can hold any of the above types
                    return image.at<double>(y, x);
            }
        }


        /**
         * @brief Return the pixel values from a 2-dimensional image with '2' channels
         * 
         * @param image 2-dimensional image with '2' channels
         * @param type OpenCV data type of pixel values in image e.g. CV_8UC2
         * @param y Row index to find pixel. We start counting indices from '0'. 
         *          The first row is found at the top of the image, and increases 
         *          from top to bottom of image.
         * @param x Column index to find pixel. We start counting indices from '0'.
         *          The first column is found on the left of the image, and increases 
         *          from left to right of image. 
         * @return cv::Scalar Pixel values, which will be stored at indices '0' & '1' 
         *                    of the cv::Scalar object
         */
        cv::Scalar pixelValue_C2(const cv::Mat& image, int type, int y, int x)
        {
            switch (type)
            {
                case CV_8UC2:
                    return image.at<cv::Vec2b>(y, x);

                case CV_8SC2:
                    return image.at<cv::Vec2s>(y, x);

                case CV_16UC2: 
                    return image.at<cv::Vec2w>(y, x);

                case CV_16SC2:
                    return image.at<cv::Vec2s>(y, x);

                case CV_32SC2:
                    return image.at<cv::Vec2i>(y, x);

                case CV_32FC2:
                    return image.at<cv::Vec2f>(y, x);

                case CV_64FC2:
                    return image.at<cv::Vec2d>(y, x);
                        
                default: // Use type 'cv::Vec2d' as it can hold any of the above types
                    return image.at<cv::Vec2d>(y, x);
            }
        }


        /**
         * @brief Return the pixel values from a 2-dimensional image with '3' channels
         * 
         * @param image 2- dimensional image with '3' channels. Color images can be of any format 
         *              e.g. BGR, RGB etc
         * @param type OpenCV data type of pixel values in image e.g. CV_8UC3
         * @param y Row index to find pixel. We start counting indices from '0'. 
         *          The first row is found at the top of the image, and increases 
         *          from top to bottom of image.
         * @param x Column index to find pixel. We start counting indices from '0'.
         *          The first column is found on the left of the image, and increases 
         *          from left to right of image. 
         * @return cv::Scalar Pixel values, which will be stored at indices '0', '1' & '2' 
         *                    of the cv::Scalar object. The values follow the format 
         *                    of the image provided e.g. BGR, RGB etc
         */
        cv::Scalar pixelValue_C3(const cv::Mat& image, int type, int y, int x)
        {
            switch (type)
            {
                case CV_8UC3:
                    return image.at<cv::Vec3b>(y, x);

                case CV_8SC3:
                    return image.at<cv::Vec3s>(y, x);

                case CV_16UC3: 
                    return image.at<cv::Vec3w>(y, x);

                case CV_16SC3:
                    return image.at<cv::Vec3s>(y, x);

                case CV_32SC3:
                    return image.at<cv::Vec3i>(y, x);

                case CV_32FC3:
                    return image.at<cv::Vec3f>(y, x);

                case CV_64FC3:
                    return image.at<cv::Vec3d>(y, x);
                        
                default: // Use type 'cv::Vec3d' as it can hold any of the above types
                    return image.at<cv::Vec3d>(y, x);
            }
        }


        /**
         * @brief Return the pixel values from a 2-dimensional image with '4' channels
         * 
         * @param image 2-dimensional image with '4' channels. Color images can be of any format 
         *              e.g. BGRA, RGBA etc
         * @param type OpenCV data type of pixel values in image e.g. CV_8UC4
         * @param y Row index to find pixel. We start counting indices from '0'. 
         *          The first row is found at the top of the image, and increases 
         *          from top to bottom of image.
         * @param x Column index to find pixel. We start counting indices from '0'.
         *          The first column is found on the left of the image, and increases 
         *          from left to right of image. 
         * @return cv::Scalar Pixel values, which will be stored at indices '0', '1', '2'  
         *                    & '3' of the cv::Scalar object. The values follow the format 
         *                    of the image provided e.g. BGRA, RGBA etc
         */
        cv::Scalar pixelValue_C4(const cv::Mat& image, int type, int y, int x)
        {
            switch (type)
            {
                case CV_8UC4:
                    return image.at<cv::Vec4b>(y, x);

                case CV_8SC4:
                    return image.at<cv::Vec4s>(y, x);

                case CV_16UC4: 
                    return image.at<cv::Vec4w>(y, x);

                case CV_16SC4:
                    return image.at<cv::Vec4s>(y, x);

                case CV_32SC4:
                    return image.at<cv::Vec4i>(y, x);

                case CV_32FC4:
                    return image.at<cv::Vec4f>(y, x);

                case CV_64FC4:
                    return image.at<cv::Vec4d>(y, x);
                        
                default: // Use type 'cv::Vec4d' as it can hold any of the above types
                    return image.at<cv::Vec4d>(y, x);
            }
        }

    }
}