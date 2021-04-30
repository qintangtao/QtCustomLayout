/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>

#include "locationlayout.h"

class LocationLayoutItem
{
public:
	LocationLayoutItem(QLayoutItem *layoutItem);

	QLayoutItem *item() const;

	QRect rect() const;
	void setRect(const QRect &rc);

	const QString &fontStyleName() const;
	void setFontStyleName(const QString &text);

	int pixelSize() const;
	void setPixelSize(int n);

	int minPixelSize() const;
	void setMinPixelSize(int n);

	int maxPixelSize() const;
	void setMaxPixelSize(int n);

private:
	QLayoutItem *m_item;
	QRect m_rc;

	//font size
	QString m_fontStyleName;
	int m_pixelSize;
	int m_minPixelSize;
	int m_maxPixelSize;
};

LocationLayoutItem::LocationLayoutItem(QLayoutItem *item)
	: m_item(item)
	, m_pixelSize(0)
	, m_minPixelSize(0)
	, m_maxPixelSize(0)
{
}

inline QLayoutItem *LocationLayoutItem::item() const {
	return m_item;
}

inline QRect LocationLayoutItem::rect() const {
	return m_rc;
}

inline void LocationLayoutItem::setRect(const QRect &rc) {
	m_rc = rc;
}

inline const QString &LocationLayoutItem::fontStyleName() const {
	return m_fontStyleName;
}
inline void LocationLayoutItem::setFontStyleName(const QString &text) {
	m_fontStyleName = text;
}

inline int LocationLayoutItem::pixelSize() const {
	return m_pixelSize;
}
inline void LocationLayoutItem::setPixelSize(int n) {
	m_pixelSize = n;
}

inline int LocationLayoutItem::minPixelSize() const {
	return m_minPixelSize;
}
inline void LocationLayoutItem::setMinPixelSize(int n) {
	m_minPixelSize = n;
}

inline int LocationLayoutItem::maxPixelSize() const {
	return m_maxPixelSize;
}
inline void LocationLayoutItem::setMaxPixelSize(int n) {
	m_maxPixelSize = n;
}

//! [1]
LocationLayout::LocationLayout(QWidget *parent, int w, int h, int margin)
    : QLayout(parent), m_wOriginal(w), m_hOriginal(h)
{
	setContentsMargins(margin, margin, margin, margin);
}

LocationLayout::LocationLayout(int w, int h, int margin)
    : m_wOriginal(w), m_hOriginal(h)
{
	setContentsMargins(margin, margin, margin, margin);
}
//! [1]

//! [2]
LocationLayout::~LocationLayout()
{
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
//! [2]

void LocationLayout::addWidget(QWidget *w, const QRect &rc)
{
	QLayout::addWidget(w);
	LocationLayoutItem *item = itemList.last();
	item->setRect(rc);
}

void LocationLayout::addWidget(QWidget *w, const QRect &rc, const QString &fontStyleName, int pixelSize, int minPixelSize, int maxPixelSize)
{
	QLayout::addWidget(w);
	LocationLayoutItem *item = itemList.last();
	item->setRect(rc);
	item->setFontStyleName(fontStyleName);
	item->setPixelSize(pixelSize);
	item->setMinPixelSize(minPixelSize);
	item->setMaxPixelSize(maxPixelSize);
	if (!fontStyleName.isEmpty())
		w->setProperty("fontStyle", fontStyleName);
}

void LocationLayout::addWidget(QWidget *w, const QRect &rc, const QString &fontStyleName, int pixelSize)
{
	addWidget(w, rc, fontStyleName, pixelSize, pixelSize > 6 ? 6 : pixelSize, pixelSize);
}

//! [3]
void LocationLayout::addItem(QLayoutItem *item)
{
    itemList.append(new LocationLayoutItem(item));
}
//! [3]


//! [5]
int LocationLayout::count() const
{
    return itemList.size();
}

QLayoutItem *LocationLayout::itemAt(int index) const
{
	LocationLayoutItem * item = itemList.value(index);
	if (item)
		return item->item();
    return 0;
}

QLayoutItem *LocationLayout::takeAt(int index)
{
	if (index >= 0 && index < itemList.size())
	{
		LocationLayoutItem *lItem = itemList.takeAt(index);
		QLayoutItem *item = lItem->item();
		delete lItem;
		return item;
	}
    else
        return 0;
}
//! [5]

//! [7]
bool LocationLayout::hasHeightForWidth() const
{
    return true;
}

int LocationLayout::heightForWidth(int width) const
{
    int height = doLayout(QRect(0, 0, width, 0), true);
    return height;
}
//! [7]

//! [8]
void LocationLayout::setGeometry(const QRect &rect)
{
    QLayout::setGeometry(rect);
    doLayout(rect, false);
}

QSize LocationLayout::sizeHint() const
{
    return minimumSize();
}

QSize LocationLayout::minimumSize() const
{
    QSize size;
    foreach (LocationLayoutItem *item, itemList)
        size = size.expandedTo(item->item()->minimumSize());

    size += QSize(2*margin(), 2*margin());
    return size;
}
//! [8]

//! [9]
int LocationLayout::doLayout(const QRect &rect, bool testOnly) const
{
    int left, top, right, bottom;
    getContentsMargins(&left, &top, &right, &bottom);
    QRect effectiveRect = rect.adjusted(+left, +top, -right, -bottom);
	int lineHeight = effectiveRect.width() * m_wOriginal / m_hOriginal;

	if (!testOnly)
	{
		double wRatio = (effectiveRect.width() * 1.0) / (m_wOriginal * 1.0);
		double hRatio = (effectiveRect.height() * 1.0) / (m_hOriginal * 1.0);
		foreach(LocationLayoutItem *item, itemList) {
			QWidget *wid = item->item()->widget();
			if (wid)
			{
				QRect rcOriginal = item->rect();

				int x = wRatio * rcOriginal.left();
				int y = hRatio * rcOriginal.top();

				int w = wRatio * rcOriginal.width();
				int h = hRatio * rcOriginal.height();
				wid->setGeometry(QRect(effectiveRect.left() + x, effectiveRect.top() + y, w, h));

				if (!item->fontStyleName().isEmpty() && item->pixelSize() > 0 && item->minPixelSize() > 0 && item->maxPixelSize() > 0)
				{
					double dRatio = qMin(wRatio, hRatio);
					int newPixelSize = dRatio * item->pixelSize();

					if (newPixelSize < item->minPixelSize())
						newPixelSize = item->minPixelSize();

					if (newPixelSize > item->maxPixelSize())
						newPixelSize = item->maxPixelSize();

					QString className = wid->metaObject()->className();
					wid->setStyleSheet(QString("%1[fontStyle=\"%2\"]{font-size: %3px;}")
						.arg(className).arg(item->fontStyleName()).arg(newPixelSize));
				}
			}
		}
	}
	return effectiveRect.y() + lineHeight + bottom;
}
//! [11]

