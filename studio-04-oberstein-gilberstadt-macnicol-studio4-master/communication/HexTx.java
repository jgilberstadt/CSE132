package communication;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import jssc.SerialPortException;

public class HexTx {
	public static void main(String[] args) {		
		SerialComm port = null;
		try {
			port = new SerialComm("/dev/cu.usbserial-D306DZOR");
		} catch (SerialPortException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		try {
			System.out.print(in.readLine());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

}
