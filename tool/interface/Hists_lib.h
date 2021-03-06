#ifndef HISTS_LIB_H
#define HISTS_LIB_H

/***************************************************************************
 *
 *	FileName : Hists.h
 *	Description : Make a class to wrap histagrams we want to use 
 *	Date : 2019 Nov 8 ~
 *	Author : Chen-Yu Chuang
 *
 * ************************************************************************/

#include "wk_MG5gen/tool/interface/Basic.h"
#include "TH1.h"
#include "TH2.h"
#include "TNtuple.h"
#include "TNtupleD.h"
#include "TFile.h"
#include <map>
#include <vector>
#include <iostream>

using namespace std;

inline double t_IntegralTH1( const TH1* h ) { return h->Integral(1,h->GetXaxis()->GetNbins()+1); }

inline void NormalizeTH1( TH1* h ) { h->Scale( (double)1./t_IntegralTH1( h ) ); }

inline double GetAcpErr( const double& Np, const double& Nn )
{	return sqrt( ( 4 * Np * Nn ) / pow( ( Np + Nn ), 3 ) );	}


//maybe we can use a mother class and inheritance, and the bins_No,hist_min/max are the mother member, and  Init(),WriteIn() are virtual functions! 

class Hists_General_Acp
{
public:
	string mode;
	bool is_init;
	int N_Obs;

	//for init option = "n1"
	
	TH1D* h_Obs_mu_P;
	TH1D* h_Obs_mu_N;
	TH1D* h_Obs_el_P;
	TH1D* h_Obs_el_N;
	
	TH1D* h_Acp_t;
	TH1D* h_Acp_mu;
	TH1D* h_Acp_el;
	
	//for "n2"
	// for more robust 1998's observable , ex. { [( N> - N< )/( N> + N< )]setA - [( N'> - N'< )/( N'> + N'< )]setA' }
	TH1D* h_Obs_mu1_P;
	TH1D* h_Obs_mu1_N;
	TH1D* h_Obs_el1_P;
	TH1D* h_Obs_el1_N;
	
	TH1D* h_Obs_mu2_P;
	TH1D* h_Obs_mu2_N;
	TH1D* h_Obs_el2_P;
	TH1D* h_Obs_el2_N;

	TH1D* h_Acp_t1;
	TH1D* h_Acp_t2;
	TH1D* h_Acp_mu1;
	TH1D* h_Acp_mu2;
	TH1D* h_Acp_el1;
	TH1D* h_Acp_el2;

	Hists_General_Acp() 
	{
		mode = "n1";
		is_init = false;
		N_Obs = 4;
	}

	Hists_General_Acp( const string& m, const int& n ) 
	{ 
		mode = m;
		is_init = false;
		N_Obs = n;
	}

	~Hists_General_Acp()
	{
		if( is_init )
		{
			if( mode == "n1" )
			{
				delete h_Obs_mu_P;
				delete h_Obs_mu_N;
				delete h_Obs_el_P;
				delete h_Obs_el_N;

				delete h_Acp_t;
				delete h_Acp_mu;
				delete h_Acp_el;
			}
			else if( mode == "n2" )
			{
				delete h_Obs_mu1_P;
				delete h_Obs_mu1_N;
				delete h_Obs_el1_P;
				delete h_Obs_el1_N;

				delete h_Obs_mu2_P;
				delete h_Obs_mu2_N;
				delete h_Obs_el2_P;
				delete h_Obs_el2_N;

				delete h_Acp_t1;
				delete h_Acp_mu1;
				delete h_Acp_el1;
				delete h_Acp_t2;
				delete h_Acp_mu2;
				delete h_Acp_el2;
			}
/*
			else if( mode == "all" )
			{
				delete h_Acp_t;
				delete h_Acp_mu;
				delete h_Acp_el;
				
				delete h_Acp_t1;
				delete h_Acp_mu1;
				delete h_Acp_el1;
				delete h_Acp_t2;
				delete h_Acp_mu2;
				delete h_Acp_el2;
			}
*/
		}

	}

