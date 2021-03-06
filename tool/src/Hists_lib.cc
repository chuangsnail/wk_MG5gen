
#include "wk_MG5gen/tool/interface/Hists_lib.h"

/***************************************************************************
 *
 *	FileName : Hists.cc
 *	Description : Make a class to wrap histagrams we want to use 
 *	Date : 2020 Feb 8 ~
 *	Author : Chen-Yu Chuang
 *
 * ************************************************************************/

#include <map>
#include <vector>
#include <iostream>

using namespace std;

void 
Hists_General_Acp::Init( const string& option )
{
/*
	if( mode == "all" )
	{
		h_Acp_t = new TH1D( "h_Acp_t", "", N_Obs, 0, N_Obs );
		h_Acp_mu = new TH1D( "h_Acp_mu", "", N_Obs, 0, N_Obs );
		h_Acp_el = new TH1D( "h_Acp_el", "", N_Obs, 0, N_Obs );
		
		h_Acp_t1 = new TH1D( "h_Acp_t1", "", N_Obs, 0, N_Obs );
		h_Acp_mu1 = new TH1D( "h_Acp_mu1", "", N_Obs, 0, N_Obs );
		h_Acp_el1 = new TH1D( "h_Acp_el1", "", N_Obs, 0, N_Obs );
		h_Acp_t2 = new TH1D( "h_Acp_t2", "", N_Obs, 0, N_Obs );
		h_Acp_mu2 = new TH1D( "h_Acp_mu2", "", N_Obs, 0, N_Obs );
		h_Acp_el2 = new TH1D( "h_Acp_el2", "", N_Obs, 0, N_Obs );
	}
*/
	if( mode == "n1" )
	{
		h_Obs_mu_P = new TH1D( "h_Obs_mu_P", "", N_Obs, 0, N_Obs );
		h_Obs_mu_N = new TH1D( "h_Obs_mu_N", "", N_Obs, 0, N_Obs );
		h_Obs_el_P = new TH1D( "h_Obs_el_P", "", N_Obs, 0, N_Obs );
		h_Obs_el_N = new TH1D( "h_Obs_el_N", "", N_Obs, 0, N_Obs );

		h_Acp_t = new TH1D( "h_Acp_t", "", N_Obs, 0, N_Obs );
		h_Acp_mu = new TH1D( "h_Acp_mu", "", N_Obs, 0, N_Obs );
		h_Acp_el = new TH1D( "h_Acp_el", "", N_Obs, 0, N_Obs );
	}
	else if( mode == "n2" )
	{
		h_Obs_mu1_P = new TH1D( "h_Obs_mu1_P", "", N_Obs, 0, N_Obs );
		h_Obs_mu1_N = new TH1D( "h_Obs_mu1_N", "", N_Obs, 0, N_Obs );
		h_Obs_el1_P = new TH1D( "h_Obs_el1_P", "", N_Obs, 0, N_Obs );
		h_Obs_el1_N = new TH1D( "h_Obs_el1_N", "", N_Obs, 0, N_Obs );

		h_Obs_mu2_P = new TH1D( "h_Obs_mu2_P", "", N_Obs, 0, N_Obs );
		h_Obs_mu2_N = new TH1D( "h_Obs_mu2_N", "", N_Obs, 0, N_Obs );
		h_Obs_el2_P = new TH1D( "h_Obs_el2_P", "", N_Obs, 0, N_Obs );
		h_Obs_el2_N = new TH1D( "h_Obs_el2_N", "", N_Obs, 0, N_Obs );
		
		h_Acp_t1 = new TH1D( "h_Acp_t1", "", N_Obs, 0, N_Obs );
		h_Acp_mu1 = new TH1D( "h_Acp_mu1", "", N_Obs, 0, N_Obs );
		h_Acp_el1 = new TH1D( "h_Acp_el1", "", N_Obs, 0, N_Obs );
		h_Acp_t2 = new TH1D( "h_Acp_t2", "", N_Obs, 0, N_Obs );
		h_Acp_mu2 = new TH1D( "h_Acp_mu2", "", N_Obs, 0, N_Obs );
		h_Acp_el2 = new TH1D( "h_Acp_el2", "", N_Obs, 0, N_Obs );
	}
}

void
Hists_General_Acp::FillIn( const int& obs_idx, const string& ch, const double& obs_value, const double& weight, const string& set = "A" )
{
	//obs_idx == { 0, 1, 2 ... , N_Obs -1 }
	double fill = (double)obs_idx + 0.5;
	if( mode == "n1" )
	{
		if( ch == "mu" )
		{
			if( obs_value > 0. ) {
				h_Obs_mu_P->Fill( fill, weight );
			}
			else if( obs_value < 0. ) {
				h_Obs_mu_N->Fill( fill, weight );
			}
		}
		else if( ch == "el" )
		{
			if( obs_value > 0. ) {
				h_Obs_el_P->Fill( fill, weight );
			}
			else if( obs_value < 0. ) {
				h_Obs_el_N->Fill( fill, weight );
			}
		}
	}
	else if( mode == "n2" )
	{
		if( set == "A" ) {
			if( ch == "mu" )
			{
				if( obs_value > 0. ) {
					h_Obs_mu1_P->Fill( fill, weight );
				}
				else if( obs_value < 0. ) {
					h_Obs_mu1_N->Fill( fill, weight );
				}
			}
			else if( ch == "el" )
			{
				if( obs_value > 0. ) {
					h_Obs_el1_P->Fill( fill, weight );
				}
				else if( obs_value < 0. ) {
					h_Obs_el1_N->Fill( fill, weight );
				}
			}
		}
		else if( set == "Abar" ) {
			if( ch == "mu" )
			{
				if( obs_value > 0. ) {
					h_Obs_mu2_P->Fill( fill, weight );
				}
				else if( obs_value < 0. ) {
					h_Obs_mu2_N->Fill( fill, weight );
				}
			}
			else if( ch == "el" )
			{
				if( obs_value > 0. ) {
					h_Obs_el2_P->Fill( fill, weight );
				}
				else if( obs_value < 0. ) {
					h_Obs_el2_N->Fill( fill, weight );
				}
			}
		}
	}
}

void
Hists_General_Acp::Cal_Acp()
{

}

void
Hists_General_Acp::WriteIn()
{

}

void
Hists_DilepAcp::Init( const string& option = "all" )
{
	if( option == "all" )
	{
		N_Obs1_t_P = 0.;
		N_Obs1_t_N = 0.;

		N_Obs3_t_P = 0.;
		N_Obs3_t_N = 0.;

		h_Obs_t_P = new TH1D( "h_Obs_t_P", "", 2, 0, 2 ); 
		h_Obs_t_N = new TH1D( "h_Obs_t_N", "", 2, 0, 2 );

		h_Acp_t = new TH1D( "h_Acp_t", "", 2, 0, 2 );
	}
}

