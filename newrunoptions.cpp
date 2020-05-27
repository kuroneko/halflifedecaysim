/*
 * HalflifeDecaySim: A Simple App to Model Radioactive Decay
 * Copyright (C) 2020 Chris Collins
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
