// Controls how model items are rendered and edited

// The common base is AbstractItemDelegate, with QStyledItemDelegate frequently used customisation

class NumberDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    QWidget* createEditor(
        QWidget* parent,
        const QStyleOptionViewItem&,
        const QModelIndex&
    ) const override {
        auto* editor = new QSpinBox(parent);
        editor->setRange(0, 100);
        return editor;
    }
};

// This delegate creates a spin box as an editor
// full editable delegate can also override setEditorData() and setModelData()