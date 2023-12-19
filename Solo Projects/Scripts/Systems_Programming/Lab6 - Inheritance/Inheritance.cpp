// Inheritance.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>
#include "BaseAccount.h"
#include "CheckingsAcc.h"
#include "SavingsAcc.h"
#include "CreditAcc.h"

void FIn(std::vector<CheckingsAcc>& _check, std::vector<SavingsAcc>& _save, std::vector<CreditAcc>& _credit);
void FOut(std::vector<CheckingsAcc>& _check, std::vector<SavingsAcc>& _save, std::vector<CreditAcc>& _credit);
int Validate();
int main()
{
	
	CheckingsAcc checkBal;
	SavingsAcc saveBal;
	CreditAcc creditBal;
	std::vector<BaseAccount> base;
	std::vector<CheckingsAcc> check;
	std::vector<SavingsAcc> save;
	std::vector<CreditAcc> credit;

	FIn(check, save, credit);

	std::cout << "Checkings\n";
	checkBal.Deposit(500);
	std::cout << "Savings\n";
	saveBal.Deposit(2000);
	std::cout << "Credit\n";
	creditBal.Deposit(300);
	
	

	int choice;
	bool stay = true;
	while (stay)
	{
		std::cout << "What would you like to do with your money?\n1.Deposit\n2.Withdraw\nChoice:";
		choice = Validate();
		switch (choice)
		{
		case 1:
			int deposit;
			std::cout << "How much would you like to deposit?\n";
			deposit = Validate();

			std::cout << "What account would you like to deposit to?\n1.Checkings\n2.Savings\n3.Credit\n";
			int account;
			account = Validate();

			switch (account)
			{
			case 1:
				checkBal.Deposit(deposit);
				break;
			case 2:
				saveBal.Deposit(deposit);
				break;
			case 3:
				creditBal.Deposit(deposit);
				break;
			}
			break;
		case 2:
			int withdraw;
			std::cout << "How much would you like to withdraw?\n";
			withdraw = Validate();

			std::cout << "What account would you like to withdraw from?\n1.Checkings\n2.Savings\n3.Credit\n";
			int acc;
			acc = Validate();

			switch (acc)
			{
			case 1:
				checkBal.Withdraw(withdraw);
				break;
			case 2:
				saveBal.Withdraw(withdraw);
				break;
			case 3:
				creditBal.Withdraw(withdraw);
				break;
			}
			break;
		}
		std::cout << "Would you like to  exit now?\n1.Yes\n2.No\n";
		int exit = Validate();
		if (exit != 2)
		{
			stay = false;
		}
	}


	check.push_back(checkBal);
	save.push_back(saveBal);
	credit.push_back(creditBal);
	FOut(check, save, credit);

}
void FIn(std::vector<CheckingsAcc>& _check, std::vector<SavingsAcc>& _save, std::vector<CreditAcc>& _credit)
{
	std::ifstream fileIn;
	fileIn.open("output.txt");
	if (fileIn.is_open())
	{
		bool done = false;
		while (!done)
		{
			CheckingsAcc check;
			SavingsAcc save;
			CreditAcc credit;

			float value;
			fileIn >> value;
			check.Deposit(value);
			float value2;
			fileIn >> value2;
			save.Deposit(value2);
			float value3;
			fileIn >> value3;
			credit.Deposit(value3);
			if (fileIn.eof())
			{
				done = true;
				break;
			}

			_check.push_back(check);
			_save.push_back(save);
			_credit.push_back(credit);
		}
		fileIn.close();
	}
	else
	{
		std::cout << "No saved file\n\n";
	}
}

void FOut(std::vector<CheckingsAcc>& _check, std::vector<SavingsAcc>& _save, std::vector<CreditAcc>& _credit)
{
	float value;
	std::ofstream fileOut;
	fileOut.open("output.txt", std::ios_base::app);
	if (fileOut.is_open())
	{
		for (int i = 0; i < _check.size(); i++)
		{
			fileOut << _check[i].GetBalance() << "\n";
		}
		for (int i = 0; i < _save.size(); i++)
		{
			fileOut << _save[i].GetBalance() << "\n";
		}
		for (int i = 0; i < _credit.size(); i++)
		{
			fileOut << _credit[i].GetBalance() << "\n";
		}

		fileOut.close();
	}
	else
	{
		std::cout << "File did not open\n";
	}
}

int Validate()
{
	int number;
	bool run = true;
	std::cin >> number;
	while (run)
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			std::cout << "Please choose a valid number.\n";
			std::cin >> number;
		}
		else
		{
			run = false;
		}
	}
	return number;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
