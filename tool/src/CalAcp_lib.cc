#include "wk_MG5gen/tool/interface/CalAcp_lib.h"

using namespace std;

void AcpMgr::InputSelObjs( const TLorentzVector& hadb, const TLorentzVector& lepb, const TLorentzVector& hardjet, const TLorentzVector& isolep, const double& LepCharge )
{
	lep_charge = LepCharge;
	if( lep_charge > 0. )
	{
		SetLorentzVector( lepb, "b" );
		SetLorentzVector( hadb, "bbar" );
	}
	else
	{
		SetLorentzVector( hadb, "b" );
		SetLorentzVector( lepb, "bbar" );
	}
	SetLorentzVector( hardjet, "j1" );
	SetLorentzVector( isolep, "lep" );
	ConvertToVect();
}

void AcpMgr::SetLorentzVector( const TLorentzVector& v, const string& option = "jet" )
{
	if( option == "b" )
	{		b = v;		}
	else if( option == "bbar" )
	{		bbar = v;	}
	else if( option == "j1" )
	{		j1 = v;		}
	else if( option == "lep" )
	{		lep = v;	}
	else
	{	cerr << "There is no option \'" << option << "\'" << endl;	}
}

void AcpMgr::ConvertToVect()
{
	_b = 		b.Vect();
	_bbar =		bbar.Vect();
	_j1 = 		j1.Vect();
	_lep = 		lep.Vect();
}

void AcpMgr::BoostAll( const TVector3& cm )
{
	b.Boost( cm );
	bbar.Boost( cm );
	j1.Boost( cm );
	lep.Boost( cm );
}

double AcpMgr::Obs3()
{
	TVector3 bbcm = -( b + bbar ).BoostVector();
	BoostAll( bbcm );
	
	double res = lep_charge * ( ( b.Vect() ).Dot( ( lep.Vect() ).Cross( j1.Vect() ) ) ) ;
	if( res == 0 ) return DBL_MAX;
	//return (res > 0) ? 1 : -1;
	return res;
}

double AcpMgr::Obs6()
{
	double res = lep_charge * ( ( _b - _bbar ).Dot( _lep.Cross( _j1 ) ) );
	if( res == 0 ) return DBL_MAX;
	//return (res > 0) ? 1 : -1;
	return res;
}

double AcpMgr::Obs12()
{
	double res = ( _b - _bbar ).Pz() * ( _b.Cross( _bbar ) ).Pz() ;
	if( res == 0 ) return DBL_MAX;
	//return (res > 0) ? 1 : -1;
	return res;
}

double AcpMgr::Obs13()
{
	double res = lep_charge * ( ( _b + _bbar ).Dot( _lep.Cross( _j1 ) ) );
	//double res = ( ( _b + _bbar ).Dot( _lep.Cross( _j1 ) ) );
	if( res == 0. ) return DBL_MAX;
	//return (res > 0) ? 1 : -1;
	return res;
}

//--- DilepAcpMgr ---//


void DilepAcpMgr::Input_ttbar( const TLorentzVector& t, const TLorentzVector& tbar )
{
	p_t = t;
	p_tbar = tbar;
}

void DilepAcpMgr::InputSelObjs( const TLorentzVector& b, const TLorentzVector& bbar, const TLorentzVector& lepp, const TLorentzVector& nuep, const TLorentzVector& lepn, const TLorentzVector& nuen  )
{
	p_b = b;
	p_bbar = bbar;
	p_lepp = lepp;
	p_nuep = nuep;
	p_lepn = lepn;
	p_nuen = nuen;
}

double DilepAcpMgr::Obs1( const string& option = "seperately" )
{
	if( option == "seperately" ) {
		return Phys::Get_4D_LeviCivita( ( p_b + p_lepp + p_nuep ), ( p_bbar + p_lepn + p_nuen ), p_lepp, p_lepn );
	}
	else if( option == "directly" ) {
		return Phys::Get_4D_LeviCivita( p_t, p_tbar, p_lepp, p_lepn );
	}
	else
		return 0.;
}

double DilepAcpMgr::Obs3()
{
	return Phys::Get_4D_LeviCivita( p_b, p_bbar, p_lepp, p_lepn );
}


//--- AcpMgr_1998 ---//

void AcpMgr_1998::Input_ttbar( const TLorentzVector& t, const TLorentzVector& tbar )
{
	p_t = t;
	p_tbar = tbar;
}
void AcpMgr_1998::Input_bbbar( const TLorentzVector& b, const TLorentzVector& bbar )
{
	p_b = b;
	p_bbar = bbar;
}
	
//for semi-leptonic

void AcpMgr_1998::Input_j1j2( const TLorentzVector& j1, const TLorentzVector& j2 )
{
	p_j1 = j1;
	p_j2 = j2;
}
void AcpMgr_1998::AcpMgr_1998::Input_lep( const TLorentzVector& lep ) 
{	
	p_lep = lep;
}
void AcpMgr_1998::Input_neu( const TLorentzVector& neu ) {	p_neu = neu;	}

//for dilep
void AcpMgr_1998::Input_lepp( const TLorentzVector& lepp ) {	p_lepp = lepp;	}
void AcpMgr_1998::Input_neup( const TLorentzVector& neup ) {	p_neup = neup;	}
void AcpMgr_1998::Input_lepn( const TLorentzVector& lepn ) {	p_lepn = lepn;	}
void AcpMgr_1998::Input_neun( const TLorentzVector& neun ) {	p_neun = neun;	}

void AcpMgr_1998::BoostLepton( const string& frame = "ttbar" )
{
	if( frame == "partonCM" )
	{
		//TVector3 partoncm = 
	}
	else if( frame == "ttbar" )
	{
		TVector3 ttcm = -( p_t + p_tbar ).BoostVector();
		if( ch.find("semi") != string::npos )
		{
			p_lep.Boost( ttcm );
		}
		else if( ch.find("di") != string::npos )
		{
			p_lepp.Boost( ttcm );
			p_lepn.Boost( ttcm );
		}
	}
}

void AcpMgr_1998::Preparation()
{
	if( ch == "None" ) return;
	BoostLepton( "ttbar" );
}

double AcpMgr_1998::O1( const string& opt = "Ot" )
{
	if( ch.find("semi") != string::npos )
	{
		if( opt == "Ot" )
		{
			return ( p_t.Vect().Unit() ).Dot( p_lep.Vect().Unit() );
		}
		else if( opt == "Otb" )
		{
			return ( p_tbar.Vect().Unit() ).Dot( p_lep.Vect().Unit() );
		}
	}
	else if( ch.find("di") != string::npos )
	{
		return ( p_t.Vect().Unit() ).Dot( p_lepp.Vect().Unit() ) - ( p_tbar.Vect().Unit() ).Dot( p_lepn.Vect().Unit() ); 
	}

	return 0.;
}

double AcpMgr_1998::O2( const string& opt = "Ot" )
{
	if( ch.find("semi") != string::npos )
	{
		if( opt == "Ot" )
		{
				
		}
		else if( opt == "Otb" )
		{
			
		}
	}
	else if( ch.find("di") != string::npos )
	{
		
	}
	return 0.;

}
