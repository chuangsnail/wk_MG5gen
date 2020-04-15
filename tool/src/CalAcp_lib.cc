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


double DilepAcpMgr::Get_4D_LeviCivita( const TLorentzVector& a, const TLorentzVector& b, const TLorentzVector& c, const TLorentzVector& d )
{
	double res = 0.;
	res = res + a.E() * b.Px() * c.Py() * d.Pz();
	res = res + b.E() * c.Px() * d.Py() * a.Pz();
	res = res + c.E() * d.Px() * a.Py() * b.Pz();
	res = res + d.E() * a.Px() * b.Py() * c.Pz();
	
	res = res - d.E() * c.Px() * b.Py() * a.Pz();
	res = res - c.E() * b.Px() * a.Py() * d.Pz();
	res = res - b.E() * a.Px() * d.Py() * c.Pz();
	res = res - a.E() * d.Px() * c.Py() * b.Pz();

	return res;
}

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
		return Get_4D_LeviCivita( ( p_b + p_lepp + p_nuep ), ( p_bbar + p_lepn + p_nuen ), p_lepp, p_lepn );
	}
	else if( option == "directly" ) {
		return Get_4D_LeviCivita( p_t, p_tbar, p_lepp, p_lepn );
	}
	else
		return 0.;
}

double DilepAcpMgr::Obs3()
{
	return Get_4D_LeviCivita( p_b, p_bbar, p_lepp, p_lepn );
}
