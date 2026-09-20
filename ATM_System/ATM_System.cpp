#include <iostream>
#include <windows.h>
#include <ctime>
#include<string>
#include<iomanip>
#include <vector>
#include<fstream>

using namespace std;

const string FileName = "ClintsDetails.txt";

struct sClient
{
	string AccountNumber = "";
	string PinCode = "";
	string Name = "";
	string Phone = "";
	double AccounBalance = 10000.0;
	bool MarkFoeDelete = false;
};


enum enMainMenue
{
	enQuick = 1, enNormalWithdraw = 2, enDeposit = 3, enCheckBalance = 4, enLogout = 5
};

sClient CurrentClient;

vector<string>SplitString(string Line, string Delim)
{
	vector<string>vString;
	short Pos;
	string sWord;
	while ((Pos = Line.find(Delim)) != std::string::npos)
	{
		sWord = Line.substr(0, Pos);
		if (sWord != "")
		{
			vString.push_back(sWord);
		}
		Line.erase(0, Pos + Delim.length());
	}
	if (Line != "")
	{
		vString.push_back(Line);
	}
	return vString;
}

sClient ConvertLineToRecordClient(string Line, string Seperator = "#//#")
{
	sClient Client;
	vector<string>vString = SplitString(Line, Seperator);
	Client.AccountNumber = vString[0];
	Client.PinCode = vString[1];
	Client.Name = vString[2];
	Client.Phone = vString[3];
	Client.AccounBalance = stod(vString[4]);
	return Client;
}

string ConvertRecordToLineClients(sClient Client, string Seperator = "#//#")
{
	string Line = "";
	Line += Client.AccountNumber + Seperator;
	Line += Client.PinCode + Seperator;
	Line += Client.Name + Seperator;
	Line += Client.Phone + Seperator;
	Line += to_string(Client.AccounBalance);

	return Line;
}

vector<sClient> SaveClientDataToFile(vector<sClient>Clients, string FileName)
{
	fstream MyFile;
	MyFile.open(FileName, ios::out);
	string Line;

	if (MyFile.is_open())
	{
		for (sClient& C : Clients)
		{
			if (C.MarkFoeDelete == false)
			{
				Line = ConvertRecordToLineClients(C);
				MyFile << Line << endl;

			}
		}
		MyFile.close();
	}
	return Clients;
}

vector<sClient>LoadDataFromFileClients(string FileName)
{
	vector<sClient>vClients;
	fstream MyFile;
	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		sClient Client;
		while (getline(MyFile, Line))
		{
			Client = ConvertLineToRecordClient(Line);
			vClients.push_back(Client);
		}
		MyFile.close();
	}

	return vClients;
}

int ReadWithDrawAccount()
{
	int Amount;
	cout << "\nPlease enter Amount Multiple of  5's ? ";
	cin >> Amount;
	bool doAgin = true;
	while (doAgin)
	{
		if (Amount % 5 != 0)
		{

			cout << "\nPlease enter Amount Multiple of  5's ? ";
			cin >> Amount;
		
		}
		else if (Amount > CurrentClient.AccounBalance)
		{
			cout << "Amount Exceeds the balance, you can Withdraw up to : " << CurrentClient.AccounBalance << endl;
			cout << "Please enter anther amount? ";
			cin >> Amount;
		}
		else
		{
			doAgin = false;
		}
		
	}

	return Amount;
}


void WithdrawClient()
{
	char Answer = 'n';
	int Withdraw;
	Withdraw = ReadWithDrawAccount();

	cout << "\n\nAre you sure you want perfrom this transaction? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		CurrentClient.AccounBalance -= Withdraw;

	}
	cout << "Done Successfully. New Balance is : " << CurrentClient.AccounBalance << endl << endl;
	cout << "Prees any key to exit ..." << endl << endl;
	system("pause>0");

}


int ReadDepositAmount()
{
	int Amount = 0;
	cout << "Enter a Positive Deposit Account? ";
	cin >> Amount;
	return Amount;
}

void DepositClient()
{
	char Answer = 'n';
	int Deposit;
	Deposit = ReadDepositAmount();

	cout << "\n\nAre you sure you want perfrom this transaction? y/n? ";
	cin >> Answer;
	if (toupper(Answer) == 'Y')
	{
		CurrentClient.AccounBalance += Deposit;

	}
	cout << "Done Successfully. New Balance is : " << CurrentClient.AccounBalance << endl << endl;
	cout << "Prees any key to exit ..." << endl << endl;
	system("pause>0");

}



void ShowNormalWithdrawClientScreen()
{
	system("cls");
	cout << "=============================================" << endl;
	cout << "\t\tNormal Withdraw Screen" << endl;
	cout << "=============================================" << endl;

	WithdrawClient();

}


void ShowCheckBalanceScreen()
{
	system("cls");
	cout << "=============================================" << endl;
	cout << "\t\tCheck Balance Screen" << endl;
	cout << "=============================================" << endl;
	cout << "Your Balance is " << CurrentClient.AccounBalance << endl;

}

void ShowDepositClientScreen()
{
	system("cls");
	cout << "=============================================" << endl;
	cout << "\t\tDeposit Screen" << endl;
	cout << "=============================================" << endl;

	DepositClient();

}

short ConvertChoiceToNumber(short Choice)
{
	int Arr[] = { 20, 50, 100, 200, 400, 600, 800, 1000 };

	return Arr[Choice - 1];
}

