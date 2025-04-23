# Image decompression with `cv::imdecode()`

:notebook_with_decorative_cover: The `cv::imdecode()` function allows us to decompress an image from a character buffer into an image array. It has the syntax: `cv::Mat cv::imdecode(cv::InputArray buf, int flags)`.

1. `buf` - Memory buffer, which normally has `std::vector<uchar>` type.
2. `flags` - Flags of type `cv::ImreadModes`. These are the same flags used by `cv::imread()`.

:notebook_with_decorative_cover: The function reads an image from the specified buffer in the memory. If the buffer is too short or contains invalid data, the function returns an empty matrix (`cv::Mat::data==NULL` or `cv::Mat::empty() == true`).

:notebook_with_decorative_cover: `cv::imdecode()` can deduce the correct codec to use from the first bytes of the compressed image in the buffer NOT from the file extension.