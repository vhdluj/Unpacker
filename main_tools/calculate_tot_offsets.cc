#include "../Unpacker/Unpacker2/EventIII.h"
#include "../Unpacker/Unpacker2/TDCHitIII.h"
#include "../Unpacker/Unpacker2/Event.h"
#include "../Unpacker/Unpacker2/TDCHit.h"
#include "../Unpacker/Unpacker2/TDCHitExtended.h"
#include "../Unpacker/Unpacker2/TDCChannel.h"
#include <TH1F.h>
#include <TF1.h>
#include <TMath.h>
#include <TH2F.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TStyle.h>
#include <TBrowser.h>
#include <iostream>


int calculate_tot_offsets(int eventsNum, const char* fileName, const char* outputConfigFile, int channelsCount)
{

TH1F* tot_hist[channelsCount];
TH2F* tot_barcode;
TH1F* stretcher_offsets;

  TChain chain("T");
  chain.Add(fileName);  
int i;

	bool noFile = false;
  
  EventIII* pEvent = 0;
  TDCChannel* pHit = 0;
  TClonesArray* pArray = 0;
  chain.SetBranchAddress("eventIII", &pEvent);

	string newFileName(outputConfigFile);
	TFile* new_file = new TFile(newFileName.c_str(), "UPDATE");
	if (new_file->IsZombie()) { noFile = true; }
	new_file->cd();
  
  Int_t entries = (Int_t)chain.GetEntries();
  cout<<"Entries = " <<entries<<endl;

	// ------ create histograms 
		// tot histograms created with 1us width
	for (int i = 0; i < channelsCount; i++) { tot_hist[i] = new TH1F(Form("tot_hist_ch%d", i), Form("tot_hist_ch%d", i), 10000, 0, 1000); }

	tot_barcode = new TH2F("tot_barcode", "tot_barcode", 10000, 0, 1000, channelsCount, 0, channelsCount);

	stretcher_offsets = new TH1F("stretcher_offsets", "stretcher_offsets", channelsCount, 0, channelsCount);

	// ------ loop over events
  for(Int_t i = 0; i < entries; i++)
	{
    if (i % 10000 == 0) cout<<i<<" of "<<entries<<"\r";
    if (i == eventsNum) break;
    chain.GetEntry(i);
    pArray = pEvent->GetTDCChannelsArray();
    if (pArray == 0) continue;
    TIter iter(pArray);

    iter.Begin();
    while( pHit = (TDCChannel*) iter.Next() )
		{
			// fill the tot histograms with all the hits on channels
			for(int j = 0; j < pHit->GetMult(); j++) { tot_hist[pHit->GetChannel()]->Fill(pHit->GetTOT(j)); }
			
			// fill the tot barcode histogram
			for(int j = 0; j < pHit->GetMult(); j++) { tot_barcode->Fill(pHit->GetTOT(j), pHit->GetChannel()); }
		}
	}

	// ------ adjust histograms
	for (int k = 0; k < channelsCount; k++) {
		// tot histograms centered at mean and +- 5ns offsets
		tot_hist[k]->GetXaxis()->SetRangeUser(tot_hist[k]->GetMean(1) - 2, tot_hist[k]->GetMean(1) + 2);
	}
	tot_barcode->GetXaxis()->SetRangeUser(tot_hist[1]->GetMean(1) - 100, tot_hist[1]->GetMean(1) + 100);

	// ------ calculating offsets and filling final histo
	for (int k = 0; k < channelsCount; k++) {
		tot_hist[k]->GetXaxis()->SetRangeUser(-50, 50);
		if (tot_hist[k]->GetMean(1) > 20) {
			stretcher_offsets->SetBinContent(k, tot_hist[k]->GetMean(1) - 10);
		}
		else {
			stretcher_offsets->Fill(k, 0.0);
		}
	}

	if (noFile == false) {
		// ------ saving histograms
		for (int k = 0; k < channelsCount; k++) { tot_hist[k]->Write("", TObject::kOverwrite); }
		tot_barcode->Write("", TObject::kOverwrite);
		stretcher_offsets->Write("", TObject::kOverwrite);
	}


	return 0;
}
