/********************************************************************
 KWin - the KDE window manager
 This file is part of the KDE project.

Copyright (C) 2007 Rivo Laks <rivolaks@hot.ee>
Copyright (C) 2008 Lucas Murray <lmurray@undefinedfire.com>
Copyright (C) 2018 ugjka <esesmu@protonmail.com>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/

#include "GrayscaleEffect.h"

#include <QAction>
#include <QFile>
#include <kwinglutils.h>
#include <kwinglplatform.h>
#include <QStandardPaths>
#include <QAction>
#include <KGlobalAccel>
#include <KLocalizedString>
#include <QMatrix4x4>

GrayscaleEffect::GrayscaleEffect()
    :   m_inited(false),
        m_valid(true),
        m_shader(NULL),
        m_allWindows(false)
{
    QAction* a = new QAction(this);
    a->setObjectName(QStringLiteral("Grayscale"));
    a->setText(i18n("Toggle Grayscale Effect"));
    KGlobalAccel::self()->setDefaultShortcut(a, QList<QKeySequence>() << Qt::CTRL + Qt::META + Qt::Key_G);
    KGlobalAccel::self()->setShortcut(a, QList<QKeySequence>() << Qt::CTRL + Qt::META + Qt::Key_G);
    KWin::effects->registerGlobalShortcut(Qt::CTRL + Qt::META + Qt::Key_G, a);
    connect(a, SIGNAL(triggered(bool)), this, SLOT(toggleScreenGrayscale()));

    QAction* b = new QAction(this);
    b->setObjectName(QStringLiteral("GrayscaleWindow"));
    b->setText(i18n("Toggle Grayscale Effect on Window"));
    KGlobalAccel::self()->setDefaultShortcut(b, QList<QKeySequence>() << Qt::CTRL + Qt::META + Qt::Key_H);
    KGlobalAccel::self()->setShortcut(b, QList<QKeySequence>() << Qt::CTRL + Qt::META + Qt::Key_H);
    KWin::effects->registerGlobalShortcut(Qt::CTRL + Qt::META + Qt::Key_H, b);
    connect(b, SIGNAL(triggered(bool)), this, SLOT(toggleWindow()));

    connect(KWin::effects, SIGNAL(windowClosed(KWin::EffectWindow*)), this, SLOT(slotWindowClosed(KWin::EffectWindow*)));
}

GrayscaleEffect::~GrayscaleEffect()
{
    delete m_shader;
}

bool GrayscaleEffect::supported()
{
    return KWin::effects->compositingType() == KWin::OpenGL2Compositing;
}

bool GrayscaleEffect::loadData()
{
    m_inited = true;

    m_shader = KWin::ShaderManager::instance()->generateShaderFromResources(KWin::ShaderTrait::MapTexture, QString(), QStringLiteral("gray.frag"));
    if (!m_shader->isValid()) {
        qCCritical(KWINEFFECTS) << "The shader failed to load!";
        return false;
    }

    return true;
}

void GrayscaleEffect::prePaintScreen(KWin::ScreenPrePaintData &data, int time)
{
    KWin::effects->prePaintScreen(data, time);
}

void GrayscaleEffect::prePaintWindow(KWin::EffectWindow *w, KWin::WindowPrePaintData &data, int time)
{
    if (m_valid && (m_allWindows != m_windows.contains(w))) {
        data.mask |= PAINT_WINDOW_TRANSFORMED;
    }
    KWin::effects->prePaintWindow(w, data, time);
}

void GrayscaleEffect::drawWindow(KWin::EffectWindow* w, int mask, QRegion region, KWin::WindowPaintData& data)
{
    // Load if we haven't already
    if (m_valid && !m_inited)
        m_valid = loadData();

    bool useShader = m_valid && (m_allWindows != m_windows.contains(w));
    if (useShader) {
        KWin::ShaderManager *shaderManager = KWin::ShaderManager::instance();
        shaderManager->pushShader(m_shader);

        data.shader = m_shader;
    }

    KWin::effects->drawWindow(w, mask, region, data);

    if (useShader) {
        KWin::ShaderManager::instance()->popShader();
    }
}

void GrayscaleEffect::paintEffectFrame(KWin::EffectFrame* frame, QRegion region, double opacity, double frameOpacity)
{
    if (m_valid && m_allWindows) {
        frame->setShader(m_shader);
        KWin::ShaderBinder binder(m_shader);
        KWin::effects->paintEffectFrame(frame, region, opacity, frameOpacity);
    } else {
        KWin::effects->paintEffectFrame(frame, region, opacity, frameOpacity);
    }
}

void GrayscaleEffect::slotWindowClosed(KWin::EffectWindow* w)
{
    m_windows.removeOne(w);
}

void GrayscaleEffect::toggleScreenGrayscale()
{
    m_allWindows = !m_allWindows;
    KWin::effects->addRepaintFull();
}

void GrayscaleEffect::toggleWindow()
{
    if (!KWin::effects->activeWindow()) {
        return;
    }
    if (!m_windows.contains(KWin::effects->activeWindow()))
        m_windows.append(KWin::effects->activeWindow());
    else
        m_windows.removeOne(KWin::effects->activeWindow());
    KWin::effects->activeWindow()->addRepaintFull();
}

bool GrayscaleEffect::isActive() const
{
    return m_valid && (m_allWindows || !m_windows.isEmpty());
}

#include "GrayscaleEffect.moc"
