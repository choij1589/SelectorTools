#include "Analysis/SelectorTools/interface/ZGenSelector.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include <TStyle.h>
#include <regex>
#include <numeric>
#include "TParameter.h"

void ZGenSelector::Init(TTree *tree)
{
    // Don't waste memory on empty e hists
    TParameter<bool>* muOnlyParam = (TParameter<bool>*) GetInputList()->FindObject("muOnly");
    bool muOnly = muOnlyParam != nullptr && muOnlyParam->GetVal();
    allChannels_ = {{mm, "mm"}}; 
    if (!muOnly) {
        allChannels_.push_back(std::make_pair<Channel, std::string>(ee, "ee"));
    }
    // Add CutFlow for Unknown to understand when channels aren't categorized
    histMap1D_[{"CutFlow", Unknown, Central}] = {};
    std::vector<std::string> basehists1D = {"CutFlow", "ZMass", "yZ", "ptZ", "phiZ", "ptl1", "etal1", "phil1", "ptl2", "etal2", "phil2", "nLeptons", 
    "ptj1", "ptj2", "ptj3", "etaj1", "etaj2", "etaj3", "phij1", "phij2", "phij3", "nJets",
	"dRj1l1", "dRj1l2", "dRj2l1", "dRj2l2", "dRj1j2", "dRl1l2", "MET", "HT",};
    hists1D_ = basehists1D;
    //std::vector<std::string> partonicChans = {"uu_dd", "uubar_ddbar", "ug_dg", "ubarg_dbarg", "gg", "other"};
    //for (auto& chan : partonicChans) {
    //    for (auto& hist : basehists1D)
    //        hists1D_.push_back(chan + "_" + hist);
    //}
    systHists_ = hists1D_;

    weighthists1D_ = {"CutFlow", "ZMass", "yZ", "ptZ", "phiZ", "ptl1", "etal1", "ptl2", "etal2", "nLeptons",
        "ptj1", "ptj2", "ptj3", "etaj1", "etaj2", "etaj3", "nJets",
        "MET", "HT", };
    nLeptons_ = 2;

    TParameter<bool>* massVar = (TParameter<bool>*) GetInputList()->FindObject("massVar");
    doMassVar_ = massVar != nullptr && massVar->GetVal();

    if (doMassVar_) {
        systematics_[mZShift50MeVUp] = "mZShift50MeVUp";
        systematics_[mZShift50MeVDown] = "mZShift50MeVDown";
        systematics_[mZShift100MeVUp] = "mZShift100MeVUp";
        systematics_[mZShift100MeVDown] = "mZShift100MeVDown";
    }
    doSystematics_ = !systematics_.empty();

    if (name_.find("nnlops") != std::string::npos) {
        MV_GEN_ = 80398.0;
        GAMMAV_GEN_ = 2088.720;
    }
    else if (name_.find("minnlo") != std::string::npos) {
        MV_GEN_ = 91153.509740726733;
        GAMMAV_GEN_ = 2493.2018986110700;
    }
    else {
        MV_GEN_ = 80419.;
        GAMMAV_GEN_ = 2050;
    }

    NanoGenSelectorBase::Init(tree);
}

