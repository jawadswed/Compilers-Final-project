/*PART III*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//Part 3
	//Beginning Part 3 get original p2 file and make new p3 cpp file.
  ifstream infile("finalp2.txt");
  ofstream offile("finalp3.cpp");
  string line = "";//matching temporary line
  while (infile >> line)//goes through entire txt file until done.
  {
	  if (line == "program")//beginning line
	  {
		  line = "#include <iostream>";//required to run
		  cout << "Replacing program with #include <iostream>...\n";
		  offile << line;//to put in the new cpp file.
		  
		  while (line != ";")//check to end at the semicolon originally in the file.
			  {
				  infile >> line;
				  if (line == ";") //skips it and hits the next line of code.
				  {
					  cout << "Removing ; for program...\n";
					  offile << endl;
					  break;
				  }
			  }
	  }
	  
    else if (line == "var")//var can become using namespace std.
	  {
		  line = "using namespace std;";
	   	  cout << "Replacing var with using namespace std;..\n";
		  offile << line << endl;
	  }
	  
	else if (line == "integer" || line == ":integer" )//integer can become int. Alaso accounts for chance text is attached.
	  {
		  line = "int";
		cout << "Replacing integer with int...\n";
		  offile << line;
	  }
    
  	else if (line == "begin")//begin can be int main() {
	  {
		  line = "int main()";
		cout << "Replacing begin with int main() {...\n";
		  offile << line << endl << "{" << endl;
	  }
  	
	else if (line == "show")//show works like cout.
	{
		line = "cout";
		cout << "Replacing show and reformatting its content with cout... \n";
		offile << line;
		infile >> line;

		if (line == "(") //syntax changes to preserve it.
		{
			line = "<<"; // carrots to lead into it.
			offile << line;
			while (line != ")" || line == ");")//preserve everything originally in the parenthesis.
			{
				infile >> line;
				if (line == ")" || line == ");") //there is left parenthesis, so this can go.
				{
					line == " ";
					break;
				}
				offile << line;
			}
		}
	}
      
	  else if (line == "end")//end can become the right brace.
	  {
		  line = "}";
		  cout << "Replacing end with a }...\n";
		  offile << line << endl;
	  }

	  else if (line == ";")//tricky but every semicolon ends with a new line of code; easier readability.
	  {
		  cout << "shifting to the next line because of ;...\n";
		  offile << line << endl;
	  }

	  else //other that continues on regardless.
	  {
		  cout << "Reading in " << line << "...\n";
		  offile << line;
	  }
   }
}
