#include "calc_param.h"

/*
* 1. Удаляется запятая между данными
* 2. На основе входных данных формируется <vector> с высотой и дальностью
* 3. Формируется структура с данными для расчета
* 4. Формируется структура с выходными данными которые выгружаются в файл путь к которому такой же как и к файлу с входными данными
*/

void CalcParam::CreateInputStruct(std::vector<std::vector<double>>& coordinates) {
	std::vector<double> heigths;
	std::vector<double> distances;
	// находим расстояние между станциями (км)
	iparam_m.distance_between_station = coordinates.at(coordinates.size() - 1).at(0) - coordinates.at(0).at(0);
	// находим высоту станции (м)
	iparam_m.height_station = coordinates.at(0).at(1);
	// высоты и расстояния преград (м)
	for (const std::vector<double>& v : coordinates) {
		if (v == coordinates.at(0) || v == coordinates.at(coordinates.size() - 1))
		{
			continue;
		}
		heigths.push_back(v.at(1));		// вставляем в вектор с высотами преград
		distances.push_back(v.at(0));	// вставляем в вектор с расстояниями преград
	}
	iparam_m.heights_blocks = heigths;
	iparam_m.distances_to_blocks = distances;
}

void CalcParam::CreateOutputStruct(std::string& path, char* posA, char* posB) {
	std::ofstream fout(path, std::ios_base::trunc | std::ios_base::out); // открываем файл для записи предварительно отчистив его
	fout << CreateString(posA) << " - " << CreateString(posB) << "\n";
	CellSettings(fout, myWORD, strlen("поправка на кривизну земли\t"));
	fout << "Поправка на кривизну земли";
	CellSettings(fout, myWORD, strlen("поправка на кривизну земли\t"));
	fout << "Видимая высота";
	CellSettings(fout, myWORD, strlen("поправка на кривизну земли\t"));
	fout << "Разница высот";
	CellSettings(fout, myWORD, strlen("поправка на кривизну земли\t"));
	fout << "Угол закрытия\n";
	for (int i = 0; i < iparam_m.distances_to_blocks.size(); i++)
	{
		oparam_m.curvature_earth.push_back(pow(iparam_m.distances_to_blocks.at(i), 2) / 12.7); // считаем поправку на кривизну земли (м)
		CellSettings(fout, myNUMBER, strlen("поправка на кривизну земли\t"));
		fout << oparam_m.curvature_earth.at(i);
		oparam_m.height_visible.push_back(iparam_m.heights_blocks.at(i) -
			oparam_m.curvature_earth.at(i)); // считаем видимую высоту (м)
		CellSettings(fout, myNUMBER, strlen("поправка на кривизну земли\t"));
		fout << oparam_m.height_visible.at(i);
		oparam_m.dheight.push_back(oparam_m.height_visible.at(i) - iparam_m.height_station); // считаем разницу высот (м)
		CellSettings(fout, myNUMBER, strlen("поправка на кривизну земли\t"));
		fout << oparam_m.dheight.at(i);
		oparam_m.closing_angle.push_back(atan(oparam_m.dheight.at(i) /
			(iparam_m.distances_to_blocks.at(i) * 1000)) * 180 / PI);					// считаем угол закрытия (м)
		CellSettings(fout, myNUMBER, strlen("поправка на кривизну земли\t"));
		fout << oparam_m.closing_angle.at(i) << std::endl;
	}
	fout.close();
}

// создаем вектор расстояние - пара
std::vector<std::vector<double>> CalcParam::CreateVectorDistanceHeght(std::string& path) {
	std::vector<std::vector<double>> coordinates;
	std::ifstream fin_vector(path);
	std::ifstream fin_string(path);
	std::string s;
	std::vector<double> data_buff(2);				// пара расстояние-высота
	while ( !fin_string.eof() )
	{
		fin_vector >> data_buff[0];		// строка
		fin_vector >> data_buff[1];		// столбец
		coordinates.push_back(data_buff);
		getline(fin_string, s, '\n');
	}
	fin_vector.close();
	fin_string.close();
	coordinates.pop_back();
	return coordinates;
}

// Формирует структуры с входными и выходными данными, заполняет выходной файл расчитанными данными
CalcParam::CalcParam(const char* path, char* posA, char* posB) {
	// копируем полученный путь в новую строку для того чтобы его преобразовать в выходной путь
	std::string ipath = CreateString(path);

	RedactFile NewOutputPath(ipath);
	// формируем выходной путь
	std::string output_path = NewOutputPath.Run();

	// формируем вектор с высотами и дистанциями
	std::vector < std::vector < double >> coordinates = CreateVectorDistanceHeght(output_path);

	CreateInputStruct(coordinates);					// заполняю iparam
	CreateOutputStruct(output_path, posA, posB);	// заполняю oparam
}

// Формирует строку содержимое которой потом выведется на экран
std::string CalcParam::PrintAngles() {
	output_parameters_s oparam_copy = oparam_m;		// чтобы не сломать выходные данные
	std::sort(oparam_copy.closing_angle.begin(), oparam_copy.closing_angle.end());

	// проверяем структуру на пустоту и если она пустая возвращаем пустую строку
	if (oparam_copy.closing_angle.empty() ||
		oparam_copy.curvature_earth.empty() ||
		oparam_copy.dheight.empty() ||
		oparam_copy.height_visible.empty() ) {
		return "";
	}
	std::string min_angle = std::to_string(oparam_copy.closing_angle[0]);
	std::string max_angle = std::to_string(oparam_copy.closing_angle[oparam_copy.closing_angle.size() - 1]);
	
	// для вывода в окно с максимальными и минимальными углами закрытия
	std::string result_str =  "Максимальный угол закрытия:\t" + max_angle + "\n"
							+ "Минимальный угол закрытия:\t" + min_angle;
	return result_str;
}