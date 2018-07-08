#include <iostream>
#include "Dataset.h"

Dataset::Dataset() : m_valid(false)
{
    ;
}

void Dataset::set(const QString& path)
{
    m_categories.clear();

    m_valid = m_dir.cd(path);

    if(m_valid)
    {
        reload_categories();
    }
}

QString Dataset::getCategoryName(int id)
{
    return m_categories[id].dirName();
}

int Dataset::getNumCategories()
{
    if(m_valid)
    {
        return m_categories.size();
    }
    else
    {
        return 0;
    }
}

int Dataset::getNumSamplesInCategory(int id)
{
    if(m_valid)
    {
        return m_categories[id].entryList(QDir::Files).size();
    }
    else
    {
        return 0;
    }
}

QString Dataset::getNextSampleFilename( int cat, const QString& prefix, const QString& extension )
{
    QString effective_prefix = ( prefix.isEmpty() ) ? "" : prefix + "_";

    QString candidate;
    int i = 0;

    do
    {
        candidate = m_categories[cat].absoluteFilePath(effective_prefix + QString::number(i) + "." + extension);
        i++;
    }
    while( QFileInfo::exists(candidate) );

    return candidate;
}

void Dataset::reload_categories()
{
    m_categories.clear();

    if(m_valid)
    {
        QStringList lst = m_dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        for(QString name : lst )
        {
            m_categories.emplace_back( m_dir.absoluteFilePath(name) );
        }
    }

    /*
    if(m_valid == false)
    {
        m_categories.clear();
    }
    */
}

bool Dataset::addCategory(const QString& name)
{
    if(m_valid)
    {
        const int ret = m_dir.mkdir(name);
        reload_categories();
        return ret;
    }
    else
    {
        return false;
    }
}

bool Dataset::renameCategory(int id, const QString& new_name)
{
    if(m_valid)
    {
        const int ret = m_dir.rename( m_categories[id].dirName(), new_name );
        reload_categories();
        return ret;
    }
    else
    {
        return false;
    }
}

bool Dataset::removeCategory(int id)
{
    if(m_valid)
    {
        const int ret = m_categories[id].removeRecursively();
        reload_categories();
        return ret;
    }
    else
    {
        return false;
    }
}

int Dataset::getTotalNumSamples()
{
    int count = 0;

    for(int i=0; i<getNumCategories(); i++)
    {
        count += getNumSamplesInCategory(i);
    }

    return count;
}

bool Dataset::clearCategory(int id)
{
    QStringList to_remove = m_categories[id].entryList( QDir::NoDotAndDotDot | QDir::Files );

    bool ok = true;

    for(QString name : to_remove)
    {
        ok = ok && m_categories[id].remove( name );
    }

    return ok;
}
