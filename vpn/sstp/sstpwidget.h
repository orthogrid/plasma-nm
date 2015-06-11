/*
    Copyright 2015 Jan Grulich <jgrulich@redhat.com>

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License as
    published by the Free Software Foundation; either version 2 of
    the License or (at your option) version 3 or any later version
    accepted by the membership of KDE e.V. (or its successor approved
    by the membership of KDE e.V.), which shall act as a proxy
    defined in Section 14 of version 3 of the license.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SSTP_WIDGET_H
#define SSTP_WIDGET_H

#include "settingwidget.h"

#include <NetworkManagerQt/VpnSetting>

class QComboBox;
class SstpSettingWidgetPrivate;

class SstpSettingWidget : public SettingWidget
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(SstpSettingWidget)
public:
    explicit SstpSettingWidget(const NetworkManager::VpnSetting::Ptr &setting, QWidget *parent = 0);
    ~SstpSettingWidget();
    virtual void loadConfig(const NetworkManager::Setting::Ptr &setting);
    virtual QVariantMap setting(bool agentOwned = false) const;
    virtual bool isValid() const;

private Q_SLOTS:
    void doAdvancedDialog();
    void passwordTypeChanged(int index);
    void setShowPassword(bool show);
    void setShowProxyPassword(bool show);
private:
    SstpSettingWidgetPrivate * const d_ptr;
    void fillOnePasswordCombo(QComboBox *, NetworkManager::Setting::SecretFlags);
    uint handleOnePasswordType(const QComboBox *, const QString &, NMStringMap &, bool agentOwned) const;
};

#endif // SSTP_WIDGET_H