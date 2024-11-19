#include "rviz-ai-panel/rviz_panel.hpp"
#include "rviz-ai-panel/topic_collector.hpp"
#include <pluginlib/class_list_macros.hpp>
#include <std_msgs/String.h>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QLabel>

#include <QFile>
#include <QTextStream>

Ai_Window::Ai_Window(QWidget *parent)
    : rviz::Panel(parent)
    , ui(new Ui::Ai_Window) {
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
    QString text = ui->textEdit->toPlainText();

    // Verwenden Sie die Mitgliedsvariable collector_
    std::vector<std::string> topics = collector_.getTopicNames();
    QString all_messages;

    for (const auto& topic : topics) {
        std::string message = collector_.getMessage(topic);
        all_messages += QString::fromStdString(topic + ":\n" + message + "\n");
    }

    // Schreibe die gesammelten Nachrichten in eine Datei
    QFile file("/catkin_ws/output.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << all_messages;
        file.close();
    }

    // Setze eine kurze Nachricht oder Bestätigung in das Textfeld
    ui->label->setText("Nachrichten wurden in die Datei geschrieben.");

    // Entferne den Code zum Erstellen und Senden einer ROS-Nachricht
    // std_msgs::String msg;
    // msg.data = text.toStdString();
    // text_publisher_.publish(msg);
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