void ZGenSelector::LoadBranchesNanoAOD(Long64_t entry, std::pair<Systematic, std::string> variation) {
    NanoGenSelectorBase::LoadBranchesNanoAOD(entry, variation);

    if (variation.first == Central)
        cenWeight = weight;
    else if (variation.first == LHEParticles) {
        ptVlhe = zCand.pt();
        mVlhe = zCand.mass()*1000.;
    }
    else if (variation.first == mZShift10MeVUp)
        weight = cenWeight*breitWignerWeight(10.);
    else if (variation.first == mZShift10MeVDown)
        weight = cenWeight*breitWignerWeight(-10.);
    else if (variation.first == mZShift20MeVUp)
        weight = cenWeight*breitWignerWeight(20.);
    else if (variation.first == mZShift20MeVDown)
        weight = cenWeight*breitWignerWeight(-20.);
    else if (variation.first == mZShift25MeVUp)
        weight = cenWeight*breitWignerWeight(25.);
    else if (variation.first == mZShift25MeVDown)
        weight = cenWeight*breitWignerWeight(-25.);
    else if (variation.first == mZShift50MeVUp)
        weight = cenWeight*breitWignerWeight(50.);
    else if (variation.first == mZShift50MeVDown)
        weight = cenWeight*breitWignerWeight(-50.);
    else if (variation.first == mZShift100MeVUp)
        weight = cenWeight*breitWignerWeight(100.);
    else if (variation.first == mZShift100MeVDown)
        weight = cenWeight*breitWignerWeight(-100.);

    if (leptons.size() < 2) {
        channel_ = Unknown;
        channelName_ = "Unknown";
        return;
    }
    if (leptons.at(0).pdgId() + leptons.at(1).pdgId() == 0) {
        if (std::abs(leptons.at(0).pdgId()) == 11) {
            channel_ = ee;
            channelName_ = "ee";
        }
        else if (std::abs(leptons.at(0).pdgId()) == 13) {
            channel_ = mm;
            channelName_ = "mm";
        }
    }
    else {
        channel_ = Unknown;
        channelName_ = "Unknown";
    }
}

void ZGenSelector::SetComposite() {
    if (leptons.size() >= 2)
        zCand = leptons.at(0).polarP4() + leptons.at(1).polarP4();
}

