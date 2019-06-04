import java.net.*;
import java.text.SimpleDateFormat;
import java.io.*;
import java.util.*;
import java.util.LinkedList;

public class ChatServer {
	
	public static void main(String[] args) {
		try{
			ServerSocket server = new ServerSocket(10001); // 서버를 생성한다 (10001번 포트로)
			System.out.println("Waiting connection..."); // Waiting connection을 print한다
			HashMap hm = new HashMap(); //hashmap 생성
			
			while(true){// while문을 실행 (true이기때문에)
				Socket sock = server.accept(); // 서버에서 클라이언트의 요청을 수락한다. (클라이언트가 서버에 접속)
				ChatThread chatthread = new ChatThread(sock, hm); // Thread를 extend 한 ChatThread 클래스를 접속한 socket과 hashmap으 ChatThread를 실행.
				chatthread.start(); // Thread를 시작.
			} // while
		}catch(Exception e){ // Exception을 다루는 부분 (try와 catch는 같이 간다. try에서 throw한 것을 catch해서 실행)
			System.out.println(e);
		}
	} // main
	
}

class ChatThread extends Thread{
	// 필드들 선언
	private Socket sock; // Socket 클래스 변수
	private String id; // String 변수
	private BufferedReader br; // BufferedReader 클래스 변수
	private HashMap hm; // HashMap 클래스 변수
	private boolean initFlag = false; // boolean 변수 (초기값으로 false)
	LinkedList<String> spam = new LinkedList<String>(); // 금지어들 저장
	
	// Constructor (socket값과 hashmap 값을 가지고 와서 초기화)
	public ChatThread(Socket sock, HashMap hm){
		ChatServer server = new ChatServer();
		
		this.sock = sock; // 받아온 socket값을 socket값에 넣어줌
		this.hm = hm; // 받아온 hashmap값을 hm 값에 넣어줌
		try{
			// socket의 OutPutStream을 OuputStream에 써서 PrintWriter 클래스 변수 pw에 넣어준다 (client에 데이터를 전송)
			PrintWriter pw = new PrintWriter(new OutputStreamWriter(sock.getOutputStream())); 
			// socket의 inPutStream을 읽어와서 BufferedReader 값에 넣어줌
			br = new BufferedReader(new InputStreamReader(sock.getInputStream()));
			
			id = br.readLine(); // String 변수인 id에 버퍼에 입력된 한줄을 읽어옴.
			
			broadcast(id + " entered."); // broadcast 메소드에 "입력받은id entered"를 전달해주며 실행한다.
			System.out.println("[Server] User (" + id + ") entered."); // print
			
			synchronized(hm){ // hm에 대해 동기화 실행 (받아온 hashmap과 동일한 Thread 동기화(실행))
				hm.put(this.id, pw); // hashmap에 id를 key로 pw를 value로 선언해 그 값을 저장한다.
			} // synchronized
			
			initFlag = true; // initFlag를 true로 바꾼다.
		}catch(Exception ex){ // try & catch
			System.out.println(ex);
		}
		
	} // construcor
	
