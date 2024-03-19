#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "chrono"
#include "functional"

using namespace std;
using namespace std::chrono_literals;

//class used to add the whole publisher
class HelloWorldNode : public rclcpp::Node{

    public: 
        //here we add the publisher info 
        HelloWorldNode() : Node("hello_world_pub_node") 
        {
            //this is adding the publisher and giving the topic name and the qos
            publisher_ = this->create_publisher<std_msgs::msg::String>(
                "hello_world", 10 //this is the topic name
            );
            //this is giving the interval after which the publisher should rerun
            timer_ = this->create_wall_timer(1s,
                bind(&HelloWorldNode::publish_hello_world,this)
            );
            //in timer we give time and then bind a function which will perform the work in publisher
            //&classname::functionname is a way to point at the function
        }
    
    private:
        //actual function that will do the action in publish
        void publish_hello_world(){
            auto message = std_msgs::msg::String();
            message.data = "Hello World " + to_string(counter_); //this is the data for the publisher
            publisher_->publish(message);
            counter_ ++;
        }
        //way of initializing pubisher and timer
        rclcpp::Publisher<std_msgs::msg::String>:: SharedPtr publisher_;
        rclcpp::TimerBase::SharedPtr timer_;
        size_t counter_ = 0;

};

int main(int argc, char * argv[]){
    rclcpp::init(argc,argv);
    rclcpp::spin(make_shared<HelloWorldNode>()); //this is kind of an infiniteloop till the user hit exit
    rclcpp::shutdown();
    return 0;
}