#include "wk_MG5gen/tool/interface/frame.h"

using namespace std;

int main( int argc, char* argv[] )
{
	//TFile* f = new TFile( argv[1] );
	TChain* ch = new TChain( "MGtree" );
	string filename = "/wk_cms2/cychuang/MG5/mg_root/" + string( argv[1] ) + "/*.root";
	ch->Add( filename.c_str() );

	Selector sel( ch, string(argv[1]) );
	if( !sel.Init( "normal" ) )
		cerr << "Failed in Init()!" << endl;

	sel.B1993( "A2", "NoSel" );
	
}

