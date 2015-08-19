#include <iostream>
#include <string>
#include <vector>

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect/objdetect.hpp"

using namespace std;
using namespace cv;

const char* params =
     "{ h | help     | false | print usage                                   }"
     "{   | detector |       | XML file with a cascade detector              }"
     "{   | image    |       | image to detect objects on                    }"
     "{   | video    |       | video file to detect on                       }"
     "{   | camera   | false | whether to detect on video stream from camera }";


void drawDetections(const vector<Rect>& detections,
                    const Scalar& color,
                    Mat& image)
{
    for (size_t i = 0; i < detections.size(); ++i)
    {
        rectangle(image, detections[i], color, 2);
    }
}

const Scalar red(0, 0, 255);
const Scalar green(0, 255, 0);
const Scalar blue(255, 0, 0);
const Scalar colors[] = {red, green, blue};

int main(int argc, char** argv)
{
    // Parse command line arguments.
    CommandLineParser parser(argc, argv, params);
    // If help flag is present, print help message and exit.
    if (parser.get<bool>("help"))
    {
        parser.printParams();
        return 0;
    }

    string detector_file = parser.get<string>("detector");
    CV_Assert(!detector_file.empty());
    string image_file = parser.get<string>("image");
    string video_file = parser.get<string>("video");
    bool use_camera = parser.get<bool>("camera");

    // TODO: Load detector.
	cv::CascadeClassifier *cascade = 0;
	cascade.load(detector_file);

   
    if (!image_file.empty())
    {
        Mat image;
		image = imread(image_file);
		vector<Rect>& objects;
		//cascade.detectMultiScale(image, objects, 1.1, 3, 0, Size(), Size());
		drawDetections(objects, green, image);
    }
    else if (!video_file.empty())
    {
	/*Mat image;
	vector<Rect>& objects;
        VideoCapture::open(video_file);
	while(VideoCapture::read(image))
	{
		CascadeClassifier::detectMultiScale(image, objects, 1.1, 3, 0, Size(), Size());
		drawDetections(objects, green, image);
	}
	while(VideoCapture::grab());
	VideoCapture::release();*/
    }


    else if (use_camera)
    {
        // TODO: Detect objects on a live video stream from camera.

    }
    else
    {
        cout << "Declare a source of images to detect on." << endl;
    }

    return 0;
}



