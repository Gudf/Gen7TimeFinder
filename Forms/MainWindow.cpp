/*
 * This file is part of Gen7TimeFinder
 * Copyright (C) 2018-2019 by Admiral_Fish
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "MainWindow.hpp"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    checkProfileJson();
    setupModel();
    updateProfiles();
}

MainWindow::~MainWindow()
{
    QSettings settings;
    settings.setValue("profile", ui->comboBoxProfiles->currentIndex());

    delete ui;
}

void MainWindow::setupModel()
{
    stationaryModel = new StationaryModel(ui->tableViewStationary);
    //eventModel = new EventModel(ui->tableViewEvent);
    //wildModel = new WildModel(ui->tableViewWild);
    idModel = new IDModel(ui->tableViewID);

    ui->tableViewStationary->setModel(stationaryModel);
    //ui->tableViewEvent->setModel(eventModel);
    //ui->tableViewWild->setModel(wildModel);
    ui->tableViewID->setModel(idModel);

    ui->comboBoxStationaryNature->addItems(Utility::getNatures());
    ui->comboBoxStationaryNature->setup();
    ui->comboBoxStationaryHiddenPower->addItems(Utility::getHiddenPowers());
    ui->comboBoxStationaryHiddenPower->setup();
    ui->comboBoxStationarySynchNature->addItems(Utility::getNatures());
    ui->comboBoxStationaryGenderRatio->addItems(Utility::getGenderRatios());

    ui->comboBoxStationaryGenderRatio->setItemData(0, 0);
    ui->comboBoxStationaryGenderRatio->setItemData(1, 126);
    ui->comboBoxStationaryGenderRatio->setItemData(2, 30);
    ui->comboBoxStationaryGenderRatio->setItemData(3, 62);
    ui->comboBoxStationaryGenderRatio->setItemData(4, 190);
    ui->comboBoxStationaryGenderRatio->setItemData(5, 224);
    ui->comboBoxStationaryGenderRatio->setItemData(6, 1);
    ui->comboBoxStationaryGenderRatio->setItemData(7, 2);

    ui->textBoxStationaryStartFrame->setValues(InputType::Frame32Bit);
    ui->textBoxStationaryEndFrame->setValues(InputType::Frame32Bit);
    ui->textBoxEventStartFrame->setValues(InputType::Frame32Bit);
    ui->textBoxEventEndFrame->setValues(InputType::Frame32Bit);
    ui->textBoxIDStartFrame->setValues(InputType::Frame32Bit);
    ui->textBoxIDEndFrame->setValues(InputType::Frame32Bit);

    qRegisterMetaType<QVector<IDResult>>("QVector<IDResult>");
    qRegisterMetaType<QVector<StationaryResult>>("QVector<StationaryResult>");
}

void MainWindow::checkProfileJson()
{
    QFile file(QApplication::applicationDirPath() + "/profiles.json");
    if (file.open(QIODevice::NewOnly | QIODevice::Text))
    {
        file.close();
    }
}

void MainWindow::on_pushButtonProfileManager_clicked()
{
    auto *manager = new ProfileManager();
    connect(manager, &ProfileManager::updateProfiles, this, &MainWindow::updateProfiles);
    manager->show();
    manager->raise();
}

void MainWindow::on_comboBoxProfiles_currentIndexChanged(int index)
{
    if (index != -1)
    {
        auto profile = profiles.at(index);
        ui->labelProfileOffsetValue->setText(QString::number(profile.getOffset()));
        ui->labelProfileTickValue->setText(QString::number(profile.getTick(), 16));
        ui->labelProfileTIDValue->setText(QString::number(profile.getTID()));
        ui->labelProfileSIDValue->setText(QString::number(profile.getSID()));
        ui->labelProfileGameValue->setText(profile.getVersionString());
        ui->labelProfileShinyCharmValue->setText(profile.getShinyCharm() ? "Yes" : "No");
    }
}

void MainWindow::on_pushButtonStationarySearch_clicked()
{
    QDateTime start = ui->dateTimeEditStationaryStartDate->dateTime();
    QDateTime end = ui->dateTimeEditStationaryEndDate->dateTime();
    u32 frameStart = ui->textBoxStationaryStartFrame->getUInt();
    u32 frameEnd = ui->textBoxStationaryEndFrame->getUInt();

    if (start > end)
    {
        QMessageBox error;
        error.setText(tr("Set end date to be after start date."));
        error.exec();
        return;
    }
    if (frameStart > frameEnd)
    {
        QMessageBox error;
        error.setText(tr("Set end frame to be after start frame"));
        error.exec();
        return;
    }

    stationaryModel->clear();
    ui->pushButtonStationarySearch->setEnabled(false);
    ui->pushButtonStationaryCancel->setEnabled(true);

    QVector<u8> min = ui->ivFilterStationary->getLower();
    QVector<u8> max = ui->ivFilterStationary->getUpper();

    StationaryFilter filter(min, max, ui->comboBoxStationaryNature->getChecked(), ui->comboBoxStationaryHiddenPower->getChecked(),
                            ui->comboBoxStationaryAbility->currentIndex() - 1, ui->checkBoxStationaryShiny->isChecked(), ui->comboBoxStationaryGender->currentIndex());

    auto *search = new StationarySearcher(start, end, frameStart, frameEnd, ui->checkBoxStationary3IVs->isChecked(),
                                          ui->checkBoxStationaryAbilityLock->isChecked() ? ui->comboBoxStationaryAbilityLock->currentIndex() : -1, ui->comboBoxStationarySynchNature->currentIndex() - 1,
                                          ui->comboBoxStationaryGenderRatio->currentData().toInt(), ui->checkBoxStationaryAlwaysSynch->isChecked(), ui->checkBoxStationaryShinyLock->isChecked(),
                                          profiles[ui->comboBoxProfiles->currentIndex()], filter);
    auto *timer = new QTimer();

    connect(search, &StationarySearcher::finished, timer, &QTimer::deleteLater);
    connect(search, &StationarySearcher::finished, timer, &QTimer::stop);
    connect(search, &StationarySearcher::finished, this, [ = ] { ui->pushButtonStationarySearch->setEnabled(true); ui->pushButtonStationaryCancel->setEnabled(false); });
    connect(search, &StationarySearcher::finished, this, [ = ] { updateStationary(search->getResults(), search->currentProgress()); });
    connect(timer, &QTimer::timeout, this, [ = ] { updateStationary(search->getResults(), search->currentProgress()); });
    connect(ui->pushButtonStationaryCancel, &QPushButton::clicked, search, &StationarySearcher::cancelSearch);

    ui->progressBarStationary->setMaximum(search->maxProgress());

    search->start();
    timer->start(1000);
}

void MainWindow::updateStationary(const QVector<StationaryResult> &frames, int val)
{
    if (!frames.isEmpty())
    {
        stationaryModel->addItems(frames);
    }

    ui->progressBarStationary->setValue(val);
}

void MainWindow::on_pushButtonIDSearch_clicked()
{
    QDateTime start = ui->dateTimeEditIDStartDate->dateTime();
    QDateTime end = ui->dateTimeEditIDEndDate->dateTime();
    u32 frameStart = ui->textBoxIDStartFrame->getUInt();
    u32 frameEnd = ui->textBoxIDEndFrame->getUInt();

    if (start > end)
    {
        QMessageBox error;
        error.setText(tr("Set end date to be after start date."));
        error.exec();
        return;
    }
    if (frameStart > frameEnd)
    {
        QMessageBox error;
        error.setText(tr("Set end frame to be after start frame"));
        error.exec();
        return;
    }

    idModel->clear();
    ui->pushButtonIDSearch->setEnabled(false);
    ui->pushButtonIDCancel->setEnabled(true);

    FilterType type;
    if (ui->radioButtonIDTID->isChecked())
    {
        type = FilterType::TID;
    }
    else if (ui->radioButtonIDSID->isChecked())
    {
        type = FilterType::SID;
    }
    else if (ui->radioButtonIDTIDSID->isChecked())
    {
        type = FilterType::TIDSID;
    }
    else
    {
        type = FilterType::G7TID;
    }

    IDFilter filter(ui->textEditIDFilter->toPlainText(), ui->textEditTSVFilter->toPlainText(), type);

    auto *search = new IDSearcher(start, end, frameStart, frameEnd, profiles[ui->comboBoxProfiles->currentIndex()], filter);
    auto *timer = new QTimer();

    connect(search, &IDSearcher::finished, timer, &QTimer::deleteLater);
    connect(search, &IDSearcher::finished, timer, &QTimer::stop);
    connect(search, &IDSearcher::finished, this, [ = ] { ui->pushButtonIDSearch->setEnabled(true); ui->pushButtonIDCancel->setEnabled(false); });
    connect(search, &IDSearcher::finished, this, [ = ] { updateID(search->getResults(), search->currentProgress()); });
    connect(timer, &QTimer::timeout, this, [ = ] { updateID(search->getResults(), search->currentProgress()); });
    connect(ui->pushButtonIDCancel, &QPushButton::clicked, search, &IDSearcher::cancelSearch);

    ui->progressBarID->setMaximum(search->maxProgress());

    search->start();
    timer->start(1000);
}

void MainWindow::updateID(const QVector<IDResult> &frames, int val)
{
    if (!frames.isEmpty())
    {
        idModel->addItems(frames);
    }

    ui->progressBarID->setValue(val);
}

void MainWindow::updateProfiles()
{
    profiles = Utility::loadProfileList();
    profiles.insert(profiles.begin(), Profile());

    ui->comboBoxProfiles->clear();

    for (const auto &profile : profiles)
    {
        ui->comboBoxProfiles->addItem(profile.getName());
    }

    QSettings setting;
    int val = setting.value("profile").toInt();
    if (val < ui->comboBoxProfiles->count())
    {
        ui->comboBoxProfiles->setCurrentIndex(val);
    }
}

void MainWindow::on_actionCalibrate_Profile_triggered()
{
    auto *searcher = new ProfileCalibrater();
    connect(searcher, &ProfileCalibrater::updateProfiles, this, &MainWindow::updateProfiles);
    searcher->show();
    searcher->raise();
}
