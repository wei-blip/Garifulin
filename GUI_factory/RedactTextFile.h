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

	std::string GetInPath(); // Геттер для пути входного файла
	std::string GetOutPath(); // Геттер для пути выходного файла
	std::string Run();
private:
	// Поток для считывания данных из файла с входными данными
	std::ifstream inDataFile_m; 
	// Поток для записи данных в выходной файл
	std::ofstream outDataFile_m;
	// Путь к файлу с входными данными
	std::string ipath_m;
	// Путь к выходному файлу
	std::string opath_m;
	// Замена одного слова в строке на другое 
	std::string StrChange(std::string str, std::string deletedWord, std::string pastedWord);
	// Удаляем запятую для того чтобы корректно считывать из файла
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
