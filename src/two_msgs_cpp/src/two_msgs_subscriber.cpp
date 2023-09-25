#include <memory>
#include <typeinfo>
#include "rclcpp/rclcpp.hpp"
#include "custom_msg_service/msg/num.hpp"
#include "custom_msg_service/msg/text.hpp"

using std::placeholders::_1;

class DoubleSub : public rclcpp :: Node
{
public:
	DoubleSub()
	: Node("double_sub")
	{
		subNum_ = this->create_subscription<custom_msg_service::msg::Num>("name_num",10,
											std::bind(&DoubleSub::num_callback,this,_1));
		subText_ = this->create_subscription<custom_msg_service::msg::Text>("name_num",10,
											std::bind(&DoubleSub::text_callback,this,_1));
	}

private:
	void num_callback(const custom_msg_service::msg::Num::SharedPtr msgNum) const
	{	
		RCLCPP_INFO(this->get_logger(),"I heard: %d",msgNum->num);
	}
	
	void text_callback(const custom_msg_service::msg::Text::SharedPtr msgText) const
	{	
		RCLCPP_INFO(this->get_logger(),msgText->text);
	}
	
	rclcpp::Subscription<custom_msg_service::msg::Num>::SharedPtr subNum_;
	rclcpp::Subscription<custom_msg_service::msg::Text>::SharedPtr subText_;
};

int main(int argc, char* argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<DoubleSub>());
	rclcpp::shutdown();
	return 0;
}