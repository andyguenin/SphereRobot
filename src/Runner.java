import Network.NetworkListener;
import Network.ReporterI;


public class Runner {

	public static void main(String[] args)
	{
		NetworkListener nl = new NetworkListener(1235);
		nl.addReporter(new ReporterI() { public void report(String message) {System.out.println(message);}});
		nl.start();
		
	}
}
