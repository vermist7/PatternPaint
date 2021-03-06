/*
 * This source file is part of EasyPaint.
 *
 * Copyright (c) 2012 EasyPaint <https://github.com/Gr1N/EasyPaint>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "sprayinstrument.h"
#include "patterneditor.h"

#include <QPen>
#include <QPainter>
#include <math.h>

SprayInstrument::SprayInstrument(QObject *parent) :
    CustomCursorInstrument(":/instruments/images/instruments-icons/cursor_spray.png", parent) {
}

void SprayInstrument::mousePressEvent(QMouseEvent *event, PatternEditor& pe, const QPoint& pt)
{
    if(event->button() == Qt::LeftButton)
    {
        mStartPoint = mEndPoint = pt;
        pe.setPaint(true);
        makeUndoCommand(pe);
    }
}

void SprayInstrument::mouseMoveEvent(QMouseEvent*, PatternEditor& pe, const QPoint& pt)
{
    if(pe.isPaint()) {
        mEndPoint = pt;
        paint(pe);
        mStartPoint = pt;
    }
}

void SprayInstrument::mouseReleaseEvent(QMouseEvent*, PatternEditor& pe, const QPoint&)
{
    if(pe.isPaint()) {
        paint(pe);
        pe.setPaint(false);
    }
}

void SprayInstrument::paint(PatternEditor& pe)
{
    QPainter painter(pe.getPattern());
    painter.setPen(QPen(pe.getPrimaryColor(), pe.getPenSize(), Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    int x, y;
    for(int i(0); i < 12; i++) {
        switch(i) {
        case 0: case 1: case 2: case 3:
            x = (qrand() % 5 - 2)
                    * sqrt(pe.getPenSize());
            y = (qrand() % 5 - 2)
                    * sqrt(pe.getPenSize());
            break;
        case 4: case 5: case 6: case 7:
            x = (qrand() % 10 - 4)
                    * sqrt(pe.getPenSize());
            y = (qrand() % 10 - 4)
                    * sqrt(pe.getPenSize());
            break;
        case 8: case 9: case 10: case 11:
            x = (qrand() % 15 - 7)
                    * sqrt(pe.getPenSize());
            y = (qrand() % 15 - 7)
                    * sqrt(pe.getPenSize());
            break;
        }

        painter.drawPoint(mEndPoint.x() + x, mEndPoint.y() + y);
    }

    painter.end();
}
