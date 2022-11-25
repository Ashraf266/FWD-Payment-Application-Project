#include "card.h"
#include "terminal.h"
#include "server.h"
#include "Application/app.h"
#include <stdio.h>
#include <string.h>

void Transaction_approved_user_story(void);
void Exceed_the_maximum_amount_user_story(void);
void Insufficient_fund_user_story(void);
void Expired_card_user_story(void);
void Stolen_card_user_story(void);

int main(void)
{
	/* Card Module Test */
	//getCardHolderNameTest();
	//getCardExpiryDateTest();
	//getCardPANTest();

	/* Terminal Module Test */
	//getTransactionDateTest();
	//isCardExpriedTest();
	//getTransactionAmountTest();
	//isBelowMaxAmountTest();
	//setMaxAmountTest();

	/* Server Module Test */
	//recieveTransactionDataTest();
	//isValidAccountTest();
	//isBlockedAccountTest();
	//isAmountAvailableTest();
	//saveTransactionTest();
	//listSavedTransactionsTest();

	/* Application Module Test */
	//appStart();



	/*************** Testing The Whole application with Different Stories ***************/

	/*As a bank customer have an account and has a valid and not expired card,
	I want to withdraw an amount of money less than the maximum allowed and less than or equal to the amount in my balance,
	so that I am expecting that the transaction is approved and my account balance is reduced by the withdrawn amount.*/
	printf("Transaction approved user story\n");
	Transaction_approved_user_story();

	printf("-----------------------------\n");



	/*As a bank customer have an account, that has a valid and not expired card,
	I want to withdraw an amount of money that exceeds the maximum allowed amount so that I am expecting the transaction declined.*/
	printf("Exceed the maximum amount user story\n");
	Exceed_the_maximum_amount_user_story();

	printf("-----------------------------\n");



	/*As a bank customer have an account and has a valid and not expired card,
	I want to withdraw an amount of money less than the maximum allowed and larger than the amount in my balance
	so that I am expecting that the transaction declined.*/
	printf("Insufficient fund user story\n");
	Insufficient_fund_user_story();

	printf("-----------------------------\n");



	/*As a bank customer have an account and a valid but expired card,
	I want to withdraw an amount of money so that I expect that the transaction declined.*/
	printf("Expired card user story\n");
	Expired_card_user_story();

	printf("-----------------------------\n");



	/*As a bank customer have an account and has a valid and not expired but stolen card,
	I want to block anyone from using my card so that I am expecting that any transaction made by this card is declined.*/
	printf("Stolen card user story\n");
	Stolen_card_user_story();
}


void Transaction_approved_user_story(void)
{
	/* Transaction approved user story */
	ST_cardData_t card;
	strcpy((char *)card.cardHolderName, "Mohamed Asrhaf Ahmed");
	strcpy((char *)card.cardExpirationDate, "06/25");
	strcpy((char *)card.primaryAccountNumber, "8989374615436851");

	ST_accountsDB_t* accountRefrence;

	ST_terminalData_t term;
	strcpy((char *)term.transactionDate, "10/10/2023");
	term.transAmount = 50;
	term.maxTransAmount = 7000;

	ST_transaction_t transaction;
	transaction.cardHolderData = card;
	transaction.terminalData = term;

	/* Card */
	if (getCardHolderName(&card) != CARD_OK)
	{
		printf("WRONG_NAME\n");
		return;
	}
	if (getCardExpiryDate(&card) != CARD_OK)
	{
		printf("WRONG_EXP_DATE\n");
		return;
	}
	if (getCardPAN(&card) != CARD_OK)
	{
		printf("WRONG_PAN\n");
		return;
	}

	/* Terminal */
	if (getTransactionDate(&term) != TERMINAL_OK)
	{
		printf("WRONG_DATE\n");
		return;
	}
	if (isCardExpired(&card, &term) != TERMINAL_OK)
	{
		printf("EXPIRED_CARD\n");
		return;
	}
	if (getTransactionAmount(&term) != TERMINAL_OK)
	{
		printf("INVALID_AMOUNT\n");
		return;
	}
	if (isBelowMaxAmount(&term) != TERMINAL_OK)
	{
		printf("EXCEED_MAX_AMOUNT\n");
		return;
	}

	/* Server */

	if (isValidAccount(&transaction.cardHolderData, &accountRefrence) != SERVER_OK)
	{
		printf("ACCOUNT_NOT_FOUND\n");
		return;
	}


	if (isBlockedAccount(accountRefrence) != SERVER_OK)
	{
		printf("BLOCKED_ACCOUNT\n");
		return;
	}

	if (isAmountAvailable(&transaction.terminalData, accountRefrence) != SERVER_OK)
	{
		printf("LOW_BALANCE\n");
		return;
	}

	/* Update the balance */
	recieveTransactionData(&transaction);

	/* Save the transaction */
	saveTransaction(&transaction);


}



