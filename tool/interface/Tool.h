#include "wk_MG5gen/tool/interface/Basic.h"

namespace Tool {
	string TransferChar( string& ori, const char& from, const char& to );
}

namespace Phys {
	double delR( const TLorentzVector& t1, const TLorentzVector& t2 );
	double Get_4D_LeviCivita( const TLorentzVector& a, const TLorentzVector& b, const TLorentzVector& c, const TLorentzVector& d );
}

