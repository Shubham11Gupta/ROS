#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "chrono"
#include "functional"
#include "cstdlib"

using namespace std;
using namespace std::chrono_literals;

class RPMpubNode : public rclcpp::Node{
    public:
        RPMpubNode():Node("RPM_pub_node"){
            publisher_ = this->create_publisher<std_msgs::msg::Int32>(
                "rpm",10
            );
            timer_ = this->create_wall_timer(1s,
                bind(&RPMpubNode::publish_rpm,this));
        }
    private:
        void publish_rpm(){
            auto message = std_msgs::msg::Int32();
            int random = (rand() % 101);
            message.data = random;
            publisher_->publish(message);
        }
        rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
};
int main(int argc, char *argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(make_shared<RPMpubNode>());
    rclcpp::shutdown();
    return 0;
}