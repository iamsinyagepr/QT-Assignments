#include "App.h"
#include "Helpers.h"
#include "ExcludeColumnProxyModel.h"

// #include <string>
#include <QFormLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QStringList>
#include <QTableView>
#include <QStandardItemModel>
#include <string>
#include <QLabel>
#include <QSortFilterProxyModel>
#include <QMessageBox>

enum SORT_FIELDS {
    Author,
    Year,
    Title,
    Journal,
    Volume,
    Issue
};


App::App(QWidget *parent) : QWidget{parent},
    // database
    database(new QTableView),
    //data model
    model(new QStandardItemModel(1,7)),
    filter_model(new ExcludeColumnProxyModel()),
    //author
    author_field(new QLineEdit),
    //year
    year_field(new QSpinBox),
    //title
    title_field(new QLineEdit),
    //journal
    journal_field(new QLineEdit),
    //volume
    volume_field(new QSpinBox),
    //issue
    issue_field(new QSpinBox),
    //pages
    pages_field(new QLineEdit),

    //addbutton
    add_button(new QPushButton("Add")),
    remove_button(new QPushButton("Remove")),
    //search
    search_field(new QLineEdit),
    searchFilter(new QComboBox),
    sort_field(new QComboBox),
    sort_direction(new QComboBox),

    //search_buttons
    find_button(new QPushButton("Find")),
    reset_button(new QPushButton("Reset"))
{
    setupGUI();
    setWindowTitle("Article Records");
    setMinimumSize(800, 600);

    //connect buttons
    connect(add_button, &QPushButton::clicked, this, &App::addToDatabase);
    connect(remove_button, &QPushButton::clicked, this, &App::removeFromDatabase);
    selection_model = database->selectionModel();
    //row selection
    connect(selection_model, &QItemSelectionModel::currentRowChanged, this, &App::handleDatabaseSelection);

    //sort handler
    connect(sort_field, &QComboBox::currentTextChanged, this, &App::sortDatabase);
    connect(sort_direction, &QComboBox::currentTextChanged, this, &App::sortDatabase);

    connect(searchFilter, &QComboBox::currentTextChanged, this, &App::onSearch);

    //on search update
    connect(search_field, &QLineEdit::textChanged, filter_model, &QSortFilterProxyModel::setFilterFixedString);
    connect(filter_model, &ExcludeColumnProxyModel::handleYearUpdates, this,  &App::paintCell);
    connect(reset_button, &QPushButton::clicked, this, &App::resetFilters);
}

void App::resetFilters(){
    searchFilter->setCurrentIndex(0);
    search_field->setText("");
}


void App::onSearch(const QString &value) {
    filter_model->setFilterKeyColumn(getColumnIndex(value.toStdString()));
}

void App::sortDatabase() {

    std::string val = sort_field->currentText().toStdString();
    std::string dir = sort_direction->currentText().toStdString();

    Qt::SortOrder sortDir = dir == "Ascending" ? Qt::AscendingOrder : Qt::DescendingOrder;

    if(val == "Author") filter_model->sort(SORT_FIELDS::Author, sortDir);
    if(val == "Year") filter_model->sort(SORT_FIELDS::Year, sortDir);
    if(val == "Title") filter_model->sort(SORT_FIELDS::Title, sortDir);
    if(val == "Journal") filter_model->sort(SORT_FIELDS::Journal, sortDir);
    if(val == "Volume") filter_model->sort(SORT_FIELDS::Volume, sortDir);
    if(val == "Issue") filter_model->sort(SORT_FIELDS::Issue, sortDir);

}

void App::handleDatabaseSelection() {

    QModelIndex selection = selection_model->currentIndex();
    int row = selection.row();

    if(row >= 0) {
        remove_button->setText(QString("Delete Item %1").arg(row+1));
        remove_button->show();
    }
}

