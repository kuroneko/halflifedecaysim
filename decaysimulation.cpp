#include "decaysimulation.h"

#include <QRandomGenerator>
#include <QVector>

DecaySimulation::DecaySimulation(int population, int iterations, double decayP, QObject *parent):
    QObject(parent),
    mPopulation(population),
    mIterations(iterations),
    mDecayProbability(decayP),
    mRawResults(),
    mPopulationTime(),
    mActualIterations(0)
{

}

void DecaySimulation::run()
{
    auto rng = QRandomGenerator::securelySeeded();

    QVector<QVector<double>>    live(mPopulation);
    QVector<QVector<double>>    rawResults(0);
    QVector<int>                populationTime(mIterations, 0);
    int iterations;
    for (iterations = 0; live.size() > 0 && iterations < mIterations; iterations++) {
        for (int j = live.size()-1; j >= 0; j--) {
            double thisVal = rng.generateDouble();
            live[j].push_back(thisVal);
            if (thisVal < mDecayProbability) {
                // it decayed, remove it from the live and add it to the results.
                rawResults.push_back(live[j]);
                live.remove(j);
            }
        }
        populationTime[iterations] = live.size();
    }
    mRawResults = std::move(rawResults);
    mPopulationTime = std::move(populationTime);
    mActualIterations = iterations;
}

QXYSeries *DecaySimulation::getPopulationTimeData(QObject *seriesParent, bool useSpline)
{
    QLineSeries *returnValue;
    if (useSpline) {
        returnValue = new QSplineSeries(seriesParent);
    } else {
        returnValue = new QLineSeries(seriesParent);
    }
    returnValue->setName(tr("p=%0").arg(QString::number(mDecayProbability, 'g', 10)));
    returnValue->setPointLabelsFormat(tr("i=@xPoint, p=@yPoint"));
    // insert the 0th item
    returnValue->append(0, mPopulation);
    // and the decay data.
    for (int i = 0; i < mPopulationTime.size(); i++) {
        returnValue->append(i+1, mPopulationTime[i]);
    }
    return returnValue;
}
