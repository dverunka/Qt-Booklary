#include "book.h"

Book::Book(QObject *parent) : QObject(parent) {}

void Book::read(const QJsonObject &json)
{
    if (json.contains("title") && json["title"].isString())
        m_title = json["title"].toString();

    if (json.contains("author") && json["author"].isString())
        m_author = json["author"].toString();

    if (json.contains("isbn") && json["isbn"].isString())
        m_isbn = json["isbn"].toString();

    if (json.contains("publisher") && json["publisher"].isString())
        m_publisher = json["publisher"].toString();

    if (json.contains("year") && json["year"].isDouble())
        m_year = json["year"].toInt();

    if (json.contains("image") && json["image"].isString())
        m_image = json["image"].toString();
}

void Book::write(QJsonObject &json) const
{
    json["title"] = m_title;
    json["author"] = m_author;
    json["isbn"] = m_isbn;
    json["publisher"] = m_publisher;
    json["year"] = m_year;
    json["image"] = m_image;
}


QString Book::title() const
{
    return m_title;
}

QString Book::isbn() const
{
    return m_isbn;
}

QString Book::author() const
{
    return m_author;
}

QString Book::publisher() const
{
    return m_publisher;
}

qint64 Book::year() const
{
    return m_year;
}

QString Book::image() const
{
    return m_image;
}

void Book::setTitle(const QString &title)
{
    if (m_title == title)
        return;
    m_title = title;
}

void Book::setIsbn(const QString &isbn)
{
    if (m_isbn == isbn)
        return;
    m_isbn = isbn;
}

void Book::setAuthor(const QString &author)
{
    if (m_author == author)
        return;
    m_author = author;
}

void Book::setPublisher(const QString &publisher)
{
    if (m_publisher == publisher)
        return;
    m_publisher = publisher;
}

void Book::setYear(const qint64 &year)
{
    if (m_year == year)
        return;
    m_year = year;
}

void Book::setImage(const QString &image) // url
{
    if (m_image == image)
        return;
    m_image = image;
}

QString Book::fulltext()
{
    QString result = title() + " " + author() + " " + isbn() + "";
    return result.toLower();
}

QString Book::listviewText()
{
    QString result = "    " + title()
            + "\n\n    author: " + author()
            + "\n    published by: " + publisher() + " in " + QString::number(year())
            + "\n    isbn: " + isbn();
    return result;
}
