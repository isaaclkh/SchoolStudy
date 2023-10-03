package edu.handong.csee.java.exmple.collections.linkedlist;

public class ListNode {
	private String data;
	private ListNode link;
	
	public ListNode() {
		link = null;
		data = null;
	}
	
	public ListNode(String newData, ListNode linkedNode) {
		data = newData;
		link = linkedNode;
	}

	public String getData() {
		return data;
	}

	public void setData(String data) {
		this.data = data;
	}

	public ListNode getLink() {
		return link;
	}

	public void setLink(ListNode link) {
		this.link = link;
	}
	
	
}
