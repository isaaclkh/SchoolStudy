package edu.handong.csee.java.examples;

import java.io.File;
import java.io.FileFilter;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.Options;

public class Runner {
	
	String path;
	boolean verbose;
	boolean help;
	boolean fullpath;

	public static void main(String[] args) {

		Runner myRunner = new Runner();
		myRunner.run(args);

	}

	private void run(String[] args) {
		Options options = createOptions();
		File f = new File(path);
		
		if(parseOptions(options, args)){
			if (help){
				printHelp(options);
				return;
			}
			
			
			// path is required (necessary) data so no need to have a branch.
			System.out.println("You provided \"" + path + "\" as the value of the option p");
			
			File[] files = f.listFiles();
			// TODO show the number of files in the path
			
			if(fullpath) {
				for(int i=0; i<files.length; i++)
					System.out.println("File name : " + files[i].getName() + " " + "Path :" + " " + files[i].getAbsolutePath());
				// TODO list all files in the path
			}
			
			else {
				for(int i=0; i<files.length; i++)
					System.out.println("File name : " + files[i].getName() + " " + "Path :" + " " + path + files[i].getName());
			}
			
			if(verbose)
				System.out.println("Your program is terminated. (This message is shown because you turned on -v option!");
		}
	}

	private boolean parseOptions(Options options, String[] args) {
		CommandLineParser parser = new DefaultParser();

		try {

			CommandLine cmd = parser.parse(options, args);

			path = cmd.getOptionValue("p");
			verbose = cmd.hasOption("v");
			help = cmd.hasOption("h");
			fullpath = cmd.hasOption("f");

		} catch (Exception e) {
			printHelp(options);
			return false;
		}

		return true;
	}

	// Definition Stage
	private Options createOptions() {
		Options options = new Options();

		// add options by using OptionBuilder
		options.addOption(Option.builder("p").longOpt("path")
				.desc("Set a path of a directory or a file to display")
				.hasArg()
				.argName("Path name to display")
				.required()
				.build());

		// add options by using OptionBuilder
		options.addOption(Option.builder("v").longOpt("verbose")
				.desc("Display detailed messages!")
				//.hasArg()     // this option is intended not to have an option value but just an option
				.argName("verbose option")
				//.required() // this is an optional option. So disabled required().
				.build());
		
		// add options by using OptionBuilder
		options.addOption(Option.builder("h").longOpt("help")
		        .desc("Help")
		        .build());
		
		// add options by using OptionBuilder
		options.addOption(Option.builder("f").longOpt("fullpath")
				.desc("Display detailed fullpath!")
				//.hasArg()
				.argName("fullpath to display")
				//.required()
				.build());
				

		return options;
	}
	
	private void printHelp(Options options) {
		// automatically generate the help statement
		HelpFormatter formatter = new HelpFormatter();
		String header = "CLI test program";
		String footer ="\nPlease report issues at https://github.com/lifove/CLIExample/issues";
		formatter.printHelp("CLIExample", header, options, footer, true);
	}

}
