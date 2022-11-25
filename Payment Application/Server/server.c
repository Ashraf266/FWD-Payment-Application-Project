/*------------------------------------------------------------------
[FILE NAME]:	server.c
[AUTHOR]:		Mohamed Ashraf
[DATE CREATED]:	11/11/2022
[DESCRIPTION]:	Source file for the Server Module
------------------------------------------------------------------*/

#include "server.h"
#include <stdio.h>
#include <string.h>



ST_accountsDB_t accountsDB[255] = { {2000.0,		RUNNING, "8989374615436851"  },
									{100000.0,	BLOCKED, 	 "5807007076043875"  },
									{7000.0,		RUNNING, "18945638745692548" },
									{6500.0,		RUNNING, "652987469875632154"},
									{3000.0,		BLOCKED, "987452369851475263"}  };

ST_transaction_t transactionsDB[255] = {0};



/*
Description:
1.This function will take all transaction data and validate its data, it contains all server logic.
2.It checks the account details and amount availability.
3.If the account does not exist return FRAUD_CARD, if the amount is not available will return DECLINED_INSUFFECIENT_FUND,
	if the account is blocked will return DECLINED_STOLEN_CARD, if a transaction can't be saved will return INTERNAL_SERVER_ERROR ,
	else returns APPROVED.
4.It will update the database with the new balance.
*/
EN_transStat_t recieveTransactionData(ST_transaction_t* transData)
{
	ST_accountsDB_t* accountRefrence;

	if (isValidAccount(&transData->cardHolderData, &accountRefrence) != SERVER_OK)
	{
		return FRAUD_CARD;
	}

	if (isBlockedAccount(accountRefrence) != SERVER_OK)
	{
		return DECLINED_STOLEN_CARD;
	}

	if (isAmountAvailable(&transData->terminalData,accountRefrence) != SERVER_OK)
	{
		return DECLINED_INSUFFECIENT_FUND;
	}

	/* Update the Balance */
	accountRefrence->balance = accountRefrence->balance - transData->terminalData.transAmount;
	/* if the code reached this section means everything is OK */
	return APPROVED;
}


/*
Description: function to test recieveTransactionData() Function
*/
void recieveTransactionDataTest(void)
{
	ST_transaction_t test;
	printf("recieveTransactionData function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: recieveTransactionData\n");
	printf("\n");
	/* Test Case 1 */
	printf("Test Case 1: \n");
	printf("Input Data: PAN: 123456789123456789  TransactionAmount: 500.0\n");
	strcpy((char *)test.cardHolderData.primaryAccountNumber, "123456789123456789");
	test.terminalData.transAmount = 500.0;
	printf("Expected Result: FRAUD_CARD\n");
	printf("Actual Result: ");
	switch(recieveTransactionData(&test))
	{
	case FRAUD_CARD:
		printf("FRAUD_CARD\n");
		break;
	case DECLINED_STOLEN_CARD:
		printf("DECLINED_STOLEN_CARD\n");
		break;
	case DECLINED_INSUFFECIENT_FUND:
		printf("DECLINED_INSUFFECIENT_FUND\n");
		break;
	default:
		printf("APPROVED\n");
	}
	printf("\n");
	/* Test Case 2 */
	printf("Test Case 2: \n");
	printf("Input Data: PAN: 8989374615436851  TransactionAmount: 5000.0\n");
	strcpy((char *)test.cardHolderData.primaryAccountNumber, "8989374615436851");
	test.terminalData.transAmount = 5000.0;
	printf("Expected Result: DECLINED_INSUFFECIENT_FUND\n");
	printf("Actual Result: ");
	switch(recieveTransactionData(&test))
	{
	case FRAUD_CARD:
		printf("FRAUD_CARD\n");
		break;
	case DECLINED_STOLEN_CARD:
		printf("DECLINED_STOLEN_CARD\n");
		break;
	case DECLINED_INSUFFECIENT_FUND:
		printf("DECLINED_INSUFFECIENT_FUND\n");
		break;
	default:
		printf("APPROVED\n");
	}
	printf("\n");
	/* Test Case 3 */
	printf("Test Case 3: \n");
	printf("Input Data: PAN: 5807007076043875  TransactionAmount: 900.0\n");
	strcpy((char *)test.cardHolderData.primaryAccountNumber, "5807007076043875");
	test.terminalData.transAmount = 900.0;
	printf("Expected Result: DECLINED_STOLEN_CARD\n");
	printf("Actual Result: ");
	switch(recieveTransactionData(&test))
	{
	case FRAUD_CARD:
		printf("FRAUD_CARD\n");
		break;
	case DECLINED_STOLEN_CARD:
		printf("DECLINED_STOLEN_CARD\n");
		break;
	case DECLINED_INSUFFECIENT_FUND:
		printf("DECLINED_INSUFFECIENT_FUND\n");
		break;
	default:
		printf("APPROVED\n");
	}
	printf("\n");
	/* Test Case 4 */
	printf("Test Case 4: \n");
	printf("Input Data: PAN: 652987469875632154  TransactionAmount: 1500.0\n");
	strcpy((char *)test.cardHolderData.primaryAccountNumber, "652987469875632154");
	test.terminalData.transAmount = 1500.0;
	printf("Expected Result: APPROVED\n");
	printf("Actual Result: ");
	switch(recieveTransactionData(&test))
	{
	case FRAUD_CARD:
		printf("FRAUD_CARD\n");
		break;
	case DECLINED_STOLEN_CARD:
		printf("DECLINED_STOLEN_CARD\n");
		break;
	case DECLINED_INSUFFECIENT_FUND:
		printf("DECLINED_INSUFFECIENT_FUND\n");
		break;
	default:
		printf("APPROVED\n");
	}
	printf("\n");
	printf("recieveTransactionData function Test Ended!! \n");
	printf("\n");
}


