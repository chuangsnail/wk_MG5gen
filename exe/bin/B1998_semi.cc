#include "wk_MG5gen/tool/interface/frame.h"

using namespace std;

int main( int argc, char* argv[] )
{
	//TFile* f = new TFile( argv[1] );
	TChain* ch = new TChain( "MGtree" );
	string filename = "/wk_cms2/cychuang/MG5/mg_root/" + string( argv[1] ) + "/*.root";
	ch->Add( filename.c_str() );

	Selector sel( ch, string(argv[1]) );
	//argv[2] is normal or test
	if( !sel.Init( string( argv[2] ) ) )
		cerr << "Failed in Init()!" << endl;

	// arguments of selection
	if( argc == 4 ) {
		sel.B1998( "semi", string(argv[3]) );	//B1998_semi
	}
	else {
		sel.B1998( "semi", "B1998_semi" );
	}
	
}

