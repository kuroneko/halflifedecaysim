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
