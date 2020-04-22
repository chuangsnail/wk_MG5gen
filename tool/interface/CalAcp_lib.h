#ifndef CALACP_LIB_H
#define CALACP_LIB_H

#include "wk_MG5gen/tool/interface/Tool.h"

#include "TLorentzVector.h"
#include "TVector3.h"
#include "TVector2.h"

#include <climits>
#include <vector>
#include <iostream>
#include <string>
#include "string.h"

using namespace std;

class AcpMgr
{
private:

	TLorentzVector b;
	TLorentzVector bbar;
	TLorentzVector j1;
	TLorentzVector lep;

	double lep_charge;

	TVector3 _b;
	TVector3 _bbar;
	TVector3 _j1;
	TVector3 _lep;
	
	void ConvertToVect();
	void BoostAll( const TVector3& );

public:
	
	AcpMgr()
	{
		lep_charge = 0.;
	}

	void SetLorentzVector( const TLorentzVector&, const string& );
	
	void InputSelObjs( const TLorentzVector& hadb, const TLorentzVector& lepb, const TLorentzVector& hardjet, const TLorentzVector& isolep, const double& LepCharge );
	
	double Obs3();
	double Obs6();
	double Obs12();
	double Obs13();

};


//--- DilepAcpMgr ---//

class DilepAcpMgr
{
private:
	TLorentzVector p_b;
	TLorentzVector p_bbar;
	TLorentzVector p_lepp;
	TLorentzVector p_nuep;
	TLorentzVector p_lepn;
	TLorentzVector p_nuen;

	//for Obs1 directly
	TLorentzVector p_t;
	TLorentzVector p_tbar;

public:
	
	void Input_ttbar( const TLorentzVector& t, const TLorentzVector& tbar );
	void InputSelObjs( const TLorentzVector& b, const TLorentzVector& bbar, const TLorentzVector& lepp, const TLorentzVector& nuep, const TLorentzVector& lepn, const TLorentzVector& nuen  );
	double Obs1( const string& option );
	double Obs3();

};




// To add-up all kind of Acp mgr

//class General_Semi_AcpMgr



class AcpMgr_1998
{
private:
	string ch;

	TLorentzVector p_t;
	TLorentzVector p_tbar;
	TLorentzVector p_b;
	TLorentzVector p_bbar;
	
	//used in semi-leptonic channel
	TLorentzVector p_j1;
	TLorentzVector p_j2;
	TLorentzVector p_lep;
	TLorentzVector p_neu;

	
	//used in dileptonic channel
	TLorentzVector p_lepp;
	TLorentzVector p_neup;
	TLorentzVector p_lepn;
	TLorentzVector p_neun;

public:

	AcpMgr_1998() 
	{
		ch = "None";
	}

	AcpMgr_1998( const string& opt ) 
	{
		ch = opt;			//"semilep" or "dilep"
	}

	void SetOption( const string& opt )
	{
		ch = opt;			//"semilep" or "dilep"
	}

	void Preparation();
	void BoostLepton( const string& frame );

	void Input_ttbar( const TLorentzVector& t, const TLorentzVector& tbar );
	void Input_bbbar( const TLorentzVector& b, const TLorentzVector& bbar );
	
	//for semi-leptonic
	void Input_j1j2( const TLorentzVector& j1, const TLorentzVector& j2 );
	void Input_lep( const TLorentzVector& lep );
	void Input_neu( const TLorentzVector& neu );

	//for dilep
	void Input_lepp( const TLorentzVector& lepp );
	void Input_neup( const TLorentzVector& neup );
	void Input_lepn( const TLorentzVector& lepn );
	void Input_neun( const TLorentzVector& neun );
	
	//Calculate Acp
	double O1( const string& opt );
	double O2( const string& opt );

};



#endif	//CALACP_LIB_H
