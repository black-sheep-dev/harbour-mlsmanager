#include "packagessortfiltermodel.h"

#include "packagesmodel.h"

PackagesSortFilterModel::PackagesSortFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setSortRole(PackagesModel::NameRole);
    setFilterRole(PackagesModel::NameRole);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void PackagesSortFilterModel::sortModel()
{
    sort(0, Qt::AscendingOrder);
}
