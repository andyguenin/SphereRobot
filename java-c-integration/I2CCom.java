import java.util.*;
public class I2CCom
{

	native void sendCommand(char command, char amount);
	native int getResponse(char command);
	static {
		System.load("/usr/lib/revo/libi2ccom.so");
	}

	public I2CCom()
	{
	
	}

	public static void main(String[] args)
	{
		I2CCom com = new I2CCom();
		for(int i =0; i < args.length; i++)
		{
			int a = Integer.parseInt(args[i]);
			System.out.println(com.getResponse(((char)a)));
		}
	}
}
