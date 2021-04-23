package communication;
import java.nio.charset.StandardCharsets;
import jssc.*;

public class MsgReceiver {
	
	final private SerialComm port;
	
	public MsgReceiver(String portname) throws SerialPortException {
		port = new SerialComm(portname);
		//port.setDebug(true);
	}

	public void run() {
		// State 0: Waiting for message
		// State 1: Reading key
		// State 2: Reading value of known length
		// State 3: Reading length of value of unknown length
		// State 4: Reading value of learned length
		int state = 0;
		
		// Variables to keep track of data
		String output = "";
		int numBytes = 0;
		int currentValue = 0;
		byte[] bytes = null;
		
		Double[] temperatures = new Double[8];
		int tempIndex = 0;
		double currentTemp = 0;
		double avgTemp = 0;
		boolean temperature = false;
		
		String error = "!!ERROR!!";
		
		while (true) {
			switch (state) {
				// Waiting for message
				case 0:
					if (port.available() && port.readByte() == '!') {
						currentValue = 0;
						state++;
					}
					break;
				
				// Reading key
				case 1:
					if (port.available()) {
						state++;
					
						switch (port.readByte()) {
							// String
							case 0x30:
								output = "String: ";
								numBytes = 2;
								state++;
								break;
							// Error
							case 0x31:
								output = "Error: ";
								numBytes = 2;
								state++;
								break;
							// Timestamp
							case 0x32:
								output = "Current time: ";
								numBytes = 4;
								break;
							// Potentiometer
							case 0x33:
								output = "Potentiometer reading: ";
								numBytes = 2;
								break;
							//temperature
							case 0x34:
								output = "Current temperature: ";
								numBytes = 2;
								temperature = true;
								break;
							// Abort
							default:
								System.out.println(error);
								state = 0;
								break;
						}
					}
					
					break;
				
				case 2:
				case 3:
				case 4:
					if (numBytes == 0) {
						// Done
						if (state == 2) {
							if (temperature) {
								// Rolling average
								currentTemp = (500 * (currentValue / 1023.0) - 50);
								
								// If first pass through array
								if (temperatures[tempIndex] == null) {
									avgTemp = ((((tempIndex) * avgTemp) + currentTemp) / (tempIndex + 1.0));
								} else {
									avgTemp -= temperatures[tempIndex] / 8.0;
									temperatures[tempIndex] = currentTemp;
									avgTemp += currentTemp / 8.0;
								}
								tempIndex = (tempIndex + 1) % 8;
								
								System.out.println(output + (int) currentTemp + " degrees Celcius");
								System.out.println("Rolling average temperature: " + (int) avgTemp + " degrees Celcius");
								temperature = false;
							} else {
								System.out.println(output + currentValue);
							}
							
							state = 0;
						}
						
						// Learned number of bytes
						else if (state == 3) {
							if (currentValue > 100) {
								System.out.println(error);
								state = 0;
							} else {
								numBytes = currentValue;
								bytes = new byte[numBytes];
								currentValue = 0;
								state++;
							}
						}
						
						// Done
						else if (state == 4) {
							System.out.println(output + new String(bytes, StandardCharsets.UTF_8));
							state = 0;
						}
					} else if (port.available()) {
						if (state == 4) {
							bytes[bytes.length - numBytes] = port.readByte();
						} else {
							currentValue = (currentValue << 8) | (port.readByte() & 0xff);
						}
						
						numBytes--;
					}
					
					break;
			}
		}
	}

	public static void main(String[] args) throws SerialPortException {
		MsgReceiver msgr = new MsgReceiver("/dev/cu.usbserial-D306DZ0R"); // Adjust this to be the right port for your machine
		msgr.run();
	}
}
