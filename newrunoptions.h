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
#ifndef NEWRUNOPTIONS_H
#define NEWRUNOPTIONS_H

#include <QDialog>

namespace Ui {
class NewRunOptions;
}

class NewRunOptions : public QDialog
{
    Q_OBJECT

public:
    explicit NewRunOptions(QWidget *parent = nullptr);
    ~NewRunOptions();

    void setProbability(double newP);
    double getProbability() const;

private:
    Ui::NewRunOptions *ui;

    void checkIfValid();

private slots:
    void on_decayProbEdit_textChanged(const QString &text);
};

#endif // NEWRUNOPTIONS_H
