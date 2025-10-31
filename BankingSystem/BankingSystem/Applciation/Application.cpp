
#include <iostream>
#include <iomanip>

#include <Core/Core.h>
#include <MyLib/My_Inputs.h>
#include <MyLib/My_String.h>


enum enMainMenueOptions { ShowClients_List = 1, AddNewClient = 2, DeleteClient = 3, UpdateClientInfo = 4,
	FindClient = 5, Transactions = 6, ManageUsers = 7, Logout = 8, Exit = 9};

enum enTransactionsMenueOptions { eDeposit = 1, eWithdraw = 2, eShowMainMenue = 3 };

enum enManageUsersMenueOptions {
	eListUsers = 1, eAddNewUser = 2, eDeleteUser = 3,
	eUpdateUser = 4, eFindUser = 5, eMainMenue = 6
};

// Global vars =====================================================
std::vector<Core::stClient> vCLIENTS = Core::LoadClientsFromFile();
std::vector<Core::stUser> vUSERS = Core::LoadUsersFromFile();
Core::stUser CURRENT_USER;
// Global vars =====================================================

bool LoadUser(const std::string& UserName, const std::string& Password, Core::stUser& CurrnetUser)
{
	short Index;
	if ((Index = Core::FindUserByUserNameAndPassword(UserName, Password, vUSERS)) != -1)
	{
		CurrnetUser = vUSERS[Index];
		return true;
	}
	return false;
}

void ShowMainMenu()
{
	system("cls");

	std::cout << "\t\t" << CURRENT_USER.UserName << " | " << CURRENT_USER.Permission << "\n";
	std::cout << "==============Main Menue==============\n";
	std::cout << "[1] Show Clients List\n";
	std::cout << "[2] Add New Client\n";
	std::cout << "[3] Delete Client\n";
	std::cout << "[4] Update Client Info\n";
	std::cout << "[5] Find Client\n";
	std::cout << "[6] Transactions\n";
	std::cout << "[7] Manage Users\n";
	std::cout << "[8] Logout\n";
	std::cout << "[9] Exit\n";
	std::cout << "======================================\n";
}

void ShowClientInfoCard(const Core::stClient& client)
{
	std::cout << "\t===========Cleint Info Card================\n";
	std::cout << "\tAccount Number : " << client.AccountNumber << std::endl;
	std::cout << "\tName           : " << client.Name << std::endl;
	std::cout << "\tPin Code       : " << client.PinCode << std::endl;
	std::cout << "\tPhone Number   : " << client.PhoneNumber << std::endl;
	std::cout << "\tBalance        : " << client.Balance << std::endl;
	std::cout << "\t===========================================\n";
}

void ShowClientsList()
{
	system("cls");
	if (!Core::IsUserHasPermission(Core::pListClients, CURRENT_USER))
	{
		std::cout << "you are not allow to this action. Contanct you admin!\n";
		system("pause");
		return;
	}


	std::cout << "-----------------------------------------------------------------------------------------------\n";

	// Header
	std::cout << "| " << std::left << std::setw(15) << "Account Number"
		<< " | " << std::left << std::setw(25) << "Name"
		<< " | " << std::left << std::setw(12) << "Pin Code"
		<< " | " << std::left << std::setw(15) << "Phone Number"
		<< " | " << std::right << std::setw(12) << "Balance"
		<< " |\n";

	std::cout << "-----------------------------------------------------------------------------------------------\n";

	// Rows
	for (const Core::stClient& c : vCLIENTS)
	{
		std::cout << "| " << std::left << std::setw(15) << c.AccountNumber
			<< " | " << std::left << std::setw(25) << c.Name
			<< " | " << std::left << std::setw(12) << c.PinCode
			<< " | " << std::left << std::setw(15) << c.PhoneNumber
			<< " | " << std::right << std::setw(12)
			<< std::fixed << std::setprecision(2) << c.Balance << "$"
			<< " |\n";
	}

	std::cout << "-----------------------------------------------------------------------------------------------\n";
	system("pause");
}

Core::stClient ReadClient()
{
	Core::stClient client;
	
	client.AccountNumber = Inputs::ReadString("Enter Accoutn Number : ");
	client.Name = Inputs::ReadString("Enter Name : ");
	client.PinCode = Inputs::ReadString("Enter Pin Code : ");
	client.PhoneNumber = Inputs::ReadString("Enter Phone Number : ");
	client.Balance = Inputs::ReadNumber("Enter balance : ");

	return client;
}

