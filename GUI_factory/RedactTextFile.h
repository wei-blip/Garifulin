//#pragma once
#include<vector>
#include<string>
#include<fstream>
#include<iostream>			

enum CellData_e
{
	myWORD	= 1,
	myNUMBER
};

std::string CreateString(char* CharPtr);

// Вставка стоп слова endl для того чтобы программа знала когда переставать считывать данные
void PasteStopWord(std::string& path);

// Удаляем запятую для того чтобы корректно считывать из файла
std::string DeleteComma(std::string& path);

std::string DeleteAndPasteNewWord(std::string str, std::string deletedWord, std::string pastedWord);

void CellSettings(std::ofstream& stream, int cell_data, int width_cell, int precision = 5);

std::string RedactFile(std::string& path);
