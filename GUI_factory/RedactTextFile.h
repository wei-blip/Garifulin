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

void PasteStopWord(std::string& path);
std::string DeleteComma(std::string& path);
std::string DeleteAndPasteNewWord(std::string str, std::string deletedWord, std::string pastedWord);
void CellSettings(std::ofstream& stream, int cell_data, int width_cell, int precision = 5);
std::string RedactFile(std::string& path);
