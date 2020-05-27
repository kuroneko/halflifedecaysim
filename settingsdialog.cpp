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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

int SettingsDialog::getIterations() const
{
    return ui->iterationsBox->value();
}

void SettingsDialog::setIterations(int iterations)
{
    ui->iterationsBox->setValue(iterations);
}

int SettingsDialog::getPopulation() const
{
    return ui->populationBox->value();
}

void SettingsDialog::setPopulation(int population)
{
    ui->populationBox->setValue(population);
}

bool SettingsDialog::getSplineCharts() const
{
    return ui->useSplineChartsCheckbox->checkState() == Qt::Checked;
}

void SettingsDialog::setSplineCharts(bool enabled) {
    ui->useSplineChartsCheckbox->setCheckState(enabled?Qt::Checked:Qt::Unchecked);
}

