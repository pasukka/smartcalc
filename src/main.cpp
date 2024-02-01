#include "view.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  
  Model model;
  Controller controller(&model);
  View view(&controller);
  view.startEventLoop();
  return a.exec();
  
  // return 1;

  // QApplication a(argc, argv);
  // MainWindow w;
  // w.show();
  // return a.exec();
}

