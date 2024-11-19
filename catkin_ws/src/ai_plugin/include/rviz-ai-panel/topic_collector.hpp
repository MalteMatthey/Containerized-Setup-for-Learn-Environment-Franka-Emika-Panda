#ifndef TOPIC_COLLECTOR_HPP
#define TOPIC_COLLECTOR_HPP

#include <ros/ros.h>
#include <ros/master.h>
#include <std_msgs/String.h>
#include <map>
#include <string>
#include <vector>
#include <set>
#include <boost/bind.hpp>
#include <topic_tools/shape_shifter.h>
#include <fstream>
#include <sstream>

class TopicCollector {
public:
    TopicCollector();
    std::string getMessage(const std::string& topic_name);
    std::vector<std::string> getTopicNames();

private:
    void updateTopics();
    void updateTopics(const ros::TimerEvent& event);
    void genericCallback(const ros::MessageEvent<topic_tools::ShapeShifter const>& event, const std::string& topic_name);
    void loadSubscribedTopics(const std::string& filename);
    std::string serializeMessage(const topic_tools::ShapeShifter::ConstPtr& msg);

    std::map<std::string, ros::Subscriber> subscribers_;
    std::map<std::string, std::string> messages_;
    std::set<std::string> subscribed_topics_;
    ros::NodeHandle nh_;
    ros::Timer timer_;
};

#endif // TOPIC_COLLECTOR_HPP