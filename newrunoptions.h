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
