/* PC上的客户端，负责向板子发送LED信息 */
import java.net.*;
import java.io.*;

public class PC_Client{
	static Socket server;
 
	public static void main(String[] args)throws Exception{
		server = new Socket(InetAddress.getLocalHost(), 3333);
		// 板子的IP为192.168.0.10
		// server = new Socket("192.168.0.10", 3333);
		// 测试用的本地IP
		BufferedReader in = new BufferedReader(new InputStreamReader(server.getInputStream()));
		PrintWriter out = new PrintWriter(server.getOutputStream());
		BufferedReader wt = new BufferedReader(new InputStreamReader(System.in));
  
		while(true){
			String str = wt.readLine();
			out.println(str);
			out.flush();
			if(str.equals("end")){
				break;
			}
			System.out.println(in.readLine());
		}
		server.close();
	}
}
