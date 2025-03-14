#include "opencv2/core.hpp"// for OpenCV core types, cv::Range, cv::TermCriteria and kmeans()
#include <iostream>
int main()
{
    // Setting up termination criteria using cv::TermCriteria class
    // ============================================================

    // Don't worry about this group of arguments
    // It is the next group that is important for now
    cv::RNG rng(12345);
    const int MAX_CLUSTERS = 5;
    int k, clusterCount = rng.uniform(2, MAX_CLUSTERS+1);
    int i, sampleCount = rng.uniform(1, 1001);
    cv::Mat points(sampleCount, 1, CV_32FC2);
    cv::Mat labels;
    clusterCount = MIN(clusterCount, sampleCount);
    std::vector<cv::Point2f> centers;

    // This is the important bit where we set our termination criteria
    // ===============================================================

    // We want to use either maxCount or epsilon to terminate algorithm
    int type = cv::TermCriteria::EPS | cv::TermCriteria::COUNT; 
    int maxCount = 10; // terminate after 10 iterations
    double epsilon = 1.0; // terminate if accuracy approaches 1.0

    // Use constructor to set everything up
    // We want our algorithm to run and terminate after 10 iterations
    // or if accuracy reaches 1.0
    cv::TermCriteria terminationCriteria { type, maxCount, epsilon };

    // Now execute the kmeans algorithm
    double compactness = cv::kmeans(points, 
                                    clusterCount, 
                                    labels, 
                                    terminationCriteria, // this is our termination criteria object
                                    3, 
                                    cv::KMEANS_PP_CENTERS, 
                                    centers);

    
    
    std::cout << '\n';
    
    return 0;
}