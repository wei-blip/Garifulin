#include"RedactTextFile.h"

void NumberCellSettings(std::ofstream& stream, int width_cell, int precision);
void WordCellSettings(std::ofstream& stream, int width_cell);

// ����������� ����
std::string RedactFile(std::string& path) {
	PasteStopWord(path);
	return DeleteComma(path);
}

// ������� � ��������� ����� �����
std::string DeleteAndPasteNewWord(std::string str, std::string deletedWord, std::string pastedWord) {
	int count = 0;
	int j = 0, i = 0;
	bool stepIn = true;
	for (; (j != deletedWord.size()) || (i < str.size()); i++)
	{
		// ������� ����������
		if ((*(deletedWord.begin() + j) == *(str.begin() + i)) && stepIn)
		{
			j++;
			count++;
		}

		if (count != j)
		{
			stepIn = not stepIn;
		}
	}
	
	str.erase(i - j, j);

	for (int i = 0; i < pastedWord.size(); i++)
	{
		str.push_back(*(pastedWord.begin() + i));
	}
	return str;
}

// ���������� � ����� ���� - �����
void PasteStopWord(std::string& path) {
	std::ifstream fin(path);				// ������� ���� � �������
	if (fin.is_open())
	{
		char ch = '\n';
		std::string data;
		std::string end = "\nendl";
		std::ofstream fout(path, std::ios_base::app);	// ���������� � ����� ���� - �����
		fout << end;
		fout.close();
	}
}

// ������� ������� � ���������� ���� � ��������� �����
std::string DeleteComma(std::string& path) {
	std::ofstream fout;
	char ch = '\n';
	std::string data;
	std::ifstream fin(path, std::ios_base::in);
	std::string new_path = DeleteAndPasteNewWord(path, "input_data.txt", "output_data.txt");	//	��������� ���� � ��������� �����
	if (fin.is_open())
	{
		fout.open(new_path);
		while (data != "endl") {							// ��������� ���� �� �������� ���� - �����
			getline(fin, data, ch);
			if (data.find(',') != std::string::npos)		// ������� �������
			{
				data.replace(data.find(','), 1, " ");
			}
			fout << data << std::endl;
		}
		fout.close();
		fin.close();
	}
	return new_path;
}

void CellSettings(std::ofstream& stream, int cell_data, int width_cell, int precision ) {
	if (cell_data == myWORD) {
		WordCellSettings(stream, width_cell);
	}
	else {
		NumberCellSettings(stream, width_cell, precision);
	}
}

void NumberCellSettings(std::ofstream& stream, int width_cell, int precision) {
	stream.width(width_cell);
	stream.precision(precision);
}

void WordCellSettings(std::ofstream& stream, int width_cell) {
	stream.width(width_cell);
}
