#include "Sudoku.h"
#include "ui_Sudoku.h"

#include <QActionGroup>
#include <QMessageBox>
#include "Board.h"

Sudoku::Sudoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Sudoku) {
    ui->setupUi(this);

    QActionGroup* group = new QActionGroup(this);
    group->setExclusive(true);
    group->addAction(ui->actionEasy);
    group->addAction(ui->actionMedium);
    group->addAction(ui->actionHard);

    QObject::connect(ui->actionRenew, SIGNAL(triggered()), ui->board, SLOT(renew()));
    QObject::connect(ui->actionReset, SIGNAL(triggered()), ui->board, SLOT(clear()));
    QObject::connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
    QObject::connect(group, SIGNAL(triggered(QAction*)), this, SLOT(changeMode(QAction*)));
    QObject::connect(ui->board, SIGNAL(completed(double)), this, SLOT(showProgress(double)));
    QObject::connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));

    this->showProgress(0);

    this->adjustSize();
    this->setFixedSize(this->size());
}

Sudoku::~Sudoku() {
    delete ui;
}

void Sudoku::changeMode(QAction* action) {
    DefaultBoards::Mode mode;

    if (action == ui->actionEasy)
        mode = DefaultBoards::Easy;
    else if (action == ui->actionMedium)
        mode = DefaultBoards::Medium;
    else if (action == ui->actionHard)
        mode = DefaultBoards::Hard;
    else {
        Q_UNREACHABLE();
        qApp->exit();
    }

    ui->board->setMode(mode);
}

void Sudoku::showAbout() {
    QMessageBox::information(this, tr("About"), tr("Sudoku\n\nAbhigyan Gupta - \n\nEmail: gupta.abhigyan@gmail.com"));
}

void Sudoku::showProgress(double progress) {
    ui->statusBar->showMessage(QString("Progress: %1%").arg(QString::number(progress, 'f', 2)));
}
