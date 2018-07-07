#pragma once

#include <QDir>
#include <string>

class Category
{
public:

    std::string getName();

    int getNumSamples();

    std::string getNextSampleFilename(
        const std::string& prefix,
        const std::string& extension);

protected:

    QDir _dir;
};

