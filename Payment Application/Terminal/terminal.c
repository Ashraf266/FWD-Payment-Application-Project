/*------------------------------------------------------------------
[FILE NAME]:	terminal.c
[AUTHOR]:		Mohamed Ashraf
[DATE CREATED]:	10/11/2022
[DESCRIPTION]:	Source file for the Terminal Module
------------------------------------------------------------------*/

#include "terminal.h"
#include <stdio.h>
#include <string.h>


/*
Description:
1.This function will ask for the transaction date and store it in terminal data.
2.Transaction date is 10 characters string in the format DD/MM/YYYY, e.g 25/06/2022.
3.If the transaction date is NULL or is less than 10 characters or wrong format will return the WRONG_DATE error,
	else return TERMINAL_OK.
*/
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
	int i;
	/* Checking length */
	if (strlen((char *)termData->transactionDate) != 10)
	{
		return WRONG_DATE;
	}
	/* Checking Format */
	for (i = 0; i < 5; i++)
	{
		/* Checking DD */
		if (i == 0)
		{
			if (termData->transactionDate[i] < '0' || termData->transactionDate[i] > '3')
			{
				return WRONG_DATE;
			}
		}
		else if (i == 1)
		{
			if (termData->transactionDate[0] == '3')
			{
				if (termData->transactionDate[i] > '1')
				{
					return WRONG_DATE;
				}
			}
			else
			{
				if (termData->transactionDate[i] < '0' || termData->transactionDate[i] > '9')
				{
					return WRONG_DATE;
				}
			}
		}
		/* Checking '/' */
		else if (i == 2 || i == 5)
		{
			if (termData->transactionDate[i] != '/')
			{
				return WRONG_DATE;
			}
		}
		/* Checking MM */
		else if (i == 3)
		{
			if (termData->transactionDate[i] < '0' || termData->transactionDate[i] > '1')
			{
				return WRONG_DATE;
			}
		}
		else if (i == 4)
		{
			if (termData->transactionDate[3] == '0')
			{
				if (termData->transactionDate[i] < '1' || termData->transactionDate[i] > '9')
				{
					return WRONG_DATE;
				}
			}
			else
			{
				if (termData->transactionDate[i] < '0' || termData->transactionDate[i] > '2')
				{
					return WRONG_DATE;
				}
			}
		}
		/* Checking YYYY */
		else
		{
			if (termData->transactionDate[i] < '0' || termData->transactionDate[i] > '9')
			{
				return WRONG_DATE;
			}
		}
	}
	/* if the code reached this section means everything is OK */
	return TERMINAL_OK;
}


