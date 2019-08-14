// Copyright (c) 20xx-2019, RTE (https://www.rte-france.com)
// See AUTHORS.txt
// This Source Code Form is subject to the terms of the Apache License, version 2.0.
// If a copy of the Apache License, version 2.0 was not distributed with this file, you can obtain one at http://www.apache.org/licenses/LICENSE-2.0.
// SPDX-License-Identifier: Apache-2.0
// This file is part of SIRIUS, a linear problem solver, used in the ANTARES Simulator : https://antares-simulator.org/.

/***********************************************************************

   FONCTION:  Calcul du chainage de la transposee de la matrice des
              contraintes
               
   AUTEUR: R. GONZALEZ

************************************************************************/

# include "spx_sys.h"

# include "spx_fonctions.h"
# include "spx_define.h"

# ifdef SPX_UTILISER_LES_OUTILS_DE_GESTION_MEMOIRE_PROPRIETAIRE	
  # include "spx_memoire.h"
# endif

/*----------------------------------------------------------------------------*/

void SPX_ChainageDeLaTransposee( PROBLEME_SPX * Spx, int TypeChainage )
{
int i; int il; int ilMax; int Var   ; int ilC      ; int * Csui        ;
int * NumeroDeContrainte  ; int * Mdeb; int * NbTerm ; int * Indcol      ;
int * Cdeb; double * ACol ; double * A ; int * CNbTerm; int * IndexCourant;
int NombreDeVariables     ; int NombreDeContraintes   ; int ilk           ;

Mdeb    = Spx->Mdeb;
NbTerm  = Spx->NbTerm;
Indcol  = Spx->Indcol;
Cdeb    = Spx->Cdeb;
ACol    = Spx->ACol;
A       = Spx->A;
CNbTerm = Spx->CNbTerm;
Csui    = Spx->Csui;
NumeroDeContrainte  = Spx->NumeroDeContrainte;
NombreDeVariables   = Spx->NombreDeVariables;
NombreDeContraintes = Spx->NombreDeContraintes;

if ( TypeChainage == COMPACT ) {

  IndexCourant = (int *) Spx->CBarreSurNBarreR;
  memset( (char *) CNbTerm , 0 , NombreDeVariables * sizeof( int ) );
  
  for ( i = 0 ; i < NombreDeContraintes ; i++ ) {
    il    = Mdeb[i];
    ilMax = il + NbTerm[i];
    while ( il < ilMax ) {
      CNbTerm[Indcol[il]]++;
      il++;
    }
  } 
  for ( ilC = 0 , Var = 0 ; Var < NombreDeVariables ; Var++ ) {
    Cdeb[Var] = ilC;
    IndexCourant[Var] = ilC;
    ilC+= CNbTerm[Var];
  }  
  for ( i = 0 ; i < NombreDeContraintes ; i++ ) { 
    il    = Mdeb[i];
    ilMax = il + NbTerm[i];
    while ( il < ilMax ) {
      ilC = IndexCourant[Indcol[il]];   
      IndexCourant[Indcol[il]]++;     
      ACol[ilC] = A[il];       
      NumeroDeContrainte[ilC] = i;
      il++;
    } 
  }  
  if ( Spx->StockageParColonneSauvegarde == NON_SPX ) {
    memcpy( (char *) Spx->CNbTermSansCoupes, (char *) CNbTerm , NombreDeVariables * sizeof( int ) );
    Spx->StockageParColonneSauvegarde = OUI_SPX;
  }

  memset( (char *) Spx->CBarreSurNBarreR , 0 , NombreDeVariables * sizeof( double ) );
	
}
else {
  for ( i = 0 ; i < NombreDeVariables ; i++ ) Cdeb[i] = -1;
  for ( i = NombreDeContraintes - 1 ; i >= 0 ; i-- ) { 
    il    = Mdeb[i];
    ilMax = il + NbTerm[i];
    while ( il < ilMax ) {
      Var = Indcol[il];
      ilk = Cdeb[Var];
      Cdeb[Var] = il;
      NumeroDeContrainte[il] = i;
      Csui[il] = ilk;    
      il++;
    }
  }
}

return;
} 
