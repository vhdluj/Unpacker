#include "TDCHit.h"
#include <iostream>

using namespace std;

ClassImp(TDCHit);

TDCHit::TDCHit() {
  channel = -1;

  leadsNum = 0;
	leadFineTime1 = -100000;
	leadCoarseTime1 = -100000;
  leadEpoch1 = -100000;
  leadTime1 = -100000;
  absoluteLead1 = -100000;

  trailsNum = 0;
	trailFineTime1 = -100000;
	trailCoarseTime1 = -100000;
  trailEpoch1 = -100000;
  trailTime1 = -100000;
  absoluteTrail1 = -100000;	

  tot = -100000;
    
  for (int i = 0; i < MAX_HITS; i++) {
		leadFineTimes[i] = -100000;
		leadCoarseTimes[i] = -100000;
    leadEpochs[i] = -100000;
    leadTimes[i] = -100000;
    absoluteLeads[i] = -100000;

		trailFineTimes[i] = -100000;
		trailCoarseTimes[i] = -100000;
    trailEpochs[i] = -100000;
    trailTimes[i] = -100000;
    absoluteTrails[i] = -100000;
  }
}

TDCHit::~TDCHit() {
}

void TDCHit::AddLeadTime(int fine, int coarse, int epoch) {
	leadFineTimes[leadsNum] = fine;
	leadCoarseTimes[leadsNum] = coarse;
	leadEpochs[leadsNum] = epoch;

	leadTimes[leadsNum] = (coarse * 5000. - fine) / 10. / 100.; 
	absoluteLeads[leadsNum] = epoch * 10235. * 100. + (coarse * 5000. - fine) / 10.;
	
	if (leadsNum == 0) {
		leadFineTime1 = fine;
		leadCoarseTime1 = coarse;
		leadEpoch1 = epoch;

		leadTime1 = (coarse * 5000. - fine) / 10. / 100.; 
		absoluteLead1 = epoch * 10235. * 100. + (coarse * 5000. - fine) / 10.;
	}

	leadsNum++;
}

void TDCHit::AddTrailTime(int fine, int coarse, int epoch) {
	trailFineTimes[trailsNum] = fine;
	trailCoarseTimes[trailsNum] = coarse;
	trailEpochs[trailsNum] = epoch;

	trailTimes[trailsNum] = (coarse * 5000. - fine) / 10. / 100.; 
	absoluteTrails[trailsNum] = (epoch * 10235. * 100.) + ((coarse * 5000. - fine) / 10.);
	
	if (trailsNum == 0) {
		trailFineTime1 = fine;
		trailCoarseTime1 = coarse;
		trailEpoch1 = epoch;

		trailTime1 = (coarse * 5000. - fine) / 10. / 100.; 
		absoluteTrail1 = (epoch * 10235. * 100.) + ((coarse * 5000. - fine) / 10.);
	}

	trailsNum++;
}
