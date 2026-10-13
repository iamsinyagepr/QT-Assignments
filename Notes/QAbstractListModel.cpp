// For a one-dimensional list you only need rowCount() and data()
class NumberModel : public QAbstractListModel {
public:
    int rowCount(const QModelIndex &parent = {}) const override {
        return 5;                                // number of rows
    }
    QVariant data(const QModelIndex &index, int role) const override {
        if (role == Qt::DisplayRole)             // what the view shows as text
            return index.row() * 10;             // row 0 -> 0, row 1 -> 10, ...
        return {};
    }
};

QListView *view = new QListView;
view->setModel(new NumberModel);
view->show();