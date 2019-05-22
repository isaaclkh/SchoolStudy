package edu.handong.analysise.utils;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;

import edu.handong.analysis.datamodel.Course;
import edu.handong.analysis.datamodel.Student;

public class Utils {
	
	public static ArrayList<String> getLines(String file,boolean removeHeader)
	{
		ArrayList<String> reading = new ArrayList<String>();
		
		String line;
		boolean remove = removeHeader;
		
		try 
		{
			File fileName = new File(file);
			FileReader fileReader = new FileReader(fileName);
			BufferedReader bufReader = new BufferedReader(fileReader);
			
			while ((line=bufReader.readLine())!=null) {
				if (remove) {
					remove = false;
				}
				else {
					reading.add(line);
					
					Course information = new Course(line);
					
					String Id = information.getStudentId();
					
					Student change = new Student(Id);
					change.addCourse(information);
				}
			} //while
			
			bufReader.close();
		} catch(FileNotFoundException e){
			System.out.println("The file path does not exist. Please check your CLI argument!");
			System.exit(0);
		} catch(IOException e) {
			System.out.println(e);
			System.exit(0);
		}
		return reading;
	}
	
	public static void writeAFile(ArrayList<String> lines, String targetFileName)
	{
		BufferedWriter bufWriter = null;
		try 
		{
			bufWriter = Files.newBufferedWriter(Paths.get());
		}
	}

}