bool IsCanQuickWithdraw(short Number)
{
	short Amount = ConvertChoiceToNumber(Number);

	return (Amount > CurrentClient.AccounBalance);
}


short ReadQuickWithdraw()
{
	short Number;
	cout << "Choose what to withdraw from [1] to [8] ? ";
	cin >> Number;

	while (IsCanQuickWithdraw(Number))
	{
		cout << "\nThe Amount exceeds your balance, make anther choice." << endl;

		cout<< "Choose what to withdraw from [1] to [8] ? ";
		cin >> Number;
	}
	while (Number < 1 || Number>9)
	{
		cout << "\nChoose what to do from [1] to [9] ? ";
		cin >> Number;
	}

	if (Number == 9)
	{
		return 0;
	}

	return Number;
}

void QuickWithdraw()
{
	short Choice = ReadQuickWithdraw();
	short Amount = ConvertChoiceToNumber(Choice);
	char Answer = 'Y';
	if (Amount == 0)
		return;

	cout << "\n\nAre you sure you want perfrom this transaction? y/n? ";
	cin >> Answer;
	
	if (toupper(Answer) == 'Y')
	{
		CurrentClient.AccounBalance -= Amount;
	}

	cout << "\nDone Successfully. New Balance is : " << CurrentClient.AccounBalance << endl << endl;
	cout << "Prees any key to exit ..." << endl << endl;
	system("pause>0");

}

void QuickWithdrawScreen()
{

	cout << "=======================================================" << endl;
	cout << "\t\t      Quick withdraw " << endl;
	cout << "=======================================================" << endl;

	cout << "\t[1] 20" << setw(20) << right << "[2] 50" << endl;
	cout << "\t[3] 100" << setw(20) << right << "[4] 200" << endl;
	cout << "\t[5] 400" << setw(20) << right << "[6] 600" << endl;
	cout << "\t[7] 800 " << setw(20) << right << "[8] 1000" << endl;
	cout << "\t[9] Exit" << endl;
	cout << "=======================================================" << endl;
	
	QuickWithdraw();

}

bool FindClientByAccountNumberAndPincode(string AccountNumber, string Pincode, sClient& Client)
{

	vector <sClient> vClients = LoadDataFromFileClients(FileName);

	for (sClient C : vClients)
	{

		if (C.AccountNumber == AccountNumber && C.PinCode == Pincode)
		{
			Client = C;
			return true;
		}

	}
	return false;

}

bool LoadClientInfo(string AccountNumber, string PinCode)
{
	if (FindClientByAccountNumberAndPincode(AccountNumber, PinCode, CurrentClient))
		return true;
	else
		return false;
}

short ReadMainMenue()
{
	short Choice;
	cout << "Choose what do you want to do ? [1 to 5]? ";
	cin >> Choice;

	return Choice;
}

void SaveCurrentClientData()
{
	vector<sClient>Clients = LoadDataFromFileClients(FileName);
	for (sClient& C : Clients)
	{
		if (C.AccountNumber == CurrentClient.AccountNumber)
		{
			C = CurrentClient;
			break;
		}
	}
	SaveClientDataToFile(Clients, FileName);
}

void ShowMainMenue();

void GoBackToMainMenue()
{
	cout << "\n\nPress any Key to go back Main Menue...";
	system("pause>0");
	ShowMainMenue();
}

void Login();

void PerfromMainMenue(enMainMenue MainMenueChoice)
{
	switch (MainMenueChoice)
	{

	case enMainMenue::enQuick:
		QuickWithdrawScreen();
		SaveCurrentClientData();
		GoBackToMainMenue();
		break;

	case enMainMenue::enNormalWithdraw:
		ShowNormalWithdrawClientScreen();
		SaveCurrentClientData();
		GoBackToMainMenue();
		break;

	case enMainMenue::enDeposit:
		ShowDepositClientScreen();
		SaveCurrentClientData();
		GoBackToMainMenue();
		break;

	case enMainMenue::enCheckBalance:
		ShowCheckBalanceScreen();
		GoBackToMainMenue();
		break;

	case enMainMenue::enLogout:
		Login();
		break;
	}

}


void ShowMainMenue()
{
	system("cls");
	cout << "\n======================================================\n";
	cout << "\t\tATM Mian Menue Screen ";
	cout << "\n======================================================\n";
	cout << "\t[1] Quick Withdraw." << endl;
	cout << "\t[2] Normal Withdraw ." << endl;
	cout << "\t[3] Deposit." << endl;
	cout << "\t[4] Check Balance." << endl;
	cout << "\t[5] Logout." << endl;
	cout << "\n======================================================\n";
	

	PerfromMainMenue((enMainMenue)ReadMainMenue());

}

void Login()
{

	bool LoginFaild = false;
	string AccountNumber, PinCode;
	do
	{
		system("cls");

		cout << "\n---------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n---------------------------------\n";

		if (LoginFaild)
		{
			cout << "Invlaid Username/Password!\n";
		}

		cout << "\nEnter Account Number : ";
		cin >> AccountNumber;

		cout << "\nEnter PinCode : ";
		cin >> PinCode;

		LoginFaild = !LoadClientInfo(AccountNumber, PinCode);

	} while (LoginFaild);

	ShowMainMenue();

}

int main()
{
	Login();
	system("pause>0");
	return 0;
}
