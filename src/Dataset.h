#pragma once

#include <memory>
#include <QDir>
#include <string>

class Dataset
{
public:

    Dataset();

    void set(const QString& path);
    bool isValid() { return m_valid; }

    int getNumCategories();
    QString getCategoryName(int id);
    int getNumSamplesInCategory(int id);
    QString getNextSampleFilename(
        int category,
        const QString& prefix,
        const QString& extension);
    int getTotalNumSamples();

    bool addCategory(const QString& name);
    bool renameCategory(int id, const QString& new_name);
    bool removeCategory(int id);

protected:

    void reload_categories();

protected:

    QDir m_dir;
    bool m_valid;
    std::vector<QDir> m_categories;
};
