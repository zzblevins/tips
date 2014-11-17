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
	Updated: Mon Oct 13 21:00:29 CDT 2014

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#define TRUE		1
#define FALSE		(!TRUE)
#define MAXFILENAME	20
#define MAXKEYLENGTH	20
#define MAXLINELENGTH	1024
#define DEFAULTDATAFILE	"./info.test"
// #define DEFAULTDATAFILE	"~/info.txt"
#define TOPICSTARTSIG "-["
#define TOPICENDSIG "]-"

main(int argc, char *argv[])
{

	FILE *fp;

	char filename[MAXFILENAME];
	char *il; 
	char *tok;
	char *tl;
	char keyword[MAXKEYLENGTH];
	char textline[MAXKEYLENGTH];
	char tokenline[MAXKEYLENGTH];

	int o;
	int fflag =		0;
	int vflag =		0;
	int dumpfile =		FALSE;

	int maxline =		MAXLINELENGTH; 

	while ((o = getopt(argc, argv, "vxf:h")) != -1) {
		switch (o) {
			case 'v':
				vflag = 1;
				break;
			case 'f':
				fflag = 1;
				strcpy(filename, optarg);
				break;
			case 'h':
				printf("Syntax: %s [-v] [-x] [-f datafile] keyword\n", argv[0]);
				printf(" -h : syntax\n");
				printf(" -v : verbose output for debug\n");
				printf(" -f datafile : alternative datfile (default=%s)\n", DEFAULTDATAFILE );
				exit(0);
				break;
			case '?':
				if (isprint(optopt))
					fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				break;
			default:
				break;
		}
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

	if (argc == 1) 
		dumpfile = TRUE;

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

	// Open  and work on the source file

	if ( ( fp = fopen(filename, "r") ) == NULL) {
			printf("Error: Can't read %s\n", filename);
			return (-1);
	}

	// Find the start definition
	
	while ( ( fgets(tokenline, maxline, fp) ) != NULL) {
		if (dumpfile) {
			printf("%s", tokenline);
		}

		if ( tok = strstr(tokenline, TOPICSTARTSIG )) {

			// Found first marker, now find keyword match
	
			if (vflag) {
				printf("@TopicStart = %s\n", TOPICSTARTSIG);
			}

			if (  (tl = strstr(tok, keyword) ) != NULL) {

				// Found keyword match, dump lines until end marker

				if (vflag) {
					printf("@KeyWord found in  %s\n", tl);
				}

				while ( ( tl = fgets(textline, maxline, fp) ) != NULL) {
					if ( strstr(tl, TOPICENDSIG ) ) {
						if (vflag) {
							printf("@TopicEND = %s\n", TOPICENDSIG);
						}
						return (0);
					} 

					printf("%s", tl);
				}
			}
		}
	}	

	fclose(fp);


	return (0);
}

