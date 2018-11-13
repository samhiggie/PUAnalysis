class scenario_info {
 private:
  Float_t tau1_pt,tau1_eta,tau1_phi,tau1_m;
  Float_t tau2_pt,tau2_eta,tau2_phi,tau2_m;
  Float_t jpt_1, jpt_2;

 public:
  scenario_info (TTree*, std::string);
  virtual ~scenario_info () {};

  Float_t get_tau1_pt()  { return tau1_pt;  };
  Float_t get_tau1_eta() { return tau1_eta; };
  Float_t get_tau1_phi() { return tau1_phi; };
  Float_t get_tau1_m()   { return tau1_m;   };
  Float_t get_tau2_pt()  { return tau2_pt;  };
  Float_t get_tau2_eta() { return tau2_eta; };
  Float_t get_tau2_phi() { return tau2_phi; };
  Float_t get_tau2_m()   { return tau2_m;   };
  Float_t get_jpt_1()    { return jpt_1;    };
  Float_t get_jpt_2()    { return jpt_2;    };
  
};


// read tau and jets from trees
scenario_info::scenario_info(TTree* tree, std::string unc) {
  // set nominal as a defalt
  std::string tau1_pt_unc = "tau1_pt";
  std::string tau1_eta_unc = "tau1_eta";
  std::string tau1_phi_unc = "tau1_phi";
  std::string tau1_m_unc = "tau1_m";
  std::string tau2_pt_unc = "tau2_pt";
  std::string tau2_eta_unc = "tau2_eta";
  std::string tau2_phi_unc = "tau2_phi";
  std::string tau2_m_unc = "tau2_m";
  std::string jpt_1_unc = "jpt_1";
  std::string jpt_2_unc = "jpt_2";

  std::cout << "-------------- " << unc << " --------------" << std::endl;
  // if branches for unc is availble, replace to them
  if (unc=="nominal") unc = "";
  else unc = "_"+unc;
  TIter next(tree->GetListOfBranches());
  TBranch *branch;
  while ((branch = (TBranch*)next())) {
    if ((tau1_pt_unc+unc)==branch->GetName())             tau1_pt_unc=branch->GetName();
    else if ((tau1_eta_unc+unc)==branch->GetName())       tau1_eta_unc=branch->GetName();
    else if ((tau1_phi_unc+unc)==branch->GetName())       tau1_phi_unc=branch->GetName();
    else if ((tau1_m_unc+unc)==branch->GetName())         tau1_m_unc=branch->GetName();
    else if ((tau2_pt_unc+unc)==branch->GetName())        tau2_pt_unc=branch->GetName();
    else if ((tau2_eta_unc+unc)==branch->GetName())       tau2_eta_unc=branch->GetName();
    else if ((tau2_phi_unc+unc)==branch->GetName())       tau2_phi_unc=branch->GetName();
    else if ((tau2_m_unc+unc)==branch->GetName())         tau2_m_unc=branch->GetName();
    else if ((jpt_1_unc+unc)==branch->GetName())          jpt_1_unc=branch->GetName();
    else if ((jpt_2_unc+unc)==branch->GetName())          jpt_2_unc=branch->GetName();
  }
  // print used tau and jet kinematics
  std::cout << tau1_pt_unc << std::endl;
  std::cout << tau1_eta_unc << std::endl;
  std::cout << tau1_phi_unc << std::endl;
  std::cout << tau1_m_unc << std::endl;
  std::cout << tau2_pt_unc << std::endl;
  std::cout << tau2_eta_unc << std::endl;
  std::cout << tau2_phi_unc << std::endl;
  std::cout << tau2_m_unc << std::endl;
  std::cout << jpt_1_unc << std::endl;
  std::cout << jpt_2_unc << std::endl;
  std::cout << "-------------- used kinematics --------------" << std::endl << std::endl;

  // pick up printed branches
  tree -> SetBranchAddress( tau1_pt_unc.c_str()  , &tau1_pt  );
  tree -> SetBranchAddress( tau1_eta_unc.c_str() , &tau1_eta );
  tree -> SetBranchAddress( tau1_phi_unc.c_str() , &tau1_phi );
  tree -> SetBranchAddress( tau1_m_unc.c_str()   , &tau1_m );
  tree -> SetBranchAddress( tau2_pt_unc.c_str()  , &tau2_pt  );
  tree -> SetBranchAddress( tau2_eta_unc.c_str() , &tau2_eta );
  tree -> SetBranchAddress( tau2_phi_unc.c_str() , &tau2_phi );
  tree -> SetBranchAddress( tau2_m_unc.c_str()   , &tau2_m );
  tree -> SetBranchAddress( jpt_1_unc.c_str()    , &jpt_1    );
  tree -> SetBranchAddress( jpt_2_unc.c_str()    , &jpt_2    );

}
