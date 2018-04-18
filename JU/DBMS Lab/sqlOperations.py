import mysql.connector as con

cnx = con.connect(user='root', password='vivek',
                  host='localhost', database='mydb')


def fetchData():
  cursor = cnx.cursor()

  query = str("SELECT name, roll, doa, address FROM Student")

  cursor.execute(query)

  data = []
  for data_row in cursor:
    data.append([data_row[0], data_row[1],
                 (data_row[2].day, data_row[2].month, data_row[2].year),
                 data_row[3]])

  cnx.commit()
  cursor.close()
  return data


def getRolls():
  cursor = cnx.cursor()

  query = str("SELECT roll FROM Student")

  cursor.execute(query)

  data = []
  for data_row in cursor:
    data.append(data_row[0])

  cnx.commit()
  cursor.close()
  return data


def getData(roll):
  cursor = cnx.cursor()

  query = str("SELECT name, doa, address FROM Student WHERE roll=%d" % roll)

  cursor.execute(query)

  if cursor.rowcount == 0:
    data = ()
  else:
    for data_row in cursor:
      data = (data_row[0],
              (data_row[1].day, data_row[1].month, data_row[1].year),
              data_row[2])

  cnx.commit()
  cursor.close()
  return data


def addEntry(name, roll, doa, address):
  cursor = cnx.cursor()

  query = str("INSERT INTO Student VALUES('%s', %d, '%s', '%s')"
              % (name, roll, doa, address))


  try:
    cursor.execute(query)
    cnx.commit()
  except con.Error as err:
    print "Query :: %s" % query
    print "Error :: %s" % err
    return err.msg
  finally:
    cursor.close()


def updateEntry(name, roll, doa, address):
  cursor = cnx.cursor()

  query = str("UPDATE Student SET name='%s', doa='%s', address='%s' WHERE roll=%d"
              % (name, doa, address, roll))

  try:
    cursor.execute(query)
    cnx.commit()
  except con.Error as err:
    print "Query :: %s" % query
    print "Error :: %s" % err
    return err.msg
  finally:
    cursor.close()


def removeEntry(roll):
  cursor = cnx.cursor()

  query = str("DELETE FROM Student WHERE roll=%d" % roll)

  try:
    cursor.execute(query)
    cnx.commit()
  except con.Error as err:
    print "Query :: %s" % query
    print "Error :: %s" % err
    return err.msg
  finally:
    cursor.close()
