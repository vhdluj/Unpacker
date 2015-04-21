#ifndef TDCHit_h
#define TDCHit_h

#include <TObject.h>

#define MAX_HITS 100

class TDCHit : public TObject {
  
protected:
  Int_t channel;

  Int_t leadsNum;
  int leadFineTime1;
  int leadFineTimes[MAX_HITS];
  int leadCoarseTime1;
  int leadCoarseTimes[MAX_HITS];
  int leadEpoch1;
  int leadEpochs[MAX_HITS];
  double leadTime1;
  double leadTimes[MAX_HITS];
  double absoluteLead1;
  double absoluteLeads[MAX_HITS];

  Int_t trailsNum;
  int trailFineTime1;
	int trailFineTimes[MAX_HITS];
	int trailCoarseTime1;
	int trailCoarseTimes[MAX_HITS];
  int trailEpoch1;
  int trailEpochs[MAX_HITS];
  double trailTime1;
  double trailTimes[MAX_HITS];
  double absoluteTrail1;
  double absoluteTrails[MAX_HITS];

  double tot;
  
public:

  TDCHit();
  ~TDCHit();
  
  void SetChannel(Int_t channel) { this->channel = channel; }
  
	void AddLeadTime(int fine, int coarse, int epoch);
	void AddTrailTime(int fine, int coarse, int epoch);

	int GetChannel() { return channel; }

	int GetLeadsNum() { return leadsNum; }
	int GetLeadFine(int mult) { return leadFineTimes[mult]; }
	int GetLeadCoarse(int mult) { return leadCoarseTimes[mult]; }
	int GetLeadEpoch(int mult) { return leadEpochs[mult]; }

	int GetTrailsNum() { return trailsNum; }
	int GetTrailFine(int mult) { return trailFineTimes[mult]; }
	int GetTrailCoarse(int mult) { return trailCoarseTimes[mult]; }
	int GetTrailEpoch(int mult) { return trailEpochs[mult]; }


  ClassDef(TDCHit,1);
};

#endif
