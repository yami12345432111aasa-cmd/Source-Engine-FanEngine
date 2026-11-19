#include "MainWindow.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Fan Engine Editor");
    resize(1100, 700);
    auto *label = new QLabel(
        "Fan Engine Editor\nGitHub Actions build starter",
        this
    );
    label->setAlignment(Qt::AlignCenter);
    setCentralWidget(label);
}