/*
Description:
1.This function will take card data and validate if the account related to this card exists or not.
2.It checks if the PAN exists or not in the server's database (searches for the card PAN in the DB).
3.If the PAN doesn't exist will return ACCOUNT_NOT_FOUND and the account reference will be NULL,
	else will return SERVER_OK and return a reference to this account in the DB.
*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t** accountRefrence)
{
	uint8_t i;

	/* Checking if the Account Exist */
	for (i = 0; i < 255; i++)
	{
		if (!(strcmp((char *)cardData->primaryAccountNumber, (char *)accountsDB[i].primaryAccountNumber)))
		{
			/* Account Exist */
			break;
		}
		else
		{
			if (i == 254)
			{
				*accountRefrence = NULL;
				return ACCOUNT_NOT_FOUND;
			}
		}
	}

	*accountRefrence = &accountsDB[i];
	/* if the code reached this section means everything is OK */
	return SERVER_OK;
}

/*
Description: function to test isValidAccount() Function
*/
void isValidAccountTest(void)
{
	ST_cardData_t test_card;
	ST_accountsDB_t *test_acc;
	printf("isValidAccount function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: isValidAccount\n");
	printf("\n");
	/* Test Case 1 */
	printf("Test Case 1: \n");
	printf("Input Data: PAN: 123456789123456789\n");
	strcpy((char *)test_card.primaryAccountNumber, "123456789123456789");
	printf("Expected Result: ACCOUNT_NOT_FOUND\n");
	printf("Actual Result: ");
	isValidAccount(&test_card, &test_acc);
	if(isValidAccount(&test_card, &test_acc) != SERVER_OK)
	{
		printf("ACCOUNT_NOT_FOUND\n");
	}
	else
	{
		printf("SERVER_OK\n");
	}
	printf("\n");
	/* Test Case 2 */
	printf("Test Case 2: \n");
	printf("Input Data: PAN: 652987469875632154\n");
	strcpy((char *)test_card.primaryAccountNumber, "652987469875632154");
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: ");
	if(isValidAccount(&test_card, &test_acc) != SERVER_OK)
	{
		printf("ACCOUNT_NOT_FOUND\n");
	}
	else
	{
		printf("SERVER_OK\n");
	}
	printf("\n");
	printf("isValidAccount function Test Ended!! \n");
	printf("\n");
}


/*
Description:
1.This function takes a reference to the account into the database and verifies if it is blocked or not.
2.If the account is running it will return SERVER_OK, else if the account is blocked it will return BLOCKED_ACCOUNT.
*/
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence)
{
	/* Checking if the Account is Blcoked */
	if (accountRefrence->state == BLOCKED)
	{
		return BLOCKED_ACCOUNT;
	}
	else
	{
		/* Account is Running */
		return SERVER_OK;
	}
}

/*
Description: function to test isBlockedAccount() Function
*/
void isBlockedAccountTest(void)
{
	ST_accountsDB_t accountRefrence;
	printf("isBlockedAccountTest function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: isBlockedAccountTest\n");
	printf("\n");
	/* Test Case 1 */
	printf("Test Case 1: \n");
	printf("Input Data: Reference to Blocked account\n");
	accountRefrence = accountsDB[1];
	printf("Expected Result: BLOCKED_ACCOUNT\n");
	printf("Actual Result: ");
	if(isBlockedAccount(&accountRefrence) != SERVER_OK)
	{
		printf("BLOCKED_ACCOUNT\n");
	}
	else
	{
		printf("SERVER_OK\n");
	}
	printf("\n");
	/* Test Case 2 */
	printf("Test Case 2: \n");
	printf("Input Data: Reference to Running account\n");
	accountRefrence = accountsDB[0];
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: ");
	if(isBlockedAccount(&accountRefrence) != SERVER_OK)
	{
		printf("BLOCKED_ACCOUNT\n");
	}
	else
	{
		printf("SERVER_OK\n");
	}
	printf("\n");
	printf("isBlockedAccountTest function Test Ended!! \n");
	printf("\n");
}