void 
Hists_DilepAcp::FillIn( const string& option, const string& ch, const double& obs_value, const double& weight )
{
	if( option == "Obs1" )
	{
		if( obs_value > 0. )
		{
			N_Obs1_t_P += weight;
			h_Obs_t_P->Fill( 0.5, weight );
		}	
		else if( obs_value < 0. )
		{
			N_Obs1_t_N += weight;
			h_Obs_t_N->Fill( 0.5, weight );
		}
	}
	else if( option == "Obs3" )
	{
		if( obs_value > 0. )
		{
			N_Obs3_t_P += weight;
			h_Obs_t_P->Fill( 1.5, weight );
		}	
		else if( obs_value < 0. )
		{
			N_Obs3_t_N += weight;
			h_Obs_t_N->Fill( 1.5, weight );
		}
	}
}

void 
Hists_DilepAcp::Cal_Acp()
{
	double Acp_Obs1_t = ( N_Obs1_t_P - N_Obs1_t_N )/( N_Obs1_t_P + N_Obs1_t_N );
	double Acp_Obs3_t = ( N_Obs3_t_P - N_Obs3_t_N )/( N_Obs3_t_P + N_Obs3_t_N );

	double Err_Obs1_t = GetAcpErr( N_Obs1_t_P, N_Obs1_t_N );
	double Err_Obs3_t = GetAcpErr( N_Obs3_t_P, N_Obs3_t_N );

	h_Acp_t->SetBinContent( 1, Acp_Obs1_t );
	h_Acp_t->SetBinContent( 2, Acp_Obs3_t );

	h_Acp_t->SetBinError( 1, Err_Obs1_t );
	h_Acp_t->SetBinError( 2, Err_Obs3_t );
}

void 
Hists_DilepAcp::WriteIn()
{
	h_Obs_t_P->Write();
	h_Obs_t_N->Write();

	h_Acp_t->Write();
}


void
Hists_Acp::Init( const string& option = "all" )
{
	if( option.find( "div" ) != string::npos )
	{
		h_Obs3_mu_P = new TH1D( "h_Obs3_mu_P", "", 2, 0.5, 2.5 ); 
		h_Obs3_mu_N = new TH1D( "h_Obs3_mu_N", "", 2, 0.5, 2.5 );
		h_Obs6_mu_P = new TH1D( "h_Obs6_mu_P", "", 2, 0.5, 2.5 ); 
		h_Obs6_mu_N = new TH1D( "h_Obs6_mu_N", "", 2, 0.5, 2.5 );
		h_Obs12_mu_P = new TH1D( "h_Obs12_mu_P", "", 2, 0.5, 2.5 ); 
		h_Obs12_mu_N = new TH1D( "h_Obs12_mu_N", "", 2, 0.5, 2.5 );
		h_Obs13_mu_P = new TH1D( "h_Obs13_mu_P", "", 2, 0.5, 2.5 ); 
		h_Obs13_mu_N = new TH1D( "h_Obs13_mu_N", "", 2, 0.5, 2.5 );

		h_Obs3_el_P = new TH1D( "h_Obs3_el_P", "", 2, 0.5, 2.5 ); 
		h_Obs3_el_N = new TH1D( "h_Obs3_el_N", "", 2, 0.5, 2.5 );
		h_Obs6_el_P = new TH1D( "h_Obs6_el_P", "", 2, 0.5, 2.5 ); 
		h_Obs6_el_N = new TH1D( "h_Obs6_el_N", "", 2, 0.5, 2.5 );
		h_Obs12_el_P = new TH1D( "h_Obs12_el_P", "", 2, 0.5, 2.5 ); 
		h_Obs12_el_N = new TH1D( "h_Obs12_el_N", "", 2, 0.5, 2.5 );
		h_Obs13_el_P = new TH1D( "h_Obs13_el_P", "", 2, 0.5, 2.5 ); 
		h_Obs13_el_N = new TH1D( "h_Obs13_el_N", "", 2, 0.5, 2.5 );
	}
	if( option.find( "all" ) != string::npos )
	{
		h_Obs_mu_P = new TH1D( "h_Obs_mu_P", "", 5, 0, 5 ); 
		h_Obs_mu_N = new TH1D( "h_Obs_mu_N", "", 5, 0, 5 );
		h_Obs_el_P = new TH1D( "h_Obs_el_P", "", 5, 0, 5 ); 
		h_Obs_el_N = new TH1D( "h_Obs_el_N", "", 5, 0, 5 );
		h_Obs_t_P = new TH1D( "h_Obs_t_P", "", 5, 0, 5 ); 
		h_Obs_t_N = new TH1D( "h_Obs_t_N", "", 5, 0, 5 );
	}

	InitMap();
}

void 
Hists_Acp::InitMap()
{
	h_Obs3_P[ "mu" ] = h_Obs3_mu_P;			h_Obs3_N[ "mu" ] = h_Obs3_mu_N;
	h_Obs6_P[ "mu" ] = h_Obs6_mu_P;			h_Obs6_N[ "mu" ] = h_Obs6_mu_N;
	h_Obs12_P[ "mu" ] = h_Obs12_mu_P;		h_Obs12_N[ "mu" ] = h_Obs12_mu_N;
	h_Obs13_P[ "mu" ] = h_Obs13_mu_P;		h_Obs13_N[ "mu" ] = h_Obs13_mu_N;
	
	h_Obs3_P[ "el" ] = h_Obs3_el_P;			h_Obs3_N[ "el" ] = h_Obs3_el_N;
	h_Obs6_P[ "el" ] = h_Obs6_el_P;			h_Obs6_N[ "el" ] = h_Obs6_el_N;
	h_Obs12_P[ "el" ] = h_Obs12_el_P;		h_Obs12_N[ "el" ] = h_Obs12_el_N;
	h_Obs13_P[ "el" ] = h_Obs13_el_P;		h_Obs13_N[ "el" ] = h_Obs13_el_N;

	h_Obs_P[ "mu" ] = h_Obs_mu_P;			h_Obs_N[ "mu" ] = h_Obs_mu_N;
	h_Obs_P[ "el" ] = h_Obs_el_P;			h_Obs_N[ "el" ] = h_Obs_el_N;
}

void Hists_Acp::
FillIn( const string& option, const string& ch , const double& obs, const double& weight )
{

	if( obs == DBL_MAX ) return;
	int cp = 1;
	if( obs > 0 ) 
	{
		cp = 1;
	}
	else
	{	
		cp = -1;
	}

	if( option == "Obs3" )
	{
		if( cp == 1 )
		{
			h_Obs_t_P->Fill( 1., weight );
			h_Obs_P[ ch ]->Fill( 1., weight );
		}
		else
		{
			h_Obs_t_N->Fill( 1., weight );
			h_Obs_N[ ch ]->Fill( 1., weight );
		}
	}
	else if( option == "Obs6" )
	{
		if( cp == 1 )
		{
			h_Obs_t_P->Fill( 2., weight );
			h_Obs_P[ ch ]->Fill( 2., weight );
		}
		else
		{
			h_Obs_t_N->Fill( 2., weight );
			h_Obs_N[ ch ]->Fill( 2., weight );
		}
	}
	else if( option == "Obs12" )
	{
		if( cp == 1 )
		{
			h_Obs_t_P->Fill( 3., weight );
			h_Obs_P[ ch ]->Fill( 3., weight );
		}
		else
		{
			h_Obs_t_N->Fill( 3., weight );
			h_Obs_N[ ch ]->Fill( 3., weight );
		}
	}
	else if( option == "Obs13" )
	{
		if( cp == 1 )
		{
			h_Obs_t_P->Fill( 4., weight );
			h_Obs_P[ ch ]->Fill( 4., weight );
		}
		else
		{
			h_Obs_t_N->Fill( 4., weight );
			h_Obs_N[ ch ]->Fill( 4., weight );
		}
	}
}


