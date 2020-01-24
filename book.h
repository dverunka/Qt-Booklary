#ifndef BOOK_H
#define BOOK_H

#include <QObject>
#include <QJsonObject>

class Book: public QObject
{
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString isbn READ isbn WRITE setIsbn NOTIFY isbnChanged)
    Q_PROPERTY(QString author READ author WRITE setAuthor NOTIFY authorChanged)
    Q_PROPERTY(QString publisher READ publisher WRITE setPublisher NOTIFY publisherChanged)
    Q_PROPERTY(qint64 year READ year WRITE setYear NOTIFY yearChanged)
    Q_PROPERTY(QString image READ image WRITE setImage NOTIFY imageChanged)

    Q_OBJECT

private:

    QString m_title;
    QString m_isbn;
    QString m_author;
    QString m_publisher;
    qint64 m_year;
    QString m_image;

public:

    explicit Book(QObject *parent = nullptr);

    QString title() const;
    QString isbn() const;
    QString author() const;
    QString publisher() const;
    qint64 year() const;
    QString image() const; // url

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    QString fulltext();
    QString listviewText();

public slots:

    void setTitle(const QString &title);
    void setIsbn(const QString &isbn);
    void setAuthor(const QString &author);
    void setPublisher(const QString &publisher);
    void setYear(const qint64 &year);
    void setImage(const QString &image);

signals:

    void titleChanged(QString title);
    void isbnChanged(QString isbn);
    void authorChanged(QString author);
    void publisherChanged(QString publisher);
    void yearChanged(qint64 year);
    void imageChanged(QString image);
};

#endif // BOOK_H
