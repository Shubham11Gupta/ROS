#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "iostream"

using namespace std;

class SpeedNode : public rclcpp::Node{
    public:
        SpeedNode() : Node("Speed_node_sub"){
            subscription_ = this->create_subscription<std_msgs::msg::String>(
                "speed",10,
                bind(&SpeedNode::speed,this,placeholders::_1)
            );
        }

    private:
        rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
        void speed(const std_msgs::msg::String &msg){
            cout<<msg.data<<endl;
        }
};

int main(int argc, char *argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(make_shared<SpeedNode>());
    rclcpp::shutdown();
    return 0;
}