void
Hists_Acp::WriteIn()
{
/*
	h_Obs3_mu_P->Write(); 
	h_Obs3_mu_N->Write();
	h_Obs6_mu_P->Write(); 
	h_Obs6_mu_N->Write();
	h_Obs12_mu_P->Write(); 
	h_Obs12_mu_N->Write();
	h_Obs13_mu_P->Write(); 
	h_Obs13_mu_N->Write();
	
	h_Obs3_el_P->Write(); 
	h_Obs3_el_N->Write();
	h_Obs6_el_P->Write(); 
	h_Obs6_el_N->Write();
	h_Obs12_el_P->Write(); 
	h_Obs12_el_N->Write();
	h_Obs13_el_P->Write(); 
	h_Obs13_el_N->Write();
*/
	h_Obs_mu_P->Write();
	h_Obs_mu_N->Write();
	h_Obs_el_P->Write();
	h_Obs_el_N->Write();
	h_Obs_t_P->Write();
	h_Obs_t_N->Write();

}

void Hists::GetObjs( string& file_name, string& option )
{
	TFile* f = new TFile( (char*)file_name.c_str() );
	

	if( option.find("NC") != string::npos )
	{
		h_TT_mu = new TH1F();		h_TT_el = new TH1F();
		h_DY_mu = new TH1F();		h_DY_el = new TH1F();
		h_WJets_mu = new TH1F();	h_WJets_el = new TH1F();
		h_VV_mu = new TH1F();		h_VV_el = new TH1F();
		h_ST_mu = new TH1F();		h_ST_el = new TH1F();
		h_QCD_mu = new TH1F();		h_QCD_el = new TH1F();
		h_Data_mu = new TH1F();		h_Data_el = new TH1F();
		h_l_TT_mu = new TH1F();		h_l_TT_el = new TH1F();
		h_l_DY_mu = new TH1F();		h_l_DY_el = new TH1F();
		h_l_WJets_mu = new TH1F();	h_l_WJets_el = new TH1F();
		h_l_VV_mu = new TH1F();		h_l_VV_el = new TH1F();
		h_l_ST_mu = new TH1F();		h_l_ST_el = new TH1F();
		h_l_QCD_mu = new TH1F();	h_l_QCD_el = new TH1F();
		h_l_Data_mu = new TH1F();	h_l_Data_el = new TH1F();

		f->GetObject("h_TT_mu",h_TT_mu);
		f->GetObject("h_DY_mu",h_DY_mu);
		f->GetObject("h_WJets_mu",h_WJets_mu);
		f->GetObject("h_VV_mu",h_VV_mu);
		f->GetObject("h_ST_mu",h_ST_mu);
		f->GetObject("h_QCD_mu",h_QCD_mu);
		f->GetObject("h_Data_mu",h_Data_mu);

		f->GetObject("h_TT_el",h_TT_el);
		f->GetObject("h_DY_el",h_DY_el);
		f->GetObject("h_WJets_el",h_WJets_el);
		f->GetObject("h_VV_el",h_VV_el);
		f->GetObject("h_ST_el",h_ST_el);
		f->GetObject("h_QCD_el",h_QCD_el);
		f->GetObject("h_Data_el",h_Data_el);

		f->GetObject("h_l_TT_mu",h_l_TT_mu);
		f->GetObject("h_l_DY_mu",h_l_DY_mu);
		f->GetObject("h_l_WJets_mu",h_l_WJets_mu);
		f->GetObject("h_l_VV_mu",h_l_VV_mu);
		f->GetObject("h_l_ST_mu",h_l_ST_mu);
		f->GetObject("h_l_QCD_mu",h_l_QCD_mu);
		f->GetObject("h_l_Data_mu",h_l_Data_mu);

		f->GetObject("h_l_TT_el",h_l_TT_el);
		f->GetObject("h_l_DY_el",h_l_DY_el);
		f->GetObject("h_l_WJets_el",h_l_WJets_el);
		f->GetObject("h_l_VV_el",h_l_VV_el);
		f->GetObject("h_l_ST_el",h_l_ST_el);
		f->GetObject("h_l_QCD_el",h_l_QCD_el);
		f->GetObject("h_l_Data_el",h_l_Data_el);

		InitNoCutVector();
	
	}
	
	if( option.find("1C") != string::npos )
	{
		
		h_TT_mu_c = new TH1F();		h_TT_el_c = new TH1F();
		h_DY_mu_c = new TH1F();		h_DY_el_c = new TH1F();
		h_WJets_mu_c = new TH1F();	h_WJets_el_c = new TH1F();
		h_VV_mu_c = new TH1F();		h_VV_el_c = new TH1F();
		h_ST_mu_c = new TH1F();		h_ST_el_c = new TH1F();
		h_QCD_mu_c = new TH1F();		h_QCD_el_c = new TH1F();
		h_Data_mu_c = new TH1F();		h_Data_el_c = new TH1F();
		h_l_TT_mu_c = new TH1F();		h_l_TT_el_c = new TH1F();
		h_l_DY_mu_c = new TH1F();		h_l_DY_el_c = new TH1F();
		h_l_WJets_mu_c = new TH1F();	h_l_WJets_el_c = new TH1F();
		h_l_VV_mu_c = new TH1F();		h_l_VV_el_c = new TH1F();
		h_l_ST_mu_c = new TH1F();		h_l_ST_el_c = new TH1F();
		h_l_QCD_mu_c = new TH1F();	h_l_QCD_el_c = new TH1F();
		h_l_Data_mu_c = new TH1F();	h_l_Data_el_c = new TH1F();

		f->GetObject("h_TT_mu_c",h_TT_mu_c);
		f->GetObject("h_DY_mu_c",h_DY_mu_c);
		f->GetObject("h_WJets_mu_c",h_WJets_mu_c);
		f->GetObject("h_VV_mu_c",h_VV_mu_c);
		f->GetObject("h_ST_mu_c",h_ST_mu_c);
		f->GetObject("h_QCD_mu_c",h_QCD_mu_c);
		f->GetObject("h_Data_mu_c",h_Data_mu_c);

		f->GetObject("h_TT_el_c",h_TT_el_c);
		f->GetObject("h_DY_el_c",h_DY_el_c);
		f->GetObject("h_WJets_el_c",h_WJets_el_c);
		f->GetObject("h_VV_el_c",h_VV_el_c);
		f->GetObject("h_ST_el_c",h_ST_el_c);
		f->GetObject("h_QCD_el_c",h_QCD_el_c);
		f->GetObject("h_Data_el_c",h_Data_el_c);

		f->GetObject("h_l_TT_mu_c",h_l_TT_mu_c);
		f->GetObject("h_l_DY_mu_c",h_l_DY_mu_c);
		f->GetObject("h_l_WJets_mu_c",h_l_WJets_mu_c);
		f->GetObject("h_l_VV_mu_c",h_l_VV_mu_c);
		f->GetObject("h_l_ST_mu_c",h_l_ST_mu_c);
		f->GetObject("h_l_QCD_mu_c",h_l_QCD_mu_c);
		f->GetObject("h_l_Data_mu_c",h_l_Data_mu_c);

		f->GetObject("h_l_TT_el_c",h_l_TT_el_c);
		f->GetObject("h_l_DY_el_c",h_l_DY_el_c);
		f->GetObject("h_l_WJets_el_c",h_l_WJets_el_c);
		f->GetObject("h_l_VV_el_c",h_l_VV_el_c);
		f->GetObject("h_l_ST_el_c",h_l_ST_el_c);
		f->GetObject("h_l_QCD_el_c",h_l_QCD_el_c);
		f->GetObject("h_l_Data_el_c",h_l_Data_el_c);
		
		InitOneCutVector();
	}
	
	if( option.find("2C") != string::npos )
	{
		h_TT_mu_cc = new TH1F();		h_TT_el_cc = new TH1F();
		h_DY_mu_cc = new TH1F();		h_DY_el_cc = new TH1F();
		h_WJets_mu_cc = new TH1F();	h_WJets_el_cc = new TH1F();
		h_VV_mu_cc = new TH1F();		h_VV_el_cc = new TH1F();
		h_ST_mu_cc = new TH1F();		h_ST_el_cc = new TH1F();
		h_QCD_mu_cc = new TH1F();		h_QCD_el_cc = new TH1F();
		h_Data_mu_cc = new TH1F();		h_Data_el_cc = new TH1F();
		h_l_TT_mu_cc = new TH1F();		h_l_TT_el_cc = new TH1F();
		h_l_DY_mu_cc = new TH1F();		h_l_DY_el_cc = new TH1F();
		h_l_WJets_mu_cc = new TH1F();	h_l_WJets_el_cc = new TH1F();
		h_l_VV_mu_cc = new TH1F();		h_l_VV_el_cc = new TH1F();
		h_l_ST_mu_cc = new TH1F();		h_l_ST_el_cc = new TH1F();
		h_l_QCD_mu_cc = new TH1F();	h_l_QCD_el_cc = new TH1F();
		h_l_Data_mu_cc = new TH1F();	h_l_Data_el_cc = new TH1F();

		f->GetObject("h_TT_mu_cc",h_TT_mu_cc);
		f->GetObject("h_DY_mu_cc",h_DY_mu_cc);
		f->GetObject("h_WJets_mu_cc",h_WJets_mu_cc);
		f->GetObject("h_VV_mu_cc",h_VV_mu_cc);
		f->GetObject("h_ST_mu_cc",h_ST_mu_cc);
		f->GetObject("h_QCD_mu_cc",h_QCD_mu_cc);
		f->GetObject("h_Data_mu_cc",h_Data_mu_cc);

		f->GetObject("h_TT_el_cc",h_TT_el_cc);
		f->GetObject("h_DY_el_cc",h_DY_el_cc);
		f->GetObject("h_WJets_el_cc",h_WJets_el_cc);
		f->GetObject("h_VV_el_cc",h_VV_el_cc);
		f->GetObject("h_ST_el_cc",h_ST_el_cc);
		f->GetObject("h_QCD_el_cc",h_QCD_el_cc);
		f->GetObject("h_Data_el_cc",h_Data_el_cc);

		f->GetObject("h_l_TT_mu_cc",h_l_TT_mu_cc);
		f->GetObject("h_l_DY_mu_cc",h_l_DY_mu_cc);
		f->GetObject("h_l_WJets_mu_cc",h_l_WJets_mu_cc);
		f->GetObject("h_l_VV_mu_cc",h_l_VV_mu_cc);
		f->GetObject("h_l_ST_mu_cc",h_l_ST_mu_cc);
		f->GetObject("h_l_QCD_mu_cc",h_l_QCD_mu_cc);
		f->GetObject("h_l_Data_mu_cc",h_l_Data_mu_cc);

		f->GetObject("h_l_TT_el_cc",h_l_TT_el_cc);
		f->GetObject("h_l_DY_el_cc",h_l_DY_el_cc);
		f->GetObject("h_l_WJets_el_cc",h_l_WJets_el_cc);
		f->GetObject("h_l_VV_el_cc",h_l_VV_el_cc);
		f->GetObject("h_l_ST_el_cc",h_l_ST_el_cc);
		f->GetObject("h_l_QCD_el_cc",h_l_QCD_el_cc);
		f->GetObject("h_l_Data_el_cc",h_l_Data_el_cc);

		InitTwoCutVector();
	}
	if( (option.find("NC") == string::npos) && (option.find("1C") == string::npos) && (option.find("2C") == string::npos) )
	{
		cerr << "Illegal option of Hists::GetObjs(\"file_name\",\"option\") ," << endl \
			 << "option should include NC/1C/2C " << endl;
	}
}

