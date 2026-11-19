#pragma once
#include <QMainWindow>

class QTreeWidget;
class QTableWidget;
class QListWidget;
class QPlainTextEdit;
class QLabel;
class SceneDocument;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void createMenus();
    void createPanels();
    void newScene();
    void openScene();
    void saveScene();
    void addObject();
    void log(const QString &message);

    QTreeWidget *hierarchy = nullptr;
    QTableWidget *inspector = nullptr;
    QListWidget *assets = nullptr;
    QPlainTextEdit *console = nullptr;
    QLabel *viewport = nullptr;
    SceneDocument *scene = nullptr;
    QString currentFile;
};
