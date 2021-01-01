#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void generateStaticPassword(const QString &text);
  void copyToClipboard();

  void on_clearClipboard_triggered();
  void on_showPassword_toggled(bool checked);

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
