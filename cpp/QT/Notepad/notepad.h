#ifndef NOTEPAD_H
#define NOTEPAD_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Notepad;
}
QT_END_NAMESPACE

class Notepad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Notepad(QWidget *parent = nullptr);
    ~Notepad() override;

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

private:
    Ui::Notepad *ui;
    QString currentFile;
};
#endif // NOTEPAD_H