/*
Description:
1.This function will take terminal data and a reference to the account in the database and
	check if the account has a sufficient amount to withdraw or not.
2.It checks if the transaction's amount is available or not.
3.If the transaction amount is greater than the balance in the database will return LOW_BALANCE,
	else will return SERVER_OK.
*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence)
{
	/* Checking if the amount is Available */
	if (termData->transAmount <= accountRefrence->balance)
	{
		/* Amount is Available */
		return SERVER_OK;
	}
	else
	{
		return LOW_BALANCE;
	}
}


/*
Description: function to test isAmountAvailable() Function
*/
void isAmountAvailableTest(void)
{
	ST_accountsDB_t accountRefrence;
	accountRefrence = accountsDB[0];
	ST_terminalData_t termData;
	printf("isAmountAvailable function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: isAmountAvailable\n");
	printf("\n");
	/* Test Case 1 */
	printf("Test Case 1: \n");
	printf("Input Data: Amount: 5000.0 , Balance: 2000.0\n");
	termData.transAmount = 5000.0;
	printf("Expected Result: LOW_BALANCE\n");
	printf("Actual Result: ");
	if(isAmountAvailable(&termData, &accountRefrence) != SERVER_OK)
	{
		printf("LOW_BALANCE\n");
	}
	else
	{
		printf("SERVER_OK\n");
	}
	printf("\n");
	/* Test Case 2 */
	printf("Test Case 2: \n");
	printf("Input Data: Amount: 1500.0 , Balance: 2000.0\n");
	termData.transAmount = 1500.0;
	printf("Expected Result: SERVER_OK\n");
	printf("Actual Result: ");
	if(isAmountAvailable(&termData, &accountRefrence) != SERVER_OK)
	{
		printf("LOW_BALANCE\n");
	}
	else
	{
		printf("SERVER_OK\n");
	}
	printf("\n");
	printf("isAmountAvailable function Test Ended!! \n");
	printf("\n");
}



/*
Description:
1.This function will store all transaction data in the transactions database.
2.It gives a sequence number to a transaction, this number is incremented once a transaction is processed into the server,
	you must check the last sequence number in the server to give the new transaction a new sequence number.
3.It saves any type of transaction, APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR.
4.It will list all saved transactions using the listSavedTransactions function.
5.Assuming that the connection between the terminal and server is always connected, then it will return SERVER_OK.
*/
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
	uint8_t transactionsDB_Capacity_Test = 0;
	uint8_t transactionState;

	switch (recieveTransactionData(transData))
	{
	case FRAUD_CARD:
		transactionState = FRAUD_CARD;
		break;
	case DECLINED_INSUFFECIENT_FUND:
		transactionState = DECLINED_INSUFFECIENT_FUND;
		break;
	case DECLINED_STOLEN_CARD:
		transactionState = DECLINED_STOLEN_CARD;
		break;
	default:
		transactionState = APPROVED;
	}

	/* Checking if the transaction Can be saved */
	while (1)
	{

		if (transactionsDB_Capacity_Test == 255)
		{
			printf("SAVING_FAILED\n");
			return SAVING_FAILED;
		}
		else if (transactionsDB[transactionsDB_Capacity_Test].transactionSequenceNumber == 0)
		{
			/* that means there's an empty space and transaction can be saved */
			break;
		}
		else
		{
			transactionsDB_Capacity_Test++;
		}
	}

	/* Save the transaction */
	transactionsDB[transactionsDB_Capacity_Test] = *transData;
	transactionsDB[transactionsDB_Capacity_Test].transState = transactionState;
	transactionsDB[transactionsDB_Capacity_Test].transactionSequenceNumber = transactionsDB_Capacity_Test + 1;

	listSavedTransactions();
	/* if the code reached this section means everything is OK */
	//printf("SERVER_OK\n");
	return SERVER_OK;
}

