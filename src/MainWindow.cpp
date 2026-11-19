#include "MainWindow.h"
#include "SceneDocument.h"

#include <QAction>
#include <QFileDialog>
#include <QFileInfo>
#include <QHeaderView>
#include <QInputDialog>
#include <QLabel>
#include <QListWidget>
#include <QMenuBar>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QStatusBar>
#include <QTableWidget>
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), scene(new SceneDocument)
{
    setWindowTitle("Fan Engine Editor");
    resize(1440, 900);
    createMenus();
    createPanels();
    newScene();
    statusBar()->showMessage("Fan Engine Editor — editor base 0.2.0");
}

void MainWindow::createMenus()
{
    auto *file = menuBar()->addMenu("&File");
    auto *newAction = file->addAction("New Scene");
    auto *openAction = file->addAction("Open Scene...");
    auto *saveAction = file->addAction("Save Scene");
    file->addSeparator();
    auto *exitAction = file->addAction("Exit");
    connect(newAction, &QAction::triggered, this, &MainWindow::newScene);
    connect(openAction, &QAction::triggered, this, &MainWindow::openScene);
    connect(saveAction, &QAction::triggered, this, &MainWindow::saveScene);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    auto *objects = menuBar()->addMenu("&Object");
    auto *add = objects->addAction("Create Empty Object");
    connect(add, &QAction::triggered, this, &MainWindow::addObject);

    auto *help = menuBar()->addMenu("&Help");
    connect(help->addAction("About Fan Engine"), &QAction::triggered, this, [this] {
        QMessageBox::about(this, "About Fan Engine",
            "Fan Engine Editor 0.2.0\nA starter desktop editor built with Qt 6 and C++17.");
    });
}

void MainWindow::createPanels()
{
    auto *outer = new QSplitter(Qt::Horizontal, this);

    hierarchy = new QTreeWidget;
    hierarchy->setHeaderLabel("Hierarchy");
    hierarchy->setMinimumWidth(190);
    outer->addWidget(hierarchy);

    auto *center = new QSplitter(Qt::Vertical);
    viewport = new QLabel("SCENE VIEWPORT\n\n3D rendering backend not connected yet");
    viewport->setAlignment(Qt::AlignCenter);
    viewport->setMinimumSize(420, 300);
    viewport->setStyleSheet("QLabel { background:#25282d; color:#d5d9df; border:1px solid #454a52; font-size:18px; }");
    center->addWidget(viewport);

    auto *bottom = new QSplitter(Qt::Horizontal);
    assets = new QListWidget;
    assets->setWindowTitle("Assets");
    assets->addItems({"assets/", "  materials/", "  models/", "  textures/", "  audio/"});
    bottom->addWidget(assets);
    console = new QPlainTextEdit;
    console->setReadOnly(true);
    console->setPlaceholderText("Output / build messages...");
    bottom->addWidget(console);
    center->addWidget(bottom);
    center->setStretchFactor(0, 3);
    center->setStretchFactor(1, 1);
    outer->addWidget(center);

    inspector = new QTableWidget(0, 2);
    inspector->setHorizontalHeaderLabels({"Property", "Value"});
    inspector->horizontalHeader()->setStretchLastSection(true);
    inspector->setMinimumWidth(230);
    outer->addWidget(inspector);
    outer->setStretchFactor(1, 1);
    setCentralWidget(outer);

    connect(hierarchy, &QTreeWidget::itemSelectionChanged, this, [this] {
        const auto selected = hierarchy->selectedItems();
        inspector->setRowCount(0);
        if (selected.isEmpty()) return;
        const QString name = selected.first()->text(0);
        for (const auto &obj : scene->objects) {
            if (obj.name == name) {
                const QStringList keys{"Name", "Type", "Position X", "Position Y", "Position Z"};
                const QStringList vals{obj.name, obj.type, QString::number(obj.x),
                    QString::number(obj.y), QString::number(obj.z)};
                for (int i = 0; i < keys.size(); ++i) {
                    inspector->insertRow(i);
                    inspector->setItem(i, 0, new QTableWidgetItem(keys[i]));
                    inspector->setItem(i, 1, new QTableWidgetItem(vals[i]));
                }
                break;
            }
        }
    });
}

void MainWindow::log(const QString &message)
{
    console->appendPlainText(message);
}

void MainWindow::newScene()
{
    scene->reset();
    currentFile.clear();
    hierarchy->clear();
    for (const auto &obj : scene->objects)
        hierarchy->addTopLevelItem(new QTreeWidgetItem(QStringList{obj.name}));
    log("New scene created.");
    inspector->setRowCount(0);
}

void MainWindow::openScene()
{
    const QString path = QFileDialog::getOpenFileName(this, "Open Scene", {}, "Fan Engine Scene (*.fscene *.json)");
    if (path.isEmpty()) return;
    QString error;
    if (!scene->load(path, &error)) {
        QMessageBox::critical(this, "Open failed", error);
        return;
    }
    currentFile = path;
    hierarchy->clear();
    for (const auto &obj : scene->objects)
        hierarchy->addTopLevelItem(new QTreeWidgetItem(QStringList{obj.name}));
    log("Opened: " + path);
}

void MainWindow::saveScene()
{
    QString path = currentFile;
    if (path.isEmpty())
        path = QFileDialog::getSaveFileName(this, "Save Scene", "NewScene.fscene", "Fan Engine Scene (*.fscene)");
    if (path.isEmpty()) return;
    QString error;
    if (!scene->save(path, &error)) {
        QMessageBox::critical(this, "Save failed", error);
        return;
    }
    currentFile = path;
    log("Saved: " + path);
    statusBar()->showMessage("Scene saved: " + QFileInfo(path).fileName(), 4000);
}

void MainWindow::addObject()
{
    bool ok = false;
    const QString name = QInputDialog::getText(this, "Create Object", "Object name:", QLineEdit::Normal, "New Object", &ok);
    if (!ok || name.trimmed().isEmpty()) return;
    scene->objects.push_back({name.trimmed(), "Empty", 0, 0, 0});
    hierarchy->addTopLevelItem(new QTreeWidgetItem(QStringList{name.trimmed()}));
    log("Created object: " + name);
}
