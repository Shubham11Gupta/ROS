#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "iostream"

using namespace std;

class HelloWorldNodeSub : public rclcpp::Node{
    public:
        HelloWorldNodeSub() : Node("hello_world_node_sub"){
            subscription_ = this->create_subscription<std_msgs::msg::String>(
                "hello_world",10,
                bind(&HelloWorldNodeSub::sub_callback, this, placeholders::_1)
            );
        }

    private:
        void sub_callback(const std_msgs::msg::String &msg){
            cout<<msg.data<<endl;
            //RCLCPP_INFO(this->get_logger(),msg.data.c_str()); // this is th logging method in ros
        }
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};


int main(int argc, char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(make_shared<HelloWorldNodeSub>()); //this is kind of an infiniteloop till the user hit exit
    rclcpp::shutdown();
    return 0;
}