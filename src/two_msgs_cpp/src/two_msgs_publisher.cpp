#include "rclcpp/rclcpp.hpp"
#include "custom_msg_service/msg/num.hpp"
#include "custom_msg_service/msg/text.hpp"

#include <chrono>

using namespace std::chrono_literals;

class DoublePub : public rclcpp :: Node
{
public:
	DoublePub()
	: Node("double_pub")
	{
		//RCLCPP_INFO(this->get_logger(), "Constructor called");

		pubNum_ = this->create_publisher<
				custom_msg_service::msg::Num>("name_num",10);
		//RCLCPP_INFO(this->get_logger(), "1st publisher init");
		pubText_ = this->create_publisher<
				custom_msg_service::msg::Text>("name_num",10);
		//RCLCPP_INFO(this->get_logger(), "2nd publisher init");
		timer_ = this->create_wall_timer(
				1500ms, std::bind(&DoublePub::timer_callback,this));
		
		//RCLCPP_INFO(this->get_logger(), "Timer launched");
	}

private:
	void timer_callback()
	{
		//RCLCPP_INFO(this->get_logger(), "Callback called");
		
		//custom_msg_service::msg::Num::SharedPtr msgNum;
		//custom_msg_service::msg::Text::SharedPtr msgText;
		
		auto msgNum = custom_msg_service::msg::Num();
		auto msgText = custom_msg_service::msg::Text();


		//RCLCPP_INFO(this->get_logger(), "MSG Init");

		//CODE DYING AT VALUE STORAGE
		
		msgNum.num = this->count_;
		//msgNum.num = 0;
		//RCLCPP_INFO(this->get_logger(), "Num value stored");
		msgText.text ="Hello, world! /U\\";
		//RCLCPP_INFO(this->get_logger(), "Text value stored");
	

		//RCLCPP_INFO(this->get_logger(), "Value stored");

		RCLCPP_INFO(this->get_logger(),"Publishing %d",count_++);

		pubNum_->publish(msgNum);
		pubText_->publish(msgText);

		//RCLCPP_INFO(this->get_logger(), "Data published");
		//RCLCPP_INFO(this->get_logger(), "Callback closed");
	}
	
	static int count_;
	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<custom_msg_service::msg::Num>::SharedPtr pubNum_;
	rclcpp::Publisher<custom_msg_service::msg::Text>::SharedPtr pubText_;
};

int DoublePub::count_ = 0;

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<DoublePub>());
	rclcpp::shutdown();
	return 0;
}