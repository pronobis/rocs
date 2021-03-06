/*  This file is part of libDAI - http://www.libdai.org/
 *
 *  libDAI is licensed under the terms of the GNU General Public License version
 *  2, or (at your option) any later version. libDAI is distributed without any
 *  warranty. See the file COPYING for more details.
 *
 *  Copyright (C) 2010  Joris Mooij  [joris dot mooij at libdai dot org]
 */

#include <dai/alldai.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace dai;

int main() {
    // This example program illustrates how to learn the
    // parameters of a Bayesian network from a sample of
    // the sprinkler network discussed at
    // http://www.cs.ubc.ca/~murphyk/Bayes/bnintro.html
    //
    // The factor graph file (sprinkler.fg) has to be generated first
    // by running example_sprinkler, and the data sample file 
    // (sprinkler.tab) by running example_sprinkler_gibbs

    // Read the factorgraph from the file
    FactorGraph SprinklerNetwork;
    SprinklerNetwork.ReadFromFile( "sprinkler.fg" );

    // Prepare junction-tree object for doing exact inference for E-step
    PropertySet infprops;
    infprops.set( "verbose", (size_t)1 );
    infprops.set( "updates", string("HUGIN") );
    InfAlg* inf = newInfAlg( "JTREE", SprinklerNetwork, infprops );
    inf->init();

    // Read sample from file
    Evidence e;
    ifstream estream( "sprinkler.tab" );
    e.addEvidenceTabFile( estream, SprinklerNetwork );
    cout << "Number of samples: " << e.nrSamples() << endl;

    // Read EM specification
    ifstream emstream( "sprinkler.em" );
    EMAlg em(e, *inf, emstream);

    // Iterate EM until convergence
    while( !em.hasSatisfiedTermConditions() ) {
        Real l = em.iterate();
        cout << "Iteration " << em.Iterations() << " likelihood: " << l <<endl;
    }

    // Output true factor graph
    cout << endl << "True factor graph:" << endl << "##################" << endl;
    cout.precision(12);
    cout << SprinklerNetwork;

    // Output learned factor graph
    cout << endl << "Learned factor graph:" << endl << "#####################" << endl;
    cout.precision(12);
    cout << inf->fg();

    // Clean up
    delete inf;

    return 0;
}