void App::paintCell(const QModelIndex &index, int value) {

    QStandardItem *item = model->item(index.row(), index.column());
    if (!item) { return; }

    if(value > 10) return item->setData(QBrush(Qt::red), Qt::BackgroundRole);
    if(value < 5) return item->setData(QBrush(Qt::green), Qt::BackgroundRole);

    return item->setData(QBrush(Qt::white), Qt::BackgroundRole);

}

void App::addToDatabase() {

    int current_year = current_date.year(),
        m_year = year_field->value();

    if(current_year < m_year)
    {
        QMessageBox::critical(
            this,
            "Year Invalid",
            QString("Year cannot be greater than %1").arg(current_year)
        );
        return;
    }

    QString m_author = author_field->text(),
        m_title = title_field->text(),
        m_journal = journal_field->text(),
        m_pages = pages_field->text();

    if(
        m_author.isEmpty() ||
        m_title.isEmpty() ||
        m_journal.isEmpty() ||
        m_pages.isEmpty()
    ) {
        QMessageBox::critical(
            this,
            "Invalid Data",
            "Author, Title and Journal cannot be empty!"
        );
        return;
    }

    if(!isValidFormat(m_pages.toStdString()))
    {
        QMessageBox::critical(
            this,
            "Invalid Pages Format",
            "Pages should be in the format 'number - number'"
        );
        return;
    }

    int m_volume = volume_field->value(),
        m_issue = issue_field->value();


    // model.setItem(0, 0, QStandardItem(m_author));
    QStandardItem *year_cell = new QStandardItem(QString::number(m_year));

    if(current_year - m_year > 10) year_cell->setData(QBrush(Qt::red), Qt::BackgroundRole);
    if(current_year - m_year < 5) year_cell->setData(QBrush(Qt::green), Qt::BackgroundRole);


    model->appendRow({
        new QStandardItem(m_author),
        year_cell,
        new QStandardItem(m_title),
        new QStandardItem(m_journal),
        new QStandardItem(QString::number(m_volume)),
        new QStandardItem(QString::number(m_issue)),
        new QStandardItem(m_pages)

    });
    sortDatabase();
    // int current_row = model->rowCount();

    author_field->setText("");
    year_field->setValue(0);
    title_field->setText("");
    journal_field->setText("");
    volume_field->setValue(0);
    issue_field->setValue(0);
    pages_field->setText("");
}


void App::removeFromDatabase() {

    QModelIndex selection = selection_model->currentIndex();
    int row = selection.row();

    model->removeRow(row);

    int size = model->rowCount();
    if(size == 0) remove_button->hide();

}

