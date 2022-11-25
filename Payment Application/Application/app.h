/*------------------------------------------------------------------
[FILE NAME]:	app.h
[AUTHOR]:		Mohamed Ashraf
[DATE CREATED]:	11/11/2022
[DESCRIPTION]:	Header file for the Application Module
------------------------------------------------------------------*/
#ifndef APP_H_
#define APP_H_



#include "std_types.h"
#include "card.h"
#include "terminal.h"
#include "server.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

 /*------------------------------------------------------------------
  [Function Name]:   appStart
  [Description]:     the app function
  [Args]:
  [in]	    NONE
  [out]	    NONE
  [in/out]   NONE

  [Returns]: Nothing
  ------------------------------------------------------------------*/
void appStart(void);


#endif /* APP_H_ */