int ReadPemission()
{
	int Permission = 0;

	if (Inputs::ReadChar("Is this is an admin? (y | n)") == std::tolower('y'))
		return Core::enUserPermissions::eAdmin;

	if (Inputs::ReadChar("Do you want him to show Clients List? (y | n)") == std::tolower('y'))
		Permission += Core::enUserPermissions::pListClients;

	if (Inputs::ReadChar("Do you want him to Add New Clients? (y | n)") == std::tolower('y'))
		Permission += Core::enUserPermissions::pAddNewClient;

	if (Inputs::ReadChar("Do you want him to Delete Clients? (y | n)") == std::tolower('y'))
		Permission += Core::enUserPermissions::pDeleteClient;

	if (Inputs::ReadChar("Do you want him to Update Clients? (y | n)") == std::tolower('y'))
		Permission += Core::enUserPermissions::pUpdateClients;

	if (Inputs::ReadChar("Do you want him to Find Clients? (y | n)") == std::tolower('y'))
		Permission += Core::enUserPermissions::pFindClient;

	if (Inputs::ReadChar("Do you want him to show pTranactions Menu? (y | n)") == std::tolower('y'))
		Permission += Core::enUserPermissions::pTranactions;

	if (Inputs::ReadChar("Do you want him to Manage Users? (y | n)") == std::tolower('y'))
		Permission += Core::enUserPermissions::pManageUsers;

	return Permission;
}

Core::stUser ReadUser()
{
	Core::stUser User;
	
	User.UserName = Inputs::ReadString("Enter User Name : ");
	User.UserName = Inputs::ReadString("Enter Password  : ");
	User.Permission = ReadPemission();

	return User;
}

void ShowAddClientMenu()
{
	system("cls");
	if (!Core::IsUserHasPermission(Core::pAddNewClient, CURRENT_USER))
	{
		std::cout << "you are not allow to this action. Contanct you admin!\n";
		system("pause");
		return;
	}

	std::cout << "===================Add Client Menue===================\n";

	char Choise = 'y';

	while (Choise == 'Y' ||Choise == 'y')
	{
		if (Core::AddNewClient(vCLIENTS, ReadClient()))
		{
			std::cout << "\a\n\tClient Added successfully!\n";
		}
		else
		{
			std::cout << "\a\n\tCan't add new client. make sure that the account Number has not used yet!\n";
		}

		std::cout << "Do you want to add more : {y : Yes | any key : No}? ";
		std::cin >> Choise;
	}
}

void ShowFindClientMenu()
{
	system("cls");
	if (!Core::IsUserHasPermission(Core::pFindClient, CURRENT_USER))
	{
		std::cout << "you are not allow to this action. Contanct you admin!\n";
		system("pause");
		return;
	}

	std::cout << "===================Find Client Menue==================\n";

	short index = Core::FindClientByAccountName(Inputs::ReadString("\nAccount Name : "), vCLIENTS);
	if (index != -1)
	{
		ShowClientInfoCard(vCLIENTS[index]);
	}
	else
	{
		std::cout << "\a\n\tClient not found!\n";
	}
	system("pause");
}

void ShowDeleteClientMenu()
{
	system("cls");
	if (!Core::IsUserHasPermission(Core::pDeleteClient, CURRENT_USER))
	{
		std::cout << "you are not allow to this action. Contanct you admin!\n";
		system("pause");
		return;
	}

	std::cout << "===================Delete Client Menue==================\n";

	if (Core::DeleteClietByAccoutnNumber(Inputs::ReadString("\nEnter Accout Number : "), vCLIENTS))
	{
		std::cout << "\a\n\tClient Deleted successfully!\n";
	}
	else
	{
		std::cout << "\a\n\tClient was not Deleted. Make sure that the account number is existed with a client!\n";
	}
	system("pause");
}

void ShowUpdateClientMenu()
{
	system("cls");
	if (!Core::IsUserHasPermission(Core::pUpdateClients, CURRENT_USER))
	{
		std::cout << "you are not allow to this action. Contanct you admin!\n";
		system("pause");
		return;
	}

	std::cout << "===================Update Client Menue==================\n";

	std::string accountNuber = Inputs::ReadString("\nEnter Accout Number    : ");
	std::string newName = Inputs::ReadString("Enter new Name         : ");
	std::string newPinCode = Inputs::ReadString("Enter new Pin Code     : ");
	std::string newPhoneNumber = Inputs::ReadString("Enter new Phone Number : ");
	float newBalance = Inputs::ReadNumber("Enter new Balance      : ");

	if (Core::UpdataClientByAccountName(accountNuber, newName, newPinCode, newPhoneNumber, newBalance, vCLIENTS))
	{
		std::cout << "\a\n\tClient Updated successfully!\n";
	}
	else
	{
		std::cout << "\a\n\tCan't update client. Make sure that the account number is existed!\n";
	}
	system("pause");
}