/*
Description: function to test getTransactionDate() Function
*/
void getTransactionDateTest(void)
{
	ST_terminalData_t test;
	printf("getTransactionDate function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: getTransactionDate\n");
	printf("\n");
	printf("Test Case 1:\n");
	printf("Input Data: 1234567891011\n");
	strcpy((char *)test.transactionDate, "1234567891011");
	printf("Expected Result: WRONG_DATE\n");
	printf("Actual Result: ");
	if(getTransactionDate(&test) != TERMINAL_OK)
	{
		printf("WRONG_DATE\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: 99/23/2012\n");
	strcpy((char *)test.transactionDate, "99/23/2012");
	printf("Expected Result: WRONG_DATE\n");
	printf("Actual Result: ");
	if(getTransactionDate(&test) != TERMINAL_OK)
	{
		printf("WRONG_DATE\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data: 30/15/2023\n");
	strcpy((char *)test.transactionDate, "30/15/2023");
	printf("Expected Result: WRONG_DATE\n");
	printf("Actual Result: ");
	if(getTransactionDate(&test) != TERMINAL_OK)
	{
		printf("WRONG_DATE\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("Test Case 4:\n");
	printf("Input Data: 12/10/2023\n");
	strcpy((char *)test.transactionDate, "12/10/2023");
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	if(getTransactionDate(&test) != TERMINAL_OK)
	{
		printf("WRONG_DATE\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("getTransactionDate function Test Ended!! \n");
	printf("\n");
}


/*
Description:
1.This function compares the card expiry date with the transaction date.
2.If the card expiration date is before the transaction date will return EXPIRED_CARD, else return TERMINAL_OK.
*/
EN_terminalError_t isCardExpired(ST_cardData_t* cardData, ST_terminalData_t* termData)
{
	if (termData->transactionDate[8] > cardData->cardExpirationDate[3])
	{
		return EXPIRED_CARD;
	}
	else if (termData->transactionDate[9] > cardData->cardExpirationDate[4])
	{
		return EXPIRED_CARD;
	}
	else if ((termData->transactionDate[9] == cardData->cardExpirationDate[4]) \
		&& (termData->transactionDate[8] == cardData->cardExpirationDate[3]))
	{
		 if (termData->transactionDate[3] > cardData->cardExpirationDate[0])
		 {
		 	 return EXPIRED_CARD;
		 }
		 else if (termData->transactionDate[4] > cardData->cardExpirationDate[1])
		 {
		 	 return EXPIRED_CARD;
		 }
	}
	/* if the code reached this section means everything is OK */
	return TERMINAL_OK;
}


/*
Description: function to test isCardExpried() Function
*/
void isCardExpriedTest(void)
{
	ST_cardData_t test_Cr;
	ST_terminalData_t test_Tr;
	printf("isCardExpried function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: isCardExpried\n");
	printf("\n");
	printf("Test Case 1:\n");
	printf("Input Data: Transaction Date: 12/10/2023 , Card Expiration Date: 08/22\n");
	strcpy((char *)test_Tr.transactionDate, "12/10/2023");
	strcpy((char *)test_Cr.cardExpirationDate, "08/22");
	printf("Expected Result: EXPIRED_CARD\n");
	printf("Actual Result: ");
	if(isCardExpired(&test_Cr, &test_Tr) != TERMINAL_OK)
	{
		printf("EXPIRED_CARD\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: Transaction Date: 12/10/2023 , Card Expiration Date: 11/24\n");
	strcpy((char *)test_Tr.transactionDate, "12/10/2023");
	strcpy((char *)test_Cr.cardExpirationDate, "11/24");
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	if(isCardExpired(&test_Cr, &test_Tr) != TERMINAL_OK)
	{
		printf("EXPIRED_CARD\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("isCardExpried function Test Ended!! \n");
	printf("\n");
}


/*
Description:
1.This function asks for the transaction amount and saves it into terminal data.
2.If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT, else return TERMINAL_OK.
*/
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount <= 0)
	{
		return INVALID_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}


/*
Description: function to test getTransactionAmount() Function
*/
void getTransactionAmountTest(void)
{
	ST_terminalData_t test;
	printf("getTransactionAmount function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: getTransactionAmount\n");
	printf("\n");
	printf("Test Case 1:\n");
	printf("Input Data: 0\n");
	test.transAmount = 0;
	printf("Expected Result: INVALID_AMOUNT\n");
	printf("Actual Result: ");
	if(getTransactionAmount(&test) != TERMINAL_OK)
	{
		printf("INVALID_AMOUNT\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: -330\n");
	test.transAmount = -330;
	printf("Expected Result: INVALID_AMOUNT\n");
	printf("Actual Result: ");
	if(getTransactionAmount(&test) != TERMINAL_OK)
	{
		printf("INVALID_AMOUNT\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data: 1000\n");
	test.transAmount = 1000;
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	if(getTransactionAmount(&test) != TERMINAL_OK)
	{
		printf("INVALID_AMOUNT\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("getTransactionAmount function Test Ended!! \n");
	printf("\n");
}


/*
Description:
1.This function compares the transaction amount with the terminal max allowed amount.
2.If the transaction amount is larger than the terminal max allowed amount will return EXCEED_MAX_AMOUNT, else return TERMINAL_OK.
*/
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
	if (termData->transAmount > termData->maxTransAmount)
	{
		return EXCEED_MAX_AMOUNT;
	}
	else
	{
		return TERMINAL_OK;
	}
}


/*
Description: function to test isBelowMaxAmount() Function
*/
void isBelowMaxAmountTest(void)
{
	ST_terminalData_t test;
	test.maxTransAmount = 5000;
	printf("isBelowMaxAmount function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: isBelowMaxAmount\n");
	printf("\n");
	printf("Test Case 1:\n");
	printf("Input Data: 6000 ,Max=5000\n");
	test.transAmount = 6000;
	printf("Expected Result: EXCEED_MAX_AMOUNT\n");
	printf("Actual Result: ");
	if(isBelowMaxAmount(&test) != TERMINAL_OK)
	{
		printf("EXCEED_MAX_AMOUNT\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: 500 ,Max=5000\n");
	test.transAmount = 500;
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	if(isBelowMaxAmount(&test) != TERMINAL_OK)
	{
		printf("EXCEED_MAX_AMOUNT\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("isBelowMaxAmount function Test Ended!! \n");
	printf("\n");
}


/*
Description:
1.This function takes the maximum allowed amount and stores it into terminal data.
2.Transaction max amount is a float number.
3.If transaction max amount less than or equal to 0 will return the INVALID_MAX_AMOUNT error, else return TERMINAL_OK.
*/
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData, float maxAmount)
{
	if (maxAmount <= 0)
	{
		return INVALID_MAX_AMOUNT;
	}
	else
	{
		termData->maxTransAmount = maxAmount;
		return TERMINAL_OK;
	}
}


/*
Description: function to test setMaxAmount() Function
*/
void setMaxAmountTest(void)
{
	ST_terminalData_t test;
	printf("setMaxAmount function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: setMaxAmount\n");
	printf("\n");
	printf("Test Case 1:\n");
	printf("Input Data: 0\n");
	test.maxTransAmount = 0;
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	printf("Actual Result: ");
	if(setMaxAmount(&test,0) != TERMINAL_OK)
	{
		printf("INVALID_MAX_AMOUNT\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("Test Case 2:\n");
	printf("Input Data: -330\n");
	test.maxTransAmount = -330;
	printf("Expected Result: INVALID_MAX_AMOUNT\n");
	printf("Actual Result: ");
	if(setMaxAmount(&test,-330) != TERMINAL_OK)
	{
		printf("INVALID_MAX_AMOUNT\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("Test Case 3:\n");
	printf("Input Data: 1000\n");
	test.maxTransAmount = 1000;
	printf("Expected Result: TERMINAL_OK\n");
	printf("Actual Result: ");
	if(setMaxAmount(&test,1000) != TERMINAL_OK)
	{
		printf("INVALID_MAX_AMOUNT\n");
	}
	else
	{
		printf("TERMINAL_OK\n");
	}
	printf("\n");
	printf("setMaxAmount function Test Ended!! \n");
	printf("\n");
}
