#ifndef FRAME_H
#define FRAME_H
#include "wk_MG5gen/tool/interface/Basic.h"
#include "wk_MG5gen/tool/interface/Hists_lib.h"
#include "wk_MG5gen/tool/interface/CalAcp_lib.h"

#define MAX_Particle_NO 256

using namespace std;


//--- Add in content of about time ---//
enum time_option { day , hour , minute };	//{0,1,2}
string get_time_str(time_option opt);

//--- some tool function ---//

class GenEvent
{
public:
	int Size;

	float Px[ MAX_Particle_NO ];
	float Py[ MAX_Particle_NO ];
	float Pz[ MAX_Particle_NO ];
	float E[ MAX_Particle_NO ];

	int idx[ MAX_Particle_NO ];
	int PdgID[ MAX_Particle_NO ];
   	int Mo[ MAX_Particle_NO ];

	void Register( TChain* chain, const string& name = "GenEvent" )
	{
		chain->SetBranchAddress( ( name + ".Size" ).c_str(), &Size );
		chain->SetBranchAddress( ( name + ".PdgID" ).c_str(), PdgID );
		chain->SetBranchAddress( ( name + ".Mo" ).c_str(), Mo );
		
		chain->SetBranchAddress( ( name + ".Px" ).c_str(), Px );
		chain->SetBranchAddress( ( name + ".Py" ).c_str(), Py );
		chain->SetBranchAddress( ( name + ".Pz" ).c_str(), Pz );
		chain->SetBranchAddress( ( name + ".E" ).c_str(), E );
	}

};

class Selector
{
private:
	GenEvent evt;
	TChain* MGtree;
	string SetName;
	string mode;
	int total_entries;
	int pass_sel;
	
	// in 1 event //
	TLorentzVector* particle;	//particle after selection
	int Size;
	
public:
	
	Selector()
	{
		mode = "normal";
		total_entries = 0;
		pass_sel = 0;
		SetName = "";
		
		Size = 0;
	}

	Selector( TChain* ch, const string& sn )
	{
		mode = "normal";
		total_entries = 0;
		pass_sel = 0;
		SetName = sn;
		MGtree = ch;
		
		Size = 0;
	}

	void SetMode( const string& m ) { mode = m; }
	bool Init( const string& m );
	
	//--- member function in 1 event ---//

	void InitEvent();
	void Get_Entry( int i ) {	MGtree->GetEntry(i);	}
	//usually used after selection
	void ConvertToP4();
	void EndEvent() { delete [] particle; Size = 0; }

	void B1993( const string& option );
	void TP_dilep( const string& option );
	//void B1998( const string& option );

	//void TP_Dilep();
/*
	//use this method to fill into outside histagram
	void FillAcp( Hists_Acp& h, double& v, double& w )
	{
		h.FillIn(v,w);
	}
*/
};

//--- Use ---//
//
// Init() ->   B1993()     ->
//				 V
//			 for loop in it
//			 	 V
//			 sel_B1993()
//
// Init() ->      TP()     ->
// 				   V
// 	intialize Hists_Acp in it and Draw


#endif //FRAME_H
