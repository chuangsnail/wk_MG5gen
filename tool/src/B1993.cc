#include "wk_MG5gen/tool/interface/frame.h"

void Selector::B1993( const string& option = "", const string& sel = "NoSel" )
{
	//There is no selection in W.B and A.B 's 1993 paper

	if( option == "A1" )
	{
		//--- Calculation obj ---//
		double Mean_A1 = 0.;
		double SD_A1 = 0.;

		for(int entry=0;entry<total_entries;++entry)
		{
			Get_Entry( entry );
			InitEvent();
			
			//--- Selection ---//
			// Note : selection before convert to P4 to rest more space //

			// An selecting example! //
/*
			int idx_t = -1;
			for(int i=0;i<Size;++i)
			if( evt.PdgID[i] == 6 ) idx_t = i;
			if( idx_t == -1 ) continue;

			TLorentzVector tmp;
			tmp.SetPxPyPzE( evt.Px[idx_t], evt.Py[idx_t], evt.Pz[idx_t], evt.E[idx_t] );
			if( tmp.Pt() < 20 ) continue;
*/
			pass_sel++;
			//--- ConvertToP4 ---//
			ConvertToP4();
			
			//--- Pick what we want ---//
			// Need to pick up 2 opposite sign leptons
			int idx_lepp = -1;
			int idx_lepn = -1;
			for(int i=0;i<Size;++i)
			{
				if( evt.PdgID[i] == 11 || evt.PdgID[i] == 13 || evt.PdgID[i] == 15 )
					idx_lepn = i;
				else if( evt.PdgID[i] == -11 || evt.PdgID[i] == -13 || evt.PdgID[i] == -15 )
					idx_lepp = i;
			}

			double tmp_A1 = particle[idx_lepp].E() - particle[idx_lepn].E();

			cout << "tmp_A1 " << tmp_A1 << endl;

			Mean_A1 += tmp_A1;
			SD_A1 += tmp_A1 * tmp_A1;

			EndEvent();
		}
		
		//--- Calculate ---//
		Mean_A1 /= (double)pass_sel;
		SD_A1 = sqrt( SD_A1/(double)pass_sel - Mean_A1 * Mean_A1 );

		//--- output ---//	
		string time_str = get_time_str( minute );
		ofstream fout;
		fout.open("/wk_cms2/cychuang/CMSSW_9_4_13/src/wk_MG5gen/exe/result/A1.txt",ios::app);	
		fout << "time : " << time_str << endl;
		fout << "dataset : " << SetName << endl;
		fout << "M_A1 : " << Mean_A1 << endl;	
		fout << "SD_A1 : " << SD_A1 << endl;
		fout << "signal-to-noise ratio : " << Mean_A1/SD_A1 << endl << endl;
		fout << "1/sqrt(N of events) : " << 1./sqrt((double)pass_sel) << endl;
		fout << "numberOfEntries : " << total_entries << endl;
		fout << "numberOfPassSelection : " << pass_sel << endl;
		fout << "=====================================" << endl << endl;

		fout.close();

	}
	else if( option == "A2" )
	{
		//--- Calculation obj ---//
		double Mean_Ot = 0., Mean_Otb = 0.;
		double SD_Ot = 0., SD_Otb = 0.;
		int N_Ot = 0, N_Otb = 0;
		
		for(int entry=0;entry<total_entries;++entry)
		{
			Get_Entry( entry );
			InitEvent();

			//--- Selection ---//
			// Note : selection before convert to P4 to rest more space //
			//
			// in this case , there is no selection at parton level
			pass_sel++;
			//--- ConvertToP4 ---//
			ConvertToP4();
			
			//--- Pick what we want ---//
			// Need to pick up t/lepn or tbar/lepp
			bool is_Ot = true;
			int idx_top = -1;
			int idx_lep = -1;
			for(int i=0;i<Size;++i) {
				if( evt.PdgID[i] == 11 || evt.PdgID[i] == 13 || evt.PdgID[i] == 15 ) {	//negative lepton
					idx_lep = i; //is_Ot = true;
				}
				else if( evt.PdgID[i] == -11 || evt.PdgID[i] == -13 || evt.PdgID[i] == -15 ) {
					idx_lep = i; is_Ot = false;
				}
			}
			for(int i=0;i<Size;++i) {
				if( is_Ot ) {
					if( evt.PdgID[i] == 6 )
						idx_top = i;
				}
				else {
					if( evt.PdgID[i] == -6 )
						idx_top = i;
				}
			}

			if( idx_lep == -1 || idx_top == -1 ) {
				cerr << "Wrong in picking out step." << endl;
				return;
			}

			double tmp_O = particle[idx_lep].Vect().Dot( particle[idx_top].Vect() );
			if( is_Ot ) {
				Mean_Ot += tmp_O;
				SD_Ot += tmp_O * tmp_O;
				++N_Ot;
			}
			else {
				Mean_Otb += tmp_O;
				SD_Otb += tmp_O * tmp_O;
				++N_Otb;
			}

			EndEvent();
		} 
		//--- Calculate ---//

		Mean_Ot /= (double)N_Ot;
		Mean_Otb /= (double)N_Otb;

		SD_Ot = sqrt( SD_Ot/(double)N_Ot - Mean_Ot * Mean_Ot );
		SD_Otb = sqrt( SD_Otb/(double)N_Otb - Mean_Otb * Mean_Otb );

		double Mean_A2 = Mean_Otb - Mean_Ot;
		double SD_A2 = sqrt( SD_Otb * SD_Otb + SD_Ot * SD_Ot );

		//--- output ---//
		string time_str = get_time_str( minute );
		ofstream fout;
		fout.open("/wk_cms2/cychuang/CMSSW_9_4_13/src/wk_MG5gen/exe/result/A2.txt",ios::app);	
		fout << "time : " << time_str << endl;
		fout << "dataset : " << SetName << endl;
		fout << "M_A2 : " << Mean_A2 << endl;	
		fout << "SD_A2 : " << SD_A2 << endl;
		fout << "signal-to-noise ratio : " << Mean_A2/SD_A2 << endl << endl;
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


