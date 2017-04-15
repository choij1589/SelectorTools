#include "Analysis/WZAnalysis/interface/WZSelector.h"
#include <boost/algorithm/string.hpp>

void WZSelector::Init(TTree *tree)
{
    WZSelectorBase::Init(tree);
    
    fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
    fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
    fChain->SetBranchAddress("Mass", &Mass, &b_Mass);
    fChain->SetBranchAddress("nvtx", &nvtx, &b_nvtx);
    fChain->SetBranchAddress("mjj", &mjj, &b_mjj);
    fChain->SetBranchAddress("type1_pfMETEt", &type1_pfMETEt, &b_type1_pfMETEt);

    if (channel_ == eee) {
        fChain->SetBranchAddress("e1_e2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("e1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("e1Eta", &l1Eta, &b_l1Eta);
        fChain->SetBranchAddress("e2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("e2Eta", &l2Eta, &b_l2Eta);
        fChain->SetBranchAddress("e3Pt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("e3Eta", &l3Eta, &b_l3Eta);
    }
    else if (channel_ == eem) { 
        fChain->SetBranchAddress("e1_e2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("mPt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("mEta", &l3Eta, &b_l3Eta);
        fChain->SetBranchAddress("e1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("e1Eta", &l1Eta, &b_l1Eta);
        fChain->SetBranchAddress("e2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("e2Eta", &l2Eta, &b_l2Eta);
    }
    else if (channel_ == emm) { 
        fChain->SetBranchAddress("m1_m2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("ePt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("eEta", &l3Eta, &b_l3Eta);
        fChain->SetBranchAddress("m1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("m1Eta", &l1Eta, &b_l1Eta);
        fChain->SetBranchAddress("m2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("m2Eta", &l2Eta, &b_l2Eta);
    }
    else if (channel_ == mmm) { 
        fChain->SetBranchAddress("m1_m2_Mass", &Zmass, &b_Zmass);
        fChain->SetBranchAddress("m1Pt", &l1Pt, &b_l1Pt);
        fChain->SetBranchAddress("m1Eta", &l1Eta, &b_l1Eta);
        fChain->SetBranchAddress("m2Pt", &l2Pt, &b_l2Pt);
        fChain->SetBranchAddress("m2Eta", &l2Eta, &b_l2Eta);
        fChain->SetBranchAddress("m3Pt", &l3Pt, &b_l3Pt);
        fChain->SetBranchAddress("m3Eta", &l3Eta, &b_l3Eta);
    }
}

void WZSelector::SlaveBegin(TTree * /*tree*/)
{
    pileupSF_ = (ScaleFactor *) GetInputList()->FindObject("pileupSF");
    if (pileupSF_ == nullptr ) 
        Abort("Must pass pileup weights SF");
    eIdSF_ = (ScaleFactor *) GetInputList()->FindObject("electronTightIdSF");
    if (eIdSF_ == nullptr ) 
        Abort("Must pass electron ID SF");
    mIdSF_ = (ScaleFactor *) GetInputList()->FindObject("muonTightIdSF");
    if (mIdSF_ == nullptr ) 
        Abort("Must pass muon ID SF");
    mIsoSF_ = (ScaleFactor *) GetInputList()->FindObject("muonIsoSF");
    if (mIsoSF_ == nullptr ) 
        Abort("Must pass muon Iso SF");
}
void WZSelector::LoadBranches(Long64_t entry) { 
    WZSelectorBase::Process(entry);
    
    b_Zmass->GetEntry(entry);
    b_Mass->GetEntry(entry);
    b_nvtx->GetEntry(entry);
    b_mjj->GetEntry(entry);
    b_type1_pfMETEt->GetEntry(entry);
    b_l1Eta->GetEntry(entry);
    b_l1Pt->GetEntry(entry);
    b_l2Eta->GetEntry(entry);
    b_l2Pt->GetEntry(entry);
    b_l3Eta->GetEntry(entry);
    b_l3Pt->GetEntry(entry);
    b_jetPt->GetEntry(entry);
    b_jetEta->GetEntry(entry);
    dEtajj = 0;
    if (jetEta->size() >= 2)
        dEtajj = std::abs(jetEta->at(0) - jetEta->at(1));
}

bool WZSelector::PassesSelection(bool tightLeps) { 
    //if (type1_pfMETEt < 30)
    //    return true;
    //if (Mass < 100)
    //    return true;
    //if (l1Pt < 25 || l2Pt < 15)
    //    return true;
    //if (Zmass > 116.1876 || Zmass < 76.1876)
    //    return true;
    if (!passesLeptonVeto)
        return false;
    if (tightLeps && !(zlep1IsTight() && zlep2IsTight() && lepton3IsTight()))
        return false;
    return true;
}

void WZSelector::FillHistograms(float weight, bool noBlind) { 
    //zmassHist_->Fill(Zmass, weight);
    //nvtxHist_->Fill(nvtx, weight);
    //l1PtHist_->Fill(l1Pt, weight);
    //l2PtHist_->Fill(l2Pt, weight);
    //l3PtHist_->Fill(l3Pt, weight);
    //mjjHist_->Fill(mjj, weight*(isMC_ || mjj < 500 || noBlind));
    //if (dEtajj > 0)
    //    dEtajjHist_->Fill(dEtajj, weight*(isMC_ || dEtajj < 2.5));
    //massHist_->Fill(Mass, weight*(isMC_ || Mass < 400 || noBlind));
    std::cout << "And now for mass it's" << hists1D_["Mass"] << std::endl;
    if (hists1D_["Mass"] != nullptr) {
        std::cout << "Filling! ";
        hists1D_["Mass"]->Fill(Mass, weight*(isMC_ || Mass < 400 || noBlind));
    }
    if (hists1D_["Zlep1_Pt"] != nullptr)
        hists1D_["Zlep1_Pt"]->Fill(l1Pt, weight);
    if (hists1D_["Zlep2_Pt"] != nullptr)
        hists1D_["Zlep2_Pt"]->Fill(l2Pt, weight);
    if (hists1D_["Wlep_Pt"] != nullptr)
        hists1D_["Wlep_Pt"]->Fill(l3Pt, weight);
}

Bool_t WZSelector::Process(Long64_t entry)
{
    LoadBranches(entry);
    if (!PassesSelection(true))
        return true;

    if (isMC_) {
        if (channel_ == eee) {
            genWeight *= eIdSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= eIdSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= eIdSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= pileupSF_->Evaluate1D(nTruePU);
        }
        else if (channel_ == eem) {
            genWeight *= eIdSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= eIdSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= pileupSF_->Evaluate1D(nTruePU);
        }
        else if (channel_ == emm) {
            genWeight *= eIdSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= pileupSF_->Evaluate1D(nTruePU);
        }
        else {
            genWeight *= mIdSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l1Eta), l1Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l2Eta), l2Pt);
            genWeight *= mIdSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= mIsoSF_->Evaluate2D(std::abs(l3Eta), l3Pt);
            genWeight *= pileupSF_->Evaluate1D(nTruePU);
        }
    }
    
    FillHistograms(genWeight, false);
    
    return true;
}

std::vector<std::string> WZSelector::ReadHistData(std::string histDataString) {
    std::vector<std::string> histData;
    boost::split(histData, histDataString, boost::is_any_of("$"));
    std::vector<std::string> binInfo;
    if (histData.size() != 2)
        return {};
    
    boost::split(binInfo, histData[1], boost::is_any_of(","));
   
    histData.pop_back();
    for (const auto& x : binInfo) {
        histData.push_back(x);
    }
    
    return histData;
}

void WZSelector::SetupNewDirectory()
{
    WZSelectorBase::SetupNewDirectory();
   
    histInfo_ = (TList *) GetInputList()->FindObject("histinfo");
    if (histInfo_ == nullptr ) 
        Abort("Must pass histogram information");
    
    //for (auto & histEntry : hists1D_) {  
        TNamed* currentHistInfo = dynamic_cast<TNamed*>(histInfo_->FindObject("Mass"));
        //TNamed* currentHistInfo = dynamic_cast<TNamed*>(histInfo_->FindObject(histEntry.first));
        if (currentHistInfo != nullptr) { 
            std::vector<std::string> histData = ReadHistData(currentHistInfo->GetTitle());
            if (histData.size() != 4) {
                //std::cerr << "Malformed data string for histogram '" << histEntry.first
                std::cerr << "Malformed data string for histogram '"
                        << ".' Must have form: 'Title; (optional info) $ nbins, xmin, xmax'" << std::endl;
                exit(1);
            }
            //std::cout << "Hist pointer is " << histEntry.second << std::endl;
            std::cout << "Hist pointer is " << hists1D_["Mass"] << std::endl;
            //AddObject<TH1D>(hists1D_[histEntry.first], 
                //(std::string(histEntry.first)+"_"+channelName_).c_str(), histData[0].c_str(),
            AddObject<TH1D>(hists1D_["Mass"], 
                (std::string("Mass")+"_"+channelName_).c_str(), histData[0].c_str(),
                std::stoi(histData[1]), std::stof(histData[2]), std::stof(histData[3]));
            //std::cout << "And now it's " << histEntry.second << std::endl;
        }
    //}
    std::cout << "And now for mass it's" << hists1D_["Mass"] << std::endl;
}
