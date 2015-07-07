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


int calculate_dnl_params(int eventsNum, const char* fileName, const char* outputConfigFile, int channelsCount)
{

	TH1F** binsHist;
	TH1F** correctionsHist;
	TH1F* correctionsDiag;

	TChain chain("T");
	chain.Add(fileName);  
  
	Event* pEvent = 0;
	TDCHit* pHit = 0;
	TClonesArray* pArray = 0;
	chain.SetBranchAddress("event", &pEvent);

	string newFileName(outputConfigFile);
	TFile* new_file = new TFile(newFileName.c_str(), "UPDATE");
	new_file->cd();
  
	Int_t entries = (Int_t)chain.GetEntries();
	cout<<"Entries = " <<entries<<endl;

	// ------ create histograms 
	correctionsDiag = new TH1F("correctionsDiag", "correctionsDiag", channelsCount, 0, channelsCount);
	binsHist = new TH1F*[channelsCount];
	correctionsHist = new TH1F*[channelsCount];
	for(int i = 0; i < channelsCount; i++){
		binsHist[i] = new TH1F(Form("binsHist%d", i), Form("binsHist%d", i), 500, 0, 5000);
		correctionsHist[i] = new TH1F(Form("correction%d", i), Form("correction%d", i), 500, 0, 500);
	}

	// ------ loop over events
	for(Int_t i = 0; i < entries; i++)
	{
		if (i % 10000 == 0) cout<<i<<" of "<<entries<<"\r";
		if (i == eventsNum) break;
		chain.GetEntry(i);
		pArray = pEvent->GetTDCHitsArray();
		if (pArray == 0) continue;
		TIter iter(pArray);

		iter.Begin();
		while( pHit = (TDCHit*) iter.Next() )
		{
			if (pHit->GetChannel() % 49) {
				binsHist[pHit->GetChannel()]->Fill(pHit->GetLeadFine(0));
			}
		}
	}

	for(int i = 0; i < channelsCount; i++)
		binsHist[i]->Scale(5000. / binsHist[i]->Integral(0, 5000));

  
	for(int i = 0; i < channelsCount; i++)
	{
		float sum = 0;
    
		for(int j = 0; j < 32 ; j++)
			correctionsHist[i]->SetBinContent(j,sum);
      
		for(int j = 32; j < 500 ; j++)
		{
			sum += binsHist[i]->GetBinContent(j);
      
			correctionsHist[i]->SetBinContent(j,sum);
		}
	}
   
	//filling linear corrections for reference channels
	for(int i = 0; i < 500; i++) {
		correctionsHist[0]->SetBinContent(i, i*10);
		correctionsHist[49]->SetBinContent(i, i*10);
		correctionsHist[98]->SetBinContent(i, i*10);
		correctionsHist[147]->SetBinContent(i, i*10);
	}

	for(int i = 0; i < channelsCount; i++)
	{
		correctionsHist[i]->Write("", TObject::kOverwrite);
		correctionsDiag->SetBinContent(i, correctionsHist[i]->GetMean());
	}
	correctionsDiag->Write("", TObject::kOverwrite);

	new_file->Close();


	return 0;
}
