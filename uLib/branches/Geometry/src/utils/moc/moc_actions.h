/*//////////////////////////////////////////////////////////////////////////////
// CMT Cosmic Muon Tomography project //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  Copyright (c) 2014, Universita' degli Studi di Padova, INFN sez. di Padova
  All rights reserved

  Authors: Andrea Rigoni Garola < andrea.rigoni@pd.infn.it >

  ------------------------------------------------------------------
  This library is free software;  you  can  redistribute  it  and/or
  modify it  under the  terms  of  the  GNU  Lesser  General  Public
  License as published  by  the  Free  Software  Foundation;  either
  version 3.0 of the License, or (at your option) any later version.

  This library is  distributed in  the hope that it will  be useful,
  but  WITHOUT ANY WARRANTY;  without  even  the implied warranty of
  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of  the GNU Lesser General  Public
  License along with this library.

//////////////////////////////////////////////////////////////////////////////*/



#ifndef MOC_ACTION_H
#define MOC_ACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

#ifndef NDEBUG
#define DEBUG( ... ) { printf(" /*["); printf( __VA_ARGS__ ); printf("]*/ "); }
#else
#define DEBUG( ... ) ;
#endif

#define CONCAT( dest , ... ) string_append(dest, __VA_ARGS__, NULL)

char * string_append(char *first, ... ) {
    va_list ap;
    va_start (ap, first);         /* Initialize the argument list. */

    char *str_in = first;
    char *str = malloc(sizeof(char) * strlen(str_in));
    strcat(str,str_in);

    str_in = va_arg (ap,char *);
    while (str_in) {
        char *tmp = malloc(sizeof(char) * (strlen(str)+strlen(str_in)) );
        memcpy(tmp,str,strlen(str));
        memcpy(tmp+strlen(str),str_in,strlen(str_in));
        free(str);
        str = tmp;
        str_in = va_arg (ap,char *);
    }
    return str;
}






// ACTIONS //



#define SIMPLE_DECLARATION simple_declaration_action

static int simple_declaration_action(const char *type, const char *ids);






// move to implementation .. //
static int simple_declaration_action(const char *type, const char *ids) {
    DEBUG("simple_declaration -> type:\"%s\" decl:\"%s\" ",type,ids);
    return 0;
}





#endif // MOC_ACTION_H
