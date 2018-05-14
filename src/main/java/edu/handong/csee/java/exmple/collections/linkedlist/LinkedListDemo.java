package edu.handong.csee.java.exmple.collections.linkedlist;

public class LinkedListDemo {

	public static void main(String[] args) {
		LinkedListDemo demonstrator = new LinkedListDemo();
		demonstrator.run();
	}

	private void run() {
		StringLinkedList list = new StringLinkedList();
		list.addANodeToStart("One");
		list.addANodeToStart("Two");
		list.addANodeToStart("Three");
		System.out.println("List has " + list.length() + " entries.");
		
		list.showList();
		
		if(list.onList("Three"))
			System.out.println("Three is on list");
		else
			System.out.println("Three is NOT on list");
		
		list.deleteHeadNode();
		list.deleteHeadNode();
		System.out.println("Start of list: ");
		list.showList();
		System.out.println("End of list: ");
	}
}
