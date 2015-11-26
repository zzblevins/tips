/*

	tips.c

	Find topics within a formatted info file

	Syntax:
	% $command [-v] [-f infofile] keyword

	Info file format:
	-[ keyword1 keyword2 ...
	Content related to keywords
	-]

	Dean Blevins
	November 2014
	Updated: Sat Nov 22 13:36:15 CST 2014

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>

#define TRUE		1
#define FALSE		(!TRUE)
#define MAXFILENAME	20
#define MAXKEYLENGTH	20
#define MAXLINELENGTH	1024
#define DEFAULTDATAFILE	"/home/dean/info.txt"
#define TOPICSTARTSIG "-["
#define TOPICENDSIG "]-"

main(int argc, char *argv[])
{

	FILE *fp;

	char filename[MAXFILENAME];
	char keyword[MAXKEYLENGTH];
	char tok[MAXKEYLENGTH] = "";
	char textline[MAXLINELENGTH];

	int o;
	int fflag =		0;
	int vflag =		0;
	int dumpfile =		FALSE;

	int maxline =		MAXLINELENGTH; 

	int opt;
	int option_index =	0;

	static const char *opt_string = "vhf:";

	static struct option long_options[] =
	{
		/* These options set a flag */
		{"help", 	no_argument,		NULL,	'h'},
		{"file", 	required_argument,	NULL,	'f'},
		{"verbose",	no_argument,		NULL,	'v'},
		{0, 0, 0, 0}
	};

	opt = getopt_long(argc, argv, opt_string, long_options, &option_index);

	while (opt != -1 ) {

		switch (opt) {
			case 'v':
				vflag = 1;
				break;
			case 'f':
				fflag = 1;
				strcpy(filename, optarg);
				break;
			case 'h':printf("Syntax: %s [-v] [-f datafile] keyword\n", argv[0]);
				printf(" -h, --help : syntax\n");
				printf(" -v, --verbose : verbose output for debug\n");
				printf(" -f, --file datafile : alternative datfile (default=%s)\n", DEFAULTDATAFILE);
				exit(0);
				break;
			default:
				break;
		}

		opt = getopt_long (argc, argv, opt_string, long_options, &option_index);
	}


	// Reasonable command line options?
	// -v must have a keyword

	if (vflag) {
		if (argc < 3) {
			fprintf(stderr, "Error: No topics to find...\n");
			return (-1);
		}
	}

	// Dump the whole file if no keyword given
	
	if (argc == optind) {
		dumpfile = TRUE;
	}

	// Use the default info file if none provided

	if (fflag == FALSE) {
		strcpy(filename, DEFAULTDATAFILE);
	}

	// Capture the keyword we're looking for in the info file
	
	if (dumpfile == FALSE) {
		strcpy(keyword, argv[optind]);
		if (vflag)
			 printf("@keyword = %s\n", keyword);
	}

	if (vflag) {
		printf("@filename = %s\n", filename);
	}

	// Open and work on the source file

	if ( ( fp = fopen(filename, "r") ) == NULL) {
			printf("Error: Can't read %s\n", filename);
			return (-1);
	}

	// Find the start definition
	
	while ( ( fgets(textline, maxline, fp) ) != NULL) {
		if (dumpfile) {
			printf("%s", textline);
		}

		if ( strstr(textline, TOPICSTARTSIG )) {

			// Found first marker, now find keyword match
			strcpy(tok, keyword);	// Refresh the keyword
	
			if ( (strstr(textline, tok) ) != NULL) {

				// Found keyword/tok match, dump lines until end marker

				if (vflag) {
					printf("@KeyWord found in  %s\n", textline);
				}

				while ( ( fgets(textline, maxline, fp) ) != NULL) {
					if ( strstr(textline, TOPICENDSIG ) ) {
						if (vflag) {
							printf("@TopicEND = %s\n", textline);
						}
						return (0);
					} 

					printf("%s", textline);
				}
			}
		}
	}	

	fclose(fp);


	return (0);
}

