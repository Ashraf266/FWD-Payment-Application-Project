/*------------------------------------------------------------------
[FILE NAME]:	card.h
[AUTHOR]:		Mohamed Ashraf
[DATE CREATED]:	10/11/2022
[DESCRIPTION]:	Header file for the Card Module
------------------------------------------------------------------*/
#ifndef CARD_H_
#define CARD_H_

#include "std_types.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS



/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/*------------------------------------------------------------------
[Enum Name]:                EN_cardError_t
[Enum Description]:         contains card status used in the application
------------------------------------------------------------------*/
typedef enum EN_cardError_t
{
    CARD_OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
}EN_cardError_t;

 /*------------------------------------------------------------------
 [Structure Name]:           ST_cardData_t
 [Structure Description]:    contains all the card data
 ------------------------------------------------------------------*/
typedef struct ST_cardData_t
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
}ST_cardData_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

 /*------------------------------------------------------------------
 [Function Name]:   getCardHolderName
 [Description]:     This function will ask for the cardholder's name and store it into card data.
 [Args]:
 [in]	NONE
 [out]	NONE
 [in/out]   ST_cardData_t* cardData
                    Pointer to the cardData structure

 [Returns]: Error if found, otherwise return success
 ------------------------------------------------------------------*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData);

/*------------------------------------------------------------------
[Function Name]:   getCardExpiryDate
[Description]:     This function will ask for the card expiry date and store it in card data.
[Args]:
[in]	NONE
[out]	NONE
[in/out]   ST_cardData_t* cardData
                   Pointer to the cardData structure

[Returns]: Error if found, otherwise return success
------------------------------------------------------------------*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData);

/*------------------------------------------------------------------
[Function Name]:   getCardPAN
[Description]:     This function will ask for the card's Primary Account Number and store it in card data.
[Args]:
[in]	NONE
[out]	NONE
[in/out]   ST_cardData_t* cardData
                   Pointer to the cardData structure

[Returns]: Error if found, otherwise return success
------------------------------------------------------------------*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData);


/*Test Functions Prototypes*/
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);


#endif /* CARD_H_ */