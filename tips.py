#!/usr/bin/python

#
# Find keyword based topics within a formatted info file
#
# Syntax:
#	% tips [-v] [-f infofile] keyword
#
#
# Dean Blevins
# Feb 2015
#

#import pdb             #Debugger

import argparse         #argv
import sys              #For program exits

defaultdatafile =	'/home/dean/info.txt'
topicsstartsig =	'-['
topicsendsig =		']-'

parser = argparse.ArgumentParser()
parser.add_argument("-v", "--verbose", help="verbose output", action="store_true")
parser.add_argument("-f", "--datafile", help="optional name of source file (default=~/info.txt)", default=defaultdatafile)
parser.add_argument("keyword", help="topic keyword")
args = parser.parse_args()

if args.verbose:
	print "@datafile: ", args.datafile
	print "@keyword: ", args.keyword

fp = open(args.datafile, 'r')

for textline in fp:

	# Look for starting topic marker
	if textline.find(topicsstartsig) != -1:

		# Found it, now look at same line for keyword match
		if textline.find(args.keyword) != -1:

			for textline in fp:

				if textline.find(topicsendsig) != -1:
					sys.exit(0)

				# Chomp and print the topic line (avoids double \n)
				print textline.rstrip()