void Hists::InitNoCutVector()
{
	h_mu.push_back(h_TT_mu);		h_mu.push_back(h_DY_mu);
	h_mu.push_back(h_WJets_mu);		h_mu.push_back(h_VV_mu);
	h_mu.push_back(h_ST_mu);		h_mu.push_back(h_QCD_mu);
	h_mu.push_back(h_Data_mu);

	h_el.push_back(h_TT_el);		h_el.push_back(h_DY_el);
	h_el.push_back(h_WJets_el);		h_el.push_back(h_VV_el);
	h_el.push_back(h_ST_el);		h_el.push_back(h_QCD_el);
	h_el.push_back(h_Data_el);
	
	h_l_mu.push_back(h_l_TT_mu);		h_l_mu.push_back(h_l_DY_mu);
	h_l_mu.push_back(h_l_WJets_mu);		h_l_mu.push_back(h_l_VV_mu);
	h_l_mu.push_back(h_l_ST_mu);		h_l_mu.push_back(h_l_QCD_mu);
	h_l_mu.push_back(h_l_Data_mu);
	
	h_l_el.push_back(h_l_TT_el);		h_l_el.push_back(h_l_DY_el);
	h_l_el.push_back(h_l_WJets_el);		h_l_el.push_back(h_l_VV_el);
	h_l_el.push_back(h_l_ST_el);		h_l_el.push_back(h_l_QCD_el);
	h_l_el.push_back(h_l_Data_el);
}

