package edu.handong.csee.java.exmple.collections.linkedlist;

import java.util.ArrayList;

public class LinkedList<E> {
private ListNode head;
	
	public LinkedList() {
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
	
	public void addANodeToStart(E addData) {
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
	
	public boolean onList(E target) {
		return find(target) != null;
	}
	
	private ListNode find(E target) {
		boolean found = false;
		ListNode position = head;
		while((position != null) && !found) {
			E dataAtPosition = position.data;
			if(dataAtPosition.equals(target))
				found = true;
			else
				position = position.link;
		}
		return position;
	}
	
	public ArrayList<E> toArrayList() {
		ArrayList<E> list = new ArrayList<E>(length());
		ListNode position = head;
		while(position != null) {
			list.add(position.data);
			position = position.link;
		}
		return list;
	}
	
	private class ListNode{
		private E data;
		
		public E getData() {
			return data;
		}

		public ListNode getLink() {
			return link;
		}

		private ListNode link;
		
		public ListNode(E newData, ListNode linkedNode) {
			data = newData;
			link = linkedNode;
		}
	}
}