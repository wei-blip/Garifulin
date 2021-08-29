//#pragma once
#include<vector>
#include<string>
#include<fstream>
#include<iostream>			


class RedactFile {
public:
	RedactFile(std::string& path) {
		this->ipath_m = path;
	}

	std::string GetInPath(); // ������ ��� ���� �������� �����
	std::string GetOutPath(); // ������ ��� ���� ��������� �����
	std::string Run();
private:
	// ����� ��� ���������� ������ �� ����� � �������� �������
	std::ifstream inDataFile_m; 
	// ����� ��� ������ ������ � �������� ����
	std::ofstream outDataFile_m;
	// ���� � ����� � �������� �������
	std::string ipath_m;
	// ���� � ��������� �����
	std::string opath_m;
	// ������ ������ ����� � ������ �� ������ 
	std::string StrChange(std::string str, std::string deletedWord, std::string pastedWord);
	// ������� ������� ��� ���� ����� ��������� ��������� �� �����
	void CommaToSpace();
};

enum CellData_e
{
	myWORD	= 1,
	myNUMBER
};

std::string CreateString(const char* CharPtr);

void CellSettings(std::ofstream& stream, int cell_data, int width_cell, int precision = 5);

//std::string RedactFile(std::string& path);
