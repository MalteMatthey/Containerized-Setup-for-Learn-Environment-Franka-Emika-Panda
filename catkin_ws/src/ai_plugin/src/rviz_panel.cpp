#include "rviz-ai-panel/rviz_panel.hpp"
#include "rviz-ai-panel/topic_collector.hpp"
#include "rviz-ai-panel/ai_agent.hpp"
#include <pluginlib/class_list_macros.hpp>
#include <std_msgs/String.h>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <cstdlib>

// Retrieve API key from environment variable
QString api_key = QString::fromStdString(std::getenv("AI_AGENT_API_KEY"));

Ai_Window::Ai_Window(QWidget *parent)
    : rviz::Panel(parent)
    , ui(new Ui::Ai_Window)
    , ai_agent_(api_key.toStdString()) {
    ui->setupUi(this);

    // Initialize ROS Publisher
    text_publisher_ = nh_.advertise<std_msgs::String>("ai_window_topic", 1);

    // Connect the button with the function
    connect(ui->pushButton, &QPushButton::clicked, this, &Ai_Window::sendRequest);
}

Ai_Window::~Ai_Window() {
    delete ui;
}

void Ai_Window::sendRequest() {
    // Collect ROS topics and messages
    std::vector<std::string> topics = collector_.getTopicNames();
    QString all_messages;

    for (const auto& topic : topics) {
        std::string message = collector_.getMessage(topic);
        all_messages += QString::fromStdString(topic + ":\n" + message + "\n");
    }

    // Write the collected messages to a file
    QFile file("/catkin_ws/output.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << all_messages;
        file.close();
    }

    // Create the prompt
    QString fullPrompt = createPrompt();
    std::string response = ai_agent_.getResponse(fullPrompt.toStdString());

    // Display the response in the label
    ui->label->setText(QString::fromStdString(response));
}

QString Ai_Window::createPrompt() {
    // Retrieve text from textEdit
    QString mainPrompt = ui->textEdit->toPlainText();

    // Get ROS topics and messages
    std::vector<std::string> topics = collector_.getTopicNames();
    QString rosInfo;

    for (const auto& topic : topics) {
        std::string message = collector_.getMessage(topic);
        rosInfo += QString::fromStdString(topic + ":\n" + message + "\n");
    }

    // Read context_prompt.txt
    QString helperPrompt;
    QFile file("/catkin_ws/src/ai_plugin/src/context_prompt.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        helperPrompt = in.readAll();
        file.close();
    } else {
        helperPrompt = "Failed to load context_prompt.txt";
    }

    // Combine all parts
    QString fullPrompt = mainPrompt + "\n\n" + helperPrompt + "\n\n" + rosInfo;

    // Print the whole prompt to the terminal
    // qDebug() << fullPrompt;

    return fullPrompt;
}

// Save user settings (e.g., text field content)
void Ai_Window::save(rviz::Config config) const {
    rviz::Panel::save(config);
    config.mapSetValue("Text", ui->textEdit->toPlainText());
}

// Load user settings
void Ai_Window::load(const rviz::Config &config) {
    rviz::Panel::load(config);
    QString text;
    if (config.mapGetString("Text", &text)) {
        ui->textEdit->setPlainText(text);
    }
}

PLUGINLIB_EXPORT_CLASS(Ai_Window, rviz::Panel)