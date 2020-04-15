#include "wk_MG5gen/tool/interface/frame.h"

void Selector::TP_dilep( const string& option = "directly" )
{
	Hists_DilepAcp hists_acp;
	hists_acp.Init("all");
	DilepAcpMgr acpMgr;

	for(int entry=0;entry<total_entries;++entry)
	{	
		Get_Entry( entry );
		InitEvent();

		pass_sel++;
		
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


	string path = "/wk_cms2/cychuang/CMSSW_9_4_13/wk_MG5gen/exe/result/";
	string filename = path + "TP_gen_Acp_" + SetName + "_" + option + ".root";
	
	TFile* f = new TFile( (char*)filename.c_str(), "recreate" );
	hists_acp.WriteIn();
	f->Close();
}
