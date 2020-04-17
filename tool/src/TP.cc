#include "wk_MG5gen/tool/interface/frame.h"

void Selector::TP_dilep( const string& option = "directly", const string& sel = "NoSel" )
{
	Hists_DilepAcp hists_acp;
	hists_acp.Init("all");
	DilepAcpMgr acpMgr;

	for(int entry=0;entry<total_entries;++entry)
	{	
		Get_Entry( entry );
		InitEvent();

		ConvertToP4();

		int idx_t = -1, idx_tb = -1, idx_b = -1, idx_bb = -1, idx_lepp = -1, idx_lepn = -1;
		int idx_nuep = -1, idx_nuen = -1;

		for(int i=0;i<Size;++i)
		{
			if( evt.PdgID[i] == 6 )
				idx_t = i;
			else if( evt.PdgID[i] == -6 )
				idx_tb = i;
			else if( evt.PdgID[i] == 5 )
				idx_b = i;
			else if( evt.PdgID[i] == -5 )
				idx_bb = i;
			else if( evt.PdgID[i] == 11 ||  evt.PdgID[i] == 13 || evt.PdgID[i] == 15 )
				idx_lepn = i;
			else if( evt.PdgID[i] == -11 ||  evt.PdgID[i] == -13 || evt.PdgID[i] == -15 )
				idx_lepp = i;
			else if( evt.PdgID[i] == -12 ||  evt.PdgID[i] == -14 || evt.PdgID[i] == -16 )
				idx_nuen = i;
			else if( evt.PdgID[i] == 12 ||  evt.PdgID[i] == 14 || evt.PdgID[i] == 16 )
				idx_nuep = i;

		}
		
		if( sel.find("GVSel") != string::npos ) {
			if( !GermanValenciaSelection_dilep( idx_b, idx_bb, idx_lepp, idx_lepn ) ) continue;
		}
		else if( sel.find("NoSel") )
		{	
			//do nothing	
		}
		pass_sel++;
		
		acpMgr.InputSelObjs( particle[idx_b], particle[idx_bb], particle[idx_lepp], particle[idx_nuep], particle[idx_lepn], particle[idx_nuen] );
		acpMgr.Input_ttbar( particle[idx_t], particle[idx_tb] );
		
		if( option == "directly" )
			hists_acp.FillIn( "Obs1", "", acpMgr.Obs1( "directly" ), 1. );
		else
			hists_acp.FillIn( "Obs1", "", acpMgr.Obs1( "seperately" ), 1. );
		hists_acp.FillIn( "Obs3", "", acpMgr.Obs3(), 1. );
	}
	
	hists_acp.Cal_Acp();

	if( mode == "test" )
	{
		cout << "hists_acp.h_Acp_t->GetBinContent(1) : " << hists_acp.h_Acp_t->GetBinContent(1) << ", hists_acp.h_Acp_t->GetBinError(1) : " << hists_acp.h_Acp_t->GetBinError(1) << endl;
		cout << "hists_acp.h_Acp_t->GetBinContent(2) : " << hists_acp.h_Acp_t->GetBinContent(2) << ", hists_acp.h_Acp_t->GetBinError(2) : " << hists_acp.h_Acp_t->GetBinError(2) << endl;
	
		return;
	}

	cout << "SetName : " << SetName << " ,pass_sel : " << pass_sel << " ,total_entries : " << total_entries  << endl;
	cout << "selection eff : " << pass_sel/total_entries << endl;

	string path = "/wk_cms2/cychuang/CMSSW_9_4_13/src/wk_MG5gen/exe/result/";
	string filename = path + "TP_dilep_genAcp_" + sel + "_" + SetName + "_" + option + ".root";
	
	TFile* f = new TFile( (char*)filename.c_str(), "recreate" );
	hists_acp.WriteIn();
	f->Close();
}