void ZGenSelector::FillHistograms(Long64_t entry, std::pair<Systematic, std::string> variation) { 
    int step = 0;
    int failStep = 0;

    step++;
    if (channel_ != mm && channel_ != ee) 
        failStep = step;

    auto lep1 = leptons.size() > 1 ? leptons.at(0) : reco::GenParticle();
    auto lep2 = leptons.size() > 1 ? leptons.at(1) : reco::GenParticle();

    step++;
	// ZCand mass cut temporarily set to 100 GeV to compare mass binned & inclusive
    //if (zCand.mass() < 50.)
	if (zCand.mass() < 100.)
        failStep = step;
    step++;
    if (lep1.pt() < 25. || lep2.pt() < 25.)
        failStep = step;
    step++;
    if ((std::abs(lep1.eta()) > 2.5 || std::abs(lep2.eta()) > 2.5) ||
            (selection_ == ZselectionTight && (std::abs(lep1.eta()) > 2.4 || std::abs(lep2.eta()) > 2.4)))
        failStep = step;
    step++;
    if ((zCand.mass() < 60. || zCand.mass() > 120.) || (selection_ == ZselectionTight && (zCand.mass() < 76.1876 || zCand.mass() > 106.1786)))
        failStep = step;

    for (int j = 0; j < (failStep == 0 ? step : failStep); j++) {
        SafeHistFill(histMap1D_, "CutFlow", channel_, variation.first, j, weight);
        //size_t nWeights = *nLHEScaleWeight;
        //for (size_t i = 0; i < nWeights; i++) {
        //    float thweight = LHEScaleWeight[i];
        //    thweight *= weight;
        //    SafeHistFill(weighthistMap1D_, "CutFlow", channel_, variation.first, j, i, thweight);
        //}
    }
    if (doFiducial_ && failStep != 0)
        return;
    if (variation.first == Central)
        mcWeights_->Fill(weight/std::abs(refWeight));

    if (std::find(theoryVarSysts_.begin(), theoryVarSysts_.end(), variation.first) != theoryVarSysts_.end()) {
        size_t nScaleWeights = nLHEScaleWeight+nLHEScaleWeightAltSet1;
        size_t minimalWeights = nLHEScaleWeight+nLHEScaleWeightAltSet1+nLHEUnknownWeight+nLHEUnknownWeightAltSet1;
        size_t allPdfWeights = std::accumulate(nLHEPdfWeights.begin(), nLHEPdfWeights.end(), 1);

        //size_t nWeights = variation.first == Central ? minimalWeights+allPdfWeights : minimalWeights;
        size_t nWeights = minimalWeights+allPdfWeights;
        size_t pdfOffset = nScaleWeights;
        size_t pdfIdx = 0;
        for (size_t i = 0; i < nWeights; i++) {
            float thweight = 1;
            if (i < nLHEScaleWeight)
                thweight = LHEScaleWeight[i];
            else if (i < nScaleWeights)
                thweight = LHEScaleWeightAltSet1[i-nLHEScaleWeight];
            else if (i < nScaleWeights+allPdfWeights) {
                thweight = LHEPdfWeights[pdfIdx][i-pdfOffset];
                if (i == pdfOffset+nLHEPdfWeights.at(pdfIdx)-1) {
                    pdfOffset += nLHEPdfWeights.at(pdfIdx++);
                }
            }

            if (centralWeightIndex_ != -1 && scaleWeights_)
                thweight /= LHEScaleWeight[centralWeightIndex_];

            if (((variation.first == ptV0to3 || variation.first == ptV0to3_lhe) && ptVlhe > 3.) ||
                    ((variation.first == ptV3to5 || variation.first == ptV3to5_lhe) && (ptVlhe < 3. || ptVlhe > 5.))  ||
                    ((variation.first == ptV5to7 || variation.first == ptV5to7_lhe) && (ptVlhe < 5. || ptVlhe > 7.)) ||
                    ((variation.first == ptV7to9 || variation.first == ptV7to9_lhe) && (ptVlhe < 7. || ptVlhe > 9.)) ||
                    ((variation.first == ptV9to12 || variation.first == ptV9to12_lhe) && (ptVlhe < 9. || ptVlhe > 12.)) ||
                    ((variation.first == ptV12to15 || variation.first == ptV12to15_lhe) && (ptVlhe < 12. || ptVlhe > 15.)) ||
                    ((variation.first == ptV15to20 || variation.first == ptV15to20_lhe) && (ptVlhe < 15. || ptVlhe > 20.)) ||
                    ((variation.first == ptV20to27 || variation.first == ptV20to27_lhe) && (ptVlhe < 20. || ptVlhe > 27.)) ||
                    ((variation.first == ptV27to40 || variation.first == ptV27to40_lhe) && (ptVlhe < 27. || ptVlhe > 40.)) ||
                    ((variation.first == ptV40toInf || variation.first == ptV40toInf_lhe) && ptVlhe < 40. )) {
                thweight = 1;
            }

            thweight *= weight;
            SafeHistFill(weighthistMap1D_, "ZMass", channel_, variation.first, zCand.mass(), i, thweight);
            SafeHistFill(weighthistMap1D_, "yZ", channel_, variation.first, zCand.Rapidity(), i, thweight);
            SafeHistFill(weighthistMap1D_, "ptZ", channel_, variation.first, zCand.pt(), i, thweight);
            SafeHistFill(weighthistMap1D_, "phiZ", channel_, variation.first, zCand.phi(), i, thweight);
            SafeHistFill(weighthistMap1D_, "ptl1", channel_, variation.first, lep1.pt(), i, thweight);
            SafeHistFill(weighthistMap1D_, "etal1", channel_, variation.first, lep1.eta(), i, thweight);
            SafeHistFill(weighthistMap1D_, "phil1", channel_, variation.first, lep1.phi(), i, thweight);
            SafeHistFill(weighthistMap1D_, "ptl2", channel_, variation.first, lep2.pt(), i, thweight);
            SafeHistFill(weighthistMap1D_, "etal2", channel_, variation.first, lep2.eta(), i, thweight);
            SafeHistFill(weighthistMap1D_, "phil2", channel_, variation.first, lep2.phi(), i, thweight);
            SafeHistFill(weighthistMap1D_, "nJets", channel_, variation.first, jets.size(), i, thweight);
            SafeHistFill(weighthistMap1D_, "MET", channel_, variation.first, genMet.pt(), i, thweight);
        }
    }
    if (((variation.first == ptV0to3 || variation.first == ptV0to3_lhe) && ptVlhe > 3.) ||
            ((variation.first == ptV3to5 || variation.first == ptV3to5_lhe) && (ptVlhe < 3. || ptVlhe > 5.))  ||
            ((variation.first == ptV5to7 || variation.first == ptV5to7_lhe) && (ptVlhe < 5. || ptVlhe > 7.)) ||
            ((variation.first == ptV7to9 || variation.first == ptV7to9_lhe) && (ptVlhe < 7. || ptVlhe > 9.)) ||
            ((variation.first == ptV9to12 || variation.first == ptV9to12_lhe) && (ptVlhe < 9. || ptVlhe > 12.)) ||
            ((variation.first == ptV12to15 || variation.first == ptV12to15_lhe) && (ptVlhe < 12. || ptVlhe > 15.)) ||
            ((variation.first == ptV15to20 || variation.first == ptV15to20_lhe) && (ptVlhe < 15. || ptVlhe > 20.)) ||
            ((variation.first == ptV20to27 || variation.first == ptV20to27_lhe) && (ptVlhe < 20. || ptVlhe > 27.)) ||
            ((variation.first == ptV27to40 || variation.first == ptV27to40_lhe) && (ptVlhe < 27. || ptVlhe > 40.)) ||
            ((variation.first == ptV40toInf || variation.first == ptV40toInf_lhe) && ptVlhe < 40. )) {
        return;
    }

    SafeHistFill(histMap1D_, "CutFlow", channel_, variation.first, step++, weight);
    SafeHistFill(histMap1D_, "ZMass", channel_, variation.first, zCand.mass(), weight);
    SafeHistFill(histMap1D_, "yZ", channel_, variation.first, zCand.Rapidity(), weight);
    SafeHistFill(histMap1D_, "ptZ", channel_, variation.first, zCand.pt(), weight);
    SafeHistFill(histMap1D_, "phiZ", channel_, variation.first, zCand.phi(), weight);
    SafeHistFill(histMap1D_, "ptl1", channel_, variation.first, lep1.pt(), weight);
    SafeHistFill(histMap1D_, "etal1", channel_, variation.first, lep1.eta(), weight);
    SafeHistFill(histMap1D_, "phil1", channel_, variation.first, lep1.phi(), weight);
    SafeHistFill(histMap1D_, "ptl2", channel_, variation.first, lep2.pt(), weight);
    SafeHistFill(histMap1D_, "etal2", channel_, variation.first, lep2.eta(), weight);
    SafeHistFill(histMap1D_, "phil2", channel_, variation.first, lep2.phi(), weight);
	SafeHistFill(histMap1D_, "nLeptons", channel_, variation.first, leptons.size(), weight);
    SafeHistFill(histMap1D_, "nJets", channel_, variation.first, jets.size(), weight);
    SafeHistFill(histMap1D_, "MET", channel_, variation.first, genMet.pt(), weight);
    SafeHistFill(histMap1D_, "HT", channel_, variation.first, ht, weight);
    for (size_t i = 1; i <= 3; i++) {
        if (jets.size() >= i ) {
            const auto& jet = jets.at(i-1);
            SafeHistFill(histMap1D_, ("ptj"+std::to_string(i)).c_str(), channel_, variation.first, jet.pt(), weight);
            SafeHistFill(histMap1D_, ("etaj"+std::to_string(i)).c_str(), channel_, variation.first, jet.eta(), weight);
            SafeHistFill(histMap1D_, ("phij"+std::to_string(i)).c_str(), channel_, variation.first, jet.phi(), weight);
        }  
    }
    // deltaR distribution
	const double dRl1l2 = reco::deltaR(lep1, lep2);
	SafeHistFill(histMap1D_, "dRl1l2", channel_, variation.first, dRl1l2, weight);
	if (jets.size() >= 1) {
		const auto& j1 = jets.at(0);
		const double dRj1l1 = reco::deltaR(j1, lep1);
		const double dRj1l2 = reco::deltaR(j1, lep2);
		SafeHistFill(histMap1D_, "dRj1l1", channel_, variation.first, dRj1l1, weight);
		SafeHistFill(histMap1D_, "dRj1l2", channel_, variation.first, dRj1l2, weight);
	}
	if (jets.size() >= 2) {
		const auto& j1 = jets.at(0);
		const auto& j2 = jets.at(1);
		const double dRj2l1 = reco::deltaR(j2, lep1);
		const double dRj2l2 = reco::deltaR(j2, lep2);
		const double dRj1j2 = reco::deltaR(j1, j2);
		SafeHistFill(histMap1D_, "dRj2l1", channel_, variation.first, dRj2l1, weight);
		SafeHistFill(histMap1D_, "dRj2l2", channel_, variation.first, dRj2l2, weight);
		SafeHistFill(histMap1D_, "dRj1j2", channel_, variation.first, dRj1j2, weight);
	}
    // Should check how slow this is. For now it's off 
    return;

    std::string partonicChan = "other";
    if ((*Generator_id1 == 1 && *Generator_id2 == 1) || (*Generator_id1 == 2 && *Generator_id2 == 2))
        partonicChan = "uu_dd";
    else if ((*Generator_id1 == 1 && *Generator_id2 == -1) || (*Generator_id1 == 2 && *Generator_id2 == -2))
        partonicChan = "uubar_ddbar";
    else if (*Generator_id1 == 21 && *Generator_id2 == 21)
        partonicChan = "gg";
    else if ((*Generator_id1 == 1 && *Generator_id2 == 21) || (*Generator_id1 == 21 && *Generator_id2 == 1) || 
                (*Generator_id1 == 2 && *Generator_id2 == 21) || (*Generator_id1 == 21 && *Generator_id2 == 2))
        partonicChan = "ug_dg";
    else if ((*Generator_id1 == -1 && *Generator_id2 == 21) || (*Generator_id1 == 21 && *Generator_id2 == -1) || 
                (*Generator_id1 == -2 && *Generator_id2 == 21) || (*Generator_id1 == 21 && *Generator_id2 == -2))
        partonicChan = "ubarg_dbarg";
    SafeHistFill(histMap1D_, (partonicChan+"_ZMass").c_str(), channel_, variation.first, zCand.mass(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_yZ").c_str(), channel_, variation.first, zCand.Rapidity(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_ptZ").c_str(), channel_, variation.first, zCand.pt(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_ptl1").c_str(), channel_, variation.first, lep1.pt(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_etal1").c_str(), channel_, variation.first, lep1.eta(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_phil1").c_str(), channel_, variation.first, lep1.phi(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_ptl2").c_str(), channel_, variation.first, lep2.pt(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_etal2").c_str(), channel_, variation.first, lep2.eta(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_phil2").c_str(), channel_, variation.first, lep2.phi(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_nJets").c_str(), channel_, variation.first, jets.size(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_MET").c_str(), channel_, variation.first, genMet.pt(), weight);
    SafeHistFill(histMap1D_, (partonicChan+"_HT").c_str(), channel_, variation.first, ht, weight);
    for (size_t i = 1; i <= 3; i++) {
        if (jets.size() >= i ) {
            const auto& jet = jets.at(i-1);
            SafeHistFill(histMap1D_, (partonicChan+"_ptj"+std::to_string(i)).c_str(), channel_, variation.first, jet.pt(), weight);
            SafeHistFill(histMap1D_, (partonicChan+"_etaj"+std::to_string(i)).c_str(), channel_, variation.first, jet.eta(), weight);
            SafeHistFill(histMap1D_, (partonicChan+"_phij"+std::to_string(i)).c_str(), channel_, variation.first, jet.phi(), weight);
        }  
    }
}

