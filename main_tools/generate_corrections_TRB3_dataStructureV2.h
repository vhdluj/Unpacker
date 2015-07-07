//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 11 16:22:35 2015 by ROOT version 5.34/25
// from TTree T/Tree
// found on file: /home/guplab/hldFiles/xx15070160653.hld.root
//////////////////////////////////////////////////////////

#ifndef generate_corrections_TRB3_dataStructureV2_h
#define generate_corrections_TRB3_dataStructureV2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
#include "../Unpacker/Unpacker2/Event.h"
//#include "/home/daq/root_v5.34.25/include/TObject.h"
//#include "/home/daq/root_v5.34.25/include/TCanvas.h"
#include "../Unpacker/Unpacker2/TDCHit.h"
#include "../Unpacker/Unpacker2/TDCHitExtended.h"
#include "../Unpacker/Unpacker2/ADCHit.h"

// Fixed size dimensions of array or collections stored in the TTree if any.
   const Int_t kMaxTDCHits = 196;
   const Int_t kMaxADCHits = 1;

class generate_corrections_TRB3_dataStructureV2 : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain



   // Declaration of leaf types
 //Event           *event;
   UInt_t          fUniqueID;
   UInt_t          fBits;
   Int_t           totalNTDCHits;
   Float_t         TDCReferenceTime;
   UInt_t          errorBits;
   Int_t           TDCHits_;
   UInt_t          TDCHits_fUniqueID[kMaxTDCHits];   //[TDCHits_]
   UInt_t          TDCHits_fBits[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_channel[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_leadsNum[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_leadFineTimes[kMaxTDCHits][100];   //[TDCHits_]
   Int_t           TDCHits_leadCoarseTimes[kMaxTDCHits][100];   //[TDCHits_]
   Int_t           TDCHits_leadEpochs[kMaxTDCHits][100];   //[TDCHits_]
   Int_t           TDCHits_trailsNum[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_trailFineTimes[kMaxTDCHits][100];   //[TDCHits_]
   Int_t           TDCHits_trailCoarseTimes[kMaxTDCHits][100];   //[TDCHits_]
   Int_t           TDCHits_trailEpochs[kMaxTDCHits][100];   //[TDCHits_]
   Int_t           TDCHits_timeLineSize[kMaxTDCHits];   //[TDCHits_]
   Int_t           TDCHits_fineTimeLine[kMaxTDCHits][200];   //[TDCHits_]
   Int_t           TDCHits_coarseTimeLine[kMaxTDCHits][200];   //[TDCHits_]
   Int_t           TDCHits_epochTimeLine[kMaxTDCHits][200];   //[TDCHits_]
   Double_t        TDCHits_shortTimeLine[kMaxTDCHits][200];   //[TDCHits_]
   Double_t        TDCHits_absoluteTimeLine[kMaxTDCHits][200];   //[TDCHits_]
   Bool_t          TDCHits_riseTimeLine[kMaxTDCHits][200];   //[TDCHits_]

   // List of branches
   TBranch        *b_event_fUniqueID;   //!
   TBranch        *b_event_fBits;   //!
   TBranch        *b_event_totalNTDCHits;   //!
   TBranch        *b_event_TDCReferenceTime;   //!
   TBranch        *b_event_errorBits;   //!
   TBranch        *b_event_TDCHits_;   //!
   TBranch        *b_TDCHits_fUniqueID;   //!
   TBranch        *b_TDCHits_fBits;   //!
   TBranch        *b_TDCHits_channel;   //!
   TBranch        *b_TDCHits_leadsNum;   //!
   TBranch        *b_TDCHits_leadFineTimes;   //!
   TBranch        *b_TDCHits_leadCoarseTimes;   //!
   TBranch        *b_TDCHits_leadEpochs;   //!
   TBranch        *b_TDCHits_trailsNum;   //!
   TBranch        *b_TDCHits_trailFineTimes;   //!
   TBranch        *b_TDCHits_trailCoarseTimes;   //!
   TBranch        *b_TDCHits_trailEpochs;   //!
   TBranch        *b_TDCHits_timeLineSize;   //!
   TBranch        *b_TDCHits_fineTimeLine;   //!
   TBranch        *b_TDCHits_coarseTimeLine;   //!
   TBranch        *b_TDCHits_epochTimeLine;   //!
   TBranch        *b_TDCHits_shortTimeLine;   //!
   TBranch        *b_TDCHits_absoluteTimeLine;   //!
   TBranch        *b_TDCHits_riseTimeLine;   //!

   generate_corrections_TRB3_dataStructureV2(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~generate_corrections_TRB3_dataStructureV2() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(generate_corrections_TRB3_dataStructureV2,0);
};

#endif

#ifdef generate_corrections_TRB3_dataStructureV2_cxx
void generate_corrections_TRB3_dataStructureV2::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);



   fChain->SetBranchAddress("fUniqueID", &fUniqueID, &b_event_fUniqueID);
   fChain->SetBranchAddress("fBits", &fBits, &b_event_fBits);
   fChain->SetBranchAddress("totalNTDCHits", &totalNTDCHits, &b_event_totalNTDCHits);
   fChain->SetBranchAddress("TDCReferenceTime", &TDCReferenceTime, &b_event_TDCReferenceTime);
   fChain->SetBranchAddress("errorBits", &errorBits, &b_event_errorBits);
   fChain->SetBranchAddress("TDCHits", &TDCHits_, &b_event_TDCHits_);
   fChain->SetBranchAddress("TDCHits.fUniqueID", TDCHits_fUniqueID, &b_TDCHits_fUniqueID);
   fChain->SetBranchAddress("TDCHits.fBits", TDCHits_fBits, &b_TDCHits_fBits);
   fChain->SetBranchAddress("TDCHits.channel", TDCHits_channel, &b_TDCHits_channel);
   fChain->SetBranchAddress("TDCHits.leadsNum", TDCHits_leadsNum, &b_TDCHits_leadsNum);
   fChain->SetBranchAddress("TDCHits.leadFineTimes[100]", TDCHits_leadFineTimes, &b_TDCHits_leadFineTimes);
   fChain->SetBranchAddress("TDCHits.leadCoarseTimes[100]", TDCHits_leadCoarseTimes, &b_TDCHits_leadCoarseTimes);
   fChain->SetBranchAddress("TDCHits.leadEpochs[100]", TDCHits_leadEpochs, &b_TDCHits_leadEpochs);
   fChain->SetBranchAddress("TDCHits.trailsNum", TDCHits_trailsNum, &b_TDCHits_trailsNum);
   fChain->SetBranchAddress("TDCHits.trailFineTimes[100]", TDCHits_trailFineTimes, &b_TDCHits_trailFineTimes);
   fChain->SetBranchAddress("TDCHits.trailCoarseTimes[100]", TDCHits_trailCoarseTimes, &b_TDCHits_trailCoarseTimes);
   fChain->SetBranchAddress("TDCHits.trailEpochs[100]", TDCHits_trailEpochs, &b_TDCHits_trailEpochs);
   fChain->SetBranchAddress("TDCHits.timeLineSize", TDCHits_timeLineSize, &b_TDCHits_timeLineSize);
   fChain->SetBranchAddress("TDCHits.fineTimeLine[200]", TDCHits_fineTimeLine, &b_TDCHits_fineTimeLine);
   fChain->SetBranchAddress("TDCHits.coarseTimeLine[200]", TDCHits_coarseTimeLine, &b_TDCHits_coarseTimeLine);
   fChain->SetBranchAddress("TDCHits.epochTimeLine[200]", TDCHits_epochTimeLine, &b_TDCHits_epochTimeLine);
   fChain->SetBranchAddress("TDCHits.shortTimeLine[200]", TDCHits_shortTimeLine, &b_TDCHits_shortTimeLine);
   fChain->SetBranchAddress("TDCHits.absoluteTimeLine[200]", TDCHits_absoluteTimeLine, &b_TDCHits_absoluteTimeLine);
   fChain->SetBranchAddress("TDCHits.riseTimeLine[200]", TDCHits_riseTimeLine, &b_TDCHits_riseTimeLine);
}

Bool_t generate_corrections_TRB3_dataStructureV2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef generate_corrections_TRB3_dataStructureV2_cxx
