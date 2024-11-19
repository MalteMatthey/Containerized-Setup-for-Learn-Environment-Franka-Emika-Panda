#include "rviz-ai-panel/topic_collector.hpp"
#include <ros/serialization.h>
#include <ros/message_traits.h>
#include <ros/message_operations.h>
#include <std_msgs/String.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Pose.h>
#include <std_msgs/Int32.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/JointState.h>
#include <geometry_msgs/WrenchStamped.h>
#include <control_msgs/JointTrajectoryControllerState.h>
#include <actionlib_msgs/GoalStatusArray.h>
#include <gazebo_msgs/LinkStates.h>
#include <gazebo_msgs/ModelStates.h>
#include <moveit_msgs/PlanningScene.h>
#include <rosgraph_msgs/Log.h>
#include <tf2_msgs/TFMessage.h>
#include <rosbag/bag.h>
#include <rosbag/view.h>
#include <boost/foreach.hpp>
#define foreach BOOST_FOREACH

// Include other message types as needed

TopicCollector::TopicCollector() {
    loadSubscribedTopics("/catkin_ws/src/ai_plugin/src/ai_subscribed_topics.txt");
    updateTopics();
    timer_ = nh_.createTimer(ros::Duration(5.0), &TopicCollector::updateTopics, this);
}

void TopicCollector::loadSubscribedTopics(const std::string& filename) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        ROS_ERROR("Failed to open %s", filename.c_str());
        return;
    }
    std::string line;
    while (std::getline(infile, line)) {
        if (!line.empty()) {
            subscribed_topics_.insert(line);
        }
    }
    infile.close();
}

void TopicCollector::updateTopics() {
    ros::TimerEvent dummy_event;
    updateTopics(dummy_event);
}

void TopicCollector::updateTopics(const ros::TimerEvent&) {
    ros::master::V_TopicInfo master_topics;
    ros::master::getTopics(master_topics);

    for (const auto& topic_info : master_topics) {
        if (subscribed_topics_.find(topic_info.name) == subscribed_topics_.end() ||
            subscribers_.find(topic_info.name) != subscribers_.end()) {
            continue;
        }

        ros::SubscribeOptions ops = ros::SubscribeOptions::create<topic_tools::ShapeShifter>(
            topic_info.name,
            1000,
            boost::bind(&TopicCollector::genericCallback, this, _1, topic_info.name),
            ros::VoidPtr(),
            nullptr
        );
        ros::Subscriber sub = nh_.subscribe(ops);
        subscribers_[topic_info.name] = sub;

        ROS_INFO("Subscribed to new topic: %s", topic_info.name.c_str());
    }
}

std::string TopicCollector::getMessage(const std::string& topic_name) {
    if (messages_.find(topic_name) != messages_.end()) {
        return messages_[topic_name];
    }
    return "";
}

std::vector<std::string> TopicCollector::getTopicNames() {
    std::vector<std::string> topic_names;
    for (const auto& entry : subscribers_) {
        topic_names.push_back(entry.first);
    }
    return topic_names;
}

