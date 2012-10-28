/*---------------------------------------------------------------------------*\
    eulerSolver - A simple parallel first order Gas-dynamics solver
                  based on the OpenFOAM library
    Copyright (C) 2012, Pavanakumar Mohanamuraly

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include<fvCFD.H>
#include<UList.H>
#include "fluxSchemes.H"

int main(int argc, char *argv[])
{
   #include "setRootCase.H"
   #include "createTime.H"
   #include "createMesh.H"
   #include "createFields.H"
   #include "readFluxScheme.H"

   /// Freestream values
   scalar rho_inf = 1.228 , p_inf = 101325.0, M_inf = 2.0 ;
   scalar magU_inf = std::sqrt( 1.40e0 * p_inf / rho_inf ) * M_inf;
   vector u_inf ( magU_inf , 0.0 , 0.0 );
   // Unit face normals
   surfaceVectorField nf = mesh.Sf() / mesh.magSf();
   label iter = 1;

   /// Time step loop
   while( runTime.loop() ) {
     Info<< "Iteration = " << iter++ << nl << endl;

     /// Construct the fluxes at faces
     #include "constructFaceFlux.H"
     
     /// Sum-up face fluxes of all associated faces of a cell
     #include "sumFlux.H"
     
     /// Obtain boundary fluxes
     #include "boundaryFlux.H"
     
     /// State update
     #include "stateUpdate.H"

     // Solution output
     runTime.write();
   }
 
   return 0;
}


