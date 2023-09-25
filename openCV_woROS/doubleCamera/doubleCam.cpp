//Every 5 mins switch feed
//Additionally add function to stop timer and continue feed (Add service)

//Refer for async: https://en.cppreference.com/w/cpp/thread/async

//Bored? Check which is better for the variable defSecond:
//1. Having a member variable which stores a data obtained from a function
//2. Not having a member variable but calling the function for each iteration

//Doubts? Tough luck.

#include<iostream>
#include<chrono>
#include<opencv2/opencv.hpp>
//#include<mutex> //Check this out if timer is not consistent with timing
#include<future> //for Async
#include<unistd.h> //for sleep
#include<thread> //For this_thread

//std::mutex m;

class Timer__
{
public:

	void timeCounter()
	{
		//Some weird data synchronization thing (memory_order_relaxed)
		while(true)
		{
			//std::cout<<"Counter Running"<<std::endl;
			//std::lock_guard<std::mutex> lk(m);
			std::this_thread::sleep_for(std::chrono::seconds(1)); //Async sleep for 1 second
			++elapsedTime;
			//std::cout<<elapsedTime.count();
			if(elapsedTime.count() == endTime.count()) resetTimer();
		}
	}

	Timer__(std::chrono::minutes endTime)
		:defSecond{std::chrono::seconds(1).count()}, //Value of 1 second
		 endTime{std::chrono::seconds(endTime).count()}, //Convert minutes to seconds
		 elapsedTime{std::chrono::seconds(0).count()} //Set start time
	{
		/*
		std::cout<<"Constructor Called"<<std::endl;
		std::cout<<"defSecond"<<defSecond.count()<<std::endl;
		std::cout<<"endTime"<<endTime.count()<<std::endl;
		std::cout<<"elapsedTime"<<elapsedTime.count()<<std::endl;
		std::cout<<"Constructor Completed"<<std::endl;
		*/
	}

	static bool toggle; //To tell which camera to activate

private:
	
	const std::chrono::seconds defSecond; //Define this so you dont need to call a function or anything over and over
	
	std::chrono::seconds elapsedTime;
	std::chrono::seconds endTime;


	void resetTimer()
	{
		std::cout<<std::endl<<"Toggling";
		toggle = !toggle;
		elapsedTime = defSecond;
	}
	
};

bool Timer__::toggle = 0;

void cameraRun()
{
	char c;

	cv::VideoCapture cap1,cap2;
	
	cap1.open(0);
	cap2.open(2);

	cv::Mat frame;
	
	cv::VideoCapture capArr[] = {cap1,cap2};
	
	cv::namedWindow("Video Stream");
	while(true)
	{
		capArr[(static_cast<int>(Timer__::toggle))] >> frame;
		imshow("Video Stream",frame);
		c = (char)cv::waitKey(25);
		if (c==27) break;
	}

	cap1.release();
	cap2.release();
} 

int main()
{
	
	//std::cout<<"Program Started"<<std::endl;
	Timer__ t1(std::chrono::minutes(1));
	//std::cout<<"Object Initialized"<<std::endl;
	std::future<void> future1 = std::async(std::launch::async,cameraRun);
	std::future<void> future2 = std::async(std::launch::async,&Timer__::timeCounter,&t1);
	std::cout<<"Async Started"<<std::endl;
	

	return 0;

}