#include "inflector.h"

#include <QRegularExpression>

/**
 * @brief Inflector::humanize
 * Creates space separated strings from camelcased or underscored strings.
 * @param str in either "CamelCased" or "under_scored" format
 * @return str in humanized form ("Camel Cased" or "under scored" for e.g.)
 */
QString Inflector::humanize(const QString & str)
{
    static QRegularExpression regExp1 {"(.)([A-Z][a-z]+)"};
    static QRegularExpression regExp2 {"([a-z0-9])([A-Z])"};

    QString result = str;
    result.replace('_', ' ');
    result.replace(regExp1, "\\1 \\2");
    result.replace(regExp2, "\\1 \\2");

    return result;
}

QString Inflector::deUnderscore(const QString &str)
{
    QString ret = str;
    return  ret.replace('_', ' ');
}

QString Inflector::upperFirst(const QString & str)
{
    QString result = str;
    if (str.length() > 1)
        result.replace(0, 1, result.mid(0, 1).toUpper());
    return result;
}

QString Inflector::lowerFirst(const QString & str)
{
    QString result = str;
    if (str.length() > 1)
        result.replace(0, 1, result.mid(0, 1).toLower());
    return result;
}
