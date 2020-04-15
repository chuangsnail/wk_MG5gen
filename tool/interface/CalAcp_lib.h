#ifndef CALACP_LIB_H
#define CALACP_LIB_H

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

	double Get_4D_LeviCivita( const TLorentzVector& a, const TLorentzVector& b, const TLorentzVector& c, const TLorentzVector& d );

public:
	
	void Input_ttbar( const TLorentzVector& t, const TLorentzVector& tbar );
	void InputSelObjs( const TLorentzVector& b, const TLorentzVector& bbar, const TLorentzVector& lepp, const TLorentzVector& nuep, const TLorentzVector& lepn, const TLorentzVector& nuen  );
	double Obs1( const string& option );
	double Obs3();

};


#endif	//CALACP_LIB_H
