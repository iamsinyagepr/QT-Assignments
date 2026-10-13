// The most general model. This minimal version is a flat list, which means
// parent() always returns an invalid index. For a real tree you would also
// store a parent pointer in each item (via createIndex's third argument).
class SimpleItemModel : public QAbstractItemModel {
public:
    QModelIndex index(int row, int column, const QModelIndex &parent = {}) const override {
        return createIndex(row, column);         // creates an index for this cell
    }
    QModelIndex parent(const QModelIndex &child) const override {
        return {};                               // no parents: everything is top-level
    }
    int rowCount(const QModelIndex &parent = {}) const override {
        return parent.isValid() ? 0 : 3;         // only top-level rows exist
    }
    int columnCount(const QModelIndex &parent = {}) const override { return 1; }
    QVariant data(const QModelIndex &index, int role) const override {
        if (role == Qt::DisplayRole)
            return QString("Item %1").arg(index.row());
        return {};
    }
};

QTreeView *view = new QTreeView;
view->setModel(new SimpleItemModel);
view->show();