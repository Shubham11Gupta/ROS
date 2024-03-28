#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/string.hpp"
#include "iostream"
#include "chrono"
#include "functional"

using namespace std;
using namespace std::chrono_literals;

class RPMNode : public rclcpp::Node{
    public:
        RPMNode() : Node("RPM_sub_node"){
            subscription_ = this->create_subscription<std_msgs::msg::Int32>(
                "rpm",10,
                bind(&RPMNode::speed,this,placeholders::_1)
            );
            publisher_ = this->create_publisher<std_msgs::msg::String>(
                "speed",10
            );
        }
    private:
        rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
        rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;

        void speed(const std_msgs::msg::Int32 &msg){
            int rpm = msg.data;
            float speed = (rpm)*10*2*(3.14)/60; //Linear velocity (m/s) = Radius (m) × Angular velocity (rpm) × (2π/60)
            cout<<"rpm = "<<rpm<<endl;
            auto message = std_msgs::msg::String();
            message.data = "Speed = "+ to_string(speed) + " m/s";
            publisher_ ->publish(message);
        }
};
int main(int argc, char *argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(make_shared<RPMNode>());
    rclcpp::shutdown();
    return 0;
}