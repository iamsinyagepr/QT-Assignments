#ifndef EXCLUDECOLUMNPROXYMODEL_H
#define EXCLUDECOLUMNPROXYMODEL_H

#include "Helpers.h"
// #include <QObject>
#include <QSortFilterProxyModel>
#include <QDate>
// #include <QBrush>

class ExcludeColumnProxyModel : public QSortFilterProxyModel {
    Q_OBJECT

public:
    explicit ExcludeColumnProxyModel(QObject *parent = nullptr)
        : QSortFilterProxyModel(parent), m_excludedColumn(-1) {}

    void setExcludedColumn(int column) {
        if (m_excludedColumn == column) return;

        beginFilterChange();
        m_excludedColumn = column;
        endFilterChange(QSortFilterProxyModel::Direction::Rows);
    }
signals:
    void handleYearUpdates(const QModelIndex &index, int value);

protected:

    bool setData(const QModelIndex &index, const QVariant &value, int role) override {

        if (!index.isValid() || role != Qt::EditRole) {
            return false;
        }


        int col = index.column();


        bool ok;
        int newValue = value.toInt(&ok);
        int current_year = current_date.year();



        if(col == 1) {
            if((newValue > current_year || !ok)) return false;

            // sourceModel()->setData(index, QBrush(Qt::red), Qt::BackgroundRole);
            emit handleYearUpdates(index, current_year - newValue);
            //do color updates
        }

        if (!ok && (col == 4 || col == 5)) { //value should be int
            return false;
        }

        if(col == 6 && !isValidFormat(value.toString().toStdString())) {
            // pages: should be 10 - 12 or 10-12
            return false;
        }

        // qDebug() << value << " year: " << current_year;

        QModelIndex sourceIndex = mapToSource(index);
        if (!sourceIndex.isValid()) {
            return false;
        }

        // This updates the actual data storage and triggers the view refresh
        return sourceModel()->setData(sourceIndex, value, role);
    }

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override {
        QString pattern = filterRegularExpression().pattern();
        if (pattern.isEmpty()) {
            return true;
        }

        // 1. Fetch the targeted column set by setFilterKeyColumn()
        int targetColumn = filterKeyColumn();

        // Case A: A single specific column is targeted
        if (targetColumn != -1) {
            // If the targeted column is the one we want to ignore, hide the row
            if (targetColumn == m_excludedColumn) {
                return false;
            }
            // Otherwise, evaluate only that single targeted column
            QModelIndex index = sourceModel()->index(sourceRow, targetColumn, sourceParent);
            QString cellText = sourceModel()->data(index, Qt::DisplayRole).toString();
            return cellText.contains(pattern, filterCaseSensitivity());
        }

        // Case B: targetColumn is -1 (Search all columns except the excluded one)
        int totalColumns = sourceModel()->columnCount(sourceParent);
        for (int col = 0; col < totalColumns; ++col) {
            if (col == m_excludedColumn) {
                continue; // Skip the excluded column
            }

            QModelIndex index = sourceModel()->index(sourceRow, col, sourceParent);
            QString cellText = sourceModel()->data(index, Qt::DisplayRole).toString();

            if (cellText.contains(pattern, filterCaseSensitivity())) {
                return true;
            }
        }

        return false;
    }

private:
    int m_excludedColumn;
    QDate current_date = QDate::currentDate();
};


#endif // EXCLUDECOLUMNPROXYMODEL_H
