#include<iostream>
#include<fstream>
#include<boost/timer.hpp>
#include<boost/thread.hpp>
#include"opencv2/opencv.hpp"
#include"opencv2/highgui/highgui.hpp"

static boost::thread capture_thread;
static boost::mutex lock_obj;
boost::timer timer;
cv::VideoCapture cap;
cv::Mat img1;
int cap_count=0;

void get_img() {
	boost::mutex::scoped_lock loc(lock_obj);
	cap >> img1;
}
void thread_cap() {
	for (;;) {
		get_img();
		boost::this_thread::sleep(boost::posix_time::milliseconds(20));
		cap_count++;
	}
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
	result_mat = timer.elapsed();
	std::cout <<"cap >> cv::Mat : ";
	std::cout << result_mat << std::endl;
	ofs <<"cap >> cv::Mat : " << result_mat << std::endl;
	

	double cap_pos0 = 0;
	double cap_pos1 = 0;
	p = img1.data;
	capture_thread = boost::thread(thread_cap);

	timer.restart();
	for (int i=0; i<100; i++) {
	 	cap_pos1 = cap.get(CV_CAP_PROP_POS_MSEC);
		ofs <<cap_pos1<<std::endl;
		if ( cap_pos1 != cap_pos0) {
		//	i++;
			cap_pos0 = cap_pos1;
		}
		val = acess_mat(p,size);
		p = img1.data;
		boost::this_thread::sleep(boost::posix_time::milliseconds(1));
	}
	result_mat = timer.elapsed();
	std::cout <<"thread_cap : ";
	std::cout << result_mat << std::endl;
	ofs <<"thread_cap : " << result_mat << std::endl;

	std::cout << cap_count << std::endl;
	cv::waitKey(0);

	return 0;
}

