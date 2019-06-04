import java.net.*;
import java.util.LinkedList;
import java.util.Scanner;
import java.io.*;

public class ChatClient_new {
	
	private String username=null;
	private String serverip=null;
	
	ChatClient_new(){ // user id와 server ip를 각각 따로 받아 클래스 초기화(constructor)
		Scanner scan = new Scanner(System.in); // Scanner : 키보드로 입력받는 값을 가져오기 위해서
		String username; // username
		String serverip; // 서버 ip
		
		System.out.printf("Your name >>");
		username = scan.next();
		
		System.out.printf("Server ip >>");
		serverip = scan.next();
		
		setUsername(username); // setter를 통해서 username 할당
		setServerip(serverip); // setter를 통해서 serverip 할당
	}
	
	public void start() {
		
		Socket sock = null;	//Socket의 클래스 변수를 선언
		BufferedReader br = null; //BufferedReader 클래스 변수 선언 (문자 입력 스트림으로부터 문자를 읽어 들일때 사용하기 위한 클래스)
		PrintWriter pw = null; //PrintWriter 클래스 변수 선언 (PrintWriter 클래스는 기본 데이터형이나 객체를 쓰기 위한 클래스)
		boolean endflag = false; //boolean 변수 선언
		
		if(username != null && serverip != null){	// username이랑 serverip에 값이 들어가있으면 실행한다.
			try{
				sock = new Socket(serverip, 10001);//입력한 서버의 1001번 서버에 접속한다.
				pw = new PrintWriter(new OutputStreamWriter(sock.getOutputStream())); //소켓에서 데이터를 쓸 때 
				br = new BufferedReader(new InputStreamReader(sock.getInputStream())); //소켓에서 데이터를 읽을 때
				BufferedReader keyboard = new BufferedReader(new InputStreamReader(System.in)); // 입력한 값을 keyboad에 저장 (메세지)
				// send username.
				pw.println(username); //client에 입력한 user의 이름을 전송한다. (버퍼에 남음)
				pw.flush(); // flush (stream 비우기)
				
				InputThread it = new InputThread(sock, br); //IputThread 클래스에 sock과 br 값을 보내며 InputThread의 인스턴스를 생성한다.
				// (sock는 Socket 클래스 변수로써 입력받은 서버의 1001번 포트로 접속한 것이고, br는 username를 말한다)
				it.start(); //sock와 br값을 받아온 Thread의 실행을 시작한다.
				String line = null; // String 클래스 변수
				while((line = keyboard.readLine()) != null){ //line에다가 키보드로부터 받아온 값을 저장하는데 그 값이 없어질 때까지 즉 키보드로부터 모든 값을 받아올 때까지를 말한다.
					pw.println(line);//client에 입력한 String을 전송한다.
					pw.flush();// flush (stream 비우기)
					if(line.equals("/quit")){ //만약에 그 입력한 값이 '/quit'와 같다면 endflag를 true로 만들어주고 break를 한다. 
						endflag = true;
						break;
					}
				}
				System.out.println("Connection closed."); //break를 통해 나오면 이렇게 Connection closed를 출력한다.
			}catch(Exception ex){ //예외처리
				if(!endflag) //endflag가 false이면 실행이 된다.
					System.out.println(ex);
			}finally{
				try{
					if(pw != null) //만약에 pw가 null이 아니면 pw를 close한다. (입력하고 닫기)
						pw.close();
				}catch(Exception ex){}
				try{ //만약에 br이 null이 아니면 br를 close한다. (입력하고 닫기)
					if(br != null)
						br.close();
				}catch(Exception ex){}
				try{ //만약에 sock이 null이 아니면 sock를 close한다. (socket를 받고 종료한다.)
					if(sock != null)
						sock.close();
				}catch(Exception ex){}
			}//finally
		}//if
	}//start

class InputThread extends Thread{ //Thread를 extend한 InputThread 클래스를 만든다. 
	private Socket sock = null; //Socket 선언
	private BufferedReader br = null; //BufferedReader 선언
	
	public InputThread(Socket sock, BufferedReader br){ //constructor
		this.sock = sock; // 받아온 sock를 (ip) 이 클래스의 sock으로 선언
		this.br = br; // 받아온 br를 
	}//InputThread
	
	public void run(){
		try{
			String line = null; //String 선언
			while((line = br.readLine()) != null){ //line에 입력값을 받아오데 null이 될 때까지 받아온다.
				System.out.println(line); //받아온 line을 출력한다.
			}//while
		}catch(Exception ex){
		}finally{
			try{ //만약에 입력받아온 값을 받아왔다면 close를 해준다.
				if(br != null) 
					br.close();
			}catch(Exception ex){}
			try{ //만약에 socket을 불러왔다면 close를 해준다.
				if(sock != null)
					sock.close();
			}catch(Exception ex){}
		} //finally
	} //run
} //Thread


//getter & setter
public void setUsername(String username) {
	this.username = username;
}

public void setServerip(String serverip) {
	this.serverip = serverip;
}

public String getUsername() {
	return this.username;
}

public String getServerip() {
	return this.serverip;
}



/**ServerSocket과 Socket 클래스가 있다. 
 * ServerSocket은 자바에서서버 프로그램을 개발할 때 쓰이는 클래스 이다.
 * Socket 클래스는 client에서 서버로 접속하거나 Server에서 accept 하는데 필요한 클래스이다.
 * 서버						                        방향          클라이언트
 * 클라이언트의 요청을 받기 위한 준비를 한다(ServerSocket)     
 * 클라이언트의 요청을 받아 들인다. (accept)                <-          서버에 접속 요청을 한다.(Socket)
 * 클라이언트가 보낸 데이터를 출력한다.(BufferedReader)      <-          서버에 메시지를 보낸다.(BufferedWriter)
 * 클라이언트에 메시지를 보낸다.(BufferedWriter)            ->         서버가 보낸 메시지를 출력한다.(BufferedReader)
 * 종료한다.(socket.close())                                      종료한다.(socket.close())
 */

/**Thread이란
 * 보통 우리가 만드는 프로그래밍 언어Java, C/C++ 등로 소스를 짜서 만든 것을 "프로그램"이라고 합니다.
 * 그리고 이 프로그램을 "실행" 시켜서 동작하게 만들면 이것을 "프로세스"라고 합니다.
 * 이 프로세스는 보통 하나의 루틴프로그램 처리 경로을 가지고 있습니다.
 * 이 루틴은 직렬적입니다. 즉 어떠한 일을 수행하는 것에 있어 프로그래머가 원하는 순서대로 일을 처리합니다.
 * 그러나 생각해보면 굳이 앞뒤 순서가 필요 없는 일들이 있을 때 분리해서 동시에 처리하고 싶은 생각이 들 때가 있습니다.
 * 이 때 자바에서 사용할 수 있는 것이 쓰레드Thread입니다.
 */

}
