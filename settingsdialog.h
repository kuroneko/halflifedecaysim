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
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    int getIterations() const;
    void setIterations(int iterations);

    int getPopulation() const;
    void setPopulation(int population);

    bool getSplineCharts() const;
    void setSplineCharts(bool enabled);


private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