void Selector::TP_semileptonic( const string& sel = "NoSel" )
{
	Hists_Acp hists_acp;
	hists_acp.Init("all");
	AcpMgr acpMgr;

	int N_tau = 0;
	
	for(int entry=0;entry<total_entries;++entry)
	{	
		Get_Entry( entry );
		InitEvent();
		
		ConvertToP4();

		//--- init objs ---//
		int idx_b = -1, idx_bb = -1, idx_lep = -1, idx_j1 = -1, idx_j2 = -1;
		bool t_leptonic = true;
		string channel = "";

		//--- assign obj ---//
		for(int i=0;i<Size;++i)
		{
			if( evt.PdgID[i] == 5 )
				idx_b = i;
			else if( evt.PdgID[i] == -5 )
				idx_bb = i;
			else if( abs(evt.PdgID[i]) == 11 || abs(evt.PdgID[i]) == 13 || abs(evt.PdgID[i]) == 15 )
				idx_lep = i;
			else if( abs( evt.PdgID[ evt.Mo[i] ]) == 24 && !(abs(evt.PdgID[i]) == 11 || abs(evt.PdgID[i]) == 13 || abs(evt.PdgID[i]) == 15 || abs(evt.PdgID[i]) == 12 || abs(evt.PdgID[i]) == 14 || abs(evt.PdgID[i]) == 16 ) ) {
				if( idx_j1 == -1 )
					idx_j1 = i;
				else
					idx_j2 = i;
			}
		}
		
		//--- management of j1/j2 ---//
		if( particle[idx_j1].Pt() < particle[idx_j2].Pt() ) {
			int tmp = idx_j1;
			idx_j1 = idx_j2;
			idx_j2 = tmp;
		}

		//--- Do the event selection ---//

		if( sel.find("GVSel") != string::npos ) {
			if( !GermanValenciaSelection_semi( idx_b, idx_bb, idx_lep, idx_j1, idx_j2 ) ) continue;
		}
		else if( sel.find("NoSel") )
		{	
			//do nothing	
		}
		pass_sel++;

		//--- see which top is leptonic ---//
		if( evt.PdgID[idx_lep] > 0 )	//negative lepton -> tbar is leptonic
		   	t_leptonic = false;
		
		//--- just for testing!!!! ---//
/*
		if( !t_leptonic ) {
			int idx_top = -1;
			for(int i=0;i<Size;++i)
			{
				if( evt.PdgID[i] == 6 ) {
					idx_top = i;
					break;
				}
			}
			TLorentzVector dirt = particle[ idx_top ];
			TLorentzVector addt = ( particle[idx_j1] + particle[idx_j2] + particle[idx_b] );
			cout << "addt (" << addt.Pt() << "," << addt.Eta() << "," << addt.Phi() << "," << addt.E() << endl;
			cout << "dirt (" << dirt.Pt() << "," << dirt.Eta() << "," << dirt.Phi() << "," << dirt.E() << endl;
		}
*/
		
		//--- channel decision ---//
		if( abs(evt.PdgID[idx_lep]) == 11 ) {
			channel = "el";
		}
		else if( abs(evt.PdgID[idx_lep]) == 13 ) {
			channel = "mu";
		}
		else {
			channel = "tau";
			N_tau++;
			continue;
		}

		//cout << "b:" << idx_b << " bb:" << idx_bb << " lep:" << idx_lep << " j1:" << idx_j1 << " j2:" << idx_j2 << endl;

		//--- input info in acpMgr ---//
		if( t_leptonic ) {
			acpMgr.InputSelObjs( particle[idx_bb], particle[idx_b], particle[idx_j1], particle[idx_lep], 1. );
		}
		else {
			acpMgr.InputSelObjs( particle[idx_b], particle[idx_bb], particle[idx_j1], particle[idx_lep], -1. );
		}
	
		//cout << acpMgr.Obs3() << endl;	
		//--- fill hists_acp ---//
		hists_acp.FillIn( "Obs6", channel, acpMgr.Obs6(), 1. );
		hists_acp.FillIn( "Obs12", channel, acpMgr.Obs12(), 1. );
		hists_acp.FillIn( "Obs13", channel, acpMgr.Obs13(), 1. );
		hists_acp.FillIn( "Obs3", channel, acpMgr.Obs3(), 1. );
		
	}
	
	if( mode == "test" )
	{
		cout << "t_entries " << total_entries << endl;
		cout << "SetName : " << SetName << " ,pass_sel : " << pass_sel << " ,total_entries : " << total_entries  << endl;
		cout << "selection eff : " << pass_sel/total_entries << endl;
		cout << "hists_acp.h_Obs_mu_P->GetBinContent(2) " << hists_acp.h_Obs_mu_P->GetBinContent(2) << endl;
		cout << "hists_acp.h_Obs_mu_N->GetBinContent(2) " << hists_acp.h_Obs_mu_N->GetBinContent(2) << endl;
		cout << N_tau << endl;
		return;
	}
	
	cout << "SetName : " << SetName << " ,pass_sel : " << pass_sel << " ,total_entries : " << total_entries  << endl;
	cout << "selection eff : " << (double)pass_sel/(double)total_entries << endl;
	string path = "/wk_cms2/cychuang/CMSSW_9_4_13/src/wk_MG5gen/exe/result/";
	SetName = Tool::TransferChar( SetName, '/', '-' );
	cout << "SetName is [ " << SetName << " ]" << endl;
	string filename = path + "TP_semilep_genAcp_" + sel + "_" + SetName  + ".root";
	
	TFile* f = new TFile( (char*)filename.c_str(), "recreate" );
	hists_acp.WriteIn();
	f->Close();
}
