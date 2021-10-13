#include "packagessortfiltermodel.h"

#include "packagesmodel.h"
#include "enums.h"

PackagesSortFilterModel::PackagesSortFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setSortRole(PackagesModel::NameRole);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

void PackagesSortFilterModel::sortModel()
{
    sort(0, Qt::AscendingOrder);
}

quint8 PackagesSortFilterModel::typeFilter() const
{
    return m_typeFilter;
}

void PackagesSortFilterModel::setNameFilter(const QString &pattern)
{
    m_namePattern = pattern;
    invalidateFilter();
}

void PackagesSortFilterModel::setTypeFilter(quint8 type)
{
    m_typeFilter = type;
    invalidateFilter();
}

bool PackagesSortFilterModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (m_namePattern.isEmpty() && m_typeFilter == 0)
        return true;

    const QModelIndex index = sourceModel()->index(source_row, 0, source_parent);

    const QString name = sourceModel()->data(index, PackagesModel::NameRole).toString();
    const quint8 type = sourceModel()->data(index, PackagesModel::TypeRole).toUInt();

    bool found{false};
    if (!m_namePattern.isEmpty()) {
        found = name.contains(name, Qt::CaseInsensitive);
    }

    if (m_typeFilter != PackageType::Undefined) {
        found = (type == m_typeFilter);
    }

    return found;
}
