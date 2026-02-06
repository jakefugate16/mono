import sys
import os

from PySide6.QtWidgets import(
	QMainWindow,
    	QWidget,
    	QWizard,
    	QWizardPage,
    	QGridLayout,
    	QApplication,
    	QPushButton,
    	QHBoxLayout,
    	QVBoxLayout
    	)

from PySide6.QtMultimedia import(
    	QCamera,
    	QCameraDevice,
    	QMediaCaptureSession,
    	QImageCapture,
    	QMediaDevices,
    	)

from PySide6.QtMultimediaWidgets import QVideoWidget 

class Window1(QWizardPage):
	def __init__(self):
        	super().__init__()
        
        	self.nextwindow = None

        	self.setWindowTitle("Window 1")
        	self.m_button1 = QPushButton("Click me!")
        	self.m_button1.clicked.connect(self.nextWindow)

        	windowlayout  = QGridLayout()
        	windowlayout.addWidget(self.m_button1, 0, 0)
        	self.setLayout(windowlayout)

	def nextWindow(self):
            	print("Button clicked.")


class Window2(QWizardPage):
	def __init__(self):
		super().__init__()
        
		#set ui
		self.setWindowTitle("Camera Window")
        
		self.m_capture_button = QPushButton("Capture Image")
		self.m_capture_button.clicked.connect(self.captureImage)
		self.m_switch_button = QPushButton("Switch Cameras")
		self.m_switch_button.clicked.connect(self.switchCamera)
        
		self.m_video_widget = QVideoWidget()

		layout = QGridLayout()
		layout.addWidget(self.m_video_widget, 0, 0)
		layout.addWidget(self.m_capture_button, 0 , 1)
		layout.addWidget(self.m_switch_button, 1, 1)
		self.setLayout(layout)

		#initialize camera member variables to track which camera is in use
		self.m_capture_session = QMediaCaptureSession()
		self.m_image_capture = QImageCapture()
		self.m_cameras = QMediaDevices.videoInputs()
		self.m_camera_current = QCamera()
		self.m_camera_index = 0
		
		self.cameraSetup()
	
	#setup a camera from list of cameras for capturing an image.
	def cameraSetup(self):	
		self.m_camera_device = self.m_cameras[self.m_camera_index]

		self.m_camera_current = QCamera(self.m_camera_device)
		self.m_capture_session.setCamera(self.m_camera_current)
		self.m_capture_session.setVideoOutput(self.m_video_widget)

		self.m_camera_current.start()		
	
	#switch camera from a list of available cameras
	def switchCamera(self):
		if (self.m_camera_index >= len(self.m_cameras) - 1):
			self.m_camera_index = 0
		else:
			self.m_camera_index += 1

		self.cameraSetup()
 
 	
	def captureImage(self):
		self.m_image_capture = QImageCapture(self.m_camera_current)
		self.m_capture_session.setImageCapture(self.m_image_capture)
		self.m_image_capture = QImageCapture(self.m_camera_current)
		self.m_capture_session.setImageCapture(self.m_image_capture)
		self.m_image_capture.setFileFormat(QImageCapture.PNG)
		self.m_image_capture.captureToFile(os.getcwd())


def main():
	app = QApplication(sys.argv)

	wizard = QWizard()
	wizard.addPage(Window1())
	wizard.addPage(Window2())
	wizard.show()
	sys.exit(app.exec())

if __name__ == "__main__":
    	main()
