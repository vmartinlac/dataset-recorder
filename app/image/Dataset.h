#pragma once

#include <vector>
#include <QString>
#include <QDir>

class Category
{
public:

    Category(
        const QString& name,
        const QString& path);

    QString getName() { return _name; }
    int getNumSamples();
    QString getNextFileName();

protected:

    QString _name;
    QDir _dir;
    int _count;
};

class Dataset
{
public:

    bool init(const QString& path);

    QString getPath() { return _path; }

    std::vector<Category>& getCategories()
    {
        return _categories;
    }

protected:

    std::vector<Category> _categories;
    QString _path;
    QDir _dir;
};