	void SetMode( const string& m ) { mode = m; }
	void SetNObs( const int& n ) { N_Obs = n; }

	void Init( const string& option );
	void FillIn( const int& obs_idx, const string& ch, const double& obs_value, const double& weight, const string& set );
	// obs_idx : which obs in this sets of observables
	// ch : channel ( just work in semi-leptonic case )
	// set : setA and setAbar, for semi-leptonic case
	void Cal_Acp();
	void WriteIn();
};

class Hists_DilepAcp
{
public:

	double N_Obs1_t_P;
	double N_Obs1_t_N;

	double N_Obs3_t_P;
	double N_Obs3_t_N;

	TH1D* h_Obs_t_P;
	TH1D* h_Obs_t_N;

	TH1D* h_Acp_t;

	void Init( const string& option );
	void FillIn( const string& option, const string& ch, const double& obs_value, const double& weight );
	void Cal_Acp();
	void WriteIn();

};


class Hists_Acp
{
public:

	//just for statistical!
	TH1D* h_Obs3_mu_P;
	TH1D* h_Obs3_mu_N;
	TH1D* h_Obs6_mu_P;
	TH1D* h_Obs6_mu_N;
	TH1D* h_Obs12_mu_P;
	TH1D* h_Obs12_mu_N;
	TH1D* h_Obs13_mu_P;
	TH1D* h_Obs13_mu_N;
	
	TH1D* h_Obs3_el_P;
	TH1D* h_Obs3_el_N;
	TH1D* h_Obs6_el_P;
	TH1D* h_Obs6_el_N;
	TH1D* h_Obs12_el_P;
	TH1D* h_Obs12_el_N;
	TH1D* h_Obs13_el_P;
	TH1D* h_Obs13_el_N;

	map<string, TH1D*> h_Obs3_P, h_Obs3_N, h_Obs6_P, h_Obs6_N, h_Obs12_P, h_Obs12_N, h_Obs13_P, h_Obs13_N;

	TH1D* h_Obs_mu_P;
	TH1D* h_Obs_mu_N;
	TH1D* h_Obs_el_P;
	TH1D* h_Obs_el_N;
	
	TH1D* h_Obs_t_P;
	TH1D* h_Obs_t_N;

	map<string, TH1D*> h_Obs_P, h_Obs_N;

	void Init( const string& );		//default is "all"
	void InitMap();

	void FillIn( const string& option, const string& ch, const double& obs, const double& weight );
	void WriteIn();
};



class Hists
{
public:
	
	Hists()
	{
		bins_No = 50;
		hist_min = 0.;
		hist_max = 500.;
		AxisInfo = " ;M_{jjb} Mass(GeV);Events(No.)";
		AxisInfo2 = " ;M_{lb} Mass(GeV);Events(No.)";

	}
	~Hists() {}


	int bins_No;
	double hist_min;
	double hist_max;
	string AxisInfo;
	string AxisInfo2;

	vector<TH1F*> h_mu, h_el, h_l_mu, h_l_el;

	TH1F* h_TT_mu;		TH1F* h_TT_el;	
	TH1F* h_DY_mu;		TH1F* h_DY_el;
	TH1F* h_WJets_mu;	TH1F* h_WJets_el;
	TH1F* h_VV_mu;		TH1F* h_VV_el;
	TH1F* h_ST_mu;		TH1F* h_ST_el;
	TH1F* h_QCD_mu;		TH1F* h_QCD_el;
	TH1F* h_Data_mu;	TH1F* h_Data_el;

	TH1F* h_l_TT_mu;	TH1F* h_l_TT_el;
	TH1F* h_l_DY_mu;	TH1F* h_l_DY_el;
	TH1F* h_l_WJets_mu;	TH1F* h_l_WJets_el;
	TH1F* h_l_VV_mu;	TH1F* h_l_VV_el;
	TH1F* h_l_ST_mu;	TH1F* h_l_ST_el;
	TH1F* h_l_QCD_mu;	TH1F* h_l_QCD_el;
	TH1F* h_l_Data_mu;	TH1F* h_l_Data_el;

	vector<TH1F*> h_mu_c, h_el_c, h_l_mu_c, h_l_el_c;

