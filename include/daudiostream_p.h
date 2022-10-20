// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#pragma once

#include "dtkaudiomanager_global.h"
#include "daudiostream.h"

#include <QObject>

DAUDIOMANAGER_BEGIN_NAMESPACE
class DAudioDevice;
class DPlatformAudioInputDevice;
class DPlatformAudioOutputDevice;
class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioStream : public QObject, public QSharedData
{
    Q_OBJECT

    Q_PROPERTY(bool mute READ mute WRITE setMute NOTIFY muteChanged)
    Q_PROPERTY(double fade READ fade WRITE setFade NOTIFY fadeChanged)
    Q_PROPERTY(double volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(double balance READ balance WRITE setBalance NOTIFY balanceChanged)
    Q_PROPERTY(bool supportBalance READ supportBalance NOTIFY supportBalanceChanged)
    Q_PROPERTY(bool supportFade READ supportFade NOTIFY supportFadeChanged)
    Q_PROPERTY(double meterVolume READ meterVolume NOTIFY meterVolumeChanged)
    Q_PROPERTY(QString card READ card NOTIFY cardChanged)
public:

    virtual bool mute() const = 0;
    virtual double fade() const = 0;
    virtual double volume() const = 0;
    virtual double balance() const = 0;

    virtual bool supportBalance() const = 0;
    virtual bool supportFade() const = 0;
    virtual double meterVolume() const = 0;

    virtual QString card() const = 0;

    void setName(const QString &name) { m_name = name; }
    QString name() const { return m_name; }

public Q_SLOTS:
    virtual void setMute(bool mute) = 0;
    virtual void setFade(double fade) = 0;
    virtual void setVolume(double volume) = 0;
    virtual void setBalance(double balance) = 0;

Q_SIGNALS:
    void muteChanged(bool mute);
    void fadeChanged(double fade);
    void volumeChanged(double volume);
    void balanceChanged(double balance);

    void supportBalanceChanged(bool supportBalance);
    void supportFadeChanged(bool supportFade);
    void meterVolumeChanged(double meterVolume);

    void cardChanged(QString card);

protected:
    QString m_name;
};

class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioInputStream : public DPlatformAudioStream
{
    Q_OBJECT

public:
    explicit DPlatformAudioInputStream(DPlatformAudioOutputDevice *parent = nullptr)
    {

    }
    virtual ~DPlatformAudioInputStream() override
    {
    }

    virtual DAudioInputStream *create()
    {
        return new DAudioInputStream(this);
    }

protected:
    DAudioInputStream *m_source = nullptr;
};

class LIBDTKAUDIOMANAGERSHARED_EXPORT DPlatformAudioOutputStream : public DPlatformAudioStream
{
    Q_OBJECT

public:
    explicit DPlatformAudioOutputStream(DPlatformAudioInputDevice *parent = nullptr)
    {

    }
    virtual ~DPlatformAudioOutputStream() override
    {
    }

    virtual DAudioOutputStream *create()
    {
        return new DAudioOutputStream(this);
    }
};
DAUDIOMANAGER_END_NAMESPACE
