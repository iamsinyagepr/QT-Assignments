// A model that simply holds a list of strings
QStringListModel *model = new QStringListModel;
model->setStringList({"Apple", "Banana", "Cherry"});

// A view that displays the model (items are editable by double-click)
QListView *view = new QListView;
view->setModel(model);
view->show();