	TH1F* h_TT_mu_c;		TH1F* h_TT_el_c;	
	TH1F* h_DY_mu_c;		TH1F* h_DY_el_c;
	TH1F* h_WJets_mu_c;		TH1F* h_WJets_el_c;
	TH1F* h_VV_mu_c;		TH1F* h_VV_el_c;
	TH1F* h_ST_mu_c;		TH1F* h_ST_el_c;
	TH1F* h_QCD_mu_c;		TH1F* h_QCD_el_c;
	TH1F* h_Data_mu_c;		TH1F* h_Data_el_c;

	TH1F* h_l_TT_mu_c;		TH1F* h_l_TT_el_c;
	TH1F* h_l_DY_mu_c;		TH1F* h_l_DY_el_c;
	TH1F* h_l_WJets_mu_c;	TH1F* h_l_WJets_el_c;
	TH1F* h_l_VV_mu_c;		TH1F* h_l_VV_el_c;
	TH1F* h_l_ST_mu_c;		TH1F* h_l_ST_el_c;
	TH1F* h_l_QCD_mu_c;		TH1F* h_l_QCD_el_c;
	TH1F* h_l_Data_mu_c;	TH1F* h_l_Data_el_c;

	vector<TH1F*> h_mu_cc, h_el_cc, h_l_mu_cc, h_l_el_cc;

	TH1F* h_TT_mu_cc;		TH1F* h_TT_el_cc;	
	TH1F* h_DY_mu_cc;		TH1F* h_DY_el_cc;
	TH1F* h_WJets_mu_cc;	TH1F* h_WJets_el_cc;
	TH1F* h_VV_mu_cc;		TH1F* h_VV_el_cc;
	TH1F* h_ST_mu_cc;		TH1F* h_ST_el_cc;
	TH1F* h_QCD_mu_cc;		TH1F* h_QCD_el_cc;
	TH1F* h_Data_mu_cc;		TH1F* h_Data_el_cc;

	TH1F* h_l_TT_mu_cc;		TH1F* h_l_TT_el_cc;
	TH1F* h_l_DY_mu_cc;		TH1F* h_l_DY_el_cc;
	TH1F* h_l_WJets_mu_cc;	TH1F* h_l_WJets_el_cc;
	TH1F* h_l_VV_mu_cc;		TH1F* h_l_VV_el_cc;
	TH1F* h_l_ST_mu_cc;		TH1F* h_l_ST_el_cc;
	TH1F* h_l_QCD_mu_cc;	TH1F* h_l_QCD_el_cc;
	TH1F* h_l_Data_mu_cc;	TH1F* h_l_Data_el_cc;

	TH2D* h_mvamax_hadmass_mu;		//with hadmass
	TH2D* h_mvamax_hadmass_el;
	TH2D* h_mvamax_lepmass_mu;		//with lepmass
	TH2D* h_mvamax_lepmass_el;
	map<string, TH2D*> h_mvamax_hadmass, h_mvamax_lepmass;
	//double algo_v_min;
	//double algo_v_max;

	TNtupleD* mvav_mass_mu;
	TNtupleD* mvav_mass_el;
	map<string, TNtupleD*> mvav_mass;

	//used before init hists
	void SetBinInfo( const int& n, const double& m, const double& M  ){
		bins_No = n;	
		hist_min = m;	
		hist_max = M;
	}

	//used before init hists
	void SetAxisInfo( const string& input1, const string& input2 )
	{
		AxisInfo = input1;
		AxisInfo2 = input2;
	}
/*
	void SetAxisTitle( const string& x, const string& y, const string total= "" )
	{
		h_Data
	}
*/

	//for fill and use new things
	void NoCutModeON();
	void OneCutModeON();
	void TwoCutModeON();
	void InitNoCutVector();
	void InitOneCutVector();
	void InitTwoCutVector();

	void TH2ModeON( const int& algo_bins_No, const double&, const double&);

