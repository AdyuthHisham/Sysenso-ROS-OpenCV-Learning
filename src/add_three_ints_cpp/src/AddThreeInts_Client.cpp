#include "rclcpp/rclcpp.hpp"
#include "custom_msg_service/srv/add_three_ints.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
	rclcpp::init(argc,argv);
	

	//Had to comment this out to make launch file work
	//Reading 7 args

	//if (argc !=4)
	//{
		//RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"usage incorrect: Number of parameters = 3 || %d",argc);
		//return 1;
	//}
	
	
	//Initializing client and pointing to it
	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("AddThreeInts_client");
	rclcpp::Client<custom_msg_service::srv::AddThreeInts>::SharedPtr client =
		node->create_client<custom_msg_service::srv::AddThreeInts>("AddThreeInts");

	//Create pointer for request and initialize with argument values
	auto request = std::make_shared<custom_msg_service::srv::AddThreeInts::Request>();
	request -> a = atoll(argv[1]);
	request -> b = atoll(argv[2]);
	request -> c = atoll(argv[3]);

	//Wait for server to get ready
	//Waits for 1 second
	//True if server became ready while waiting
	//False on timeout 
	///Basically while server is not ready/connecting
	while(!client->wait_for_service(1s))
	{
		if (!rclcpp::ok())
		{
			RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service, Exiting");
			return 0;
		}
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"service not available, waiting again...");
	}

	auto result = client->async_send_request(request);
	//Spin means run the callback(?) till result is obtained and it is a success
	if(rclcpp::spin_until_future_complete(node,result) == rclcpp::executor::FutureReturnCode::SUCCESS)
	{
		RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Sum: %ld", result.get()->sum);
	}
	else
	{
		RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service AddThreeInts");
	}

	rclcpp::shutdown();
	return 0;
}

