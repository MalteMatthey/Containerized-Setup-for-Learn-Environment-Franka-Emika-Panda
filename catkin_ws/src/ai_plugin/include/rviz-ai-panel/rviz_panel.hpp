#ifndef AI_WINDOW_H
#define AI_WINDOW_H

#include <rviz/panel.h>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <QWidget>
#include <QPushButton>
#include <QObject>
#include "rviz-ai-panel/topic_collector.hpp"
#include "rviz-ai-panel/ai_agent.hpp"

/** 
 *  Include header generated from the UI file.
 *  Note that you will need to use the add_library function first
 *  in order to generate the header file from the UI.
 */
#include <ui_ai_panel.h>

// Other ROS dependencies
#include <std_msgs/Bool.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class Ai_Window;
}
QT_END_NAMESPACE

class Ai_Window : public rviz::Panel {
    Q_OBJECT

public:
    Ai_Window(QWidget *parent = nullptr);  // Constructor, default parent widget
    ~Ai_Window();                         // Destructor

    // Save and load user-specific settings
    virtual void load(const rviz::Config &config) override;
    virtual void save(rviz::Config config) const override;

private:
    Ui::Ai_Window *ui;                   // Pointer to UI elements
    ros::NodeHandle nh_;                 // ROS NodeHandle
    ros::Publisher text_publisher_;      // ROS Publisher for text messages
    TopicCollector collector_;           // TopicCollector object to collect messages
    AiAgent ai_agent_;                   // AiAgent object to interact with AI model
    QString createPrompt(); // Helper method to create the prompt

private Q_SLOTS:
    void sendRequest();  // Slot to handle button click for sending requests

};

#endif // AI_WINDOW_H