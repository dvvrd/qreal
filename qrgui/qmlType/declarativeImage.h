#pragma once

#include <QtCore/QFileInfo>
#include <QtDeclarative/QDeclarativeItem>
#include <QtSvg/QSvgRenderer>
#include <qrkernel/settingsManager.h>

#include <qrkernel/settingsManager.h>

namespace qmlTypes {

class DeclarativeImage : public QDeclarativeItem
{
	Q_OBJECT

	Q_PROPERTY(int x1 READ x1 WRITE setX1 NOTIFY x1Changed)
	Q_PROPERTY(int y1 READ y1 WRITE setY1 NOTIFY y1Changed)
	Q_PROPERTY(int x2 READ x2 WRITE setX2 NOTIFY x2Changed)
	Q_PROPERTY(int y2 READ y2 WRITE setY2 NOTIFY y2Changed)
	Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)

public:
	explicit DeclarativeImage(QDeclarativeItem *parent = 0);
	~DeclarativeImage() {qDebug() << "in descturctor" << mSource; }
	int x1() const;
	int y1() const;
	int x2() const;
	int y2() const;
	QString source() const;

signals:
	void x1Changed();
	void y1Changed();
	void x2Changed();
	void y2Changed();
	void sourceChanged();

protected:
	void updateSize();
	void setX1(int x1);
	void setY1(int y1);
	void setX2(int x2);
	void setY2(int y2);
	void setSource(QString source);

private:
	/// Cache for images that contains them pre-loaded and parsed and is able to quickly draw it on a painter.
	/// Pixmaps and svg images are contained separately as they are rendered differently.
	class ImagesCache {
	public:
		/// Draws image with given file name on given painter in given rectangle. Note that actual file, from which
		/// an image will be loaded may be different from fileName, as described in selectBestImageFile.
		/// @see selectBestImageFile
		void drawImage(QString const &fileName, QPainter &painter, QRect const &rect);

		/// Clears prerendered svg cache.
		void invalidateSvgCache(double zoomFactor);

	private:
		/// Selects "best available" image file, using following rules:
		/// - if there is .svg file with given name in a directory from filePath, it is used as actual image file.
		/// - else if there is a file with other extension but with correct name, it is used.
		/// - else, if there is no such file, it tries to select a file with name "default" in given directory, using the
		///   rules above.
		/// - if everything above fails, system default image file, from qrgui/icons (or, when compiled,
		///   from ":/icons/default.svg"), is used.
		static QFileInfo selectBestImageFile(QString const &filePath);

		/// Loads pixmap from given file, returns empty QByteArray if file does not exist.
		static QByteArray loadPixmap(QFileInfo const &fileInfo);

		/// Maps file name to pre-loaded pixmap with image.
		QHash<QString, QPixmap> mFileNamePixmapMap;

		/// Maps file name to a svg renderer object.
		QHash<QString, QSharedPointer<QSvgRenderer>> mFileNameSvgRendererMap;

		/// Maps file name to pixmaps with pre-rendered svg images.
		QHash<QString, QPixmap> mPrerenderedSvgs;

		/// Current scene zoom factor for rendering svg files.
		double mCurrentZoomFactor = 1;
	};

	/// Loads pixmap from given file, returns empty QByteArray if file does not exist.
	static QByteArray loadPixmap(QFileInfo const &fileInfo);

	/// Smart cache for images, to avoid loading image from disc on every paint() call.
	ImagesCache mImagesCache;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	void drawImage(QString const &fileName, QPainter &painter, QRect const &rect);
protected:
	int mX1;
	int mY1;
	int mX2;
	int mY2;
	QString mSource;
};

}
QML_DECLARE_TYPE(qmlTypes::DeclarativeImage)
