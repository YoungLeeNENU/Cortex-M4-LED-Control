/**
 * PC上的java程序客户端，负责向板子发送LED信息
*/
import java.net.*;
import java.io.*;

public class Client{
	static Socket server;

	public static void main(String[] args)throws Exception{
		server = new Socket(InetAddress.getLocalHost(), 2012);
            // 板子的IP地址
            // server = new Socket("192.168.0.10", 2012);
		BufferedReader in = new BufferedReader(new InputStreamReader(server.getInputStream()));
		PrintWriter out = new PrintWriter(server.getOutputStream());
		BufferedReader wt = new BufferedReader(new InputStreamReader(System.in));

		while(true){
			String str = wt.readLine();
			out.println(str);
			out.flush();
			if(str.equals("q")){
				break;
			}
                // System.out.println(in.readLine());
		}
		server.close();
	}
}
