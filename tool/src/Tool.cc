#include "wk_MG5gen/tool/interface/Tool.h"

string 
Tool::TransferChar( string& ori, const char& from, const char& to )
{
	char tmp_ch[500];
	strcpy( tmp_ch, (char*)ori.c_str() );
	//tmp_ch = (char*)ori.c_str();

	for(int i=0;i<(int)ori.length();++i) {
		//cout << tmp_ch[i] << endl;
		if( tmp_ch[i] == from ) {
			tmp_ch[i] = to;
		}
	}
	string res = string(tmp_ch);

	return res;
}

double 
Phys::delR( const TLorentzVector& t1, const TLorentzVector& t2 )
{
	double delEta = t1.Eta() - t2.Eta();
	double delPhi = TVector2::Phi_mpi_pi(t1.Phi() - t2.Phi());
	return sqrt( pow(delEta,2) + pow(delPhi,2) );
}
