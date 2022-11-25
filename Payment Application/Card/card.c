/*------------------------------------------------------------------
[FILE NAME]:	card.c
[AUTHOR]:		Mohamed Ashraf
[DATE CREATED]:	10/11/2022
[DESCRIPTION]:	Source file for the Card Module
------------------------------------------------------------------*/

#include "card.h"
#include <stdio.h>
#include <string.h>



/*
Description:
1.This function will ask for the cardholder's name and store it into card data.
2.Cardholder name is 24 alphabetic characters string max and 20 min.
3.If the cardholder name is NULL, less than 20 characters or more than 24 will return a WRONG_NAME error, else return CARD_OK.
*/
EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
	if (cardData->cardHolderName[0] == '\0' || strlen((char *)cardData->cardHolderName) < 20 || strlen((char *)cardData->cardHolderName) > 24)
	{
		return WRONG_NAME;
	}
	else
	{
		return CARD_OK;
	}

}

/*
Description: function to test getCardHolderName() Function
*/
void getCardHolderNameTest(void)
{
	ST_cardData_t test;
	printf("getCardHolderName function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: getCardHolderName\n");
	printf("\n");
	printf("Test Case 1:\n");
	printf("Input Data: Mohamed\n");
	strcpy((char *)test.cardHolderName, "Mohamed");
	printf("Expected Result: WRONG_NAME\n");
	printf("Actual Result: ");
	if(getCardHolderName(&test) != CARD_OK)
	{
		printf("WRONG_NAME\n");
	}
	else
	{
		printf("CARD_OK\n");
	}
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: Mohamed Ashraf AbdelFatah\n");
	strcpy((char *)test.cardHolderName, "Mohamed Ashraf AbdelFatah");
	printf("Expected Result: WRONG_NAME\n");
	printf("Actual Result: ");
	if(getCardHolderName(&test) != CARD_OK)
	{
		printf("WRONG_NAME\n");
	}
	else
	{
		printf("CARD_OK\n");
	}
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data: Mohamed Ashraf Ahmed\n");
	strcpy((char *)test.cardHolderName, "Mohamed Ashraf Ahmed");
	printf("Expected Result: CARD_OK\n");
	printf("Actual Result: ");
	if(getCardHolderName(&test) != CARD_OK)
	{
		printf("WRONG_NAME\n");
	}
	else
	{
		printf("CARD_OK\n");
	}
	printf("\n");
	printf("getCardHolderName function Test Ended!! \n");
	printf("\n");
}


/*
Description:
1.This function will ask for the card expiry date and store it in card data.
2.Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25".
3.If the card expiry date is NULL, less or more than 5 characters,
  or has the wrong format will return the WRONG_EXP_DATE error, else return CARD_OK.
*/
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
	int i;
	/* Checking string length */
	if (strlen((char *)cardData->cardExpirationDate) != 5)
	{
		return WRONG_EXP_DATE;
	}
	/* Checking Format */
	for (i = 0; i < 5; i++)
	{
		/* Checking MM */
		if (i == 0)
		{
			if (cardData->cardExpirationDate[i] < '0' || cardData->cardExpirationDate[i] > '1')
			{
				return WRONG_EXP_DATE;
			}
		}
		else if (i == 1)
		{
			if (cardData->cardExpirationDate[0] == '0')
			{
				if (cardData->cardExpirationDate[i] < '1' || cardData->cardExpirationDate[i] > '9')
				{
					return WRONG_EXP_DATE;
				}
			}
			else
			{
				if (cardData->cardExpirationDate[i] < '0' || cardData->cardExpirationDate[i] > '2')
				{
					return WRONG_EXP_DATE;
				}
			}
		}
		/* Checking '/' */
		else if (i == 2)
		{
			if (cardData->cardExpirationDate[i] != '/')
			{
				return WRONG_EXP_DATE;
			}
		}
		/* Checking YY */
		else
		{
			if (cardData->cardExpirationDate[i] < '0' || cardData->cardExpirationDate[i] > '9')
			{
				return WRONG_EXP_DATE;
			}
		}
	}
	/* if the code reached this section means everything is OK */
	return CARD_OK;
}

