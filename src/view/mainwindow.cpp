#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(s21::Facade *facade, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->render_area->setFacade(facade);
  caveWindow = new CaveWindow(facade);
  setWindowTitle("Maze");
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btn_load_clicked() {
  QString filename = QFileDialog::getOpenFileName(
      this, ("Open file"), USER_APP "datasets/", "*.txt");
  if (filename.isEmpty()) return;
  try {
    ui->render_area->drawFromFile(filename);
  } catch (std::exception &ex) {
    showMessageBox(this, "Wrong file format");
  }

  ui->label_filename->setText(truncater(filename, 18));
}

void MainWindow::on_btn_generate_clicked() {
  ui->render_area->drawGenerate(ui->spinBox_width->value(),
                                ui->spinBox_height->value());
}

void MainWindow::on_btn_save_maze_clicked() {
  QString file_path = QFileDialog::getSaveFileName(this, "Save Maze", "maze",
                                                   tr("Text files (*.txt)"));
  if (!file_path.isEmpty()) {
    if (file_path.endsWith(".txt")) {
      ui->render_area->saveMaze(file_path);
    }
  }
}

void MainWindow::on_actionCave_triggered() {
  hide();
  caveWindow->show();
}

void MainWindow::on_actionMaze_triggered() {
  caveWindow->hide();
  show();
}

QString truncater(QString str, int size) {
  qsizetype n = str.lastIndexOf('/') + 1;
  str = str.right(str.size() - n);
  if (str.size() > size) {
    str.truncate(size - 3);
    QString dots = "...";
    str += dots;
  }
  return str;
}

void showMessageBox(QWidget *parent, QString message) {
  QMessageBox msg_box(parent);
  msg_box.setStyleSheet("background-color: #171923;");
  QPushButton *btn = msg_box.addButton("Ok, sorry!", QMessageBox::ActionRole);
  btn->setStyleSheet(
      "QPushButton {"
      "text-transform: uppercase;"
      "letter-spacing: 2.5px;"
      "color: #FFFFFF;"
      "background-color: #AF2B36;"
      "border: none;"
      "padding: 5px 10px;"
      "}"

      "QPushButton:hover {"
      "background: #171923;"
      "color: #AF2B36;"
      "}"

      "QPushButton:pressed {"
      "background: #171923;"
      "color: #FCFEF1;"
      "}");
  msg_box.setText(message);
  msg_box.exec();
}