void ShowDepositMenu()
{
	system("cls");

	std::cout << "===================Deposit Menue==================\n";

	std::string AccountNumber = Inputs::ReadString("Account Number : ");

	short Index;
	if ((Index = Core::FindClientByAccountName(AccountNumber, vCLIENTS)) != -1)
	{
		ShowClientInfoCard(vCLIENTS[Index]);

		float Ammount = Inputs::ReadNumber("Ammount : ");
		if (Core::DepositByAccountNumber(Ammount, AccountNumber, vCLIENTS))
		{

			std::cout << "\a\tYou have already deposited from Account Number : " << AccountNumber << " of Ammount : " << Ammount
				<< std::endl << "The current balance is : " << vCLIENTS[Index].Balance << std::endl;;
		}
		else
		{
			std::cout << "\a\tSomething went wrong make sure that the account number is existed with a vailed client!" << std::endl;
		}
	}
	else
	{
		std::cout << "\a\tCan't find client with Account number : << " << AccountNumber << " !" << std::endl;
	}
}

void ShowWithdrawMenu()
{
	system("cls");

	std::cout << "===================Withdraw Menue==================\n";

	std::string AccountNumber = Inputs::ReadString("Account Number : ");

	short Index;
	if ((Index = Core::FindClientByAccountName(AccountNumber, vCLIENTS)) != -1)
	{
		ShowClientInfoCard(vCLIENTS[Index]);

		float Ammount = Inputs::ReadNumber("Ammount : ");
		if (Core::WithdrawByAccountNumber(Ammount, AccountNumber, vCLIENTS))
		{

			std::cout << "\a\tYou have already withdrawed from Account Number : " << AccountNumber << " of Ammount : " << Ammount
				<< std::endl << "The current balance is : " << vCLIENTS[Index].Balance << vCLIENTS[Index].Balance << std::endl;;
		}
		else
		{
			std::cout << "\a\tSomething went wrong make sure that the account number is existed with a vailed client or the account has enought money!" << std::endl;
		}
	}
	else
	{
		std::cout << "\a\tCan't find client with Account number : << " << AccountNumber << " !" << std::endl;
	}
}

void ShowTransactionsMenu()
{
	system("cls");
	if (!Core::IsUserHasPermission(Core::pTranactions, CURRENT_USER))
	{
		std::cout << "you are not allow to this action. Contanct you admin!\n";
		system("pause");
		return;
	}

	std::cout << "===================Transactions Menue==================\n";
	std::cout << "\t[1] Deposit.\n";
	std::cout << "\t[2] Withdraw.\n";
	std::cout << "\t[3] Main Menu.\n";

	enTransactionsMenueOptions Choise = (enTransactionsMenueOptions)Inputs::ReadNumber("What you want to do? [1-3] : ", 1, 3);
	switch (Choise)
	{
	case enTransactionsMenueOptions::eDeposit:
		ShowDepositMenu();
		break;
	case enTransactionsMenueOptions::eWithdraw:
		ShowWithdrawMenu();
		break;
	case enTransactionsMenueOptions::eShowMainMenue:
		ShowMainMenu();
		break;
	}
	
	system("pause");
}

void ShowUsersList()
{
	std::cout << "-----------------------------------------------\n";

	// Header
	std::cout << "| " << std::left << std::setw(15) << "User Name"
		<< " | " << std::left << std::setw(25) << "Permission"
		<< " |\n";

	std::cout << "-----------------------------------------------\n";

	// Rows
	for (const Core::stUser& u : vUSERS)
	{
		std::cout << "| " << std::left << std::setw(15) << u.UserName
			<< " | " << std::left << std::setw(25) << u.Permission			
			<< " |\n";
	}

	std::cout << "-----------------------------------------------\n";
	system("pause");
}

void ShowAddUsersMenu()
{
	system("cls");
	std::cout << "===================Add Users Menue===================\n";

	char Choise = 'y';

	while (Choise == 'Y' || Choise == 'y')
	{
		Core::stUser User = ReadUser();
		if (Core::AddNewUser(vUSERS, User))
		{
			std::cout << "\a\n\tUser Added successfully!\n";
		}
		else
		{
			std::cout << "\a\n\tCan't add new user. make sure that the User Name has not used yet!\n";
		}

		std::cout << "Do you want to add more : {y : Yes | any key : No}? ";
		std::cin >> Choise;
	}
}

void ShowFindUserMenu()
{
	system("cls");

	std::cout << "===================Find User Menue==================\n";
	
	std::string userName = Inputs::ReadString("Enter User Name : ");
	std::string password = Inputs::ReadString("Enter Password : ");
	short index = Core::FindUserByUserNameAndPassword(userName, password, vUSERS);
	if (index != -1)
	{
		std::cout << "\n"
			<< "Name     : " << vUSERS[index].UserName << " \n"
			<< "Password : " << vUSERS[index].Password << "\n\n";
	}
	else
	{
		std::cout << "\a\n\tUser not found!\n";
	}
	system("pause");
}