void Hists::InitOneCutVector()
{
	h_mu_c.push_back(h_TT_mu_c);		h_mu_c.push_back(h_DY_mu_c);
	h_mu_c.push_back(h_WJets_mu_c);		h_mu_c.push_back(h_VV_mu_c);
	h_mu_c.push_back(h_ST_mu_c);		h_mu_c.push_back(h_QCD_mu_c);
	h_mu_c.push_back(h_Data_mu_c);

	h_el_c.push_back(h_TT_el_c);		h_el_c.push_back(h_DY_el_c);
	h_el_c.push_back(h_WJets_el_c);		h_el_c.push_back(h_VV_el_c);
	h_el_c.push_back(h_ST_el_c);		h_el_c.push_back(h_QCD_el_c);
	h_el_c.push_back(h_Data_el_c);
	
	h_l_mu_c.push_back(h_l_TT_mu_c);		h_l_mu_c.push_back(h_l_DY_mu_c);
	h_l_mu_c.push_back(h_l_WJets_mu_c);		h_l_mu_c.push_back(h_l_VV_mu_c);
	h_l_mu_c.push_back(h_l_ST_mu_c);		h_l_mu_c.push_back(h_l_QCD_mu_c);
	h_l_mu_c.push_back(h_l_Data_mu_c);
	
	h_l_el_c.push_back(h_l_TT_el_c);		h_l_el_c.push_back(h_l_DY_el_c);
	h_l_el_c.push_back(h_l_WJets_el_c);		h_l_el_c.push_back(h_l_VV_el_c);
	h_l_el_c.push_back(h_l_ST_el_c);		h_l_el_c.push_back(h_l_QCD_el_c);
	h_l_el_c.push_back(h_l_Data_el_c);
}


void Hists::InitTwoCutVector()
{
	h_mu_cc.push_back(h_TT_mu_cc);		h_mu_cc.push_back(h_DY_mu_cc);
	h_mu_cc.push_back(h_WJets_mu_cc);		h_mu_cc.push_back(h_VV_mu_cc);
	h_mu_cc.push_back(h_ST_mu_cc);		h_mu_cc.push_back(h_QCD_mu_cc);
	h_mu_cc.push_back(h_Data_mu_cc);

	h_el_cc.push_back(h_TT_el_cc);		h_el_cc.push_back(h_DY_el_cc);
	h_el_cc.push_back(h_WJets_el_cc);		h_el_cc.push_back(h_VV_el_cc);
	h_el_cc.push_back(h_ST_el_cc);		h_el_cc.push_back(h_QCD_el_cc);
	h_el_cc.push_back(h_Data_el_cc);
	
	h_l_mu_cc.push_back(h_l_TT_mu_cc);		h_l_mu_cc.push_back(h_l_DY_mu_cc);
	h_l_mu_cc.push_back(h_l_WJets_mu_cc);		h_l_mu_cc.push_back(h_l_VV_mu_cc);
	h_l_mu_cc.push_back(h_l_ST_mu_cc);		h_l_mu_cc.push_back(h_l_QCD_mu_cc);
	h_l_mu_cc.push_back(h_l_Data_mu_cc);
	
	h_l_el_cc.push_back(h_l_TT_el_cc);		h_l_el_cc.push_back(h_l_DY_el_cc);
	h_l_el_cc.push_back(h_l_WJets_el_cc);		h_l_el_cc.push_back(h_l_VV_el_cc);
	h_l_el_cc.push_back(h_l_ST_el_cc);		h_l_el_cc.push_back(h_l_QCD_el_cc);
	h_l_el_cc.push_back(h_l_Data_el_cc);
}

void Hists::TH2ModeON( const int& algo_bins_No, const double& m, const double& M )
{
	double algo_v_min = m;
	double algo_v_max = M;
	h_mvamax_hadmass_mu = new TH2D("h_mvamax_hadmass_mu","",bins_No,hist_min,hist_max,algo_bins_No,algo_v_min,algo_v_max);
	h_mvamax_hadmass_el = new TH2D("h_mvamax_hadmass_el","",bins_No,hist_min,hist_max,algo_bins_No,algo_v_min,algo_v_max);
	h_mvamax_hadmass[ "mu" ] = h_mvamax_hadmass_mu;			
	h_mvamax_hadmass[ "el" ] = h_mvamax_hadmass_el;
	
	h_mvamax_lepmass_mu = new TH2D("h_mvamax_lepmass_mu","",bins_No,hist_min,hist_max,algo_bins_No,algo_v_min,algo_v_max);
	h_mvamax_lepmass_el = new TH2D("h_mvamax_lepmass_el","",bins_No,hist_min,hist_max,algo_bins_No,algo_v_min,algo_v_max);
	h_mvamax_lepmass[ "mu" ] = h_mvamax_lepmass_mu;			
	h_mvamax_lepmass[ "el" ] = h_mvamax_lepmass_el;
}
void Hists::NoCutModeON()
{
	h_TT_mu = new TH1F("h_TT_mu","",bins_No,hist_min,hist_max);
	h_TT_el = new TH1F("h_TT_el","",bins_No,hist_min,hist_max);
	
	h_DY_mu = new TH1F("h_DY_mu","",bins_No,hist_min,hist_max);
	h_DY_el = new TH1F("h_DY_el","",bins_No,hist_min,hist_max);

	h_WJets_mu = new TH1F("h_WJets_mu","",bins_No,hist_min,hist_max);
	h_WJets_el = new TH1F("h_WJets_el","",bins_No,hist_min,hist_max);
	
	h_VV_mu = new TH1F("h_VV_mu","",bins_No,hist_min,hist_max);
	h_VV_el = new TH1F("h_VV_el","",bins_No,hist_min,hist_max);

	h_ST_mu = new TH1F("h_ST_mu","",bins_No,hist_min,hist_max);
	h_ST_el = new TH1F("h_ST_el","",bins_No,hist_min,hist_max);
	
	h_QCD_mu = new TH1F("h_QCD_mu","",bins_No,hist_min,hist_max);
	h_QCD_el = new TH1F("h_QCD_el","",bins_No,hist_min,hist_max);
	
	h_Data_mu = new TH1F("h_Data_mu",(char*)AxisInfo.c_str(),bins_No,hist_min,hist_max);	
	h_Data_el = new TH1F("h_Data_el",(char*)AxisInfo.c_str(),bins_No,hist_min,hist_max);

	h_l_TT_mu = new TH1F("h_l_TT_mu","",bins_No,hist_min,hist_max);
	h_l_TT_el = new TH1F("h_l_TT_el","",bins_No,hist_min,hist_max);
	
	h_l_DY_mu = new TH1F("h_l_DY_mu","",bins_No,hist_min,hist_max);
	h_l_DY_el = new TH1F("h_l_DY_el","",bins_No,hist_min,hist_max);

	h_l_WJets_mu = new TH1F("h_l_WJets_mu","",bins_No,hist_min,hist_max);
	h_l_WJets_el = new TH1F("h_l_WJets_el","",bins_No,hist_min,hist_max);
	
	h_l_VV_mu = new TH1F("h_l_VV_mu","",bins_No,hist_min,hist_max);
	h_l_VV_el = new TH1F("h_l_VV_el","",bins_No,hist_min,hist_max);

	h_l_ST_mu = new TH1F("h_l_ST_mu","",bins_No,hist_min,hist_max);
	h_l_ST_el = new TH1F("h_l_ST_el","",bins_No,hist_min,hist_max);
	
	h_l_QCD_mu = new TH1F("h_l_QCD_mu","",bins_No,hist_min,hist_max);
	h_l_QCD_el = new TH1F("h_l_QCD_el","",bins_No,hist_min,hist_max);
	
	h_l_Data_mu = new TH1F("h_l_Data_mu",(char*)AxisInfo2.c_str(),bins_No,hist_min,hist_max);
	h_l_Data_el = new TH1F("h_l_Data_el",(char*)AxisInfo2.c_str(),bins_No,hist_min,hist_max);

	InitNoCutVector();
}

