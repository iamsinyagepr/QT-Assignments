#ifndef APP_H
#define APP_H

#include <QWidget>
#include <QObject>
#include <QDate>
// class QVBoxLayout;
// class QHBoxLayout;
class QFormLayout;
class QLineEdit;
class QTextEdit;
class QPushButton;
class QComboBox;
class QSpinBox;
class QTableView;
class QStandardItemModel;
class QItemSelectionModel;
class ExcludeColumnProxyModel;

class App : public QWidget {
    Q_OBJECT

public:
    explicit App(QWidget *parent = nullptr);

private slots:

private:
    void setupGUI();
    void addToDatabase();
    void removeFromDatabase();
    void sortDatabase();
    void onSearch(const QString &value);
    void handleDatabaseSelection();

    void paintCell(const QModelIndex &index, int value);
    void resetFilters();

    QItemSelectionModel *selection_model;

    //date time
    QDate current_date = QDate::currentDate();

    //database (table)
    QTableView *database;
    // data model
    QStandardItemModel *model;
    ExcludeColumnProxyModel *filter_model;

    //author
    QLineEdit *author_field;
    //year
    QSpinBox *year_field;
    //title
    QLineEdit *title_field;
    //journal
    QLineEdit *journal_field;
    //volume
    QSpinBox *volume_field;
    //issue
    QSpinBox *issue_field;
    //pages
    QLineEdit *pages_field;

    //add button
    QPushButton *add_button;
    //remove button
    QPushButton *remove_button;

    //search field
    QLineEdit *search_field;
    //filter field
    QComboBox *searchFilter;
    //filter field
    QComboBox *sort_field;
    QComboBox *sort_direction;

    //find button
    QPushButton *find_button;
    //reset button
    QPushButton *reset_button;


};

#endif // APP_H
