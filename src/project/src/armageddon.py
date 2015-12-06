import platform
from time import sleep
import usb.core
import usb.util
import rospy

class Armageddon(object):

	#Based on https://github.com/codedance/Retaliation

	DOWN = 0x01
	UP = 0x02
	LEFT = 0x04
	RIGHT = 0x08
	FIRE = 0x10
	STOP = 0x20

	DEVICE_ORIGINAL = 'Original'
	DEVICE_THUNDER = 'Thunder'

	def working(self):
		FIRE()

	def __init__(self):
		self._get_device()
		self._detach_hid()
		self.DEVICE.set_configuration()

	def _get_device(self):
		self.DEVICE = usb.core.find(idVendor=0x2123, idProduct=0x1010)
		if self.DEVICE is None:
			self.DEVICE = usb.core.find(idVendor=0x0a81, idProduct=0x0701)
			if self.DEVICE is None:
				raise ValueError('Missile device not found')
			else:
				self.DEVICE_TYPE = self.DEVICE_ORIGINAL
		else:
			self.DEVICE_TYPE = self.DEVICE_THUNDER

	def _detach_hid(self):
		if "Linux" == platform.system():
			try:
				self.DEVICE.detach_kernel_driver(0)
			except Exception, e:
				pass

	def send_cmd(self, cmd):
		if self.DEVICE_THUNDER == self.DEVICE_TYPE:
			self.DEVICE.ctrl_transfer(0x21, 0x09, 0, 0,
									  [0x02, cmd, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00])
		elif self.DEVICE_ORIGINAL == self.DEVICE_TYPE:
			self.DEVICE.ctrl_transfer(0x21, 0x09, 0x0200, 0,
									  [cmd])

	def UP(self, duration_ms):
		self.send_cmd(0x02)
		sleep(duration_ms / 1000)
		self.send_cmd(0x20)

	def DOWN(self, duration_ms):
		self.send_cmd(0x01)
		sleep(duration_ms / 1000)
		self.send_cmd(0x20)

	def LEFT(self, duration_ms):
		self.send_cmd(0x04)
		sleep(duration_ms / 1000)
		self.send_cmd(0x20)

	def RIGHT(self, duration_ms):
		self.send_cmd(0x08)
		sleep(duration_ms / 1000)
		self.send_cmd(0x20)

	def FIRE(self):
		self.send_cmd(0x10)

	def send_move(self, cmd, duration_ms):
		self.send_cmd(cmd)
		sleep(duration_ms / 1000.0)
		self.send_cmd(self.STOP)
