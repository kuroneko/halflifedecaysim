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
