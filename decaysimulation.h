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
#ifndef DECAYSIMULATION_H
#define DECAYSIMULATION_H

#include <QObject>
#include <QVector>
#include <QtCharts>

class DecaySimulation: public QObject
{    
    Q_OBJECT

public:
    DecaySimulation(int population, int maxIterations, double decayP, QObject *parent=nullptr);

    void run();

    QtCharts::QXYSeries *getPopulationTimeData(QObject *seriesParent = nullptr, bool useSpline = false);

protected:
    int mPopulation;
    int mIterations;
    double mDecayProbability;

    QVector<QVector<double>>    mRawResults;
    QVector<int>                mPopulationTime;
    int mActualIterations;

};

#endif // DECAYSIMULATION_H
