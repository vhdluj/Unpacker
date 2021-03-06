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
#include <TStopwatch.h>
#include <TFile.h>
#include <time.h>
#include <ctime>

int calculate_hits(int eventsNum, const char* fileName, int referenceChannel);
int calculate_times(int eventsNum, const char* fileName, int refChannelOffset, const char* calibFile);

int run_analysis(int eventsNum, char* fileName, char* confFile, int referenceChannel, const char* calibFile)
{
	TStopwatch watch = TStopwatch();  
	watch.Start();

	string newFileName = "bleble";
	newFileName = string(fileName);

	fprintf(stderr, "\n\n >>>>>>>  Unpacking data\n\n");
	Unpacker2(fileName, confFile, eventsNum);

	fprintf(stderr, "\n\n >>>>>>>  Calculating Times and Hits\n\n");
	newFileName += ".root";
	calculate_times(eventsNum, newFileName.c_str(), 49, calibFile);

	newFileName = newFileName.substr(0, newFileName.size() - 5);
	newFileName += "_times.root";

	calculate_hits(eventsNum, newFileName.c_str(), referenceChannel);

	newFileName = newFileName.substr(0, newFileName.size() - 5);
	newFileName += "_hits.root";

  	fprintf(stderr, "\n\n >>>>>>>  Final file: %s\n", newFileName.c_str());
	fprintf(stderr, "Time taken %d seconds\n", watch.RealTime());

    return 0;
}
