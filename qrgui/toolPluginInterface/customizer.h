#pragma once

#include <QtCore/QObject>
#include <QtGui/QIcon>

#include "mainwindow/mainWindowDockInterface.h"

namespace qReal {

/// Customization class for configuring QReal's main GUI module
class Customizer
{
public:
	/// Tells if we should show the button of opening the interpreted diagram or not
	virtual bool showInterpeterButton() const
	{
		return true;
	}

	/// Allows to customize main window's title from plugin
	virtual QString windowTitle() const
	{
		return "QReal";
	}

	/// Customizes QReal's icon
	virtual QIcon applicationIcon() const
	{
		return QIcon();
	}

	/// Customizes QReal`s logo in large format
	virtual QImage applicationLogo() const
	{
		return QImage(":/icons/kroki6.png");
	}

	/// Customizes product version
	virtual QString productVersion() const
	{
		return "1.0.0";
	}

	/// Customizes text in about dialog
	virtual QString aboutText() const
	{
		return "<b>QReal<b><br><br><a href=\"http://qreal.ru/\">http://qreal.ru/</a>";
	}

	/// Customizes default examples directory for current system.
	/// Empty string as result means that the system doesn`t have examples
	virtual QString examplesDirectory() const
	{
		return QString();
	}

	/// Tells if we should show trace connections menu or not
	virtual bool showConnectionRelatedMenus() const
	{
		return false;
	}

	virtual bool showUsagesRelatedMenus() const
	{
		return false;
	}

	/// Customizes docks placement and visibility. Default implementation does nothing
	virtual void customizeDocks(gui::MainWindowDockInterface *dockInterface)
	{
		Q_UNUSED(dockInterface)
	}

	virtual QString addExplosionMenuName() const
	{
		return QObject::tr("Add connection");
	}

	virtual QString changeExplosionMenuName() const
	{
		return QObject::tr("Connect to other");
	}

	virtual QString deleteExplosionMenuName() const
	{
		return QObject::tr("Disconnect");
	}

	virtual QString goToConnectedMenuName() const
	{
		return QObject::tr("Go to connected element");
	}

	virtual bool showExpandConnectionAction() const
	{
		return false;
	}

	virtual QString expandExplosionActionText() const
	{
		return QObject::tr("Expand explosion");
	}

	virtual QString collapseExplosionActionText() const
	{
		return QObject::tr("Collapse explosion");
	}

	virtual QString userPaletteTitle() const
	{
		return QObject::tr("Existing connections");
	}

	virtual QString userPaletteDescription() const
	{
		return QObject::tr("Elements from this group exist"\
				" for reusing all created connections");
	}
};

}
