import sys
from PyQt4.QtGui import *
from PyQt4.QtCore import *

import mainScreen as screen

if __name__ == '__main__':
  app = QApplication(sys.argv)
  screen = screen.mainScreen('DBMS GUI')
  sys.exit(app.exec_())
