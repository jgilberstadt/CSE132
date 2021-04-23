package communication;

import jssc.*;

public class SerialComm {

	SerialPort port;

	private boolean debug;  // Indicator of "debugging mode"
	
	// This function can be called to enable or disable "debugging mode"
	void setDebug(boolean mode) {
		debug = mode;
	}	
	
	// Constructor for the SerialComm class
	public SerialComm(String name) throws SerialPortException {
		port = new SerialPort(name);		
		port.openPort();
		port.setParams(SerialPort.BAUDRATE_9600,
			SerialPort.DATABITS_8,
			SerialPort.STOPBITS_1,
			SerialPort.PARITY_NONE);
		
		debug = false; // Default is to NOT be in debug mode
	}
		
	public boolean writeByte(byte b) {
		if (debug) {
			System.out.println("<0x" + b + ">");
			try {
				return port.writeByte(b);
			} catch (Exception e) {
				System.out.println(e);
				return false;
			}
		}
		return false;
	}
	
	public boolean available() {
		try {
			return port.getInputBufferBytesCount() > 0;
		} catch (Exception e) {
			System.out.println(e);
			return false;
		}
	}
	
	public byte readByte() {
		byte b;
		
		try {
			b = port.readBytes(1)[0];
		} catch (Exception e) {
			System.out.println(e);
			return 0x0;
		}
		
		if (debug) {
			System.out.println("[0x" + String.format("%02x", b) + "]");
		}
		return b;
	}
	
	public static void main(String[] args) {
		try {
			SerialComm cereal = new SerialComm("/dev/cu.usbserial-D306DZ0R");
			cereal.setDebug(true);
			
			while (true) {
				if (cereal.available()) {
					System.out.print((char) cereal.readByte());
				}
			}
		} catch (Exception e) {
			System.out.println(e);
		}
	}
}
