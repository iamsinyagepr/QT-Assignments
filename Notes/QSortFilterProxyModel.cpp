// The proxy sits between an existing model and the view
QSortFilterProxyModel *proxy = new QSortFilterProxyModel;
proxy->setSourceModel(model);                   // any existing model
proxy->setFilterCaseSensitivity(Qt::CaseInsensitive);
proxy->setFilterKeyColumn(-1);                  // -1 = search all columns
proxy->setFilterFixedString("app");             // only rows containing "app"

QTableView *view = new QTableView;
view->setModel(proxy);
view->setSortingEnabled(true);                  // click headers to sort
view->show();