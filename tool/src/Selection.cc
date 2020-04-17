#include "wk_MG5gen/tool/interface/frame.h"

double
Selector::MET()
{
	TLorentzVector missing_ET;
	for(int i=0;i<Size;++i)
	{
		if( abs(evt.PdgID[i]) == 12 || abs(evt.PdgID[i]) == 14 || abs(evt.PdgID[i]) == 16 ) {
			missing_ET = missing_ET + particle[i];
		}
	}
	return missing_ET.Et();
}


bool 
Selector::GermanValenciaSelection_semi( const int& b, const int& bb, const int& lep, const int& j1, const int& j2 )
{
	if( particle[b].Pt() < 25. || particle[bb].Pt() < 25. ) return false;
	if( particle[j1].Pt() < 20. || particle[j2].Pt() < 20. || particle[lep].Pt() < 20. ) return false;

	if( MET() < 30. ) return false;

	vector<int> v;
	v.push_back( b );
	v.push_back( bb );
	v.push_back( lep );
	v.push_back( j1 );
	v.push_back( j2 );

	for(int i=0;i<5;++i) {
		for(int j=i+1;j<5;++j) {
			if( Phys::delR( particle[ v.at(i) ], particle[ v.at(j) ] ) < 0.4 ) return false;
		}
	}

	return true;
}

bool
Selector::GermanValenciaSelection_dilep( const int& b, const int& bb, const int& lepp, const int& lepn )
{
	if( particle[b].Pt() < 25. || particle[bb].Pt() < 25. ) return false;
	if( particle[lepp].Pt() < 20. || particle[lepn].Pt() < 20. ) return false;

	if( MET() < 30. ) return false;

	vector<int> v;
	v.push_back( b );
	v.push_back( bb );
	v.push_back( lepp );
	v.push_back( lepn );

	for(int i=0;i<4;++i) {
		for(int j=i+1;j<4;++j) {
			if( Phys::delR( particle[ v.at(i) ], particle[ v.at(j) ] ) < 0.4 ) return false;
		}
	}

	return true;
}
