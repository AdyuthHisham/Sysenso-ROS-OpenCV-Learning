from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
	
	request_a = LaunchConfiguration('num1')
	request_b = LaunchConfiguration('num2')
	request_c = LaunchConfiguration('num3')

	'''
	request_a_arg = DeclareLaunchArgument(
		'request_a',
		default_value='0')
	request_b_arg = DeclareLaunchArgument(
		'request_b',
		default_value='0')
	request_c_arg = DeclareLaunchArgument(
		'request_c',
		default_value='0')
	'''
	
	return LaunchDescription([
		Node(
			package='add_three_ints_cpp',
			executable='addThreeInts_server',
			name= 'Server' 
			),
		Node(
			package='add_three_ints_cpp',
			executable='addThreeInts_client',
			name= 'Client',
			arguments=[request_a,request_b,request_c]
			)
		])