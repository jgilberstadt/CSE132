public class Heartbeat {
	
	public static void main(String[] args) {
		int sec = 0;
		while (true) {
			try {
				System.out.println(sec + " seconds have elapsed :)");
				Thread.sleep(1000);
				sec++;
			} catch (Exception e) {
				System.out.println(e);
			}
		}
	}
}