/*
Description: function to test getCardExpiryDate() Function
*/
void getCardExpiryDateTest(void)
{
	ST_cardData_t test;
	printf("getCardExpiryDate function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: getCardExpiryDate\n");
	printf("\n");
	printf("Test Case 1:\n");
	printf("Input Data: 12345\n");
	strcpy((char *)test.cardExpirationDate, "12345");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: ");
	if(	getCardExpiryDate(&test) != CARD_OK)
	{
		printf("WRONG_EXP_DATE\n");
	}
	else
	{
		printf("CARD_OK\n");
	}
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: 99/23\n");
	strcpy((char *)test.cardExpirationDate, "99/23");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: ");
	getCardExpiryDate(&test);
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data: 00/23\n");
	strcpy((char *)test.cardExpirationDate, "00/23");
	printf("Expected Result: WRONG_EXP_DATE\n");
	printf("Actual Result: ");
	if(	getCardExpiryDate(&test) != CARD_OK)
	{
		printf("WRONG_EXP_DATE\n");
	}
	else
	{
		printf("CARD_OK\n");
	}
	printf("\n");
	printf("Test Case 4:\n");
	printf("Input Data: 05/28\n");
	strcpy((char *)test.cardExpirationDate, "05/28");
	printf("Expected Result: CARD_OK\n");
	printf("Actual Result: ");
	if(	getCardExpiryDate(&test) != CARD_OK)
	{
		printf("WRONG_EXP_DATE\n");
	}
	else
	{
		printf("CARD_OK\n");
	}
	printf("\n");
	printf("getCardExpiryDate function Test Ended!! \n");
	printf("\n");
}


/*
Description:
1.This function will ask for the card's Primary Account Number and store it in card data.
2.PAN is 20 numeric characters string, 19 character max, and 16 character min.
3.If the PAN is NULL, less than 16 or more than 19 characters, will return the WRONG_PAN error, else return CARD_OK.
*/
EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
	if (cardData->primaryAccountNumber[0] == '\0' || strlen((char *)cardData->primaryAccountNumber) < 16 || strlen((char *)cardData->primaryAccountNumber) > 19)
	{
		return WRONG_PAN;
	}
	else
	{
		return CARD_OK;
	}
}

/*
Description: function to test getCardPAN() Function
*/
void getCardPANTest(void)
{
	ST_cardData_t test;
	printf("getCardPAN function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: getCardPAN\n");
	printf("\n");
	printf("Test Case 1:\n");
	printf("Input Data: 123456789\n");
	strcpy((char *)test.primaryAccountNumber, "123456789");
	printf("Expected Result: WRONG_PAN\n");
	printf("Actual Result: ");
	if(	getCardPAN(&test) != CARD_OK)
	{
		printf("WRONG_PAN\n");
	}
	else
	{
		printf("CARD_OK\n");
	}
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: 123456789123456789123456789\n");
	strcpy((char *)test.primaryAccountNumber, "123456789123456789123456789");
	printf("Expected Result: WRONG_PAN\n");
	printf("Actual Result: ");
	if(	getCardPAN(&test) != CARD_OK)
	{
		printf("WRONG_PAN\n");
	}
	else
	{
		printf("CARD_OK\n");
	}
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data: 123456789123456789\n");
	strcpy((char *)test.primaryAccountNumber, "123456789123456789");
	printf("Expected Result: CARD_OK\n");
	printf("Actual Result: ");
	if(	getCardPAN(&test) != CARD_OK)
	{
		printf("WRONG_PAN\n");
	}
	else
	{
		printf("CARD_OK\n");
	}
	printf("\n");
	printf("getCardPAN function Test Ended!! \n");
	printf("\n");
}