void Hists::OneCutModeON()
{
	h_TT_mu_c = new TH1F("h_TT_mu_c","",bins_No,hist_min,hist_max);
	h_TT_el_c = new TH1F("h_TT_el_c","",bins_No,hist_min,hist_max);
	
	h_DY_mu_c = new TH1F("h_DY_mu_c","",bins_No,hist_min,hist_max);
	h_DY_el_c = new TH1F("h_DY_el_c","",bins_No,hist_min,hist_max);

	h_WJets_mu_c = new TH1F("h_WJets_mu_c","",bins_No,hist_min,hist_max);
	h_WJets_el_c = new TH1F("h_WJets_el_c","",bins_No,hist_min,hist_max);
	
	h_VV_mu_c = new TH1F("h_VV_mu_c","",bins_No,hist_min,hist_max);
	h_VV_el_c = new TH1F("h_VV_el_c","",bins_No,hist_min,hist_max);

	h_ST_mu_c = new TH1F("h_ST_mu_c","",bins_No,hist_min,hist_max);
	h_ST_el_c = new TH1F("h_ST_el_c","",bins_No,hist_min,hist_max);
	
	h_QCD_mu_c = new TH1F("h_QCD_mu_c","",bins_No,hist_min,hist_max);
	h_QCD_el_c = new TH1F("h_QCD_el_c","",bins_No,hist_min,hist_max);
	
	h_Data_mu_c = new TH1F("h_Data_mu_c",(char*)AxisInfo.c_str(),bins_No,hist_min,hist_max);	
	h_Data_el_c = new TH1F("h_Data_el_c",(char*)AxisInfo.c_str(),bins_No,hist_min,hist_max);

	h_l_TT_mu_c = new TH1F("h_l_TT_mu_c","",bins_No,hist_min,hist_max);
	h_l_TT_el_c = new TH1F("h_l_TT_el_c","",bins_No,hist_min,hist_max);
	
	h_l_DY_mu_c = new TH1F("h_l_DY_mu_c","",bins_No,hist_min,hist_max);
	h_l_DY_el_c = new TH1F("h_l_DY_el_c","",bins_No,hist_min,hist_max);

	h_l_WJets_mu_c = new TH1F("h_l_WJets_mu_c","",bins_No,hist_min,hist_max);
	h_l_WJets_el_c = new TH1F("h_l_WJets_el_c","",bins_No,hist_min,hist_max);
	
	h_l_VV_mu_c = new TH1F("h_l_VV_mu_c","",bins_No,hist_min,hist_max);
	h_l_VV_el_c = new TH1F("h_l_VV_el_c","",bins_No,hist_min,hist_max);

	h_l_ST_mu_c = new TH1F("h_l_ST_mu_c","",bins_No,hist_min,hist_max);
	h_l_ST_el_c = new TH1F("h_l_ST_el_c","",bins_No,hist_min,hist_max);
	
	h_l_QCD_mu_c = new TH1F("h_l_QCD_mu_c","",bins_No,hist_min,hist_max);
	h_l_QCD_el_c = new TH1F("h_l_QCD_el_c","",bins_No,hist_min,hist_max);
	
	h_l_Data_mu_c = new TH1F("h_l_Data_mu_c",(char*)AxisInfo2.c_str(),bins_No,hist_min,hist_max);
	h_l_Data_el_c = new TH1F("h_l_Data_el_c",(char*)AxisInfo2.c_str(),bins_No,hist_min,hist_max);
	
	InitOneCutVector();
}

void Hists::TwoCutModeON()
{
	h_TT_mu_cc = new TH1F("h_TT_mu_cc","",bins_No,hist_min,hist_max);
	h_TT_el_cc = new TH1F("h_TT_el_cc","",bins_No,hist_min,hist_max);
	
	h_DY_mu_cc = new TH1F("h_DY_mu_cc","",bins_No,hist_min,hist_max);
	h_DY_el_cc = new TH1F("h_DY_el_cc","",bins_No,hist_min,hist_max);

	h_WJets_mu_cc = new TH1F("h_WJets_mu_cc","",bins_No,hist_min,hist_max);
	h_WJets_el_cc = new TH1F("h_WJets_el_cc","",bins_No,hist_min,hist_max);
	
	h_VV_mu_cc = new TH1F("h_VV_mu_cc","",bins_No,hist_min,hist_max);
	h_VV_el_cc = new TH1F("h_VV_el_cc","",bins_No,hist_min,hist_max);

	h_ST_mu_cc = new TH1F("h_ST_mu_cc","",bins_No,hist_min,hist_max);
	h_ST_el_cc = new TH1F("h_ST_el_cc","",bins_No,hist_min,hist_max);
	
	h_QCD_mu_cc = new TH1F("h_QCD_mu_cc","",bins_No,hist_min,hist_max);
	h_QCD_el_cc = new TH1F("h_QCD_el_cc","",bins_No,hist_min,hist_max);
	
	h_Data_mu_cc = new TH1F("h_Data_mu_cc",(char*)AxisInfo.c_str(),bins_No,hist_min,hist_max);	
	h_Data_el_cc = new TH1F("h_Data_el_cc",(char*)AxisInfo.c_str(),bins_No,hist_min,hist_max);

	h_l_TT_mu_cc = new TH1F("h_l_TT_mu_cc","",bins_No,hist_min,hist_max);
	h_l_TT_el_cc = new TH1F("h_l_TT_el_cc","",bins_No,hist_min,hist_max);
	
	h_l_DY_mu_cc = new TH1F("h_l_DY_mu_cc","",bins_No,hist_min,hist_max);
	h_l_DY_el_cc = new TH1F("h_l_DY_el_cc","",bins_No,hist_min,hist_max);

	h_l_WJets_mu_cc = new TH1F("h_l_WJets_mu_cc","",bins_No,hist_min,hist_max);
	h_l_WJets_el_cc = new TH1F("h_l_WJets_el_cc","",bins_No,hist_min,hist_max);
	
	h_l_VV_mu_cc = new TH1F("h_l_VV_mu_cc","",bins_No,hist_min,hist_max);
	h_l_VV_el_cc = new TH1F("h_l_VV_el_cc","",bins_No,hist_min,hist_max);

	h_l_ST_mu_cc = new TH1F("h_l_ST_mu_cc","",bins_No,hist_min,hist_max);
	h_l_ST_el_cc = new TH1F("h_l_ST_el_cc","",bins_No,hist_min,hist_max);
	
	h_l_QCD_mu_cc = new TH1F("h_l_QCD_mu_cc","",bins_No,hist_min,hist_max);
	h_l_QCD_el_cc = new TH1F("h_l_QCD_el_cc","",bins_No,hist_min,hist_max);
	
	h_l_Data_mu_cc = new TH1F("h_l_Data_mu_cc",(char*)AxisInfo2.c_str(),bins_No,hist_min,hist_max);
	h_l_Data_el_cc = new TH1F("h_l_Data_el_cc",(char*)AxisInfo2.c_str(),bins_No,hist_min,hist_max);

	InitTwoCutVector();
}

