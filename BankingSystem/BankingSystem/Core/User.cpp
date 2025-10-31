#include "User.h"

#include <string>
#include <fstream>

#include <MyLib/My_String.h>

const char* USERS_FILE_NAME = "Users.txt";

using namespace Core;

bool Core::IsExistedUserByUserNumber(const std::string& UserName, const std::vector<stUser>& vUsers)
{
	for (const stUser& User : vUsers)
	{
		if (User.UserName == UserName)
			return true;
	}

	return false;
}

bool Core::AddNewUser(std::vector<stUser>& vUsers, const stUser& newUser)
{
	if (IsExistedUserByUserNumber(newUser.UserName, vUsers)) // return false if there is a user with the same user name
		return false;

	vUsers.push_back(newUser);
	SaveUserToFile(newUser);

	return true;
}

std::string Core::ConvertUserRecoredToLine(const stUser& user, const char* separator)
{
    std::string Line = "";

    Line = user.UserName + separator + user.Password + separator + std::to_string(user.Permission);

    return Line;
}

void Core::SaveUserToFile(const stUser User)
{
	std::fstream File;
	File.open(USERS_FILE_NAME, std::ios::out | std::ios::app); // appined mode

	if (File.is_open())
	{
		File << ConvertUserRecoredToLine(User, "//#//");
		File << std::endl;
	}
	File.close();
}

void Core::SaveUsersToFile(const std::vector<stUser>& vUsers)
{
	std::fstream File;
	File.open(USERS_FILE_NAME, std::ios::out); // write mode

	if (File.is_open())
	{
		for (const stUser& user : vUsers)
		{
			if (!user.markForDelete)
			{
				File << ConvertUserRecoredToLine(user, "//#//");
				File << std::endl;
			}
		}
	}
	File.close();
}

void Core::RefreshUsersVector(std::vector<stUser>& vUsers)
{
	vUsers = LoadUsersFromFile();
}

stUser Core::ConvertUserLineToRecored(const std::string& line)
{
	stUser User;

	std::vector<std::string> vUsersData = String::SliptString("//#//", line);

	User.UserName = vUsersData[0];
	User.Password = vUsersData[1];
	User.Permission = std::stoi(vUsersData[2]);

	return User;
}

std::vector<stUser> Core::LoadUsersFromFile()
{
	std::vector<stUser> vUsers;

	std::fstream File;
	File.open(USERS_FILE_NAME, std::ios::in); // Read Mode

	if (File.is_open())
	{
		std::string line;
		while (std::getline(File, line))
		{
			stUser user = ConvertUserLineToRecored(line);
			vUsers.push_back(user);
		}
	}
	File.close();

	return vUsers;
}

short Core::FindUserByUserNameAndPassword(const std::string& UserName, const std::string& Password, const std::vector<stUser>& vUsers)
{
	for (int i = 0; i < vUsers.size(); i++)
	{
		if (vUsers[i].UserName == UserName && vUsers[i].Password == Password)
		{
			return i;
		}
	}
	return -1;
}

bool Core::DeleteUserByUserNameAndPasword(const std::string& UserName, const std::string& Password, std::vector<stUser>& vUsers)
{
	short Index;
	if ((Index = FindUserByUserNameAndPassword(UserName, Password, vUsers)) != -1)
	{
		vUsers[Index].markForDelete = true;
		SaveUsersToFile(vUsers);

		RefreshUsersVector(vUsers);
		return true;
	}
	else
	{
		return false;
	}
}

bool Core::UpdataUserByUserNameAndPassword(const std::string& UserName, const std::string& Password,
	const std::string& newUserName, const std::string& newPassword, int newPermission, std::vector<stUser>& vUsers)
{
	int Index;
	if ((Index = FindUserByUserNameAndPassword(UserName, Password, vUsers)) != -1)
	{
		vUsers[Index].UserName = newUserName;
		vUsers[Index].Password = newPassword;

		vUsers[Index].Permission = newPermission; 



		SaveUsersToFile(vUsers);

		return true;
	}
	else
	{
		return false;
	}

}

bool Core::IsUserHasPermission(enUserPermissions actionPermission, const stUser& currentUser)
{
	if (currentUser.Permission == enUserPermissions::eAdmin)
		return true;

	if ((currentUser.Permission & actionPermission) == actionPermission)
		return true;

	return false;
}