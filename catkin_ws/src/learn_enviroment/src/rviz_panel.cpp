#include "learn-enviroment/rviz_panel.hpp"
#include <pluginlib/class_list_macros.hpp>
#include <QProcess>
#include <QFile>
#include <QDebug>
#include <ros/ros.h>


Learn_Window::Learn_Window(QWidget *parent)
    : rviz::Panel(parent), ui(new Ui::Learn_Window), process(new QProcess(this)) {
        ui ->setupUi(this);
        connect(ui->executeButton, SIGNAL(clicked()), this, SLOT(onExecuteButtonClicked()));
    }

Learn_Window::~Learn_Window() {
    delete ui;
}

void Learn_Window::load(const rviz::Config &config) {
    rviz::Panel::load(config);
}

void Learn_Window::save(rviz::Config config) const {
    rviz::Panel::save(config);
}

void Learn_Window::onExecuteButtonClicked() {
    QString scriptPath = "/catkin_ws/src/learn_enviroment/src/learn_env.py";

    if (!QFile::exists(scriptPath)) {
        ROS_INFO("File not found: %s", scriptPath.toStdString().c_str());
        return;
    }

    ROS_INFO("Starting script: %s", scriptPath.toStdString().c_str());

    std::string command = "python3 " + scriptPath.toStdString();
    int result = std::system(command.c_str());
    if (result != 0) {
        ROS_ERROR("Failed to execute script: %s", scriptPath.toStdString().c_str());
    }
}

PLUGINLIB_EXPORT_CLASS(Learn_Window, rviz::Panel)