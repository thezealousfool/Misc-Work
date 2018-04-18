from PyQt4.QtGui import *
from PyQt4.QtCore import *

import AddTab, UpdateTab, DeleteTab

import sqlOperations as sql

class mainScreen(QMainWindow):
  def __init__(self, title):
    super(mainScreen, self).__init__()
    self.initUi(800, 500, 10, title)


  def initUi(self, winWidth, winHeight, winMargins, title):

    self.setWindowTitle(title)
    self.setMinimumSize(winWidth, winHeight)
    self.resize(winWidth, winHeight)

    # main Virtical Layout
    vLayout = QVBoxLayout()
    vLayout.setSpacing(winMargins)
    vLayout.setMargin(2 * winMargins)

    # Tab Group
    tabGroup = QTabWidget()
    vLayout.addWidget(tabGroup)

    # Table to show records
    self.tableDisplay = QTableWidget()
    self.tableDisplay.setColumnCount(4)
    self.tableDisplay.setHorizontalHeaderLabels(['Name', 'Roll', 'Date of Admission', 'Address'])
    self.tableDisplay.setEditTriggers(QAbstractItemView.NoEditTriggers)
    self.tableDisplay.horizontalHeader().setResizeMode(3, QHeaderView.Stretch)
    vLayout.addWidget(self.tableDisplay)

    # Adding tabs to the main Tab Group
    tabGroup.addTab(AddTab.addTab(parent=self), 'Add')
    tabGroup.addTab(UpdateTab.updateTab(parent=self), 'Update')
    tabGroup.addTab(DeleteTab.deleteTab(parent=self), 'Delete')

    # setting central widget
    mainVLayoutWidget = QWidget()
    mainVLayoutWidget.setLayout(vLayout)
    self.setCentralWidget(mainVLayoutWidget)

    self.refreshTableDisplay()
    self.show()

  
  # Funtion to refresh the contents of the table
  def refreshTableDisplay(self):
    self.tableDisplay.setRowCount(0)
    # fetching data from MySQL
    data = sql.fetchData()
    for row in data:
      # Populating table with data
      self.tableDisplay.insertRow(self.tableDisplay.rowCount())
      self.tableDisplay.setItem(self.tableDisplay.rowCount()-1, 0, QTableWidgetItem(str(row[0])))
      self.tableDisplay.setItem(
          self.tableDisplay.rowCount()-1, 1, QTableWidgetItem(str(row[1])))
      self.tableDisplay.setItem(
          self.tableDisplay.rowCount()-1, 2,
          QTableWidgetItem(str(row[2][0]) + '-' + str(row[2][1]) + '-' + str(row[2][2])))
      self.tableDisplay.setItem(
          self.tableDisplay.rowCount()-1, 3, QTableWidgetItem(str(row[3])))