void Exceed_the_maximum_amount_user_story(void)
{
	/* Transaction approved user story */
	ST_cardData_t card;
	strcpy((char *)card.cardHolderName, "Mohamed Asrhaf Ahmed");
	strcpy((char *)card.cardExpirationDate, "06/25");
	strcpy((char *)card.primaryAccountNumber, "8989374615436851");

	ST_terminalData_t term;
	strcpy((char *)term.transactionDate, "10/10/2023");
	term.transAmount = 5000;
	term.maxTransAmount = 2000;

	ST_accountsDB_t* accountRefrence;

	ST_transaction_t transaction;
	transaction.cardHolderData = card;
	transaction.terminalData = term;

	/* Card */
	if (getCardHolderName(&card) != CARD_OK)
	{
		printf("WRONG_NAME\n");
		return;
	}
	if (getCardExpiryDate(&card) != CARD_OK)
	{
		printf("WRONG_EXP_DATE\n");
		return;
	}
	if (getCardPAN(&card) != CARD_OK)
	{
		printf("WRONG_PAN\n");
		return;
	}

	/* Terminal */
	if (getTransactionDate(&term) != TERMINAL_OK)
	{
		printf("WRONG_DATE\n");
		return;
	}
	if (isCardExpired(&card, &term) != TERMINAL_OK)
	{
		printf("EXPIRED_CARD\n");
		return;
	}
	if (getTransactionAmount(&term) != TERMINAL_OK)
	{
		printf("INVALID_AMOUNT\n");
		return;
	}
	if (isBelowMaxAmount(&term) != TERMINAL_OK)
	{
		printf("EXCEED_MAX_AMOUNT\n");
		return;
	}

	/* Server */

	if (isValidAccount(&transaction.cardHolderData, &accountRefrence) != SERVER_OK)
	{
		printf("ACCOUNT_NOT_FOUND\n");
		return;
	}


	if (isBlockedAccount(accountRefrence) != SERVER_OK)
	{
		printf("BLOCKED_ACCOUNT\n");
		return;
	}

	if (isAmountAvailable(&transaction.terminalData, accountRefrence) != SERVER_OK)
	{
		printf("LOW_BALANCE\n");
		return;
	}

	/* Update the balance */
	recieveTransactionData(&transaction);

	/* Save the transaction */
	saveTransaction(&transaction);

}

void Insufficient_fund_user_story(void)
{
	/* Transaction approved user story */
	ST_cardData_t card;
	strcpy((char *)card.cardHolderName, "Mohamed Asrhaf Ahmed");
	strcpy((char *)card.cardExpirationDate, "06/25");
	strcpy((char *)card.primaryAccountNumber, "8989374615436851");

	ST_terminalData_t term;
	strcpy((char *)term.transactionDate, "10/10/2023");
	term.transAmount = 5000;
	term.maxTransAmount = 8000;

	ST_accountsDB_t* accountRefrence;

	ST_transaction_t transaction;
	transaction.cardHolderData = card;
	transaction.terminalData = term;

	/* Card */
	if (getCardHolderName(&card) != CARD_OK)
	{
		printf("WRONG_NAME\n");
		return;
	}
	if (getCardExpiryDate(&card) != CARD_OK)
	{
		printf("WRONG_EXP_DATE\n");
		return;
	}
	if (getCardPAN(&card) != CARD_OK)
	{
		printf("WRONG_PAN\n");
		return;
	}

	/* Terminal */
	if (getTransactionDate(&term) != TERMINAL_OK)
	{
		printf("WRONG_DATE\n");
		return;
	}
	if (isCardExpired(&card, &term) != TERMINAL_OK)
	{
		printf("EXPIRED_CARD\n");
		return;
	}
	if (getTransactionAmount(&term) != TERMINAL_OK)
	{
		printf("INVALID_AMOUNT\n");
		return;
	}
	if (isBelowMaxAmount(&term) != TERMINAL_OK)
	{
		printf("EXCEED_MAX_AMOUNT\n");
		return;
	}

	/* Server */

	if (isValidAccount(&transaction.cardHolderData, &accountRefrence) != SERVER_OK)
	{
		printf("ACCOUNT_NOT_FOUND\n");
		return;
	}


	if (isBlockedAccount(accountRefrence) != SERVER_OK)
	{
		printf("BLOCKED_ACCOUNT\n");
		return;
	}

	if (isAmountAvailable(&transaction.terminalData, accountRefrence) != SERVER_OK)
	{
		printf("LOW_BALANCE\n");
		return;
	}

	/* Update the balance */
	recieveTransactionData(&transaction);

	/* Save the transaction */
	saveTransaction(&transaction);

}


