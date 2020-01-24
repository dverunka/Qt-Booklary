#ifndef WINDOW_H
#define WINDOW_H
#include "library.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:

    Window(QWidget *parent = nullptr);
    ~Window();

    Library *library;

    void addNewBook();
    void loadBooks();
    void loadImageFromDisk();
    void showBooks();

private slots:

    void on_searchButton_clicked();
    void on_imageButton_clicked();
    void on_addButton_clicked();

private:

    Ui::Window *ui;

};
#endif // WINDOW_H
