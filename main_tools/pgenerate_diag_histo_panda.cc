#include "../Unpacker2/EventIII.h"
#include "../Unpacker2/TDCHitIII.h"
#include "../Unpacker2/Event.h"
#include "../Unpacker2/TDCHit.h"
#include "../Unpacker2/TDCHitExtended.h"
#include "../Unpacker2/TDCChannel.h"
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

#define CHANNELS_NUMBER 196

//SET UP BINS FOR HISTOS
#define DT_BINS  2900
#define DT_MIN  -1700
#define DT_MAX  1200




TH1F* tot_hist[CHANNELS_NUMBER];
TH1F* mult_hist[CHANNELS_NUMBER];
TH1F* dt_hist[CHANNELS_NUMBER];
TH2F* tot_mult_hist[CHANNELS_NUMBER];
TH2F* tot_barcode;
TH2F* dt_barcode;
TH1F* refTimesDiff;



int pgenerate_diag_histo_panda(int eventsNum, const char* fileName, int referenceChannel = 51)
{
  TChain chain("T");
  chain.Add(fileName);  
int i;
  
  EventIII* pEvent = 0;
  TDCChannel* pHit = 0;
  TClonesArray* pArray = 0;
  chain.SetBranchAddress("eventIII", &pEvent);

	string newFileName(fileName);
	newFileName = newFileName.substr(0, newFileName.size() - 5);
	newFileName += "_histos.root";

	TFile* new_file = new TFile(newFileName.c_str(), "RECREATE");
	new_file->cd();
  
  Int_t entries = (Int_t)chain.GetEntries();
  cout<<"Entries = " <<entries<<endl;

	// ------ create histograms 
		// tot histograms created with 1us width
	for (int i = 0; i < CHANNELS_NUMBER; i++) { tot_hist[i] = new TH1F(Form("tot_hist_ch%d", i), Form("tot_hist_ch%d", i), 10000, 0, 1000); }
		// tot vs multiplicity
	for (int i = 0; i < CHANNELS_NUMBER; i++) { tot_mult_hist[i] = new TH2F(Form("tot_mult_hist_ch%d", i), Form("tot_mult_hist_ch%d", i), 10000, 0, 1000, 128, 0, 128); }
		// multiplicity
	for (int i = 0; i < CHANNELS_NUMBER; i++) { mult_hist[i] = new TH1F(Form("mult_hist_ch%d", i), Form("mult_hist_ch%d", i), 128, 0, 128); }
		// tot barcode over channels
	tot_barcode = new TH2F("tot_barcode", "tot_barcode", 10000, 0, 1000, CHANNELS_NUMBER, 0, CHANNELS_NUMBER);
	dt_barcode = new TH2F("dt_barcode", "dt_barcode", DT_BINS, DT_MIN, DT_MAX, CHANNELS_NUMBER, 0, CHANNELS_NUMBER);
		// drift time histograms
	for (int i = 0; i < CHANNELS_NUMBER; i++) { dt_hist[i] = new TH1F(Form("dt_hist%d", i), Form("dt_hist%d", i), DT_BINS,DT_MIN,DT_MAX); }
	refTimesDiff = new TH1F("refTimesDiff","refTimesDiff", 20000, -1000, 1000);

	// ------ loop over events
  for(Int_t i = 0; i < entries; i++)
	{
    if (i % 10000 == 0) cout<<i<<" of "<<entries<<"\r";
    if (i == eventsNum) break;
    chain.GetEntry(i);
    pArray = pEvent->GetTDCChannelsArray();
    if (pArray == 0) continue;
    TIter iter(pArray);

   double refTime = -200000;
   double refTime0 = -200000;
   double refTime49 = -200000;
   double refTime98 = -200000;
   double refTime147 = -200000;
   //extracting reference time
   while( pHit = (TDCChannel*) iter.Next() )
   {
         // fetch the ref time
         if (pHit->GetChannel() == referenceChannel && pHit->GetMult() > 0)
	        refTime = pHit->GetLeadTime1();
	if (pHit->GetChannel() == 0 && pHit->GetMult() > 0)
		refTime0 = pHit->GetLeadTime1();
	if(pHit->GetChannel() == 49 && pHit->GetMult() > 0 )
		refTime49 = pHit->GetLeadTime1();
	if(pHit->GetChannel() == 98 && pHit->GetMult() > 0 )
		refTime98 = pHit->GetLeadTime1();
	if(pHit->GetChannel() == 147 && pHit->GetMult() > 0 )
		refTime147 = pHit->GetLeadTime1();
   }

    /*if (refTime == -200000) //skipping events with no ref time set
	continue;
	
    if (refTime0 == -200000) //skipping events with no ref time set
	continue;
    if (refTime49 == -200000) //skipping events with no ref time set
	continue;
		// ------ loop over channels
//	std::cerr<<i++<<std::endl;
    if (refTime98 == -200000) //skipping events with no ref time set
        continue;

    if (refTime147 == -200000) //skipping events with no ref time set
        continue;*/

		refTimesDiff->Fill(refTime0 - refTime98);

    iter.Begin();
    while( pHit = (TDCChannel*) iter.Next() )
		{
			// fill the tot histograms with the first hits on channels
			//tot_hist[pHit->GetChannel()]->Fill(pHit->GetTOT1());

			// fill the tot histograms with all the hits on channels
			for(int j = 0; j < pHit->GetMult(); j++) { tot_hist[pHit->GetChannel()]->Fill(pHit->GetTOT(j)); }

			// fill the tot vs multiplicity histograms
			for(int j = 0; j < pHit->GetMult(); j++) { tot_mult_hist[pHit->GetChannel()]->Fill(pHit->GetTOT(j), j); }

			// fill the tot barcode histogram
			for(int j = 0; j < pHit->GetMult(); j++) { tot_barcode->Fill(pHit->GetTOT(j), pHit->GetChannel()); }
			//fill the drift time barcode histogram
			for(int j = 0; j < pHit->GetMult(); j++) { dt_barcode->Fill( pHit->GetLeadTime(j)-refTime, pHit->GetChannel()); }

//			for(int j = 0; j < pHit->GetMult(); j++) { dt_hist[pHit->GetChannel()]-> Fill(refTime - pHit->GetLeadTime(j));}


			/*if (pHit->GetChannel() == 1) {
				printf("1: %f %f\n", pHit->GetLeadTime1(), refTime0);
			}
			if (pHit->GetChannel() == 100) {
				printf("100: %f %f\n", pHit->GetLeadTime1(), refTime98);
			}
			if (pHit->GetChannel() == 50) {
				printf("50: %f %f\n", pHit->GetLeadTime1(), refTime49);
			}*/

			if(pHit->GetMult() > 0 ) 
			{
			for(int j = 0; j < pHit->GetMult(); j++) { dt_hist[pHit->GetChannel()]-> Fill(pHit->GetLeadTime(j)-refTime);}
			//dt_hist[pHit->GetChannel()]-> Fill(pHit->GetLeadTime1()-refTime);
			//std::cout<<"refTime: "<<refTime<<"  leadTime: "<<pHit->GetLeadTime1()<<"  dt:"<<pHit->GetLeadTime1()-refTime<<std::endl;		
	
			}
			else
			{
			dt_hist[pHit->GetChannel()]-> Fill(-2222222);
			//std::cout<<"Mult <0 refTime: "<<refTime<<"  leadTime: "<<pHit->GetLeadTime1()<<std::endl;
			}
			// fill the multiplicity histograms
			mult_hist[pHit->GetChannel()]->Fill(pHit->GetMult());

			

		}
	}

	// ------ adjust histograms
	for (int i = 0; i < CHANNELS_NUMBER; i++) {
		// tot histograms centered at mean and +- 5ns offsets
		tot_hist[i]->GetXaxis()->SetRangeUser(tot_hist[i]->GetMean(1) - 5, tot_hist[i]->GetMean(1) + 5);
		tot_mult_hist[i]->GetXaxis()->SetRangeUser(tot_hist[i]->GetMean(1) - 100, tot_hist[i]->GetMean(1) + 100);
	}
	tot_barcode->GetXaxis()->SetRangeUser(tot_hist[1]->GetMean(1) - 100, tot_hist[1]->GetMean(1) + 100);

	// ------ draw fits
	//for (int i = 0; i < CHANNELS_NUMBER; i++) {
	//	tot_hist[i]->Fit("gaus");
	//}

	// ------ saving histograms
	for (int i = 0; i < CHANNELS_NUMBER; i++) { tot_hist[i]->Write();	}
	for (int i = 0; i < CHANNELS_NUMBER; i++) { mult_hist[i]->Write(); }
	for (int i = 0; i < CHANNELS_NUMBER; i++) { dt_hist[i]->Write(); }
	tot_barcode->Write();
	dt_barcode->Write();
	return 0;
}
