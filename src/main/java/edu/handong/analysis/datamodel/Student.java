package edu.handong.analysis.datamodel;

import java.util.ArrayList;
import java.util.HashMap;

public class Student {
	private String studentId;
	ArrayList<Course> coursesTaken;
	HashMap<String,Integer> semestersByYearAndSemester;
	
	public Student(String studentId){
		this.studentId = studentId;
	}
	
	public void addCourse(Course newRecord) {
		/*semestersByYearAndSemester = new HashMap<String,Integer>();
		int yearTaken = newRecord.getYearTaken();
		int semester = newRecord.getSemesterCourseTaken();
		
		String yearTakenPlusSemesterTaken = yearTaken + "-" + semester;*/
		
		coursesTaken.add(newRecord);
	}
	
	public HashMap<String,Integer> getSemestersByYearAndSemester(){
		semestersByYearAndSemester = new HashMap<String, Integer>();
		int count=0;
		
		for(; count<coursesTaken.size(); count++) {
			String year = String.valueOf(coursesTaken.get(count).getYearTaken());
			String semester = String.valueOf(coursesTaken.get(count).getSemesterCourseTaken());
			String yearTakenPlusSemesterTaken = year + "-" + semester;
			semestersByYearAndSemester.put(yearTakenPlusSemesterTaken, count+1);
		}
		
		getNumCourseInNthSemester(count);
		
		return semestersByYearAndSemester;
	}
	
	public int getNumCourseInNthSemester(int semester) {
		
		return semester;
	}
	
	//getter & setter
	public String getStudentId() {
		return studentId;
	}

	public void setStudentId(String studentId) {
		this.studentId = studentId;
	}

	
}
