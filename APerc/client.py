import socket
import random
import time
import datetime
from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *

class Client(QWidget):
    def __init__(self, parent=None):
        super(Client, self).__init__(parent)
        self.port = 5000
        vbox = QVBoxLayout(self)
        self.setLayout(vbox)
        self.lineEdit = QLineEdit(self)
        self.lineEdit.setValidator(QIntValidator())
        self.lineEdit.setMaxLength(4)
        self.lineEdit.setAlignment(Qt.AlignRight)
        self.lineEdit.setPlaceholderText('Port')
        self.lineEdit.textChanged.connect(self.textChangedPort)
        vbox.addWidget(self.lineEdit)
        button = QPushButton('Connect to server via port')
        button.clicked.connect(self.client_program)       
        vbox.addWidget(button)
        self.rec = QRect(500,500,500,500)
        vbox.setGeometry(self.rec)
        self.setWindowTitle("Client program")

    def textChangedPort(self, text):
        self.port = text

    def client_program(self):
        subWindow = QDialog()
        layout = QGridLayout()
        self.text = QTextEdit(subWindow)
        self.text.setReadOnly(True)
        self.text.insertPlainText("")
        subWindow.setWindowTitle('Session')
        subWindow.setGeometry(self.rec)
        self.text.setSizeAdjustPolicy(QAbstractScrollArea.AdjustToContents)
        layout.addWidget(self.text,0,0)
        button = QPushButton('Close connection')
        button.clicked.connect(self.closeSession)
        layout.addWidget(button)
        subWindow.setLayout(layout)
        self.s = socket.socket()
        self.s.connect((socket.gethostname(), int(self.port)))  # connect to the server
        curr_time = datetime.datetime.now()
        curr = curr_time.strftime("%Y-%m-%d %H:%M:%S")
        seedHour = curr_time.hour
        random.seed(curr)
        rand = random.randint(1,40)
        subWindow.show()
        QApplication.processEvents()        
        self.refresh_data(str(curr))
        while True:
            e_data = self.s.recv(1024).decode()  # receive response
            if not e_data:
                break
            curr_time = datetime.datetime.now()
            curr = curr_time.strftime("%Y-%m-%d %H:%M:%S")
            if seedHour != curr_time.hour:
                random.seed(curr)
                self.refresh_data("changing seed")
                seedHour = curr_time.hour
                rand = random.randint(1,40)
                self.refresh_data(str(curr))
            d_data = ""
            for i in range(0, len(e_data)):
                d_data += chr(ord(e_data[i]) - rand)
            self.refresh_data(str(e_data))
            self.refresh_data(str(d_data))
            self.refresh_data("")
        self.s.close()

    def refresh_data(self, data):
        self.text.append(data)
        QApplication.processEvents()

    def closeSession(self):
        self.s.close()  # close the connection

if __name__ == '__main__':
    app = QApplication([])
    client = Client()
    client.show()
    app.exec()