// Serialize message into human-readable format
std::string TopicCollector::serializeMessage(const topic_tools::ShapeShifter::ConstPtr& msg) {
    std::stringstream ss;
    std::string datatype = msg->getDataType();

    // Handle known message types
    if (datatype == "std_msgs/String") {
        std_msgs::String::ConstPtr typed_msg = msg->instantiate<std_msgs::String>();
        if (typed_msg) {
            ros::message_operations::Printer<std_msgs::String>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate std_msgs/String\n";
        }
    }
    else if (datatype == "sensor_msgs/Image") {
        sensor_msgs::Image::ConstPtr typed_msg = msg->instantiate<sensor_msgs::Image>();
        if (typed_msg) {
            ros::message_operations::Printer<sensor_msgs::Image>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate sensor_msgs/Image\n";
        }
    }
    else if (datatype == "geometry_msgs/Pose") {
        geometry_msgs::Pose::ConstPtr typed_msg = msg->instantiate<geometry_msgs::Pose>();
        if (typed_msg) {
            ros::message_operations::Printer<geometry_msgs::Pose>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate geometry_msgs/Pose\n";
        }
    }
    else if (datatype == "std_msgs/Int32") {
        std_msgs::Int32::ConstPtr typed_msg = msg->instantiate<std_msgs::Int32>();
        if (typed_msg) {
            ros::message_operations::Printer<std_msgs::Int32>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate std_msgs/Int32\n";
        }
    }
    else if (datatype == "geometry_msgs/Twist") {
        geometry_msgs::Twist::ConstPtr typed_msg = msg->instantiate<geometry_msgs::Twist>();
        if (typed_msg) {
            ros::message_operations::Printer<geometry_msgs::Twist>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate geometry_msgs/Twist\n";
        }
    }
    else if (datatype == "sensor_msgs/JointState") {
        sensor_msgs::JointState::ConstPtr typed_msg = msg->instantiate<sensor_msgs::JointState>();
        if (typed_msg) {
            ros::message_operations::Printer<sensor_msgs::JointState>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate sensor_msgs/JointState\n";
        }
    }
    else if (datatype == "geometry_msgs/WrenchStamped") {
        geometry_msgs::WrenchStamped::ConstPtr typed_msg = msg->instantiate<geometry_msgs::WrenchStamped>();
        if (typed_msg) {
            ros::message_operations::Printer<geometry_msgs::WrenchStamped>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate geometry_msgs/WrenchStamped\n";
        }
    }
    else if (datatype == "control_msgs/JointTrajectoryControllerState") {
        control_msgs::JointTrajectoryControllerState::ConstPtr typed_msg = msg->instantiate<control_msgs::JointTrajectoryControllerState>();
        if (typed_msg) {
            ros::message_operations::Printer<control_msgs::JointTrajectoryControllerState>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate control_msgs::JointTrajectoryControllerState\n";
        }
    }
    else if (datatype == "actionlib_msgs/GoalStatusArray") {
        actionlib_msgs::GoalStatusArray::ConstPtr typed_msg = msg->instantiate<actionlib_msgs::GoalStatusArray>();
        if (typed_msg) {
            ros::message_operations::Printer<actionlib_msgs::GoalStatusArray>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate actionlib_msgs::GoalStatusArray\n";
        }
    }
    else if (datatype == "gazebo_msgs/LinkStates") {
        gazebo_msgs::LinkStates::ConstPtr typed_msg = msg->instantiate<gazebo_msgs::LinkStates>();
        if (typed_msg) {
            ros::message_operations::Printer<gazebo_msgs::LinkStates>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate gazebo_msgs::LinkStates\n";
        }
    }
    else if (datatype == "gazebo_msgs/ModelStates") {
        gazebo_msgs::ModelStates::ConstPtr typed_msg = msg->instantiate<gazebo_msgs::ModelStates>();
        if (typed_msg) {
            ros::message_operations::Printer<gazebo_msgs::ModelStates>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate gazebo_msgs::ModelStates\n";
        }
    }
    else if (datatype == "moveit_msgs/PlanningScene") {
        moveit_msgs::PlanningScene::ConstPtr typed_msg = msg->instantiate<moveit_msgs::PlanningScene>();
        if (typed_msg) {
            ros::message_operations::Printer<moveit_msgs::PlanningScene>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate moveit_msgs::PlanningScene\n";
        }
    }
    else if (datatype == "rosgraph_msgs/Log") {
        rosgraph_msgs::Log::ConstPtr typed_msg = msg->instantiate<rosgraph_msgs::Log>();
        if (typed_msg) {
            ros::message_operations::Printer<rosgraph_msgs::Log>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate rosgraph_msgs::Log\n";
        }
    }
    else if (datatype == "tf2_msgs/TFMessage") {
        tf2_msgs::TFMessage::ConstPtr typed_msg = msg->instantiate<tf2_msgs::TFMessage>();
        if (typed_msg) {
            ros::message_operations::Printer<tf2_msgs::TFMessage>::stream(ss, "", *typed_msg);
        } else {
            ss << "Failed to instantiate tf2_msgs::TFMessage\n";
        }
    }
    // Add more as needed
    else {
        ss << "Unsupported message type: " << datatype << "\n";
    }

    return ss.str();
}

void TopicCollector::genericCallback(const ros::MessageEvent<topic_tools::ShapeShifter const>& event, const std::string& topic_name) {
    const topic_tools::ShapeShifter::ConstPtr& msg = event.getMessage();
    std::string serialized_message = serializeMessage(msg);
    messages_[topic_name] = serialized_message;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "topic_collector");
    TopicCollector collector;
    ROS_INFO("TopicCollector is initialized");
    ros::spin();
    return 0;
}