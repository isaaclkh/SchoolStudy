import java.util.LinkedList;

public class ChatClient {

	public static void main(String[] args) {
		
			ChatClient_new chatClient = new ChatClient_new(); // ChatClient_new에 입력받은 두개의 값을 전달
			
			if(chatClient.getUsername()==null||chatClient.getServerip()==null) {
				System.out.println("Usage : java ChatClient <username> <server-ip>"); // 출력
			}
			
			else {
				chatClient.start(); // chatClient 실행
			}
	}
}
