#include "../Unpacker2/EventIII.h"
#include "../Unpacker2/TDCHitIII.h"
#include "../Unpacker2/Event.h"
#include "../Unpacker2/Unpacker2.h"
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TH2F.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;


int calculate_dnl_params(int eventsNum, const char* fileName, const char* outputConfigFile, int channelsCount);
int calculate_tot_offsets(int eventsNum, const char* fileName, const char* outputConfigFile, int channelsCount);
int calculate_hits(int eventsNum, const char* fileName, int referenceChannel);
int calculate_times(int eventsNum, const char* fileName, int refChannelOffset, const char* calibFile);


void generate_temp_raw_calib_file(char* confFile)
{
	string line;
	string name = string(confFile);
	fstream file(name.c_str(), ios::in);
	ofstream file2((name+"tempraw.xml").c_str(), ios::out);
	if (file.is_open() && file2.is_open() )
	{
		while (getline(file, line))
		{
			if (line.find("<CORRECTION_FILE>") != string::npos)
			{
				line.replace(line.find("<CORRECTION_FILE>"), line.find("</CORRECTION_FILE>") - 4, "<CORRECTION_FILE>raw");
			}
			file2<<line<<endl;
		}
	}else{cerr<<"error opening files"<<endl;}
}

void generate_temp_full_calib_file(char* confFile, string newFile)
{
	string line;
	string name = string(confFile);
	fstream file(name.c_str(), ios::in);
	ofstream file2((name + "tempfull.xml").c_str(), ios::out);
	if (file.is_open() && file2.is_open())
	{
		while (getline(file, line))
		{
			if (line.find("<CORRECTION_FILE>") != string::npos)
			{
				line.replace(line.find("<CORRECTION_FILE>"), line.find("</CORRECTION_FILE>") - 4, "<CORRECTION_FILE>" + newFile);
			}
			file2<<line<<endl;
		}
	}else{cerr<<"error opening files"<<endl;}
}


int run_calibration(int eventsNum, char* fileName, char* confFile, int referenceChannel)
{
	clock_t tStart = clock();

	// alter the config file to remove the calib file
	generate_temp_raw_calib_file(confFile);

	// run the analysis procedures
  
	string newFileName = "bleble";
	newFileName = string(fileName);

	string confTemp = string(confFile);
	confTemp += "tempraw.xml";

	printf("\n\n >>>>>>>  Unpacking RAW data\n\n");
	Unpacker2(fileName, confTemp.c_str(), eventsNum);

	printf("\n\n >>>>>>>  Calculating DNL corrections\n\n");
	string calibFileName = string(fileName) + "_params.root";
	newFileName += ".root";
	calculate_dnl_params(eventsNum, newFileName.c_str(), calibFileName.c_str(), 196);

	
	// alter the config file to remove the calib file
	printf("\n\n >>>>>>>  Unpacking data with APPLIED corrections\n\n");
	generate_temp_full_calib_file(confFile, calibFileName);
	remove(confTemp.c_str());

	confTemp = string(confFile);
	confTemp += "tempfull.xml";
	Unpacker2(fileName, confTemp.c_str(), eventsNum);

	remove(confTemp.c_str());
	
	// calculating times and hits
	printf("\n\n >>>>>>>  Calculating Times and Hits\n\n");
	calculate_times(eventsNum, newFileName.c_str(), 49, "");

	newFileName = newFileName.substr(0, newFileName.size() - 5);
	newFileName += "_times.root";

	calculate_hits(eventsNum, newFileName.c_str(), referenceChannel);

	newFileName = newFileName.substr(0, newFileName.size() - 5);
	newFileName += "_hits.root";

	// calculating tots offsets
	printf("\n\n >>>>>>>  Calculating TOT offsets\n\n");
	calculate_tot_offsets(eventsNum, newFileName.c_str(), calibFileName.c_str(), 196);


  	printf("\n\n >>>>>>>  Calib file: %s", calibFileName.c_str());
  	printf("\n\n >>>>>>>  Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

	return 0;
}


