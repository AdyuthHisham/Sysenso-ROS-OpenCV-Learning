#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/image.hpp"
#include "opencv2/opencv.hpp"
#include "cv_bridge/cv_bridge.h"
#include "custom_msg_service/srv/toggle_camera.hpp"
#include <chrono>

using namespace std::chrono_literals;

class CapPublisher : public rclcpp :: Node
{
	public:
	CapPublisher()
	: Node("cap_publisher")
	{
		capArr[0] = cv::VideoCapture(0);
		capArr[1] = cv::VideoCapture(2);
		publisher_ = this->create_publisher<sensor_msgs::msg::Image>("capture_frames",10);
		service__ = this -> create_service<custom_msg_service::srv::ToggleCamera>("capture_frames", std::bind(&CapPublisher::toggleFeed,this,std::placeholders::_1,std::placeholders::_2));
		timer_ = this->create_wall_timer(
		150ms, std::bind(&CapPublisher::timer_callback,this));
	}

	private:
	void timer_callback()
	{
		if(!capArr[0].isOpened()&&!capArr[1].isOpened())
		{
		RCLCPP_INFO(this->get_logger(), "\nCANT PARSE VIDEO");	
		}
		else
		{
			capArr[static_cast<int>(toggle)].read(frame);
			sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(
						std_msgs::msg::Header(), sensor_msgs::image_encodings::BGR8, frame).toImageMsg();
			publisher_->publish(*msg.get());
		}

		RCLCPP_INFO(this->get_logger(), "\nPublishing Video Frame");
	}

	void toggleFeed(const std::shared_ptr<custom_msg_service::srv::ToggleCamera::Request> request,
		 std::shared_ptr<custom_msg_service::srv::ToggleCamera::Response> response )
	{	
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Toggling Feed: %d",request->toggle);
		response->reply = true;
		toggle = !toggle;
		
	}

	cv::VideoCapture capArr[2];
	cv::Mat frame;
	bool toggle;
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Service<custom_msg_service::srv::ToggleCamera>::SharedPtr service__;
	rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;

};

int main(int argc, char * argv[])
{
	rclcpp::init(argc,argv);
	rclcpp::spin(std::make_shared<CapPublisher>());
	rclcpp::shutdown();
	return 0;
}
