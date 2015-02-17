#include <cv.h>
#include <highgui.h>

using namespace cv;

/// Global Variables
const int maxRGB = 255;

int min_BGR[3];

int max_BGR[3];

/// Matrices to store images
Mat src;
Mat dst;

Mat color_filter(Mat mat) {
  inRange(mat, Scalar(min_BGR[0], min_BGR[1], min_BGR[2]),  Scalar(max_BGR[0], max_BGR[1], max_BGR[2]), dst);
  
  return dst;
}

/**
 * @function on_trackbar
 * @brief Callback for trackbar
 */
void on_trackbar( int, void* )
{

  imshow( "Image Threshold",  color_filter(src) );
}

int main( int argc, char** argv )
{
 /// Read image
 src = imread(argv[1]);

 if( !src.data ) { printf("Error loading src \n"); return -1; }

 min_BGR[3] = {0};
 max_BGR[3] = {0};

 for (int i=0; i<argc-2 && i<3; i++) {
   min_BGR[i] = atoi(argv[i+2]);
 }

 for (int j=0; j<argc-5 && j<3; j++) {
   max_BGR[j] = atoi(argv[j+5]);
 }

 /// Create Windows
 namedWindow("Image", WINDOW_AUTOSIZE);
 namedWindow("Image Threshold", WINDOW_AUTOSIZE);
 namedWindow("Color Threshold", WINDOW_AUTOSIZE);

 moveWindow("Image", 100, 25);

 // create trackbars for color change
 createTrackbar ("Min B", "Color Threshold", &min_BGR[0], maxRGB, on_trackbar);
 createTrackbar ("Min G", "Color Threshold", &min_BGR[1], maxRGB, on_trackbar);
 createTrackbar ("Min R", "Color Threshold", &min_BGR[2], maxRGB, on_trackbar);

 createTrackbar ("Max B", "Color Threshold", &max_BGR[0], maxRGB, on_trackbar);
 createTrackbar ("Max G", "Color Threshold", &max_BGR[1], maxRGB, on_trackbar);
 createTrackbar ("Max R", "Color Threshold", &max_BGR[2], maxRGB, on_trackbar);

 imshow("Image", src);
 on_trackbar(0,0);

 /// Wait until user press some key
 waitKey(0);
 return 0;
}
