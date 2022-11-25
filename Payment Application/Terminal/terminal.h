/*------------------------------------------------------------------
[FILE NAME]:	terminal.h
[AUTHOR]:		Mohamed Ashraf
[DATE CREATED]:	10/11/2022
[DESCRIPTION]:	Header file for the Terminal Module
------------------------------------------------------------------*/
#ifndef TERMINAL_H_
#define TERMINAL_H_

#include "std_types.h"
#include "card.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

 /*------------------------------------------------------------------
 [Enum Name]:                EN_terminalError_t
 [Enum Description]:         contains Terminal status used in the application
 ------------------------------------------------------------------*/
typedef enum EN_terminalError_t
{
    TERMINAL_OK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
}EN_terminalError_t;

/*------------------------------------------------------------------
[Structure Name]:           ST_cardData_t
[Structure Description]:    contains all the Terminal data
------------------------------------------------------------------*/
typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
}ST_terminalData_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

 /*------------------------------------------------------------------
 [Function Name]:   getTransactionDate
 [Description]:     This function will ask for the transaction date and store it in terminal data.
 [Args]:
 [in]	NONE
 [out]	NONE
 [in/out]   ST_terminalData_t* termData
                    Pointer to the termData structure

 [Returns]: Error if found, otherwise return success
 ------------------------------------------------------------------*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData);

/*------------------------------------------------------------------
[Function Name]:   isCardExpired
[Description]:     This function compares the card expiry date with the transaction date.
[Args]:
[in]	NONE
[out]	NONE
[in/out]   ST_terminalData_t* termData
                   Pointer to the termData structure
           ST_cardData_t* cardData
                   Pointer to the cardData structure

[Returns]: Error if found, otherwise return success
------------------------------------------------------------------*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData);

/*------------------------------------------------------------------
[Function Name]:   getTransactionAmount
[Description]:     This function asks for the transaction amount and saves it into terminal data.
[Args]:
[in]	NONE
[out]	NONE
[in/out]   ST_terminalData_t* termData
                   Pointer to the termData structure

[Returns]: Error if found, otherwise return success
------------------------------------------------------------------*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData);

/*------------------------------------------------------------------
[Function Name]:   isBelowMaxAmount
[Description]:     This function compares the transaction amount with the terminal max allowed amount.
[Args]:
[in]	NONE
[out]	NONE
[in/out]   ST_terminalData_t* termData
                   Pointer to the termData structure

[Returns]: Error if found, otherwise return success
------------------------------------------------------------------*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData);

/*------------------------------------------------------------------
[Function Name]:   setMaxAmount
[Description]:     This function takes the maximum allowed amount and stores it into terminal data.
[Args]:
[in]	   float maxAmount
                   The Maximum Amount allowed to be stored
[out]	NONE
[in/out]   ST_terminalData_t* termData
                   Pointer to the termData structure

[Returns]: Error if found, otherwise return success
------------------------------------------------------------------*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount);

/*Test Functions Prototypes*/
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmountTest(void);
void setMaxAmountTest(void);





#endif /* TERMINAL_H_ */
