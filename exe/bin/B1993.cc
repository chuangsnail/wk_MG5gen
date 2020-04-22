#include "wk_MG5gen/tool/interface/frame.h"

using namespace std;
//
// argv = 'B1993 [sample name] ["A1" or "A2"] ["normal" or "test"] [selection type]'
//


int main( int argc, char* argv[] )
{
	//TFile* f = new TFile( argv[1] );
	TChain* ch = new TChain( "MGtree" );
	string filename = "/wk_cms2/cychuang/MG5/mg_root/" + string( argv[1] ) + "/*.root";
	ch->Add( filename.c_str() );

	Selector sel( ch, string(argv[1]) );
	if( !sel.Init( string(argv[3]) )) {		//argv[2] is "normal" or "test"
		cerr << "Failed in Init()!" << endl;
	}

	if( args == 4 ) {
		sel.B1993( string(argv[2]), string(argv[4]) );
	}
	else
		sel.B1993( string(argv[2]), "NoSel" );
	
}

