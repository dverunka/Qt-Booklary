#include "library.h"
#include "book.h"
#include <QFile>
#include <QList>
#include <QJsonArray>
#include <QJsonDocument>

Library::Library() {}

bool Library::loadFromJson()
{
    QFile loadFile(QStringLiteral("save.json"));

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't load file.");
    }

    QByteArray saveData = loadFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    readJson(loadDoc.object());

    if (this->bookList.isEmpty()) {

        Book *zelda = new Book();
        zelda->setTitle("Legend of Zelda: Encyclopedia");
        zelda->setIsbn("150670638X, 9781506706382");
        zelda->setAuthor("Nintendo of America Inc");
        zelda->setPublisher("Dark Horse Comics");
        zelda->setYear(2018);
        zelda->setImage(":/images/zelda.jpg");

        Book *lake = new Book();
        lake->setTitle("The Witcher: Lady of the Lake");
        lake->setIsbn("1473211611, 9781473211612");
        lake->setAuthor("Andrzej Sapkowski");
        lake->setPublisher("Orion");
        lake->setYear(2017);
        lake->setImage(":/images/lake.jpg");

        Book *nin = new Book();
        nin->setTitle("Influential Video Game Designers: Shigeru Miyamoto");
        nin->setIsbn("1628923873, 9781628923872");
        nin->setAuthor("Jennifer deWinter");
        nin->setPublisher("Bloomsbury Publishing USA");
        nin->setYear(2015);
        nin->setImage(":/images/shigeru.jpg");

        bookList.append(nin);
        bookList.append(lake);
        bookList.append(zelda);
    }
    return true;
}

void Library::readJson(const QJsonObject &json)
{
    this->bookList.clear();
    QJsonArray bookArray = json["books"].toArray();

    for (int i = 0; i < bookArray.size(); ++i) {

        QJsonObject jsonBook = bookArray[i].toObject();
        Book* b = new Book();
        b->read(jsonBook);
        this->bookList.append(b);
    }
}

bool Library::saveToJson()
{
    QFile saveFile(QStringLiteral("save.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't save file.");
        return false;
    }

    QJsonObject gameObject;
    writeJson(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveDoc.toJson());

    return true;
}

void Library::writeJson(QJsonObject &json) const
{
    QJsonArray bookArray;
    foreach (const Book* b, this->bookList) {

        QJsonObject jsonBook;
        b->write(jsonBook);
        bookArray.append(jsonBook);
    }
    json["books"] = bookArray;
}





