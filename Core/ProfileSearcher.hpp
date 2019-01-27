#ifndef PROFILESEARCHER_HPP
#define PROFILESEARCHER_HPP

#include <QDateTime>
#include <QMutex>
#include <QThread>
#include <QVector>
#include <Core/Utility.hpp>

class ProfileSearcher : public QThread
{
    Q_OBJECT

public:
    ProfileSearcher(const QDateTime &start, u32 initialSeed, u32 baseTick, u32 baseOffset, u32 tickRange, u32 offsetRange);
    void run() override;
    int maxProgress();
    int currentProgress();
    QVector<QPair<u32, u32>> getResults();

public slots:
    void cancelSearch();

private:
    bool cancel;
    QDateTime startDate;
    u32 initialSeed;
    u32 baseTick, baseOffset;
    u32 tickRange, offsetRange;
    int progress;

    QVector<QPair<u32, u32>> results;
    QMutex mutex;

};

#endif // PROFILESEARCHER_HPP