	public void run(){ // run 메소드
		try{
			String line = null; // String 변수 line
			int result;
			int add;
			
			//금지어들
			spam.add("hate");
			spam.add("never");
			spam.add("no!");
			spam.add("disgusting");
			spam.add("dead");
			
			while((line = br.readLine()) != null){ // line에 값이 있을 때(버퍼드에 입력받은 한줄을 line에 저장함) 
				result = 0;
				add=0;
				
				if(line.equals("/quit")) // 만약에 line 즉 버퍼에 입력받은 String이 '/quit' 와 같다면 
					break; // while문을 빠져나옴(즉 종료)
				
				if(line.equals("/userlist")) {
					send_userlist();
				}
				if(line.indexOf("/to ") == 0){ // 만약에 line 즉 버퍼에 입력받은 String이 '/to'이 처음에 있으면
					sendmsg(line); // 그 line을 sendmsg 메소드에 전달하며 실행.
				}
				if(line.equals("/spamlist")){
					for(int i=0; i<spam.size(); i++) {
						broadcast2(String.valueOf(i+1) + ". " + spam.get(i));
					}
				}
				if(line.indexOf("/addspam") == 0){
					String[] cut = line.split(" ");
					String spammsg = cut[1];
					spam.add(spammsg);
					broadcast2("금지어가 저장되었습니다");
					add++;
				}
				
				if(add==0) {
					for(int i=0; i<spam.size(); i++) {
						if(line.contains(spam.get(i))) result++;
					}
				}
				
				if(result>0) {
					broadcast2("금지어 입니다.");
				}
				
				else // '/quit'나 '/to'나 금지어가 아닌 String이라면
					broadcast(id + " : " + line); // broadcast 메소드에 "(입력받은 id) : (입력한 String)"을 전달하며 실행
				
			}
		}catch(Exception ex){ //try & catch (예외사항 처리)
			System.out.println(ex); // 에러 출력
		}finally{ // finally 블록이 사용되면 finally 블록의 내용은 예외 발생 유무나 예외 catch 유무와 상관 없이 무조건 수행된다. 
				  // 따라서, 데이터베이스나 파일을 사용한 후 닫는 기능과 같이 항상 수행해야 할 필요가 있는 경우에 사용한다.
			synchronized(hm){ // hashmap 동기화 (hashmap과 동일한 thread를 동기화(실행) )
				hm.remove(id); // hashmap에 있는 id를 지움
			}
			broadcast(id + " exited."); // broadcast 메소드에 "(입력받은 id) exited" String 값을 전달하며 실행
			try{
				if(sock != null) // 만약에 socket값이 아직도 남아있다면
					sock.close(); // socket을 닫는다.
			}catch(Exception ex){} // try & catch
		}
	} // run
	public void sendmsg(String msg){ // sendmsg 메소드
		int start = msg.indexOf(" ") +1; // int형 변수 start 값에 받아온 String 값 msg에서 공백 다음부터의 값의 자리를 저장 (보낼 id)
		int end = msg.indexOf(" ", start); // int형 변수 end 값에 받아온 String 값 msg에서 start 다음에 오는 공백부터의 자리 값을 저장 (메세지)
		if(end != -1){ // 만약에 end가 있다면
			String to = msg.substring(start, end); // start부터 end사이의 String 값을 String 변수 to에다 저장 (보낼 id)
			String msg2 = msg.substring(end+1); // end 이후부터의 String 값은 String 변수 msg2에다 저장 (message)
			Object obj = hm.get(to); // Object 클래스 변수인 obj에 입력받은 id의 key에 대한 메세지(value)로 저장한다.
			
			SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss"); //SimpleDateFormat를 사용해서 시간 불러오기 (시:분:초)
			String format_time = format.format(System.currentTimeMillis()); //format으로 만든 SimpleDateFormat을 string 값으로 할당
			String timeFinal = makingTime(format_time); // makingTime 메소드로 string 보냄
			
			if(obj != null){ // 만약에 obj가 null이 아니면 (즉 메시지가 있으면)
				PrintWriter pw = (PrintWriter)obj; // obj를 PrintWriter 변수 pw에 저장
				pw.println(timeFinal + id + " whispered. : " + msg2); // "(입력id) whisphered : (message)" 형태로 출력
				pw.flush(); // flush (stream 비우기)
			} // if
		}
	} // sendmsg
	public void broadcast(String msg){// broadcast 메소드 선언
		synchronized(hm){// 해당 hashmap에 대해서 동기화(실행)
			
			
			Collection collection = hm.values(); // Collection 클래수 변수 collection 선언. collection 안에 hashmap hm의 value를 저장.
			// Iterator는 모든 Collection 클래스에 데이터를 읽어오는데 사용된다.
			Iterator iter = collection.iterator(); // Collection 클래스 변수 collection의 데이터를 iter에다 저장.
			
			SimpleDateFormat format = new SimpleDateFormat("HH:mm:ss");
			String format_time = format.format(System.currentTimeMillis());
			String timeFinal = makingTime(format_time);
			
			while(iter.hasNext()){ // iter이 아직 남아 있다면
				PrintWriter pw = (PrintWriter)iter.next();//pw에 값을 넣어줌 
				String key=(String)getKey(hm,pw);//value에 대한 key값 찾는 함수에 넣기
				
				if(key.equals(id)) {//만약에 id가 같다면
					continue;//그냥 continue
				}
				else { //id가 다르다면
					pw.println(timeFinal+msg); // 메세지를 출력
					pw.flush(); // flush (stream 비우기)
				}
			}
		}
	} // broadcast
	
