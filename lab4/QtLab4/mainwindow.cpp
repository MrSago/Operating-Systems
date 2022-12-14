#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  shared_state = new SharedState;
  thread_generate = new ThreadGenerateString(shared_state, this);
  thread_reader = new ThreadReaderString(shared_state, this);

  connect(thread_generate, SIGNAL(updateBufferTextEdit(QString)), this,
          SLOT(onUpdateBufferTextEdit(QString)));

  connect(thread_reader, SIGNAL(updateBufferTextEdit(QString)), this,
          SLOT(onUpdateBufferTextEdit(QString)));

  thread_generate->start();
  thread_reader->start();

  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  thread_generate->terminate();
  thread_generate->wait();
  delete thread_generate;

  thread_reader->terminate();
  thread_reader->wait();
  delete thread_reader;

  delete shared_state;
  delete ui;
}

void MainWindow::onUpdateBufferTextEdit(const QString& str) {
  ui->textEditStrBuffer->setText(str);
}

void MainWindow::on_horizontalSlider_valueChanged(int value) {
  thread_generate->setLatency(value);
  ui->label_3->setText(QString::number(value));
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value) {
  thread_reader->setLatency(value);
  ui->label_4->setText(QString::number(value));
}
