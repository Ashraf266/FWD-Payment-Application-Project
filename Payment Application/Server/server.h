/*------------------------------------------------------------------
[FILE NAME]:	server.h
[AUTHOR]:		Mohamed Ashraf
[DATE CREATED]:	10/11/2022
[DESCRIPTION]:	Header file for the Server Module
------------------------------------------------------------------*/
#ifndef SERVER_H_
#define SERVER_H_


#include "std_types.h"
#include "card.h"
#include "terminal.h"

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

 /*------------------------------------------------------------------
 [Enum Name]:                EN_transStat_t
 [Enum Description]:         contains Transaction status used in the application
 ------------------------------------------------------------------*/
typedef enum EN_transState_t
{
    APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR
}EN_transStat_t;

/*------------------------------------------------------------------
[Enum Name]:                EN_serverError_t
[Enum Description]:         contains Server Error Types
------------------------------------------------------------------*/
typedef enum EN_serverError_t
{
    SERVER_OK, SAVING_FAILED, TRANSACTION_NOT_FOUND, ACCOUNT_NOT_FOUND, LOW_BALANCE, BLOCKED_ACCOUNT
}EN_serverError_t;

/*------------------------------------------------------------------
[Enum Name]:                EN_accountState_t
[Enum Description]:         contains Account status used in the application
------------------------------------------------------------------*/
typedef enum EN_accountState_t
{
    RUNNING,
    BLOCKED
}EN_accountState_t;

/*------------------------------------------------------------------
[Structure Name]:           ST_transaction
[Structure Description]:    contains all the Transaction data Needed
------------------------------------------------------------------*/
typedef struct ST_transaction_t
{
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transStat_t transState;
    uint32_t transactionSequenceNumber;
}ST_transaction_t;

/*------------------------------------------------------------------
[Structure Name]:           ST_accountsDB_t
[Structure Description]:    contains all the Accounts including its PAN & State
------------------------------------------------------------------*/
typedef struct ST_accountsDB_t
{
    float balance;
    EN_accountState_t state;
    uint8_t primaryAccountNumber[20];
}ST_accountsDB_t;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

 /*------------------------------------------------------------------
  [Function Name]:   recieveTransactionData
  [Description]:     This function will take all transaction data and validate its data, it contains all server logic.
  [Args]:
  [in]	NONE
  [out]	NONE
  [in/out]   ST_transaction_t* transData
                     Pointer to the transData structure

  [Returns]: Error if found, otherwise return success
  ------------------------------------------------------------------*/
EN_transStat_t recieveTransactionData(ST_transaction_t* transData);

/*------------------------------------------------------------------
 [Function Name]:   isValidAccount
 [Description]:     This function will take card data and validate if the account related to this card exists or not.
 [Args]:
 [in]	NONE
 [out]	NONE
 [in/out]   ST_accountsDB_t* accountRefrence
                    Pointer to the Accounts DataBase structure
            ST_cardData_t* cardData
                    Pointer to the cardData structure

 [Returns]: Error if found, otherwise return success
 ------------------------------------------------------------------*/
EN_serverError_t isValidAccount(ST_cardData_t* cardData, ST_accountsDB_t** accountRefrence);

/*------------------------------------------------------------------
 [Function Name]:   isBlockedAccount
 [Description]:     This function takes a reference to the account into the database and verifies if it is blocked or not.
 [Args]:
 [in]	NONE
 [out]	NONE
 [in/out]   ST_accountsDB_t* accountRefrence
                    Pointer to the Accounts DataBase structure

 [Returns]: Error if found, otherwise return success
 ------------------------------------------------------------------*/
EN_serverError_t isBlockedAccount(ST_accountsDB_t* accountRefrence);

/*------------------------------------------------------------------
 [Function Name]:   isAmountAvailable
 [Description]:     This function will take terminal data and a reference to the account in the database
                     and check if the account has a sufficient amount to withdraw or not.
 [Args]:
 [in]	NONE
 [out]	NONE
 [in/out]   ST_accountsDB_t* accountRefrence
                    Pointer to the Accounts DataBase structure
            ST_terminalData_t* termData
                    Pointer to the termData structure

 [Returns]: Error if found, otherwise return success
 ------------------------------------------------------------------*/
EN_serverError_t isAmountAvailable(ST_terminalData_t* termData, ST_accountsDB_t* accountRefrence);

/*------------------------------------------------------------------
 [Function Name]:   saveTransaction
 [Description]:     This function will store all transaction data in the transactions database.
 [Args]:
 [in]	NONE
 [out]	NONE
 [in/out]   ST_transaction_t* transData
                    Pointer to the transData structure

 [Returns]: Error if found, otherwise return success
 ------------------------------------------------------------------*/
EN_serverError_t saveTransaction(ST_transaction_t* transData);

/*------------------------------------------------------------------
 [Function Name]:   listSavedTransactions
 [Description]:     This function prints all transactions found in the transactions DB.
 [Args]:
 [in]	    NONE
 [out]	    NONE
 [in/out]   NONE

 [Returns]: Nothing
 ------------------------------------------------------------------*/
void listSavedTransactions(void);

/*Test Functions Prototypes*/
void recieveTransactionDataTest(void);
void isValidAccountTest(void);
void isBlockedAccountTest(void);
void isAmountAvailableTest(void);
void saveTransactionTest(void);
void listSavedTransactionsTest(void);

#endif /* SERVER_H_ */
