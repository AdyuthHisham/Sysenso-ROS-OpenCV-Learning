#include "rclcpp/rclcpp.hpp"
#include "custom_msg_service/srv/add_three_ints.hpp" //Importing custom service

#include <memory>

void add(const std::shared_ptr<custom_msg_service::srv::AddThreeInts::Request> request,
		 std::shared_ptr<custom_msg_service::srv::AddThreeInts::Response> response )
{
	//Receiving inputs/requests and returning an output/response
	response->sum = request->a + request->b + request->c; //a,b,c are defined as inputs in the service //sum is defined as output

			//get_logger(name of logger)
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Incoming request\na: %ld | b: %ld | c: %ld", //Sending message to console
												request->a, request->b, request->c);
	RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Sending back response: [%ld]",
												(long int)response->sum);

}

int main(int argc, char **argv)
{
	rclcpp::init(argc, argv);

	//make_shared is like shared_ptr but better since there is only one heap allocation as opposed to the two allocations performed by the latter
	std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("AddThreeInts_server");

	//Defining server/service
	//create_service<template of message>(service name, callback function)
	rclcpp::Service<custom_msg_service::srv::AddThreeInts>::SharedPtr service = 
		node -> create_service<custom_msg_service::srv::AddThreeInts>("AddThreeInts", &add);

	RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add three ints.");

	//By invoking spin() of the executor instance, the thread starts querying the rcl and middleware layers for incoming messages
	//and other events and calls the corresponding callback functions until the node shuts off
	rclcpp::spin(node);
	rclcpp::shutdown();
}
