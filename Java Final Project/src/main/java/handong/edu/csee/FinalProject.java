package handong.edu.csee;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.Options;

/**This is Final Project.
 * This class mixes files together.
 */
public class FinalProject {
	public String path;
	public String result;
	public boolean help;
	
	public void run(String[] command) {
		Options options = createOptions();

		if(parseOptions(options, command)) {
			if (help){
				printHelp(options);
				return;
			}
			
			gettingFile(1); //첫번째
			gettingFile(2); //두번째
		}
		
		
	}
	
	/**This is createOptions.
	 * I made two options.
	 * One is "i" option, the other is "o".
	 * "i" is to get the input file's path,
	 * and "o" for getting the output file's path.
	 */
	private Options createOptions() {
		Options options = new Options();
		
		options.addOption(Option.builder("i").longOpt("in")
			.desc("Input File")
			.hasArg()
			.argName("Input path")
			.required()
			.build()); //i option
		
		options.addOption(Option.builder("o").longOpt("out")
				.desc("Output File")
				.hasArg()
				.argName("output path")
				.required()
				.build());
		
		return options;
	}
	
	/**This is for getting the path of the input file and output file. */
	private boolean parseOptions(Options options, String[] args) {
		CommandLineParser parser = new DefaultParser();

		try {

			CommandLine cmd = parser.parse(options, args);

			path = cmd.getOptionValue("i");
			result = cmd.getOptionValue("o");

		} catch (Exception e) {
			//printHelp(options);
			return false;
		}

		return true;
	}
	
	/**This is printing the help option.*/
	private void printHelp(Options options) {
		// automatically generate the help statement
		HelpFormatter formatter = new HelpFormatter();
		String header = "Java Final Projects";
		String footer ="\nPlease report issues at https://github.com/isaaclkh/JavaFinalProject";
		formatter.printHelp("CLIExample", header, options, footer, true);
	}
	
	/**This method is to get the file.
	 * We have two kinds of files so to distinguish, it is needed to put the integer.
	 * And then sort by the id.
	 * Finally write the excel file.
	 * Use join to separate.
	 */
	public void gettingFile(int num) {
		String path = this.path;
		File file = new File(path);
		File[] Files = file.listFiles();
		
		HashMap<String, HashMap<String, ArrayList<String>>> hm = new HashMap<String,HashMap<String, ArrayList<String>>>();
		
		for(File f : Files) {
			if(f.isFile()) {
				String fileN = file.getName();
				
				System.out.println(fileN);
				
				for(int i=1; i<3; i++) {
					Threading threaded = new Threading(fileN,i);
					threaded.start();
					
					try {
						threaded.join();
						hm.put(threaded.getFileName(), threaded.getForWriting());
					}catch(InterruptedException e){
						e.printStackTrace();
					}
				}
			}
		}
		
		Map<String, HashMap<String, ArrayList<String>>> sorting = new TreeMap<String, HashMap<String, ArrayList<String>>>();
		ExcelWriter ew = new ExcelWriter(num, sorting, result);
	}
	
	/**Thread for this project.
	 *First set the file name and the distinguished number.
	 *Unzip by the full path of the input file, output's path, and the file name.
	 *And then put in to the hashmap.
	 *Other methods are getters and setters(adding to the array list).
	 */
	class Threading extends Thread{
		private String filen;
		private int num;
		private ArrayList<String> writing;
		
		HashMap<String, ArrayList<String>> forWriting = new HashMap<String, ArrayList<String>>();
		
		public Threading(String filen, int num) {
			this.filen = filen;
			this.num = num;
		}
		
		public void run() {
			ZipReader zip = new ZipReader();
			
			writing = zip.run(num, path + "/" + filen, result, filen);
			ArrayList<String> list = new ArrayList<String>();
			
			list = writing;
			forWriting.put(filen, list);
			
		}
		
		public HashMap<String, ArrayList<String>> getForWriting(){
			return forWriting;
		}
		
		public String getFileName() {
			return filen;
		}
		
		public ArrayList<String> getWriting(){
			return writing;
		}
		
		public void addWriting(String str) {
			writing.add(str);
		}
		
	}
	
	
}
