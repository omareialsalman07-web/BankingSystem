#pragma once

#include<iostream>
#include<vector>

namespace Core
{

	enum enUserPermissions {
		eAdmin = -1, pListClients = 1, pAddNewClient = 2, pDeleteClient = 4,
		pUpdateClients = 8, pFindClient = 16, pTranactions = 32, pManageUsers = 64
	};


	struct stUser
	{
		std::string UserName;
		std::string Password;
		int Permission = -1;

		bool markForDelete = false;
	};

	bool IsExistedUserByUserNumber(const std::string& UserName, const std::vector<stUser>& vUsers);

	bool AddNewUser(std::vector<stUser>& vUsers, const stUser& newUser);

	// Related to saving users
	std::string ConvertUserRecoredToLine(const stUser& user, const char* separator);
	void SaveUserToFile(const stUser user);
	// =====================================

	// Related to loading Clients ==========
	stUser ConvertUserLineToRecored(const std::string& line);
	std::vector<stUser> LoadUsersFromFile();
	void SaveUsersToFile(const std::vector<stUser>& vUsers);
	void RefreshUsersVector(std::vector<stUser>& vUsers);
	// ======================================

	short FindUserByUserNameAndPassword(const std::string& UserName, const std::string& Password, const std::vector<stUser>& vUsers);

	bool DeleteUserByUserNameAndPasword(const std::string& UserName, const std::string& Password, std::vector<stUser>& vUsers);

	bool UpdataUserByUserNameAndPassword(const std::string& UserName, const std::string& Password,
		const std::string& newUserName, const std::string& newPassword, int newPermission, std::vector<stUser>& vUsers);

	bool IsUserHasPermission(enUserPermissions actionPermission, const stUser& currentUser);
}