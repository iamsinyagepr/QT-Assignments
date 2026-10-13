// For a table you need rowCount(), columnCount() and data()
class TimesTableModel : public QAbstractTableModel {
public:
    int rowCount(const QModelIndex &parent = {}) const override { return 5; }
    int columnCount(const QModelIndex &parent = {}) const override { return 5; }
    QVariant data(const QModelIndex &index, int role) const override {
        if (role == Qt::DisplayRole)
            return (index.row() + 1) * (index.column() + 1);  // multiplication table
        return {};
    }
};

QTableView *view = new QTableView;
view->setModel(new TimesTableModel);
view->show();