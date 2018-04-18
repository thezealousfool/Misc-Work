from PyQt4.QtGui import *
from PyQt4.QtCore import *

import sqlOperations as sql

class addTab(QWidget):
  def __init__(self, parent):
    super(addTab, self).__init__()
    self.parent = parent

    # Grid layout to show the form
    gridLayout = QGridLayout()

    # Name form row
    self.name = QLineEdit()
    gridLayout.addWidget(QLabel('Name'), 0, 0)
    gridLayout.addWidget(self.name, 0, 1)

    # Roll form row
    self.roll = QLineEdit()
    gridLayout.addWidget(QLabel('Roll'), 1, 0)
    gridLayout.addWidget(self.roll, 1, 1)

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
    button = QPushButton('Add')
    button.clicked.connect(self.addClick)
    buttonL.addWidget(button)
    buttonL.addStretch(1)
    gridLayout.addLayout(buttonL, 4, 1)

    vLayout = QVBoxLayout(self)
    vLayout.addLayout(gridLayout)


  # Function called on click of Add button
  def addClick(self):
    try:
      # Adding the entry to SQL
      err = sql.addEntry(name=str(self.name.text()),
                         roll=int(self.roll.text()),
                         doa=str(self.DOA.text()),
                         address=str(self.address.text()))
    except ValueError:
      # ValueError occurs in int(self.roll.text())
      # When self.roll.text() is a non-integer value
      # Python raises this error even before executing
      # any SQL query, hence handled separately
      msgBox = QMessageBox()
      msgBox.setText('Adding Entry Failed.')
      msgBox.setInformativeText('Roll field should have a valid integer number')
      msgBox.setWindowTitle('Error')
      msgBox.setIcon(QMessageBox.Critical)
      msgBox.exec_()

    if err:
      # If error occurs in executing SQL Query
      # it shows the SQL error message in a Message Box
      msgBox = QMessageBox()
      msgBox.setText('Adding Entry Failed.')
      msgBox.setInformativeText(str(err))
      msgBox.setWindowTitle('Error')
      msgBox.setIcon(QMessageBox.Critical)
      msgBox.exec_()
    else:
      # If no error, Successful Message Box shown
      msgBox = QMessageBox()
      msgBox.setText('Adding Entry Successful.')
      msgBox.setInformativeText('Successfully added %s' % str(self.name.text()))
      msgBox.setWindowTitle('Success')
      msgBox.setIcon(QMessageBox.Information)
      msgBox.exec_()

    # Update the contents of the table
    self.parent.refreshTableDisplay()
