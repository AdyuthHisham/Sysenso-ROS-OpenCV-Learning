#include<iostream>
#include<opencv2/opencv.hpp>


int main()
{
	char c;

	cv::VideoCapture cap1,cap2;
	cv::Mat frame1,frame2;

	cv::namedWindow("Video 1");
	cv::namedWindow("Video 2");

	cap1.open(0);
	cap2.open(2);

	while( cap1.isOpened() || cap2.isOpened() )
	{
		cap1 >> frame1;
		cap2 >> frame2;

		imshow("Video 1",frame1);
		imshow("Video 2",frame2);

		c = (char)cv::waitKey(25);
		if (c==27) break;
	}

	cap1.release();
	cap2.release();
	return 0;
}