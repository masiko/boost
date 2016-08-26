#include<iostream>
#include<fstream>
#include<boost/timer.hpp>
#include<boost/thread.hpp>
#include"opencv2/opencv.hpp"
#include"opencv2/highgui/highgui.hpp"

static boost::thread capture_thread;
static boost::mutex lock_obj;
boost::timer timer;

int cal_img1(unsigned char* p, int size) {
	const int val = 125;
	for (int i=0; i<size; i++) {
		*p++ = val;
		*p++ = val;
		*p++ = val;
	}
	return 0;
}

int cal_img2(cv::Mat img, int size) {
	const int val = 0;
	unsigned char *p = img.data;
	for (int i=0; i<size; i++) {
		*p++ = val;
		*p++ = val;
		*p++ = val;
	}
	return 0;
}

int cal_img3(cv::Mat *img, int size) {
	const int val = 100;
	unsigned char *p = img->data;
	for (int i = 0; i<size; i++) {
		*p++ = val;
		*p++ = val;
		*p++ = val;
	}
	return 0;
}


int main(){
	cv::VideoCapture cap;
	cv::Mat img1;

	int size;
	int val;
	unsigned char *p;
	std::ofstream ofs("OpencvCallTime.txt");

	double result_mat = timer.elapsed();
	//device Open
	cap.open(CV_CAP_DSHOW + 0);
	if (!cap.isOpened()) {
		std::cout<<"can't open camera device!!\n";
		return -1;
	}
	
	cap >> img1;
	size = img1.cols*img1.rows;
	
	ofs << "Open Camera device" << std::endl << "cv::Mat: " << img1.cols <<" * "<<img1.rows<<std::endl;
	ofs << std::endl << "### call Time ###" << std::endl;

	cv::namedWindow("cap_img");
	cv::imshow("cap_img", img1);
	cv::waitKey(100);


	timer.restart();
	for (int i = 0; i < 100; i++) {
		p = img1.data;
		cal_img1(p, size);
	}
	result_mat = timer.elapsed();
	std::cout <<"call by refarence : ";
	std::cout << result_mat << std::endl;
	ofs <<"call by refarence : " << result_mat << std::endl;

	cv::namedWindow("dst1");
	cv::imshow("dst1", img1);

	cv::waitKey(0);

	

	p = img1.data;
	timer.restart();
	for (int i=0; i<100; i++) {
		cal_img2(img1, size);
	}
	result_mat = timer.elapsed();
	std::cout <<"cv::Mat : ";
	std::cout << result_mat << std::endl;
	ofs <<"cv::Mat : " << result_mat << std::endl;

	cv::imshow("dst1", img1);
	cv::waitKey(0);



	p = img1.data;
	timer.restart();
	for (int i = 0; i<100; i++) {
		cal_img3(&img1, size);
	}
	result_mat = timer.elapsed();
	std::cout << "&cv::Mat : ";
	std::cout << result_mat << std::endl;
	ofs << "&cv::Mat : " << result_mat << std::endl;

	cv::imshow("dst1", img1);
	cv::waitKey(0);
	return 0;
}