void Hists::WriteIn( const string& option = "NC" )
{
	if( option.find("NT") != string::npos )
	{
		mvav_mass_mu->Write();
		mvav_mass_el->Write();
	}
	if( option.find("NC") != string::npos )
	{
		h_TT_mu->Write();		
		h_TT_el->Write();	
		h_DY_mu->Write();		
		h_DY_el->Write();
		h_WJets_mu->Write();	
		h_WJets_el->Write();
		h_VV_mu->Write();		
		h_VV_el->Write();
		h_ST_mu->Write();		
		h_ST_el->Write();
		h_QCD_mu->Write();		
		h_QCD_el->Write();
		h_Data_mu->Write();	
		h_Data_el->Write();

		h_l_TT_mu->Write();	
		h_l_TT_el->Write();
		h_l_DY_mu->Write();	
		h_l_DY_el->Write();
		h_l_WJets_mu->Write();	
		h_l_WJets_el->Write();
		h_l_VV_mu->Write();	
		h_l_VV_el->Write();
		h_l_ST_mu->Write();	
		h_l_ST_el->Write();
		h_l_QCD_mu->Write();	
		h_l_QCD_el->Write();
		h_l_Data_mu->Write();	
		h_l_Data_el->Write();
	}	
	
	if( option.find("1C") != string::npos )
	{
		h_TT_mu_c->Write();		
		h_TT_el_c->Write();	
		h_DY_mu_c->Write();		
		h_DY_el_c->Write();
		h_WJets_mu_c->Write();	
		h_WJets_el_c->Write();
		h_VV_mu_c->Write();		
		h_VV_el_c->Write();
		h_ST_mu_c->Write();		
		h_ST_el_c->Write();
		h_QCD_mu_c->Write();		
		h_QCD_el_c->Write();
		h_Data_mu_c->Write();	
		h_Data_el_c->Write();

		h_l_TT_mu_c->Write();	
		h_l_TT_el_c->Write();
		h_l_DY_mu_c->Write();	
		h_l_DY_el_c->Write();
		h_l_WJets_mu_c->Write();	
		h_l_WJets_el_c->Write();
		h_l_VV_mu_c->Write();	
		h_l_VV_el_c->Write();
		h_l_ST_mu_c->Write();	
		h_l_ST_el_c->Write();
		h_l_QCD_mu_c->Write();	
		h_l_QCD_el_c->Write();
		h_l_Data_mu_c->Write();	
		h_l_Data_el_c->Write();
	}

	if( option.find("2C") != string::npos )
	{
		h_TT_mu_cc->Write();		
		h_TT_el_cc->Write();	
		h_DY_mu_cc->Write();		
		h_DY_el_cc->Write();
		h_WJets_mu_cc->Write();	
		h_WJets_el_cc->Write();
		h_VV_mu_cc->Write();		
		h_VV_el_cc->Write();
		h_ST_mu_cc->Write();		
		h_ST_el_cc->Write();
		h_QCD_mu_cc->Write();		
		h_QCD_el_cc->Write();
		h_Data_mu_cc->Write();	
		h_Data_el_cc->Write();

		h_l_TT_mu_cc->Write();	
		h_l_TT_el_cc->Write();
		h_l_DY_mu_cc->Write();	
		h_l_DY_el_cc->Write();
		h_l_WJets_mu_cc->Write();	
		h_l_WJets_el_cc->Write();
		h_l_VV_mu_cc->Write();	
		h_l_VV_el_cc->Write();
		h_l_ST_mu_cc->Write();	
		h_l_ST_el_cc->Write();
		h_l_QCD_mu_cc->Write();	
		h_l_QCD_el_cc->Write();
		h_l_Data_mu_cc->Write();	
		h_l_Data_el_cc->Write();
	}
	
	if( (option.find("NC") == string::npos) && (option.find("1C") == string::npos) && (option.find("2C") == string::npos) )
	{
		cerr << "Illegal option of Hists::WriteIn(\"file_name\",\"option\") ," << endl \
			 << "option should include NC/1C/2C " << endl;
	}

}

void
Hists::FillHist( const string& option, const int& k, const string& ch, const double& hadm, const double& lepm, const double& weight )
{
	if( option.find("NC") != string::npos )
	{
		if( ch == "mu" )
		{
			h_mu.at(k)->Fill(hadm, weight);
			h_l_mu.at(k)->Fill(lepm, weight);

		}
		else if( ch == "el" )
		{
			h_el.at(k)->Fill(hadm, weight);
			h_l_el.at(k)->Fill(lepm, weight);
		}
		else
			return;
	}
	else if( option.find("1C") != string::npos )
	{
		if( ch == "mu" )
		{
			h_mu_c.at(k)->Fill(hadm, weight);
			h_l_mu_c.at(k)->Fill(lepm, weight);

		}
		else if( ch == "el" )
		{
			h_el_c.at(k)->Fill(hadm, weight);
			h_l_el_c.at(k)->Fill(lepm, weight);
		}
		else
			return;
	}
	else if( option.find("2C") != string::npos )
	{
		if( ch == "mu" )
		{
			h_mu_cc.at(k)->Fill(hadm, weight);
			h_l_mu_cc.at(k)->Fill(lepm, weight);

		}
		else if( ch == "el" )
		{
			h_el_cc.at(k)->Fill(hadm, weight);
			h_l_el_cc.at(k)->Fill(lepm, weight);
		}
		else
			return;
	}
	else
	{
		cerr << "Illegal option of Hists::WriteIn(\"file_name\",\"option\") ," << endl \
			 << "option should include NC/1C/2C " << endl;
	}
}





