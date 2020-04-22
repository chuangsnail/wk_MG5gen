#include "wk_MG5gen/tool/interface/frame.h"

void Selector::B1998( const string& option = "", const string& sel = "NoSel" )
{
	//There is no selection in W.B and A.B's 1993 paper

	if( option == "di" )
	{
		//--- Calculation obj ---//

		for(int entry=0;entry<total_entries;++entry)
		{
			Get_Entry( entry );
			InitEvent();
			
			//--- ConvertToP4 ---//
			ConvertToP4();
			
			//--- Pick what we want ---//
			// Need to pick up 2 opposite sign leptons
			for(int i=0;i<Size;++i)
			{
				
			}

			//--- Selection ---//
			pass_sel++;

			EndEvent();
		}
		
		//--- Calculate ---//

		//--- output ---//	

	}
	else if( option == "semi" )
	{
		//--- Calculation obj ---//
/*
		double Mean_Ot = 0.;
		double Mean_Otb = 0.;
		double SD_Ot = 0.;
		double SD_Otb = 0.;
		int N_Ot = 0;
		int N_Otb = 0;
*/
		AcpMgr_1998 acpMgr( "semilep" );

		int N_Ot_P = 0, N_Ot_N = 0;
		int N_Otb_P = 0, N_Otb_N = 0;
		
		for(int entry=0;entry<total_entries;++entry)
		{
			Get_Entry( entry );
			InitEvent();

			//--- ConvertToP4 ---//
			ConvertToP4();
			
			int idx_t = -1, idx_tb = -1, idx_b = -1, idx_bb = -1, idx_j1 = -1, idx_j2 = -1, idx_lep = -1;
			bool t_leptonic = true;		//positive lep
			string channel = "";

			//--- Pick what we want ---//
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
				else if( abs( evt.PdgID[i] ) == 11 ||  abs( evt.PdgID[i] ) == 13 || abs( evt.PdgID[i] ) == 15 )
					idx_lep = i;
				else if( abs( evt.PdgID[ evt.Mo[i] ]) == 24 && !(abs(evt.PdgID[i]) == 11 || abs(evt.PdgID[i]) == 13 || abs(evt.PdgID[i]) == 15 || abs(evt.PdgID[i]) == 12 || abs(evt.PdgID[i]) == 14 || abs(evt.PdgID[i]) == 16 ) ) {
					if( idx_j1 == -1 )
						idx_j1 = i;
					else
						idx_j2 = i;
				}
			}

			if( evt.PdgID[idx_lep] > 0 )
				t_leptonic = false;

			//--- Selection ---//

			if( sel.find( "B1998_semi" ) != string::npos ) {
				if( !B1998_semi( idx_t, idx_tb, idx_b, idx_bb, idx_j1, idx_j2, idx_lep ) ) continue;
			}

			acpMgr.Input_ttbar( particle[idx_t], particle[idx_tb] );	
			acpMgr.Input_lep( particle[idx_lep] );
		
			//--- for test ---//	
			if( mode == "test" ) {
				cout << "O1 : " << acpMgr.O1("Ot") << endl;
			}

			if( t_leptonic )
			{
				if( acpMgr.O1("Ot") > 0. ) {
					N_Ot_P++;
				}
				else {
					N_Ot_N++;
				}
			}
			else
			{
				if( acpMgr.O1("Otb") > 0. ) {
					N_Otb_P++;
				}
				else {
					N_Otb_N++;
				}
			}

			pass_sel++;

			EndEvent();
		} 
		//--- Calculate ---//
/*
		Mean_Ot /= (double)N_Ot;
		Mean_Otb /= (double)N_Otb;

		SD_Ot = sqrt( SD_Ot/(double)N_Ot - Mean_Ot * Mean_Ot );
		SD_Otb = sqrt( SD_Otb/(double)N_Otb - Mean_Otb * Mean_Otb );
*/
		double Mean_A = ( (double)N_Ot_P - (double)N_Ot_N )/( (double)N_Ot_P + (double)N_Ot_N );
		double Mean_Ab = ( (double)N_Otb_P - (double)N_Otb_N )/( (double)N_Otb_P + (double)N_Otb_N );
		double Err = sqrt( pow( GetAcpErr( (double)N_Ot_P, (double)N_Ot_N ), 2 ) + pow( GetAcpErr( (double)N_Otb_P, (double)N_Otb_N ), 2 ) );
	
		if( mode == "test" )
		{
			cout << "selection : " << sel << endl;
			cout << "O_1 Mean : " << Mean_A - Mean_Ab << endl;	
			cout << "O_1 1-sigma Err (propagate from stat.) : " << Err << endl;
			cout << "(N_Ot_P),(N_Otb_P) : " << N_Ot_P << ", " << N_Otb_P << endl;
			cout << "(N_Ot_N),(N_Otb_N) : " << N_Ot_N << ", " << N_Otb_N << endl;
			cout << "numberOfEntries : " << total_entries << endl;
			cout << "numberOfPassSelection : " << pass_sel << endl;
			return;
		}

		//--- output ---//
		string time_str = get_time_str( minute );
		ofstream fout;
		fout.open("/wk_cms2/cychuang/CMSSW_9_4_13/src/wk_MG5gen/exe/result/B1998_semi01.txt",ios::app);	
		fout << "time : " << time_str << endl;
		fout << "dataset : " << SetName << endl;
		fout << "selection : " << sel << endl;
		fout << "O_1 Mean : " << Mean_A - Mean_Ab << endl;	
		fout << "O_1 1-sigma Err (propagate from stat.) : " << Err << endl;
		fout << "(N_Ot_P),(N_Otb_P) : " << N_Ot_P << ", " << N_Otb_P << endl;
		fout << "(N_Ot_N),(N_Otb_N) : " << N_Ot_N << ", " << N_Otb_N << endl;
		fout << "1/sqrt(N of events) : " << 1./sqrt((double)pass_sel) << endl;
		fout << "numberOfEntries : " << total_entries << endl;
		fout << "numberOfPassSelection : " << pass_sel << endl;
		fout << "=====================================" << endl << endl;
	}
	else
	{
		cerr << "There is illegal option for Selector::B1993() [ " << option << " ]" << endl;
	}

}


