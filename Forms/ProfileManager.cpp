/*
 * This file is part of Gen7TimeFinder
 * Copyright (C) 2018 by Admiral_Fish
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

#include "ProfileManager.hpp"
#include "ui_ProfileManager.h"

ProfileManager::ProfileManager(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ProfileManager)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setAttribute(Qt::WA_DeleteOnClose);
}

ProfileManager::~ProfileManager()
{
    delete ui;
}

void ProfileManager::setupModels()
{
    model = new ProfileModel();
    model->setModel(Utility::loadProfileList());
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void ProfileManager::on_pushButtonNew_clicked()
{
    auto *dialog = new ProfileEditor();
    if (dialog->exec() == QDialog::Accepted)
    {
        Profile profile = dialog->getNewProfile();
        Utility::saveProfile(profile);
        model->addItem(profile);
        emit updateProfiles();
    }
    delete dialog;
}

void ProfileManager::on_pushButtonEdit_clicked()
{
    int r = ui->tableView->currentIndex().row();

    if (r < 0)
    {
        QMessageBox error;
        error.setText(tr("Please select a profile."));
        error.exec();
        return;
    }

    ProfileEditor *dialog = new ProfileEditor(model->getProfile(r));
    if (dialog->exec() == QDialog::Accepted)
    {
        Profile profile = dialog->getNewProfile();
        Utility::updateProfile(dialog->getOriginal(), profile);
        int r = ui->tableView->currentIndex().row();
        model->updateProfile(profile, r);
        emit updateProfiles();
    }
    delete dialog;
}

void ProfileManager::on_pushButtonDelete_clicked()
{
    int r = ui->tableView->currentIndex().row();

    if (r < 0)
    {
        QMessageBox error;
        error.setText(tr("Please select a profile."));
        error.exec();
        return;
    }

    Utility::deleteProfile(model->getProfile(r));
    model->removeProfile(r);
    emit updateProfiles();
}

void ProfileManager::on_pushButtonDone_clicked()
{
    this->close();
}
