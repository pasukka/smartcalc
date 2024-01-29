#include "view.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}


/*
#include "consoleView.h"

int main() {
    ExampleModel model;
    ExampleController controller(&model);
    ConsoleView view(&controller);
    view.startEventLoop();
    return 1;
}
*/