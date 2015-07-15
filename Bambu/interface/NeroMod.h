#ifndef NeroProducer_Bambu_NeroMod_h
#define NeroProducer_Bambu_NeroMod_h

#include "MitAna/TreeMod/interface/BaseMod.h"
#include "NeroProducer/Bambu/interface/Collections.h"
#include "NeroProducer/Bambu/interface/BaseConfig.h"
#include "NeroProducer/Bambu/interface/BaseFiller.h"
#include "NeroProducer/Core/interface/BareCollection.hpp"

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TNamed.h"

namespace mithep {

  class NeroMod : public BaseMod {
  public:
    NeroMod(char const* name = "NeroMod", char const* title = "Nero-Bambu interface");
    ~NeroMod();

    void SetTag(char const* _tag) { tag_.SetTitle(_tag); }
    void SetHead(char const* _head) { head_.SetTitle(_head); }
    void SetInfo(char const* _info) { info_.SetTitle(_info); }
    void SetFileName(char const* _name) { fileName_ = _name; }
    void AddConfig(nero::BaseConfig* _config) { config_[_config->collection()] = _config; }

  private:
    void SlaveBegin() override;
    void SlaveTerminate() override;
    void Process() override;

    TString fileName_{"nero.root"};
    TTree* eventsTree_ = 0;
    TTree* allTree_ = 0;
    TH1F* hXsec_ = 0;
    
    TNamed tag_{"tag", ""};
    TNamed head_{"head", ""};
    TNamed info_{"info", "Nero"};

    nero::BaseConfig* config_[nero::nCollections] = {};
    nero::BaseFiller* filler_[nero::nCollections] = {};
    BareCollection* collection_[nero::nCollections] = {};

    ClassDef(NeroMod, 0)
  };

}

#endif
