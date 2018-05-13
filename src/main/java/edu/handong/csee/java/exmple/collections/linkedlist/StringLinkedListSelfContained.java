package edu.handong.csee.java.exmple.collections.linkedlist;

public class StringLinkedListSelfContained {
private ListNode head;
	
	public StringLinkedListSelfContained() {
		head = null;
	}

	public void showList() {
		ListNode position = head;
		while(position != null) {
			System.out.println(position.data);
			position = position.link;
		}
	}
	
	public int length() {
		int count = 0;
		ListNode position = head;
		while(position != null) {
			count++;
			position = position.link;
		}
		return count;
	}
	
	public void addANodeToStart(String addData) {
		head = new ListNode(addData,head);
	}
	
	public void deleteHeadNode() {
		if(head != null)
			head = head.link;
		else {
			System.out.println("Deleting from an empty list.");
			System.exit(0);
		}
	}
	
	public boolean onList(String target) {
		return find(target) != null;
	}
	
	private ListNode find(String target) {
		boolean found = false;
		ListNode position = head;
		while((position != null) && !found) {
			String dataAtPosition = position.data;
			if(dataAtPosition.equals(target))
				found = true;
			else
				position = position.link;
		}
		return position;
	}
	
	public String[] toArray() {
		String[] anArray = new String[length()];
		ListNode position = head;
		int i= 0;
		while(position != null) {
			anArray[i] = position.data;
			i++;
			position = position.link;
		}
		return anArray;
	}
	
	private class ListNode{
		private String data;
		private ListNode link;
		
		public ListNode(String newData, ListNode linkedNode) {
			data = newData;
			link = linkedNode;
		}
	}
}