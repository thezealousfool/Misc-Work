from PyQt4.QtGui import *
from PyQt4.QtCore import *

import sqlOperations as sql

class updateTab(QWidget):
  def __init__(self, parent):
    super(updateTab, self).__init__()
    self.parent = parent

    # Grid layout to show the form
    gridLayout = QGridLayout()

    # Roll form row
    self.roll = QComboBox()
    self.roll.currentIndexChanged.connect(self.rollChanged)
    gridLayout.addWidget(QLabel('Roll'), 0, 0)
    gridLayout.addWidget(self.roll, 0, 1)

    # Name form row
    self.name = QLineEdit()
    gridLayout.addWidget(QLabel('Name'), 1, 0)
    gridLayout.addWidget(self.name, 1, 1)

    # Date of Admission form row
    self.DOA = QLineEdit()
    gridLayout.addWidget(QLabel('Date of Admission'), 2, 0)
    gridLayout.addWidget(self.DOA, 2, 1)

    # Address form row
    self.address = QLineEdit()
    gridLayout.addWidget(QLabel('Address'), 3, 0)
    gridLayout.addWidget(self.address, 3, 1)

    # Add Button
    buttonL = QHBoxLayout()
    button = QPushButton('Update')
    button.clicked.connect(self.updateClick)
    buttonL.addWidget(button)
    buttonL.addStretch(1)
    gridLayout.addLayout(buttonL, 4, 1)

    vLayout = QVBoxLayout(self)
    vLayout.addLayout(gridLayout)

    self.populateRolls()


  def rollChanged(self):
    roll = int(self.roll.currentText())
    (name, doa, address) = sql.getData(roll=roll)
    self.name.setText(str(name))
    self.DOA.setText(str(doa[2]) + '-' + str(doa[1]) + '-' + str(doa[0]))
    self.address.setText(address)


  def populateRolls(self):
    data = sql.getRolls()
    for roll in data:
      self.roll.addItem(str(roll))


  def updateClick(self):
    err = sql.updateEntry(name=str(self.name.text()),
                          roll=int(self.roll.currentText()),
                          doa=str(self.DOA.text()),
                          address=str(self.address.text()))

    if err:
      # If error occurs in executing SQL Query
      # it shows the SQL error message in a Message Box
      msgBox = QMessageBox()
      msgBox.setText('Updating Entry Failed.')
      msgBox.setInformativeText(str(err))
      msgBox.setWindowTitle('Error')
      msgBox.setIcon(QMessageBox.Critical)
      msgBox.exec_()
    else:
      # If no error, Successful Message Box shown
      msgBox = QMessageBox()
      msgBox.setText('Updating Entry Successful.')
      msgBox.setInformativeText('Successfully updated %s' %
                                str(self.name.text()))
      msgBox.setWindowTitle('Success')
      msgBox.setIcon(QMessageBox.Information)
      msgBox.exec_()

    # Update the contents of the table
    self.parent.refreshTableDisplay()
