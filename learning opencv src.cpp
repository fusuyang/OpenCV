//Example2_3
#include <cv.h>
#include <highgui\highgui.hpp>
int g_slider_position = 0;
CvCapture *g_capture = NULL;

void onTrackbarSlider(int pos) {
	cvSetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES, pos);
}

int main(int argc, char *argv[]) {
	cvNamedWindow("Example3", CV_WINDOW_AUTOSIZE);
	g_capture = cvCreateFileCapture(argv[1]);
	int frames = static_cast<int>(cvGetCaptureProperty(g_capture, CV_CAP_PROP_FRAME_COUNT));
	if (frames != 0) {
		cvCreateTrackbar("Position", "Example3", &g_slider_position, frames, onTrackbarSlider);
	}
	IplImage *frame;
	while (1) {
		frame = cvQueryFrame(g_capture);
		if (!frame) break;
		cvShowImage("Example2", frame);
		char c = cvWaitKey(33);
		if (c == 27) break;
		cvSetTrackbarPos("Position", "Example3", static_cast<int>(cvGetCaptureProperty(g_capture, CV_CAP_PROP_POS_FRAMES)));//auto refresh sliderbar
	}
	cvReleaseCapture(&g_capture);
	cvDestroyWindow("Example3");
	return 0;
}

//Example2_4
#include <cv.h>
#include <highgui\highgui.hpp>
int g_slider_position = 0;
CvCapture *g_capture = NULL;

void example2_4(IplImage *image) {
	cvNamedWindow("Example2_4-in", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Example2_4-out", CV_WINDOW_AUTOSIZE);
	cvShowImage("Example2_4-in", image);
	IplImage *out = cvCreateImage(cvGetSize(image), IPL_DEPTH_8U, 3);
	cvSmooth(image, out, CV_GAUSSIAN, 3, 3);
	cvShowImage("Example2_4-out", out);
	cvReleaseImage(&out);
	cvWaitKey(0);
	cvDestroyWindow("Example2_4-in");
	cvDestroyWindow("Example2_4-out");
}

int main(int argc, char *argv[]) {
	IplImage *img = cvLoadImage(argv[1]);
	example2_4(img);
	cvReleaseImage(&img);
	return 0;
}

//Example2_5
IplImage *doPyrDown(IplImage *in, int filter = CV_GAUSSIAN_5x5) {
	assert(in->width % 2 == 0 && in->height % 2 == 0);
	IplImage *out = cvCreateImage(cvSize(in->width / 2, in->height / 2), in->depth, in->nChannels);
	cvPyrDown(in, out);
	return out;
}

//Example2_6
IplImage *doCanny(IplImage *in, double lowThresh, double highThresh, double aperture) {
	if (in->nChannels != 1) {
		std::cout << "Error: hahaha " << in->nChannels << std::endl;
		return 0;
	}
	IplImage *out = cvCreateImage(cvGetSize(in), IPL_DEPTH_8U, 1);
	cvCanny(in, out, lowThresh, highThresh, aperture);
	return out;
}

//Example2_10
