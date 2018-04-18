from PyQt4.QtGui import *
from PyQt4.QtCore import *

import sqlOperations as sql

class deleteTab(QWidget):
  def __init__(self, parent):
    super(deleteTab, self).__init__()
    self.parent = parent

    # Grid layout to show the form
    gridLayout = QGridLayout()

    # Roll form row
    self.roll = QComboBox()
    gridLayout.addWidget(QLabel('Roll'), 0, 0)
    gridLayout.addWidget(self.roll, 0, 1)

    # Add Button
    buttonL = QHBoxLayout()
    button = QPushButton('Remove')
    button.clicked.connect(self.removeClick)
    buttonL.addWidget(button)
    buttonL.addStretch(1)
    gridLayout.addLayout(buttonL, 1, 1)

    vLayout = QVBoxLayout(self)
    vLayout.addLayout(gridLayout)

    self.populateRolls()


  def populateRolls(self):
    data = sql.getRolls()
    for roll in data:
      self.roll.addItem(str(roll))


  def removeClick(self):
    roll = int(self.roll.currentText())
    err = sql.removeEntry(roll=roll)
    if err:
      # If error occurs in executing SQL Query
      # it shows the SQL error message in a Message Box
      msgBox = QMessageBox()
      msgBox.setText('Removing Entry Failed.')
      msgBox.setInformativeText(str(err))
      msgBox.setWindowTitle('Error')
      msgBox.setIcon(QMessageBox.Critical)
      msgBox.exec_()
    else:
      # If no error, Successful Message Box shown
      msgBox = QMessageBox()
      msgBox.setText('Removing Entry Successful.')
      msgBox.setInformativeText('Successfully removed roll %s' %
                                str(roll))
      msgBox.setWindowTitle('Success')
      msgBox.setIcon(QMessageBox.Information)
      msgBox.exec_()

    # Update the contents of the table
    self.parent.refreshTableDisplay()
