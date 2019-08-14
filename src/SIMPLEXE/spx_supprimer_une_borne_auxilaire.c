// Copyright (c) 20xx-2019, RTE (https://www.rte-france.com)
// See AUTHORS.txt
// This Source Code Form is subject to the terms of the Apache License, version 2.0.
// If a copy of the Apache License, version 2.0 was not distributed with this file, you can obtain one at http://www.apache.org/licenses/LICENSE-2.0.
// SPDX-License-Identifier: Apache-2.0
// This file is part of SIRIUS, a linear problem solver, used in the ANTARES Simulator : https://antares-simulator.org/.

/***********************************************************************

   FONCTION: Remet la borne native d'une variable.
                
   AUTEUR: R. GONZALEZ

************************************************************************/

# include "spx_sys.h"

# include "spx_define.h"
# include "spx_fonctions.h"

# ifdef UTILISER_BORNES_AUXILIAIRES   

/*----------------------------------------------------------------------------*/

void SPX_SupprimerUneBorneAuxiliaire( PROBLEME_SPX * Spx, int Var )
{

/* Si la variable entrante avait sur une borne sup auxiliaire on libere la borne */

if ( Spx->StatutBorneSupCourante[Var] == BORNE_AUXILIAIRE_DE_VARIABLE_BORNEE_INFERIEUREMENT ) {
	Spx->TypeDeVariable          [Var] = BORNEE_INFERIEUREMENT;
  Spx->StatutBorneSupCourante  [Var] = BORNE_NATIVE;
	Spx->Xmax[Var] = LINFINI_SPX;
  Spx->NombreDeBornesAuxiliairesUtilisees--;	
	if ( Spx->NombreDeBornesAuxiliairesUtilisees < 0 ) {
	  printf("BUG dans SPX_SupprimerUneBorneAuxiliaire : NombreDeBornesAuxiliairesUtilisees = %d\n",Spx->NombreDeBornesAuxiliairesUtilisees);
		exit(0);
	}	
}
else if ( Spx->StatutBorneSupCourante[Var] == BORNE_AUXILIAIRE_DE_VARIABLE_NON_BORNEE ) {			
	/* Si la variable etait sur borne inf alors cela signifie qu'on avait cree une borne inf
	   de valeur non nulle */		 
  if ( Spx->PositionDeLaVariable[Var] == HORS_BASE_SUR_BORNE_INF ) {
		Spx->CalculerBBarre = OUI_SPX;
	}	
	Spx->TypeDeVariable          [Var] = NON_BORNEE;
  Spx->StatutBorneSupCourante  [Var] = BORNE_NATIVE;
	Spx->Xmax[Var] = LINFINI_SPX; 
	Spx->Xmin[Var] = -LINFINI_SPX; 	 
  Spx->NombreDeBornesAuxiliairesUtilisees--;
	if ( Spx->NombreDeBornesAuxiliairesUtilisees < 0 ) {
	  printf("BUG, le nombre de bornes auxiliaires utilisees est negatif: %d\n",Spx->NombreDeBornesAuxiliairesUtilisees);
		exit(0);
	}
}

return;
}
/*----------------------------------------------------------------------------*/

# endif  

