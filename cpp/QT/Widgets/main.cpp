
/*
 * Qt6 Widgets Showcase
 * ---------------------
 * A single compilable example instantiating every major Qt Widget
 * with its most commonly used properties set in code.
 *
 * Build (command line):
 *   qmake6 -project (or CMake, see below)
 *   Requires: Qt6 Widgets module
 *
 * Minimal CMakeLists.txt to build this file:
 * -------------------------------------------------
 * cmake_minimum_required(VERSION 3.16)
 * project(WidgetsShowcase)
 * set(CMAKE_AUTOMOC ON)
 * find_package(Qt6 REQUIRED COMPONENTS Widgets)
 * add_executable(WidgetsShowcase qt6_widgets_showcase.cpp)
 * target_link_libraries(WidgetsShowcase Qt6::Widgets)
 * ------
 * -------------------------------------------
 */
#include "mainwindow.h"

#include <QApplication>
#include <QMainWindow>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLCDNumber>
#include <QProgressBar>
#include <QPushButton>
#include <QToolButton>
#include <QRadioButton>
#include <QCheckBox>
#include <QCommandLinkButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QPlainTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QDateEdit>
#include <QTimeEdit>
#include <QDateTimeEdit>
#include <QSlider>
#include <QDial>
#include <QScrollBar>
#include <QTabWidget>
#include <QStackedWidget>
#include <QSplitter>
#include <QFrame>
#include <QToolBox>
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QIcon>
#include <QStyle>

static QGroupBox *wrap(const QString &title, QWidget *w)
{
    auto *box = new QGroupBox(title);
    auto *layout = new QVBoxLayout(box);

    layout->addWidget(w);

    return box;
}

class ShowcaseWindow : public QMainWindow
{
public:
    ShowcaseWindow(QWidget *parent = nullptr) : QMainWindow(parent)
    {
        setWindowTitle("QT6 Widgets Showcase");

        buildMenuBar();

        resize(900, 700);
    }

private:
    void buildMenuBar()
    {
        QMenuBar *menuBar = this->menuBar();
        QMenu *fileMenu = menuBar->addMenu("&File");
        fileMenu->setSeparatorsCollapsible(true);

        QAction *openAction = fileMenu->addAction("Open...");
        connect(openAction, &QAction::triggered, this, &ShowcaseWindow::onOpenFile);

        QAction *colorAction = fileMenu->addAction("Pick Color...");
        connect(colorAction, &QAction::triggered, this, &ShowcaseWindow::onPickColor);

        fileMenu->addSeparator();
        QAction *exitAction = fileMenu->addAction("Exit");
        connect(exitAction, &QAction::triggered, this, &QWidget::close);
    }

    void onOpenFile()
    {
        QFileDialog dialog(this);
        dialog.setDirectory(QDir::homePath());
        dialog.setNameFilters({"Text files (*.txt)", "All files (*.*)"});
        dialog.setFileMode(QFileDialog::ExistingFile);
        dialog.setAcceptMode(QFileDialog::AcceptOpen);

        if (dialog.exec()) {
            QStringList files = dialog.selectedFiles();
            statusBar()->showMessage("Selected: " + files.join(", "), 4000);
        }
    }

    void onPickColor()
    {
        QColor color = QColorDialog::getColor(Qt::blue, this, "Pick a Color");

        if (color.isValid()) {
            statusBar()->showMessage("Color chosen: " + color.name(), 4000);
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowcaseWindow w;
    w.show();
    return QApplication::exec();
}
