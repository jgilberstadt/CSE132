package communication;

import java.util.Scanner;

public class PCToMorseCode {
	public static void main(String[] args) {		
		// TODO:  Fix this: 
		//           a) Uncomment to create a SerialComm object
		//           b) Update the "the port" to refer to the serial port you're using
		//              (The port listed in the Arduino IDE Tools>Port menu.		
		//           c) Deal with the unresolved issue
		try {
			SerialComm port = new SerialComm("/dev/cu.usbserial-D306DZ0R");
			Scanner scan = new Scanner(System.in);
			String morse;
			
			while (true) {
				morse = scan.nextLine();
				for (int i = 0; i < morse.length(); i++) {
					port.writeByte((byte) morse.charAt(i));
				}
			}
		} catch (Exception e) {
			System.out.println(e);
		}
		// TODO: Complete section 6 of the Studio (gather sanitized user input
		//       and send it to the Arduino)
	}

}
