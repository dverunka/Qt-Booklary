#ifndef LIBRARY_H
#define LIBRARY_H
#include <QList>
#include "book.h"


class Library
{
public:
    Library();

    QList<Book*> bookList;

    bool loadFromJson();
    bool saveToJson();
    void writeJson(QJsonObject &json) const;
    void readJson(const QJsonObject &json);
};

#endif // LIBRARY_H
