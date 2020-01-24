#include "window.h"
#include "ui_window.h"
#include "book.h"
#include "library.h"
#include <QList>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

Window::Window(QWidget *parent): QMainWindow(parent), ui(new Ui::Window)
{
    ui->setupUi(this);

    this->library = new Library();
    this->library->loadFromJson();

    showBooks();
}

Window::~Window()
{
    delete ui;
    this->library->saveToJson();
}

void Window::addNewBook()
{
    Book* newBook = new Book();

    bool success;
    QString title = ui->titleInput->toPlainText();
    QString author = ui->authorInput->toPlainText();
    QString isbn = ui->isbnInput->toPlainText();
    QString publisher = ui->publisherInput->toPlainText();
    QString image = ui->imagePathInput->toPlainText();

    if (title.isNull() || title.isEmpty()) {
        success = false;
        QMessageBox::warning(this, "Booklary", "Enter book title, please.");
        return;
    }
    if (author.isNull() || author.isEmpty()) {
        success = false;
        QMessageBox::warning(this, "Booklary", "Enter book author, please.");
        return;
    }
    if (isbn.isNull() || isbn.isEmpty()) {
        success = false;
        QMessageBox::warning(this, "Booklary", "Enter book ISBN, please.");
        return;
    }
    if (publisher.isNull() || publisher.isEmpty()) {
        success = false;
        QMessageBox::warning(this, "Booklary", "Enter book publisher, please.");
        return;
    }
    if (image.isNull() || image.isEmpty()) {
        success = false;
        QMessageBox::warning(this, "Booklary", "Upload book image, please.");
        return;
    }

    qint64 year = ui->yearInput->toPlainText().toInt(&success);

    if (success) {
        newBook->setTitle(title);
        newBook->setIsbn(isbn);
        newBook->setAuthor(author);
        newBook->setPublisher(publisher);
        newBook->setYear(year);
        newBook->setImage(image);

        this->library->bookList.append(newBook);
        QMessageBox::information(this, "Booklary", "Book succesfully added.");

        ui->titleInput->clear();
        ui->isbnInput->clear();
        ui->authorInput->clear();
        ui->publisherInput->clear();
        ui->yearInput->clear();
        ui->imagePathInput->clear();
    } else {
        QMessageBox::warning(this, "Booklary", "Enter valid year, please.");
        ui->yearInput->clear();
    }
}

void Window::showBooks()
{
    QString search = ui->searchInput->toPlainText().toLower();
    QList<Book*> books;
    if (!search.isEmpty()) {
        foreach (Book* b, this->library->bookList) {
            if (b->fulltext().contains(search)) {
                books.append(b);
            }
        }
    } else {
        books = this->library->bookList;
    }
    ui->bookListWidget->clear();
    foreach (Book* b, books) {
        QListWidgetItem *item = new QListWidgetItem(QIcon(b->image()), b->title());
        ui->bookListWidget->addItem(item);
    }
}

void Window::loadImageFromDisk()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Image", "", "Image file (*.jpg)");
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly)) {
            QDataStream in(&file);
            ui->imagePathInput->setText(fileName);
            file.close();
        } else {
            QMessageBox::warning(this, "Booklary", "Unable to open image.");
        }
    }
}

void Window::on_searchButton_clicked()
{
    showBooks();
}

void Window::on_imageButton_clicked()
{
    loadImageFromDisk();
}

void Window::on_addButton_clicked()
{
    addNewBook();
    showBooks();
}