void ShowDeleteUsersMenu()
{
	system("cls");

	std::cout << "===================Delete User Menue==================\n";

	std::string userName = Inputs::ReadString("\nEnter User Name : ");
	std::string password = Inputs::ReadString("\nEnter Password : ");

	if (Core::DeleteUserByUserNameAndPasword(userName, password, vUSERS))
	{
		std::cout << "\a\n\tUser Deleted successfully!\n";
	}
	else
	{
		std::cout << "\a\n\tUser was not Deleted. Make sure that the User Name or the Password are true or check whether the user is existed or not!\n";
	}
	system("pause");
}

void ShowUpdateUsertMenu()
{
	system("cls");

	std::cout << "===================Update User Menue==================\n";

	std::string userName = Inputs::ReadString("\nEnter User Name     : ");
	std::string password = Inputs::ReadString("\nEnter Password      : ");
	std::string newUserName = Inputs::ReadString("\n\nEnter new User Name : ");
	std::string newPassword = Inputs::ReadString("\nEnter new Password  : ");
	int newPermission = ReadPemission();



	if (Core::UpdataUserByUserNameAndPassword(userName, password, newUserName, newPassword, newPermission, vUSERS))
	{
		std::cout << "\a\n\tClient Updated successfully!\n";
	}
	else
	{
		std::cout << "\a\n\tCan't update client. Make sure that the account number is existed!\n";
	}
	system("pause");
}

void ShowManangeUsersMenu()
{
	system("cls");
	if (!Core::IsUserHasPermission(Core::pManageUsers, CURRENT_USER))
	{
		std::cout << "you are not allow to this action. Contanct you admin!\n";
		system("pause");
		return;
	}

	std::cout << "===================Manage Users Menue==================\n";
	std::cout << "\t[1] Users list.\n";
	std::cout << "\t[2] Add new user.\n";
	std::cout << "\t[3] Delete user.\n";
	std::cout << "\t[4] Update user.\n";
	std::cout << "\t[5] Find user.\n";
	std::cout << "\t[6] Main Menu.\n";
	std::cout << "=======================================================\n";

	enManageUsersMenueOptions Choise = (enManageUsersMenueOptions)Inputs::ReadNumber("What you want to do? [1-6] : ", 1, 6);
	switch (Choise)
	{
	case enManageUsersMenueOptions::eListUsers:
		ShowUsersList();
		break;
	case enManageUsersMenueOptions::eAddNewUser:
		ShowAddUsersMenu();
		break;
	case enManageUsersMenueOptions::eDeleteUser:
		ShowDeleteUsersMenu();
		break;
	case enManageUsersMenueOptions::eUpdateUser:
		ShowUpdateUsertMenu();
		break;
	case enManageUsersMenueOptions::eFindUser:
		ShowFindUserMenu();
		break;
	case enManageUsersMenueOptions::eMainMenue:
		return;
	}

	ShowManangeUsersMenu(); // to stil in Manage users menu until we press [6]
}

void ShowLoginMenu()
{
	bool isFaild = false;
	do
	{
		system("cls");
		std::cout << "==============Login Menue==============\n";
		std::string userName = Inputs::ReadString("Enter User Name : ");
		std::string password = Inputs::ReadString("Enter Password : ");
		std::cout << "======================================\n";

		isFaild = !LoadUser(userName, password, CURRENT_USER);
		if (isFaild)
		{
			std::cout << "Invailed Username or Password!\n";
			system("pause");
		}
	} while (isFaild);
}

void RunGame()
{
	ShowMainMenu();

	enMainMenueOptions MenuChoise = (enMainMenueOptions)Inputs::ReadNumber("What you Want to do? [1-9] ", 1, 9);
	switch (MenuChoise)
	{
	case enMainMenueOptions::ShowClients_List:
		ShowClientsList();
		break;
	case enMainMenueOptions::AddNewClient:
		ShowAddClientMenu();
		break;
	case enMainMenueOptions::DeleteClient:
		ShowDeleteClientMenu();
		break;
	case enMainMenueOptions::UpdateClientInfo:
		ShowUpdateClientMenu();
		break;
	case enMainMenueOptions::FindClient:
		ShowFindClientMenu();
		break;
	case enMainMenueOptions::Transactions:
		ShowTransactionsMenu();
		break;
	case enMainMenueOptions::ManageUsers:
		ShowManangeUsersMenu();
		break;
	case enMainMenueOptions::Logout:
		ShowLoginMenu();
		break;
	case enMainMenueOptions::Exit:
		exit(0);
		break;
	}
}

int main()
{	
	ShowLoginMenu();
	while (true)
	{
		RunGame();
	}

	return 0;
}