/*
Description: function to test saveTransaction() Function
*/
void saveTransactionTest(void)
{
	ST_cardData_t card;
	strcpy((char *)card.cardHolderName, "Mohamed Asrhaf Ahmed");
	strcpy((char *)card.cardExpirationDate, "06/25");
	strcpy((char *)card.primaryAccountNumber, "8989374615436851");

	ST_terminalData_t term;
	strcpy((char *)term.transactionDate, "20/10/2022");
	term.transAmount = 50;
	term.maxTransAmount = 7000;

	ST_transaction_t transaction;
	transaction.cardHolderData = card;
	transaction.terminalData = term;

	printf("saveTransaction function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: saveTransaction\n");
	printf("\n");
	/* Test Case 1 */
	printf("Test Case 1: \n");
	printf("Input Data:	Name: Mohamed Asrhaf Ahmed	ExpDate: 06/25  PAN: 8989374615436851	Transaction Date: 20/10/2022	Amount: 50	Max Amount: 7000\n");
	printf("Expected Result: \n\
#########################\n\
Transaction Sequence Number : 1\n\
Transaction Date : 20 / 10 / 2022\n\
Transaction Amount : 50.000000\n\
Transaction State : APPROVED\n\
Terminal Max Amount : 7000.000000\n\
Cardholder Name : Mohamed Asrhaf Ahmed\n\
PAN : 8989374615436851\n\
Card Expiration Date : 06 / 25\n\
#########################\n");
	printf("Actual Result: \n");
	saveTransaction(&transaction);
	printf("\n");
	printf("saveTransaction function Test Ended!! \n");
	printf("\n");
}


/*
Description:
This function prints all transactions found in the transactions DB.
*/
void listSavedTransactions(void)
{
	uint8_t i;
	for (i = 0; transactionsDB[i].transactionSequenceNumber != 0; i++)
	{
		printf("#########################\n");
		printf("Transaction Sequence Number: ");
		printf("%ld\n", transactionsDB[i].transactionSequenceNumber);
		printf("Transaction Date: ");
		printf("%s\n", transactionsDB[i].terminalData.transactionDate);
		printf("Transaction Amount: ");
		printf("%f\n", transactionsDB[i].terminalData.transAmount);
		printf("Transaction State: ");
		switch (transactionsDB[i].transState)
		{
		case FRAUD_CARD:
			printf("FRAUD_CARD\n");
			break;
		case DECLINED_INSUFFECIENT_FUND:
			printf("DECLINED_INSUFFECIENT_FUND\n");
			break;
		case DECLINED_STOLEN_CARD:
			printf("DECLINED_STOLEN_CARD\n");
			break;
		default:
			printf("APPROVED\n");
		}
		printf("Terminal Max Amount: ");
		printf("%f\n", transactionsDB[i].terminalData.maxTransAmount);
		printf("Cardholder Name: ");
		printf("%s\n", transactionsDB[i].cardHolderData.cardHolderName);
		printf("PAN: ");
		printf("%s\n", transactionsDB[i].cardHolderData.primaryAccountNumber);
		printf("Card Expiration Date: ");
		printf("%s\n", transactionsDB[i].cardHolderData.cardExpirationDate);
		printf("#########################\n");
	}
}

/*
Description: function to test listSavedTransactions() Function
*/
void listSavedTransactionsTest(void)
{
	ST_cardData_t card;
	strcpy((char *)card.cardHolderName, "Mohamed Asrhaf Ahmed");
	strcpy((char *)card.cardExpirationDate, "06/25");
	strcpy((char *)card.primaryAccountNumber, "8989374615436851");

	ST_terminalData_t term;
	strcpy((char *)term.transactionDate, "20/10/2022");
	term.transAmount = 50;
	term.maxTransAmount = 7000;

	ST_transaction_t transaction;
	transaction.cardHolderData = card;
	transaction.terminalData = term;

	printf("listSavedTransactions function Test Started!! \n");
	printf("\n");
	printf("Tester Name: Mohamed Ashraf\n");
	printf("Function Name: listSavedTransactions\n");
	printf("\n");
	/* Test Case 1 */
	printf("Test Case 1: \n");
	printf("Input Data:	Name: Mohamed Asrhaf Ahmed	ExpDate: 06/25  PAN: 8989374615436851	Transaction Date: 20/10/2022	Amount: 50	Max Amount: 7000\n");
	saveTransaction(&transaction);
	printf("Expected Result: \n\
#########################\n\
Transaction Sequence Number : 1\n\
Transaction Date : 20 / 10 / 2022\n\
Transaction Amount : 50.000000\n\
Transaction State : APPROVED\n\
Terminal Max Amount : 7000.000000\n\
Cardholder Name : Mohamed Asrhaf Ahmed\n\
PAN : 8989374615436851\n\
Card Expiration Date : 06 / 25\n\
#########################\n");
	printf("Actual Result: \n");
	listSavedTransactions();
	printf("\n");
	printf("listSavedTransactions function Test Ended!! \n");
	printf("\n");
}
