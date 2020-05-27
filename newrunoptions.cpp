#include "newrunoptions.h"
#include "ui_newrunoptions.h"

#include <QDialogButtonBox>
#include <QPushButton>

NewRunOptions::NewRunOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRunOptions)
{
    ui->setupUi(this);
    setProbability(0.2);
}

NewRunOptions::~NewRunOptions()
{
    delete ui;
}

void NewRunOptions::setProbability(double newP)
{
    ui->decayProbEdit->setText(QString::number(newP, 'g'));
}

double NewRunOptions::getProbability() const
{
    return ui->decayProbEdit->text().toDouble();
}

void NewRunOptions::checkIfValid()
{
    bool doubleOk = false;
    QString probText = ui->decayProbEdit->text();
    probText.toDouble(&doubleOk);
    QPushButton *okbutton = ui->buttonBox->button(QDialogButtonBox::Ok);
    assert(okbutton != nullptr);

    // and set the form correctly.
    okbutton->setEnabled(doubleOk);
}

void NewRunOptions::on_decayProbEdit_textChanged(const QString &)
{
    checkIfValid();
}
