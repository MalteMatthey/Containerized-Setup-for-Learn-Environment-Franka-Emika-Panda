#include "rviz-ai-panel/topic_collector.hpp"
#include <ros/serialization.h>

TopicCollector::TopicCollector() {
    updateTopics(); // Aufruf der überladenen Methode ohne Argument
    timer_ = nh_.createTimer(ros::Duration(5.0), &TopicCollector::updateTopics, this); // Update every 5 seconds
}

void TopicCollector::updateTopics() {
    ros::TimerEvent dummy_event;
    updateTopics(dummy_event);
}

void TopicCollector::updateTopics(const ros::TimerEvent&) {
    ros::master::V_TopicInfo master_topics;
    ros::master::getTopics(master_topics);

    for (const auto& topic_info : master_topics) {
        if (topic_info.name == "/rosout" || subscribers_.find(topic_info.name) != subscribers_.end()) {
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

void TopicCollector::genericCallback(const ros::MessageEvent<const topic_tools::ShapeShifter>& event, const std::string& topic_name) {
    const topic_tools::ShapeShifter::ConstPtr& msg = event.getMessage();
    uint32_t serial_size = ros::serialization::serializationLength(*msg);
    std::vector<uint8_t> buffer(serial_size);
    ros::serialization::OStream stream(buffer.data(), serial_size);
    ros::serialization::serialize(stream, *msg);

    std::string data(buffer.begin(), buffer.end());
    messages_[topic_name] = data;
}

std::vector<std::string> TopicCollector::getTopicNames() {
    std::vector<std::string> topic_names;
    for (const auto& entry : subscribers_) {
        topic_names.push_back(entry.first);
    }
    return topic_names;
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "topic_collector");
    TopicCollector collector;
    ROS_INFO("TopicCollector is initialized");
    ros::spin();
    return 0;
}