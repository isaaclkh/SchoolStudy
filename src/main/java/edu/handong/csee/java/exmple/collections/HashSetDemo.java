package edu.handong.csee.java.exmple.collections;

import java.util.HashSet;

public class HashSetDemo {

	public static void main(String[] args) {
		HashSetDemo demonstrator = new HashSetDemo();
		demonstrator.run();

	}

	private void run() {
		HashSet<Integer> integers = new HashSet<Integer>();
		integers.add(2);
		integers.add(7);
		integers.add(7);
		integers.add(3);
		
		printSet(integers);
		
		
	}

	private void printSet(HashSet<Integer> integers) {
		System.out.println("The set contains");
		for(Integer integer: integers) {
			System.out.println(integer);
		}
		
	}

}
