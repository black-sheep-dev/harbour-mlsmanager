#ifndef ENUMS_H
#define ENUMS_H

#include <QObject>

class PackageType
{
    Q_GADGET
public:
    enum Type {
        Undefined,
        Country,
        Region
    };
    Q_ENUM(Type)
};

#endif // ENUMS_H
