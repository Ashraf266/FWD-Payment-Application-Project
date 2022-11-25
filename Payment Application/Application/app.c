/*------------------------------------------------------------------
[FILE NAME]:	app.c
[AUTHOR]:		Mohamed Ashraf
[DATE CREATED]:	11/11/2022
[DESCRIPTION]:	Source file for the Application Module
------------------------------------------------------------------*/


#include "app.h"
#include <stdio.h>
#include <string.h>


void appStart(void)
{
	ST_cardData_t card;
	strcpy((char *)card.cardHolderName, "Mohamed Asrhaf Ahmed");
	strcpy((char *)card.cardExpirationDate, "06/25");
	strcpy((char *)card.primaryAccountNumber, "8989374615436851");

	ST_terminalData_t term;
	strcpy((char *)term.transactionDate, "10/10/2023");
	term.transAmount = 50;
	term.maxTransAmount = 7000;

	ST_accountsDB_t* accountRefrence;

	ST_transaction_t transaction;
	transaction.cardHolderData = card;
	transaction.terminalData = term;

	/* Card */
	if (getCardHolderName(&card)  != CARD_OK)
	{
		return;
	}
	if (getCardExpiryDate(&card) != CARD_OK)
	{
		return;
	}
	if (getCardPAN(&card) != CARD_OK)
	{
		return;
	}
	
	/* Terminal */
	if (getTransactionDate(&term) != TERMINAL_OK)
	{
		return;
	}
	if (isCardExpired(&card, &term) != TERMINAL_OK)
	{
		return;
	}
	if (getTransactionAmount(&term) != TERMINAL_OK)
	{
		return;
	}
	if (isBelowMaxAmount(&term) != TERMINAL_OK)
	{
		return;
	}
	
	/* Server */

	if (isValidAccount(&transaction.cardHolderData, &accountRefrence) != SERVER_OK)
	{
		printf("Declined Invalid account\n");
		return;
	}


	if (isBlockedAccount(accountRefrence) != SERVER_OK)
	{
		printf("Declined stolen card\n");
		return;
	}

	if (isAmountAvailable(&transaction.terminalData, accountRefrence) != SERVER_OK)
	{
		printf("Declinded Insuffecient funds\n");
		return;
	}

	/* Update the balance */
	recieveTransactionData(&transaction);

	/* Save the transaction */
	saveTransaction(&transaction);

}



