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

#include "ProfileEditor.hpp"
#include "ui_ProfileEditor.h"

ProfileEditor::ProfileEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileEditor)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

    setupModels();
}

ProfileEditor::ProfileEditor(const Profile &profile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileEditor)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

    setupModels();

    ui->lineEditProfileName->setText(profile.getName());
    ui->comboBoxProfileVersion->setCurrentIndex(ui->comboBoxProfileVersion->findData(profile.getVersion()));
    ui->textBoxProfileOffset->setText(QString::number(profile.getOffset()));
    ui->textBoxProfileTick->setText(QString::number(profile.getTick(), 16));
    ui->textBoxProfileTID->setText(QString::number(profile.getTID()));
    ui->textBoxProfileSID->setText(QString::number(profile.getSID()));
    ui->checkBoxShinyCharm->setChecked(profile.getShinyCharm());

    original = profile;
}

ProfileEditor::ProfileEditor(u32 tick, u32 offset, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProfileEditor)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_QuitOnClose, false);
    setWindowFlags(Qt::Widget | Qt::MSWindowsFixedSizeDialogHint);

    setupModels();

    ui->textBoxProfileOffset->setText(QString::number(offset));
    ui->textBoxProfileTick->setText(QString::number(tick, 16));
}

ProfileEditor::~ProfileEditor()
{
    delete ui;
}

Profile ProfileEditor::getNewProfile()
{
    return fresh;
}

Profile ProfileEditor::getOriginal()
{
    return original;
}

void ProfileEditor::setupModels()
{
    ui->textBoxProfileTID->setValues(InputType::ID);
    ui->textBoxProfileSID->setValues(InputType::ID);
    ui->textBoxProfileTick->setValues(InputType::Seed32Bit);
    ui->textBoxProfileOffset->setValues(0, 100);

    ui->comboBoxProfileVersion->setItemData(0, Game::Sun);
    ui->comboBoxProfileVersion->setItemData(1, Game::Moon);
    ui->comboBoxProfileVersion->setItemData(2, Game::UltraSun);
    ui->comboBoxProfileVersion->setItemData(3, Game::UltraMoon);
}

void ProfileEditor::on_buttonBox_accepted()
{
    QString input = ui->lineEditProfileName->text().trimmed();
    if (input.isEmpty())
    {
        QMessageBox error;
        error.setText(tr("Enter a Profile Name."));
        error.exec();
        return;
    }

    fresh = Profile(input, ui->textBoxProfileOffset->getUInt(), ui->textBoxProfileTick->getUInt(), ui->textBoxProfileTID->getUShort(),
                    ui->textBoxProfileSID->getUShort(), static_cast<Game>(ui->comboBoxProfileVersion->currentData().toInt()), ui->checkBoxShinyCharm->isChecked());

    done(QDialog::Accepted);
}

void ProfileEditor::on_buttonBox_rejected()
{
    done(QDialog::Rejected);
}
