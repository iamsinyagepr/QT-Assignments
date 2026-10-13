// Smart pointers manage object lifetime automatically

// std::unique_ptr -> Exclusive ownership
auto model =
    std::make_unique<QStringListModel>();
// when model goes out of scope, the object is deleted


// std::shared_ptr -> Shared ownership
// std::weak_ptr -> Non-owning reference to shared object
// QSharedPointer -> Qt shared ownership
// QScopedPointer -> Scope-bound ownership
// QPointer -> Guarded pointer to QObject, not an owning smart pointer


// Qt parent child ownership
QWidget* parent = new QWidget;

QPushButton* child =
    new QPushButton("Save", parent);

// deleting the parent deletes its child QObjects
// Avoid accidentally combining incompatible ownership strategies, such as allowing both QObject parent and an unrelated smart pointer to delete the same object

