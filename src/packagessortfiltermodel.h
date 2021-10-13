#ifndef PACKAGESSORTFILTERMODEL_H
#define PACKAGESSORTFILTERMODEL_H

#include <QSortFilterProxyModel>

class PackagesSortFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(quint8 typeFilter READ typeFilter WRITE setTypeFilter NOTIFY typeFilterChanged)

public:
    explicit PackagesSortFilterModel(QObject *parent = nullptr);

    Q_INVOKABLE void sortModel();

    quint8 typeFilter() const;

signals:
    void typeFilterChanged(quint8 type);

public slots:
    void setNameFilter(const QString &pattern);
    void setTypeFilter(quint8 type);

private:
    QString m_namePattern;
    quint8 m_typeFilter{0};

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

#endif // PACKAGESSORTFILTERMODEL_H
