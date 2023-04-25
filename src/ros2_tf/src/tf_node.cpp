#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
// #include "tf2_msgs/msg/tf_message.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class ROS2_TF_Node : public rclcpp::Node
{
  public:
    ROS2_TF_Node() : Node("minimal_publisher")
    {
      publisher_ = this->create_publisher<geometry_msgs::msg::TransformStamped>("tf", 10);


      subscription_ = this->create_subscription<geometry_msgs::msg::TransformStamped>(
      "topic", 10, std::bind(&ROS2_TF_Node::topic_callback, this, _1));

    }

  private:
    // void timer_callback()
    // {
    //   auto message = std_msgs::msg::String();
    //   message.data = "Hello, world! " + std::to_string(count_++);
    //   RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
    //   publisher_->publish(message);
    // }


    // Callback of every messages on tf topic
    void topic_callback(const std_msgs::msg::String & msg) const
    {
      // Fetch the message
      RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
      
      // Publish the message on a different topic
      auto message = std_msgs::msg::String();
      message.data = msg.data;
      RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
      publisher_->publish(message);
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;



    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ROS2_TF_Node>());
  rclcpp::shutdown();
  return 0;
}