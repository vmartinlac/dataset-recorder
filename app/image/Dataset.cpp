#include <iostream>
#include "Dataset.h"

Category::Category(
    const QString& name,
    const QString& path)
{
    _name = name;
    _dir.cd(path);
    _count = 0;
}

int Category::getNumSamples()
{
    QStringList l = _dir.entryList({"*.png"});
    return l.size();
}

QString Category::getNextFileName()
{
    QString ret = QString::number(_count) + ".png";

    while( _dir.exists(ret) )
    {
        _count++;
        ret = QString::number(_count) + ".png";
    }

    return ret;
}

bool Dataset::init(const QString& path)
{
    _categories.clear();

    _path = path;

    if( _dir.cd(path) == false )
    {
        std::cerr << "Dataset path not found !" << std::endl;

        return false;
    }
    else
    {
        QStringList content = _dir.entryList({}, QDir::Dirs|QDir::NoDotAndDotDot);

        for(QString& s : content)
        {
            _categories.emplace_back( s, _dir.absoluteFilePath(s) );
        }

        if ( _categories.empty() )
        {
            return true;
        }
        else
        {
            std::cerr << "No category in dataset !" << std::endl;
            return false;
        }
    }
}
