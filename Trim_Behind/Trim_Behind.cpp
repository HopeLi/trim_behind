// Trim_Behind.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <getopt.h>
#include <string>
#include <boost/algorithm/string.hpp>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	string delimiter = ":"; //default delimiter is ':'

	//phase command line
	static struct option long_options[] =
	{
		{"delimiter",  required_argument, 0, 's'},	//specify the symbol behind which to trim off.
		{"help",  no_argument, 0, 'h'},	//specify the symbol behind which to trim off.
		{0, 0, 0, 0}
	};
	int opt_return, option_index;
	while((opt_return=getopt_long(argc, argv, "s:h", long_options, &option_index))!=-1)
    {
        switch (opt_return)
        {
         case 's':
			 if(optarg)
			 {
				 delimiter = optarg;
			 }
             break;
         case 'h':
			 cout<<"trim_behind  input_file [output_file] [option]\n\n";
			 exit(0);
             break;
		 case '?':
			 exit(0);
			 break;
         default:
             abort ();
        }
    }

	//too many non-option arguments
	if(optind+2 <argc)
	{
		cout<<"too many non-option arguments\n";
		cout<<"use -h or --help option to see usage"<<endl;
		exit(0);
	}

	bool pure_console = false;
	if(optind==argc)
	{
		pure_console = true;
		cout<<"do not specified non-option arguments, for more help, use -h"<<endl;
	}

	//read input file
	errno_t in_file_err;
	FILE *in_file = NULL;
	if(optind!=argc)
	{
		in_file_err = _tfreopen_s(&in_file,argv[optind++],"r",stdin);
		if(in_file_err!=0)
		{
			_tfreopen_s(&in_file,"con", "r", stdin);
			cout<<"cannot open input file, and use command line as input!!"<<endl;
		}
	}
	else
	{
		cout<<"not specified in_file, get input from console!!"<<endl;
	}
	
	//reopen stdout
	errno_t out_file_err;
	FILE *out_file = NULL;
	if(optind!=argc)
	{
		out_file_err = _tfreopen_s(&out_file,argv[optind++],"w",stdout);
		if(out_file_err!=0)
		{
			_tfreopen_s(&out_file,"con", "r", stdin);
			cout<<"cannot open the file, send output to console!!"<<endl;
		}
	}
	else
	{
		cout<<"not specified out_file, output results to console!!"<<endl;
	}

	cout<<endl;
	// process input file, output it to stdout
	string line;
	while(getline(cin,line))
	{
		if(pure_console)
			cout<<"-------------------------------------------------------------------------------"
			<<endl;
		if(boost::starts_with(line,delimiter))
		{
			cout<<delimiter<<endl;
		}
		else
		{
			cout<<line<<endl;
		}

		if(pure_console)
			cout<<endl<<endl;

	}
	
	//close file
	if(in_file!=NULL)
	{
		fclose(in_file);
	}	

	if(out_file!=NULL)
	{
		fclose(out_file);
	}	

	cout<<"\n...exit program..."<<endl;
	return 0;
}

