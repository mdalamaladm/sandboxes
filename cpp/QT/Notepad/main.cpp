#include "notepad.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyleSheet(
        "QMainWindow { background-color: #2b2b2b; }"
        "QTextEdit { background-color: #1e1e1e; color: #dcdcdc; font-family: Consolas; font-size: 12pt; border: none; }"
        "QToolBar { background-color: #3c3c3c; spacing: 6px; }"
        "QMenuBar { background-color: #3c3c3c; color: white; }"
        "QMenuBar::item:selected { background-color: #505050; }"
        "QPushButton { background-color: #444; color: white; border-radius: 4px; padding: 5px; }"
        "QPushButton:hover { background-color: #555; }"
    );

    Notepad w;
    w.show();
    return QApplication::exec();
}
