#ifndef INFLECTOR_H
#define INFLECTOR_H

#include <QString>

class Inflector
{
public:
    static QString humanize(const QString &str);
    static QString deUnderscore(const QString &str);
    static QString upperFirst(const QString &str);
    static QString lowerFirst(const QString &str);
};

#endif // INFLECTOR_H