void Expired_card_user_story(void)
{
	/* Transaction approved user story */
	ST_cardData_t card;
	strcpy((char *)card.cardHolderName, "Mohamed Asrhaf Ahmed");
	strcpy((char *)card.cardExpirationDate, "06/21");
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
	if (getCardHolderName(&card) != CARD_OK)
	{
		printf("WRONG_NAME\n");
		return;
	}
	if (getCardExpiryDate(&card) != CARD_OK)
	{
		printf("WRONG_EXP_DATE\n");
		return;
	}
	if (getCardPAN(&card) != CARD_OK)
	{
		printf("WRONG_PAN\n");
		return;
	}

	/* Terminal */
	if (getTransactionDate(&term) != TERMINAL_OK)
	{
		printf("WRONG_DATE\n");
		return;
	}
	if (isCardExpired(&card, &term) != TERMINAL_OK)
	{
		printf("EXPIRED_CARD\n");
		return;
	}
	if (getTransactionAmount(&term) != TERMINAL_OK)
	{
		printf("INVALID_AMOUNT\n");
		return;
	}
	if (isBelowMaxAmount(&term) != TERMINAL_OK)
	{
		printf("EXCEED_MAX_AMOUNT\n");
		return;
	}

	/* Server */

	if (isValidAccount(&transaction.cardHolderData, &accountRefrence) != SERVER_OK)
	{
		printf("ACCOUNT_NOT_FOUND\n");
		return;
	}


	if (isBlockedAccount(accountRefrence) != SERVER_OK)
	{
		printf("BLOCKED_ACCOUNT\n");
		return;
	}

	if (isAmountAvailable(&transaction.terminalData, accountRefrence) != SERVER_OK)
	{
		printf("LOW_BALANCE\n");
		return;
	}

	/* Update the balance */
	recieveTransactionData(&transaction);

	/* Save the transaction */
	saveTransaction(&transaction);

}


void Stolen_card_user_story(void)
{
	/* Transaction approved user story */
	ST_cardData_t card;
	strcpy((char *)card.cardHolderName, "Mohamed Asrhaf Ahmed");
	strcpy((char *)card.cardExpirationDate, "06/25");
	strcpy((char *)card.primaryAccountNumber, "5807007076043875");

	ST_terminalData_t term;
	strcpy((char *)term.transactionDate, "10/10/2023");
	term.transAmount = 50;
	term.maxTransAmount = 7000;

	ST_accountsDB_t* accountRefrence;

	ST_transaction_t transaction;
	transaction.cardHolderData = card;
	transaction.terminalData = term;

	/* Card */
	if (getCardHolderName(&card) != CARD_OK)
	{
		printf("WRONG_NAME\n");
		return;
	}
	if (getCardExpiryDate(&card) != CARD_OK)
	{
		printf("WRONG_EXP_DATE\n");
		return;
	}
	if (getCardPAN(&card) != CARD_OK)
	{
		printf("WRONG_PAN\n");
		return;
	}

	/* Terminal */
	if (getTransactionDate(&term) != TERMINAL_OK)
	{
		printf("WRONG_DATE\n");
		return;
	}
	if (isCardExpired(&card, &term) != TERMINAL_OK)
	{
		printf("EXPIRED_CARD\n");
		return;
	}
	if (getTransactionAmount(&term) != TERMINAL_OK)
	{
		printf("INVALID_AMOUNT\n");
		return;
	}
	if (isBelowMaxAmount(&term) != TERMINAL_OK)
	{
		printf("EXCEED_MAX_AMOUNT\n");
		return;
	}

	/* Server */

	if (isValidAccount(&transaction.cardHolderData, &accountRefrence) != SERVER_OK)
	{
		printf("ACCOUNT_NOT_FOUND\n");
		return;
	}


	if (isBlockedAccount(accountRefrence) != SERVER_OK)
	{
		printf("BLOCKED_ACCOUNT\n");
		return;
	}

	if (isAmountAvailable(&transaction.terminalData, accountRefrence) != SERVER_OK)
	{
		printf("LOW_BALANCE\n");
		return;
	}

	/* Update the balance */
	recieveTransactionData(&transaction);

	/* Save the transaction */
	saveTransaction(&transaction);

}
