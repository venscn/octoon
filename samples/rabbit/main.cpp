#include <qapplication.h>
#include <qdesktopwidget.h>

#include "views/main_window.h"
#include "views/splash_screen.h"

int main(int argc, char *argv[])
{
#ifdef _WINDOWS_
	::SetConsoleOutputCP(CP_UTF8);
#endif

	QFile styleSheet(":res/qss/default.qss");

	if (styleSheet.open(QIODevice::ReadOnly))
	{
		QApplication app(argc, argv);
		app.setStyleSheet(styleSheet.readAll());

		auto splash = std::make_unique<rabbit::SplashScreen>();
		splash->show();

		rabbit::MainWindow w(splash.get());
		w.show();
		w.move((QApplication::desktop()->width() - w.width()) / 2, (QApplication::desktop()->height() - w.height()) / 2);

		splash.reset();

		app.exec();
	}
	else
	{
		qWarning("Can't open the style sheet file.");
		return 0;
	}
}