	public void broadcast2(String msg){// broadcast 메소드 선언
		synchronized(hm){// 해당 hashmap에 대해서 동기화(실행)
			
			
			Collection collection = hm.values(); // Collection 클래수 변수 collection 선언. collection 안에 hashmap hm의 value를 저장.
			// Iterator는 모든 Collection 클래스에 데이터를 읽어오는데 사용된다.
			Iterator iter = collection.iterator(); // Collection 클래스 변수 collection의 데이터를 iter에다 저장.
			
			while(iter.hasNext()){ // iter이 아직 남아 있다면
				PrintWriter pw = (PrintWriter)iter.next();//pw에 값을 넣어줌 
				String key=(String)getKey(hm,pw);//value에 대한 key값 찾는 함수에 넣기
				
				if(key.equals(id)) {//만약에 id가 같다면
					pw.println(msg); // 메세지를 출력
					pw.flush(); // flush (stream 비우기)
				}
				else { //id가 다르다면
					continue;//그냥 continue
				}
			}
		}
	} // broadcast
	
	public String makingTime(String format_time) { // "[오후] 11:30" 이렇게 시간 표시 해주는 method
	
		String[] spliting = format_time.split(":"); //':'에 대해서 split
		String hour = spliting[0]; // spliting 한 값에서 첫번째 즉 시간을 가져옴
		String min = spliting[1]; // spliting 한 값에서 두번째 즉 분을 가져옴
		String finalTime; // finalTime으로 지정된 format으로 만듬
		
		if(Integer.parseInt(hour)>12) hour = "오후 " + String.valueOf(Integer.parseInt(hour)-12); // 만약에 12시간이 넘으면 오후를 표시해주고
		else hour += "오전 "; // 아니면 오전으로 표시
		
		finalTime = "[" + hour + ":" + min + "]"; // "[" 과 "]" 를 포함한 string으로 finalTime으로 사용
		
		return finalTime; // return
	}
	
	public void send_userlist() { // hashmap의 key들을 불러옴 (즉 id들)
		Set key = hm.keySet(); // key에다 key를 넣음
		int count=0;
		for(Iterator iterator = key.iterator(); iterator.hasNext();) { //key 아직 key값이 남아 있다면 계속 실행하면서 iterator에다 넣어줌
			String keyName = (String) iterator.next(); // String 값으로 변환해서 keyName에 넣어줌
			broadcast2(keyName); // 출력
			count++;
		}
		broadcast2("총 " + String.valueOf(count) + "명의 user 있습니다.");
	}
	
	public Object getKey(HashMap m, Object value) { 
		for(Object o: m.keySet()) { 
			if(m.get(o).equals(value)) { 
				return o; 
			} 
		} 
		return null; 
	}

	
}

/*BufferedReader / BufferedWriter는 문자 입력 스트림으로부터 문자를 읽어 들이거나 문자 출력 스트림으로 문자를 내보낼 때 버퍼링을 함으로써 문자, 문자 배열, 문자열 라인 등을 보다 효율적으로 처리할 수 있도록 해준다.
InputStreamReader / OutputStreamWriter를 사용하는 경우는 한 문자씩 읽지만 버퍼링을 하게 되면 입출력 스트림으로부터 미리 버퍼에 데이터를 갖다 놓기 때문에 보다 효율적으로 입출력할 수 있다.
*/

/** Synchronized
 * synchronized(동기화)란 여러개의 Thread가 한개의 자원을 사용하고자 할 때
 * 해당 Thread만 제외하고 나머지는 접근을 못하도록 막는 것이다.
 * 자바 동기화는 synchronized 식별자로 구현하게 된다. (변수와 함수에 사용해서 동기화 할 수 있다.)
 */

/** Collection
 * Collection 인터페이스는 java.util 패키지에 선언되어 있으며, 
 * 여러 개의 객체를 하나의 객체에 담아 처리할 때 공통적으로 사용되는 여러 메소드들을 선언해 놓았다.
 */