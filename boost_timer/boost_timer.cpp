#include<iostream>
#include<fstream>
#include<boost/timer.hpp>
#include"opencv2/opencv.hpp"

int main(){
	const int col = 480;
	const int row = 640;
	int size = col*row;
	int val;
	std::ofstream ofs("OpencvMemoryAcessTime.txt");

	cv::Mat img1 = cv::Mat::zeros(col,row, CV_8UC3);
	IplImage *img2 = cvCreateImage(cvSize(row, col), 8, 3);
	unsigned short *p = (unsigned short*)img2->imageData;
	boost::timer timer;
	// boost::timer::cpu_timer timer;


	ofs << "image: 640x480 CV_8UC3" << std::endl << "loop: 100" << std::endl;
	ofs << std::endl << "### Read Time ###" << std::endl;
	timer.restart();
	for (int i=0; i<100; i++) {
		for (int j=0; j<size; j++) {
			val = img1.data[j];
		}
	}
	double result_mat = timer.elapsed();
	std::cout <<"cv::Mat::data[x]: ";
	std::cout << result_mat << std::endl;
	ofs <<"cv::Mat::data[x]: " << result_mat << std::endl;

	unsigned char *mp = img1.data;
	timer.restart();
	for (int i = 0; i<100; i++) {
		for (int j = 0; j<size; j++) {
			val = (unsigned char)*mp;
			mp + 3;
		}
	}
	result_mat = timer.elapsed();
	std::cout << "&(cv::Mat::data)+3: ";
	std::cout << result_mat << std::endl;
	ofs << "&(cv::Mat::data[x])+3: " << result_mat << std::endl;

	
	timer.restart();
	for (int i=0; i<100; i++) {
		for (int j=0; j<size; j++) {
			val = img2->imageData[j];
		}
	}
	double result_ipl = timer.elapsed();
	std::cout << "IplImage->imageData[x]: ";
	std::cout << result_ipl << std::endl;
	ofs << "IplImage->imageData[x]: " << result_ipl << std::endl;


	IplImage img1_ipl = img1;
	unsigned short *q = (unsigned short*)img1_ipl.imageData;
	timer.restart();
	for (int i = 0; i<100; i++) {
		for (int j = 0; j<size; j++) {
			val = (unsigned short)*q;
			q + 3;
		}
	}
	double result_mat2 = timer.elapsed();
	std::cout << "&(cv::Mat::Iplimage)+3: ";
	std::cout << result_mat2 << std::endl;
	ofs << "&(cv::Mat::Iplimage)+3: " << result_mat2 << std::endl;

	
	timer.restart();
	for (int i=0; i<100; i++) {
		for (int j=0; j<size; j++) {
			val = *p;
			p+3;
		}
	}
	double result_ipl2 = timer.elapsed();
	std::cout << "&(Iplimage)+3: ";
	std::cout << result_ipl2 << std::endl;
	ofs << "&(Iplimage)+3: " << result_ipl2 << std::endl;



	ofs << std::endl << "### Write Time ###" << std::endl;

	timer.restart();
	for (int i = 0; i<100; i++) {
		for (int j = 0; j<size; j++) {
			img1.data[j] = 1;
		}
	}
	result_mat = timer.elapsed();
	std::cout << "cv::Mat::data[x]: ";
	std::cout << result_mat << std::endl;
	ofs << "cv::Mat::data[x]: " << result_mat << std::endl;


	mp = img1.data;
	timer.restart();
	for (int i = 0; i<100; i++) {
		for (int j = 0; j<size; j++) {
			*mp = 1;
			mp + 3;
		}
	}
	result_mat = timer.elapsed();
	std::cout << "&(cv::Mat::data)+3: ";
	std::cout << result_mat << std::endl;
	ofs << "&(cv::Mat::data[x])+3: " << result_mat << std::endl;



	timer.restart();
	for (int i = 0; i<100; i++) {
		for (int j = 0; j<size; j++) {
			img2->imageData[j] = 1;
		}
	}
	result_ipl = timer.elapsed();
	std::cout << "IplImage->imageData[x]: ";
	std::cout << result_ipl << std::endl;
	ofs << "IplImage->imageData[x]: " << result_ipl << std::endl;


	q = (unsigned short*)img1_ipl.imageData;
	timer.restart();
	for (int i = 0; i<100; i++) {
		for (int j = 0; j<size; j++) {
			*q = 1;
			q + 3;
		}
	}
	result_mat2 = timer.elapsed();
	std::cout << "&(cv::Mat::Iplimage)+3: ";
	std::cout << result_mat2 << std::endl;
	ofs << "&(cv::Mat::Iplimage)+3: " << result_mat2 << std::endl;


	timer.restart();
	for (int i = 0; i<100; i++) {
		for (int j = 0; j<size; j++) {
			*p = 1;
			p + 3;
		}
	}
	result_ipl2 = timer.elapsed();
	std::cout << "&(Iplimage)+3: ";
	std::cout << result_ipl2 << std::endl;
	ofs << "&(Iplimage)+3: " << result_ipl2 << std::endl;





	cv::waitKey(0);

	return 0;
}

