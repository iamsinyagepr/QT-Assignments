// General-purpose model: you build the items yourself

QStandardItemModel *model = new QStandardItemModel;
model->setHorizontalHeaderLabels({"Name"});

QStandardItem *parentItem = new QStandardItem("Fruits");
parentItem->appendRow(new QStandardItem("Apple"));   // child row
parentItem->appendRow(new QStandardItem("Banana"));  // child row
model->appendRow(parentItem);                        // top-level row

QTreeView *view = new QTreeView;
view->setModel(model);
view->expandAll();
view->show();