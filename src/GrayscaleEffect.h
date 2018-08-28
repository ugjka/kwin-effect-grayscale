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

#ifndef EFFECTS_GRAYSCALE_H
#define EFFECTS_GRAYSCALE_H

#include <kwineffects.h>

//class GLShader;

/**
 * Grayscales desktop's colors
 **/
class GrayscaleEffect
    : public KWin::Effect
{
    Q_OBJECT
public:
    GrayscaleEffect();
    ~GrayscaleEffect();

    void drawWindow(KWin::EffectWindow* w, int mask, QRegion region, KWin::WindowPaintData& data);
    void prePaintScreen(KWin::ScreenPrePaintData &data, int time);
    void prePaintWindow(KWin::EffectWindow *w, KWin::WindowPrePaintData &data, int time);
    void paintEffectFrame(KWin::EffectFrame* frame, QRegion region, double opacity, double frameOpacity);
    bool isActive() const;

    static bool supported();

public Q_SLOTS:
    void toggleScreenGrayscale();
    void toggleWindow();
    void slotWindowClosed(KWin::EffectWindow *w);

protected:
    bool loadData();

private:
    bool m_inited;
    bool m_valid;
    KWin::GLShader* m_shader;
    bool m_allWindows;
    QList<KWin::EffectWindow*> m_windows;
};

#endif
