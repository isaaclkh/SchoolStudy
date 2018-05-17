package edu.handong.csee.java.exmple.collections.linkedlist;

public class LinkedListFinalDemo {

	public static void main(String[] args) {
		LinkedListFinalDemo demonstrator = new LinkedListFinalDemo();
		demonstrator.run();
	}

	private void run() {
		LinkedList<String> strList = new LinkedList<String>();
		strList.addANodeToStart("Hello");
		strList.addANodeToStart("Good-bye");
		strList.showList();
		
		
		LinkedList<Integer> numberList = new LinkedList<Integer>();
		for(int i = 0; i < 5 ; i++) {
			numberList.addANodeToStart(i);
		}
		numberList.deleteHeadNode();
		numberList.deleteTailNode();
		numberList.addANodeToTail(3);
		numberList.showList();
	}
}
