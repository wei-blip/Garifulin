#include"RedactTextFile.h"

void NumberCellSettings(std::ofstream& stream, int width_cell, int precision);
void WordCellSettings(std::ofstream& stream, int width_cell);

std::string RedactFile::GetInPath() { 
	return this->ipath_m;
}

std::string RedactFile::GetOutPath() {
	return this->opath_m;
}

void RedactFile::CommaToSpace() {
	std::string data;
	if (inDataFile_m.is_open())
	{
		outDataFile_m.open(opath_m);
		while (!inDataFile_m.eof()) {							// считываем пока не дойдём до конца файла
			getline(inDataFile_m, data, '\n');
			if (data.find(',') != std::string::npos)			// удаляем запятую и заменяем её на пробел
			{
				data.replace(data.find(','), 1, " ");
			}
			outDataFile_m << data << std::endl;
		}
		outDataFile_m.close();
		inDataFile_m.close();
	}
}

// удаляем и вставляем новое слово
std::string RedactFile::StrChange(std::string str, std::string deletedWord, std::string pastedWord) {
	long int j = 0, i = 0;
	for (; i < str.size(); i++)
	{
		// находим совпадение
		// если буквы совпадают то j инкрементируется
		// иначе j обнуляется
		if ( (*(deletedWord.begin() + j) == *(str.begin() + i)) ) {
			j++;
		}
		else {
			j = 0;
		}

	}
	
	str.erase(i - j, j);

	for (int i = 0; i < pastedWord.size(); i++)
	{
		str.push_back(*(pastedWord.begin() + i));
	}
	return str;
}

// удаляем запятую и возвращаем путь к выходному файлу
std::string RedactFile::Run() {
	inDataFile_m.open(ipath_m, std::ios_base::in); // отсюда считываем строку из которой будем удалять запятую
	opath_m = StrChange(ipath_m, "input_data.txt", "output_data.txt");	//	формируем путь к выходному файлу
	CommaToSpace();
	return opath_m;
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

std::string CreateString(const char* CharPtr) {
	std::string str;
	while (*(CharPtr)) {
		str += *(CharPtr++);
	}
	return str;
}