void
Hists_bb::Init()
{
	//we want the binNo at had t mass is same as the mva values'
	h_mvamax_mass_mu = new TH2D("h_mvamax_mass_mu","",bins_No1,hist_min2,hist_max2,bins_No1,hist_min1,hist_max1);
	h_mvamax_mass_el = new TH2D("h_mvamax_mass_el","",bins_No1,hist_min2,hist_max2,bins_No1,hist_min1,hist_max1);
	h_mvamax_mass_t = new TH2D("h_mvamax_mass_t","",bins_No1,hist_min2,hist_max2,bins_No1,hist_min1,hist_max1);
	h_mvamax_mass[ "mu" ] = h_mvamax_mass_mu;			h_mvamax_mass[ "el" ] = h_mvamax_mass_el;
	
	h_correct_t = new TH1F("h_correct_t"," ;mva value;events",bins_No1,hist_min1,hist_max1);
	h_mistag_t = new TH1F("h_mistag_t"," ;mva value;events",bins_No1,hist_min1,hist_max1);
	h_charge_mis_t = new TH1F("h_charge_mis_t"," ;mva value;events",bins_No1,hist_min1,hist_max1); 

	h_correct_mu = new TH1F("h_correct_mu"," ;mva value;events",bins_No1,hist_min1,hist_max1);
	h_mistag_mu = new TH1F("h_mistag_mu"," ;mva value;events",bins_No1,hist_min1,hist_max1);
	h_charge_mis_mu = new TH1F("h_charge_mis_mu"," ;mva value;events",bins_No1,hist_min1,hist_max1); 
	h_correct_el = new TH1F("h_correct_el"," ;mva value;events",bins_No1,hist_min1,hist_max1);
	h_mistag_el = new TH1F("h_mistag_el"," ;mva value;events",bins_No1,hist_min1,hist_max1);
	h_charge_mis_el = new TH1F("h_charge_mis_el"," ;mva value;events",bins_No1,hist_min1,hist_max1);
	

	h_lt_correct_t = new TH1F("h_lt_correct_t"," ;mass;events",bins_No2,hist_min2,hist_max2);
	h_lt_mistag_t = new TH1F("h_lt_mistag_t"," ;mass;events",bins_No2,hist_min2,hist_max2);
	h_lt_charge_mis_t = new TH1F("h_lt_charge_mis_t"," ;mass;events",bins_No2,hist_min2,hist_max2); 
	
	h_lt_correct_mu = new TH1F("h_lt_correct_mu"," ;mass;events",bins_No2,hist_min2,hist_max2);
	h_lt_mistag_mu = new TH1F("h_lt_mistag_mu"," ;mass;events",bins_No2,hist_min2,hist_max2);
	h_lt_charge_mis_mu = new TH1F("h_lt_charge_mis_mu"," ;mass;events",bins_No2,hist_min2,hist_max2); 
	h_lt_correct_el = new TH1F("h_lt_correct_el"," ;mass;events",bins_No2,hist_min2,hist_max2);
	h_lt_mistag_el = new TH1F("h_lt_mistag_el"," ;mass;events",bins_No2,hist_min2,hist_max2);
	h_lt_charge_mis_el = new TH1F("h_lt_charge_mis_el"," ;mass;events",bins_No2,hist_min2,hist_max2);
	
	
	h_correct[ "mu" ] = h_correct_mu;			h_correct[ "el" ] = h_correct_el;
	h_charge_mis[ "mu" ] = h_charge_mis_mu;		h_charge_mis[ "el" ] = h_charge_mis_el;
	h_mistag[ "mu" ] = h_mistag_mu;				h_mistag[ "el" ] = h_mistag_el;
	h_lt_correct[ "mu" ] = h_lt_correct_mu;				h_lt_correct[ "el" ] = h_lt_correct_el;
	h_lt_charge_mis[ "mu" ] = h_lt_charge_mis_mu;		h_lt_charge_mis[ "el" ] = h_lt_charge_mis_el;
	h_lt_mistag[ "mu" ] = h_lt_mistag_mu;				h_lt_mistag[ "el" ] = h_lt_mistag_el;
}

void
Hists_bb::WriteIn()
{
	
	h_mvamax_mass_mu->Write();
	h_mvamax_mass_el->Write();
	h_mvamax_mass_t->Write();

	h_correct_t->Write();
	h_mistag_t->Write();
	h_charge_mis_t->Write();

	h_correct_mu->Write();
	h_mistag_mu->Write();
	h_charge_mis_mu->Write();

	h_correct_el->Write();
	h_mistag_el->Write();
	h_charge_mis_el->Write();

	h_lt_correct_t->Write();
	h_lt_mistag_t->Write();
	h_lt_charge_mis_t->Write();

	h_lt_correct_mu->Write();
	h_lt_mistag_mu->Write();
	h_lt_charge_mis_mu->Write();

	h_lt_correct_el->Write();
	h_lt_mistag_el->Write();
	h_lt_charge_mis_el->Write();
}


void Hists_cor::Init()
{
	h_max_mva_mu = new TH1F("h_max_mva_mu","",bins_No1,hist_min1,hist_max1);
	h_max_mva_cor_mu = new TH1F("h_max_mva_cor_mu","",bins_No1,hist_min1,hist_max1);
	h_max_mva_incor_mu = new TH1F("h_max_mva_incor_mu","",bins_No1,hist_min1,hist_max1);
	
	h_max_mva_el = new TH1F("h_max_mva_el","",bins_No1,hist_min1,hist_max1);
	h_max_mva_cor_el = new TH1F("h_max_mva_cor_el","",bins_No1,hist_min1,hist_max1);
	h_max_mva_incor_el = new TH1F("h_max_mva_incor_el","",bins_No1,hist_min1,hist_max1);
	
	h_max_mva_t = new TH1F("h_max_mva_t","",bins_No1,hist_min1,hist_max1);
	h_max_mva_cor_t = new TH1F( "h_max_mva_cor_t","",bins_No1,hist_min1,hist_max1);
	h_max_mva_incor_t = new TH1F( "h_max_mva_incor_t","",bins_No1,hist_min1,hist_max1);
	
	h_max_mva[ "mu" ] = h_max_mva_mu;					h_max_mva[ "el" ] = h_max_mva_el;
	h_max_mva_cor[ "mu" ] = h_max_mva_cor_mu;			h_max_mva_cor[ "el" ] = h_max_mva_cor_el;
	h_max_mva_incor[ "mu" ] = h_max_mva_incor_mu;		h_max_mva_incor[ "el" ] = h_max_mva_incor_el;
	

	h_chosen_mu = new TH1F( "h_chosen_mu","",2,0.,2. );
	h_cor_mu = new TH1F( "h_cor_mu","",2,0.,2. );

	h_chosen_el = new TH1F( "h_chosen_el","",2,0.,2. );
	h_cor_el = new TH1F( "h_cor_el","",2,0.,2. );
	
	h_chosen_t = new TH1F( "h_chosen","",2,0.,2. );
	h_cor_t = new TH1F( "h_cor","",2,0.,2. );

	h_chosen[ "mu" ] = h_chosen_mu;		h_chosen[ "el" ] = h_chosen_el;
	h_cor[ "mu" ] = h_cor_mu;			h_cor[ "el" ] = h_cor_el;
}


void Hists_cor::WriteIn()
{
	h_max_mva_mu->Write();
	h_max_mva_cor_mu->Write();
	h_max_mva_incor_mu->Write();
		
	h_max_mva_el->Write();
	h_max_mva_cor_el->Write();
	h_max_mva_incor_el->Write();

	h_max_mva_t->Write();
	h_max_mva_cor_t->Write();
	h_max_mva_incor_t->Write();
	
	h_chosen_mu->Write();
	h_cor_mu->Write();
		
	h_chosen_el->Write();
	h_cor_el->Write();
	
	h_chosen_t->Write();
	h_cor_t->Write();
}