void App::setupGUI() {


    // app layout
    QVBoxLayout *app_layout(new QVBoxLayout(this));
    app_layout->setContentsMargins(0,0,0,0);

    QWidget *centralWidget(new QWidget());
    centralWidget->setContentsMargins(0, 0, 0, 0);
    centralWidget->setStyleSheet(
        QString("%1 %2 %3 %4")
            .arg(
                "QPushButton { background-color: #FF0000; color: #FFFFFF; border-radius: 5; padding: 10px 5px; }"
                "QLineEdit { padding: 5px 10px; }",
                "QLineEdit, QComboBox, QSpinBox { border-radius: 5; padding: 5px; border: 1px solid #a8a8a8; }"
                "QComboBox::drop-down { subcontrol-origin: padding; subcontrol-position: top right; }"
                // "QSpinBox { border-radius: 10; padding: 5; }"
                )
        );

    QHBoxLayout *app_wrapper(new QHBoxLayout());
    app_wrapper->setContentsMargins(0, 0, 0, 0);

    // left (forms) side layout
    QVBoxLayout *forms_layout(new QVBoxLayout);


    // form layout
    QFormLayout *form_layout(new QFormLayout());
    form_layout->setHorizontalSpacing(40);
    //add fields
    author_field->setPlaceholderText("Article Author");
    form_layout->addRow("Author", author_field);

    year_field->setRange(0, current_date.year());
    qDebug() << current_date.year();
    year_field->setButtonSymbols(QAbstractSpinBox::NoButtons);
    form_layout->addRow("Year", year_field);

    title_field->setPlaceholderText("Article Title");
    form_layout->addRow("Title", title_field);

    journal_field->setPlaceholderText("Journal Name");
    form_layout->addRow("Journal", journal_field);

    volume_field->setMaximum(INT_MAX);
    volume_field->setButtonSymbols(QAbstractSpinBox::NoButtons);
    form_layout->addRow("Volume", volume_field);

    issue_field->setMaximum(INT_MAX);
    issue_field->setButtonSymbols(QAbstractSpinBox::NoButtons);
    form_layout->addRow("Issue", issue_field);

    pages_field->setPlaceholderText("Pages Of Article");
    form_layout->addRow("Pages", pages_field);

    // form layout to forms layout
    forms_layout->addLayout(form_layout);

    QVBoxLayout *form_buttons(new QVBoxLayout());
    //add button
    form_buttons->addWidget(add_button);
    //remove button
    remove_button->hide();
    form_buttons->addWidget(remove_button);

    //add buttons to layout
    forms_layout->addLayout(form_buttons);
    forms_layout->addStretch(50);

    // search layout
    QVBoxLayout *sort_fields(new QVBoxLayout());

    //sort form
    QLabel *sort_label(new QLabel("Sort Database"));
    sort_fields->addWidget(sort_label);

    QFormLayout *sort_form(new QFormLayout());


    QStringList sort_keys = {"Author", "Year", "Title", "Journal", "Volume", "Issue"};
    sort_field->addItems(sort_keys);
    sort_form->addRow("Sort By", sort_field);

    QStringList sort_directions = {"Ascending", "Descending"};
    sort_direction->addItems(sort_directions);
    sort_form->addRow("Sort Direction", sort_direction);


    sort_fields->addLayout(sort_form);
    forms_layout->addLayout(sort_fields);
    // search_fields->addStretch(50);




    // add left (forms) side to layout
    QWidget *left_side = new QWidget();
    database->setFrameShape(QFrame::NoFrame);


    left_side->setFixedWidth(250);
    left_side->setLayout(forms_layout);

    app_wrapper->addWidget(left_side);


    //right (table) side layout
    // set table headers
    setTableHeader(model, { "Author", "Year", "Title", "Journal", "Volume", "Issue", "Pages" });

    //bind model
    model->sort(SORT_FIELDS::Author, Qt::AscendingOrder);

    // QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel();
    filter_model->setSourceModel(model);
    filter_model->setFilterCaseSensitivity(Qt::CaseInsensitive);
    filter_model->setFilterKeyColumn(-1);
    filter_model->setExcludedColumn(6);
    // filter_model->set

    database->setModel(filter_model);


    //add to right side
    QWidget *right_side(new QWidget());
    QVBoxLayout *table_layout(new QVBoxLayout());


    // search buttons layout
    QHBoxLayout *search_wrapper(new QHBoxLayout());

    // add search fields
    search_field->setPlaceholderText("Search Article");
    search_wrapper->addWidget(search_field);

    // searchable field
    QStringList search_keys = {"*", "Author", "Year", "Title", "Journal", "Volume", "Issue"};
    searchFilter->addItems(search_keys); // add searchable fields to combo box
    search_wrapper->addWidget(searchFilter);


    // reset button
    reset_button->setFixedWidth(100);

    search_wrapper->addWidget(reset_button);

    //
    table_layout->addLayout(search_wrapper);
    table_layout->addWidget(database);
    right_side->setLayout(table_layout);

    app_wrapper->addWidget(right_side);


    centralWidget->setLayout(app_wrapper);
    app_layout->addWidget(centralWidget);

    model->removeRow(0);

}










