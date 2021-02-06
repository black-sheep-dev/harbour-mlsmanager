#ifndef PACKAGESSORTFILTERMODEL_H
#define PACKAGESSORTFILTERMODEL_H

#include <QSortFilterProxyModel>

class PackagesSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit PackagesSortFilterModel(QObject *parent = nullptr);

    Q_INVOKABLE void sortModel();

};

#endif // PACKAGESSORTFILTERMODEL_H