	void NtupleModeON(){
		mvav_mass_mu = new TNtupleD( "mvav_mass_mu", "store event by event", "max_mva_value:hadt_mass:lept_mass:weight:dataset" );
		mvav_mass_el = new TNtupleD( "mvav_mass_el", "store event by event", "max_mva_value:hadt_mass:lept_mass:weight:dataset" );
		mvav_mass[ "mu" ] = mvav_mass_mu;
		mvav_mass[ "el" ] = mvav_mass_el;
	}

	void WriteIn( const string& option );
	
	//for plots or some applicatin
	void GetObjs( string& file_name, string& option );

	void FillHist( const string&, const int&, const string&, const double&, const double&, const double& );
	//how many cut, k(which sample), channel name, hadmass, lepmass, weight

};

class Hists_bb
{
public:
	
	Hists_bb()
	{
		bins_No1 = 50;
		hist_min1 = 0.;
		hist_max1 = 1.;
		
		bins_No2 = 100;
		hist_min2 = 0.;
		hist_max2 = 500.;

		no_match_number = 0;
	}
	~Hists_bb() {}
	
	map<string,TH1F*> h_correct, h_charge_mis, h_mistag, h_lt_correct, h_lt_charge_mis, h_lt_mistag;
	map<string, TH2D*> h_mvamax_mass;
	
	TH2D* h_mvamax_mass_mu;
	TH2D* h_mvamax_mass_el;
	TH2D* h_mvamax_mass_t;

	TH1F* h_correct_t;
	TH1F* h_mistag_t;
	TH1F* h_charge_mis_t;

	TH1F* h_correct_mu;
	TH1F* h_mistag_mu;
	TH1F* h_charge_mis_mu;

	TH1F* h_correct_el;
	TH1F* h_mistag_el;
	TH1F* h_charge_mis_el;

	TH1F* h_lt_correct_t;
	TH1F* h_lt_mistag_t;
	TH1F* h_lt_charge_mis_t;

	TH1F* h_lt_correct_mu;
	TH1F* h_lt_mistag_mu;
	TH1F* h_lt_charge_mis_mu;

	TH1F* h_lt_correct_el;
	TH1F* h_lt_mistag_el;
	TH1F* h_lt_charge_mis_el;

	int no_match_number;

	//for algo value
	int bins_No1;
	double hist_min1;
	double hist_max1;
	//for Mlb
	int bins_No2;
	double hist_min2;
	double hist_max2;

	void SetAlgoBin( const int& n, const double& m, const double& M ){
		bins_No1 = n;	
		hist_min1 = m;	
		hist_max1 = M;
	}
	void Init();
	void WriteIn();
};

class Hists_cor
{
public:

	Hists_cor()
	{
		bins_No1 = 100;	
		hist_min1 = 0.;	
		hist_max1 = 1.;
	}

	~Hists_cor(){}

	//for store	mva
	map<string, TH1F*> h_max_mva, h_max_mva_cor, h_max_mva_incor;
	
	TH1F* h_max_mva_mu;
	TH1F* h_max_mva_cor_mu;
	TH1F* h_max_mva_incor_mu;
		
	TH1F* h_max_mva_el;
	TH1F* h_max_mva_cor_el;
	TH1F* h_max_mva_incor_el;

	TH1F* h_max_mva_t;
	TH1F* h_max_mva_cor_t;
	TH1F* h_max_mva_incor_t;

	int bins_No1;
	double hist_min1;
	double hist_max1;
	
	//for store to calculate Poisson error
	//chosen -> 'all': pass full-sel / 'part': pass full-sel and pass gen-matching		
	//cor -> pass 'all'/'pass' and it's correct permutation(combination)
	
	map<string, TH1F*> h_chosen, h_cor;
	
	TH1F* h_chosen_mu;
	TH1F* h_cor_mu;
		
	TH1F* h_chosen_el;
	TH1F* h_cor_el;
	
	TH1F* h_chosen_t;
	TH1F* h_cor_t;
	
	void SetAlgoBin( const int& n, const double& m, const double& M ){
		bins_No1 = n;	
		hist_min1 = m;	
		hist_max1 = M;
	}
	void Init();
	void WriteIn();

};

#endif
