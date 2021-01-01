#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QClipboard>
#include <QCryptographicHash>
#include <QTextDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->serviceName, SIGNAL(textChanged(const QString &)), this,
          SLOT(generateStaticPassword(const QString &)));
  connect(ui->serviceName, SIGNAL(returnPressed()), this,
          SLOT(copyToClipboard()));

  connect(ui->masterPassword, SIGNAL(textChanged(const QString &)), this,
          SLOT(generateStaticPassword(const QString &)));
  connect(ui->masterPassword, SIGNAL(returnPressed()), this,
          SLOT(copyToClipboard()));

  connect(ui->staticPassword, SIGNAL(linkActivated(QString)), this,
          SLOT(copyToClipboard()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::generateStaticPassword(const QString &text) {
  Q_UNUSED(text)

  QString serviceName = ui->serviceName->text(),
          masterPassword = ui->masterPassword->text(),
          staticPassword = QString();

  if (!serviceName.isEmpty() && !masterPassword.isEmpty()) {
    staticPassword =
        QCryptographicHash::hash((serviceName + masterPassword).toLatin1(),
                                 QCryptographicHash::Sha1)
            .toHex()
            .toBase64()
            .left(32);
  }

  ui->staticPassword->setText(
      QString("<a href=\"%1\">%1</a>").arg(staticPassword));
}

void MainWindow::copyToClipboard() {
  QTextDocument document;
  document.setHtml(ui->staticPassword->text());

  QApplication::clipboard()->setText(document.toPlainText());
}

void MainWindow::on_clearClipboard_triggered() {
  ui->serviceName->clear();
  ui->masterPassword->clear();

  QApplication::clipboard()->clear();
}

void MainWindow::on_showPassword_toggled(bool checked) {
  ui->masterPassword->setEchoMode(checked ? QLineEdit::Normal
                                          : QLineEdit::Password);
}
