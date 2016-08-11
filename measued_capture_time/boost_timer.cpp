#include<iostream>
#include<fstream>
#include<boost/timer.hpp>
#include<boost/thread.hpp>
#include"opencv2/opencv.hpp"
#include"opencv2/highgui/highgui.hpp"

static boost::thread capture_thread;
static boost::mutex lock_obj;
cv::VideoCapture cap;
cv::Mat img1;

void thread_cap() {
 	boost::mutex::scoped_lock loc(lock_obj);
	cap >> img1;
	boost::this_thread::sleep(boost::posix_time::milliseconds(20));

}

unsigned char acess_mat(unsigned char* p, int size){
	unsigned char val;
 	boost::mutex::scoped_lock loc(lock_obj);
	for (int j = 0; j < size; j++) {
		val = (unsigned char)*p;
		p += 3;
	}
	return (unsigned char)0;
}

int main(){
	int size;
	int val;
	unsigned char *p;
	std::ofstream ofs("OpencvCapyureAndAccessTime.txt");

	//cv::Mat img1;
	boost::timer timer;

	//device Open
	cap.open(0);
	if (!cap.isOpened()) {
		std::cout<<"can't open camera device!!\n";
		return -1;
	}
	
	cap >> img1;
	size = img1.cols*img1.rows;

	ofs << "Open Camera device" << std::endl << "cv::Mat: " << img1.cols <<" * "<<img1.rows<<std::endl;
	ofs << std::endl << "### Capture & Acess Time ###" << std::endl;

	timer.restart();
	for (int i = 0; i < 100; i++) {
		cap >> img1;
		p = img1.data;
		for (int j = 0; j < size; j++) {
			val = (unsigned char)*p;
			p += 3;
		}
		p = img1.data;
	}
	double result_mat = timer.elapsed();
	std::cout <<"cap >> cv::Mat : ";
	std::cout << result_mat << std::endl;
	ofs <<"cap >> cv::Mat : " << result_mat << std::endl;




	capture_thread = boost::thread(thread_cap);

	p = img1.data;
	timer.restart();
	for (int i=0; i<100; i++) {
	 	for (int j=0; j<size; j++) {
		 	val = acess_mat(p,size);
		}
		p = img1.data;
	}
	result_mat = timer.elapsed();
	std::cout <<"thread_cap : ";
	std::cout << result_mat << std::endl;
	ofs <<"thread_cap : " << result_mat << std::endl;
	cv::waitKey(0);

	return 0;
}

