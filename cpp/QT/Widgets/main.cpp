
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
        buildStatusBar();
        buildToolBar();
        buildCentralArea();

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

        QAction *fontAction = fileMenu->addAction("Pick Font...");
        connect(fontAction, &QAction::triggered, this, &ShowcaseWindow::onPickFont);

        QAction *inputAction = fileMenu->addAction("Text Input...");
        connect(inputAction, &QAction::triggered, this, &ShowcaseWindow::onTextInput);

        fileMenu->addSeparator();
        QAction *exitAction = fileMenu->addAction("Exit");
        connect(exitAction, &QAction::triggered, this, &QWidget::close);
    }

    void buildToolBar()
    {
        QToolBar *toolBar = addToolBar("Main Toolbar");
        toolBar->setMovable(true);
        toolBar->setFloatable(true);
        toolBar->setIconSize(QSize(12, 12));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

        QAction *msgAction = toolBar->addAction(
            style()->standardIcon(QStyle::SP_MessageBoxInformation),
            "Show Message"
        );

        connect(msgAction, &QAction::triggered, this, &ShowcaseWindow::onShowMessage);
    }

    void buildStatusBar()
    {
        QStatusBar *status = statusBar();
        status->setSizeGripEnabled(true);
        status->showMessage("Ready", 5000);
    }

    void buildCentralArea()
    {
        auto *scrollArea = new QScrollArea;
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        auto *content = new QWidget;
        auto *mainLayout = new QVBoxLayout(content);

        mainLayout->addWidget(buildDisplayGroup());

        scrollArea->setWidget(content);
        setCentralWidget(scrollArea);
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

    void onPickFont()
    {
        bool ok = false;
        QFont font = QFontDialog::getFont(&ok, QFont("Arial", 12), this, "Pick a Font");

        if (ok) {
            statusBar()->showMessage("Font chosen: " + font.family(), 4000);
        }
    }

    void onTextInput()
    {
        bool ok = false;
        QString text = QInputDialog::getText(this, "Input Dialog", "Enter your name:", QLineEdit::Normal, "", &ok);

        if (ok && !text.isEmpty()) {
            statusBar()->showMessage("You entered: " + text, 4000);
        }
    }

    void onShowMessage()
    {
        QMessageBox msgBox(this);
        msgBox.setText("This is a QMessageBox.");
        msgBox.setStyleSheet("QMessageBox { min-width: 400px; min-height: 200px; }");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }

    QGroupBox *buildDisplayGroup()
    {
        auto *group = new QGroupBox("Basic Display Widgets");
        auto *layout = new QHBoxLayout(group);

        auto *label = new QLabel("<b>Hello Qt6!</b>");
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(true);
        label->setToolTip("This is a QLabel");
        layout->addWidget(wrap("QLabel", label));

        auto *lcd = new QLCDNumber;
        lcd->setDigitCount(5);
        lcd->setMode(QLCDNumber::Dec);
        lcd->setSegmentStyle(QLCDNumber::Flat);
        lcd->display(12345);
        layout->addWidget(wrap("QLCDNumber", lcd));

        auto *progress = new QProgressBar;
        progress->setMinimum(0);
        progress->setMaximum(100);
        progress->setValue(65);
        progress->setTextVisible(true);
        progress->setFormat("%p% complete");
        layout->addWidget(wrap("QProgressBar", progress));

        return group;
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShowcaseWindow w;
    w.show();
    return QApplication::exec();
}
