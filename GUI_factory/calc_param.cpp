#include "calc_param.h"

/*
* 1. Добавляется стоп слово в конец
* 2. Удаляется запятая между данными
* 3. На основе входных данных формируется <vector> с высотой и дальностью
* 4. Формируется структура с данными для расчета
* 5. Формируется структура с выходными данными которые выгружаются в файл путь к которому такой же как и к файлу с входными данными
*/

input_parameters_s CreateInputStruct(std::vector<std::vector<double>>& coordinates) {
	input_parameters_s param;
	std::vector<double> heigths;
	std::vector<double> distances;
	// находим расстояние между станциями (км)
	param.distance_between_station = coordinates.at(coordinates.size() - 1).at(0) - coordinates.at(0).at(0);
	// находим высоту станции (м)
	param.height_station = coordinates.at(0).at(1);
	// высоты и расстояния преград (м)
	for (const std::vector<double>& v : coordinates) {
		if (v == coordinates.at(0) || v == coordinates.at(coordinates.size() - 1))
		{
			continue;
		}
		heigths.push_back(v.at(1));		// вставляем в вектор с высотами преград
		distances.push_back(v.at(0));	// вставляем в вектор с расстояниями преград
	}
	param.heights_blocks = heigths;
	param.distances_to_blocks = distances;
	return param;
}

output_parameters_s CreateOutputStruture(input_parameters_s* iparam, std::string& path,
	char* posA, char* posB) {
	output_parameters_s oparam;
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
	for (int i = 0; i < iparam->distances_to_blocks.size(); i++)
	{
		oparam.curvature_earth.push_back(pow(iparam->distances_to_blocks.at(i), 2) / 12.7); // считаем поправку на кривизну земли (м)
		CellSettings(fout, myNUMBER, strlen("поправка на кривизну земли\t"));
		fout << oparam.curvature_earth.at(i);
		oparam.height_visible.push_back(iparam->heights_blocks.at(i) - 
			oparam.curvature_earth.at(i)); // считаем видимую высоту (м)
		CellSettings(fout, myNUMBER, strlen("поправка на кривизну земли\t"));
		fout << oparam.height_visible.at(i);
		oparam.dheight.push_back(oparam.height_visible.at(i) - iparam->height_station); // считаем разницу высот (м)
		CellSettings(fout, myNUMBER, strlen("поправка на кривизну земли\t"));
		fout << oparam.dheight.at(i);
		oparam.closing_angle.push_back(atan(oparam.dheight.at(i) / 
			(iparam->distances_to_blocks.at(i) * 1000)) * 180 / PI);					// считаем угол закрытия (м)
		CellSettings(fout, myNUMBER, strlen("поправка на кривизну земли\t"));
		fout << oparam.closing_angle.at(i) << std::endl;
	}
	fout.close();
	return oparam;
}

// создаем вектор расстояние - пара
std::vector<std::vector<double>> CreateVectorDistanceHeght(std::string& path) {
	std::vector<std::vector<double>> coordinates;
	std::ifstream fin_string(path);
	std::ifstream fin_double(path);
	std::string data_string;
	std::vector<double> data_buff(2);				// пара расстояние-высота
	int i = 0;
	int j = 0;
	while (data_string != "endl")
	{
		fin_double >> data_buff[0];		// строка
		fin_double >> data_buff[1];		// столбец
		coordinates.push_back(data_buff);
		getline(fin_string, data_string, '\n');
	}
	fin_string.close();
	fin_double.close();
	coordinates.pop_back();
	return coordinates;
}

std::string Run(const char* path, char* posA, char* posB) {
	// копируем полученный путь в новую строку для того чтобы его преобразовать в выходной путь
	int i = 0;
	std::string s;
	while (*(path + i)) {
		s += *(path + i++);
	}

	// формируем выходной путь
	std::string output_path = RedactFile(s);

	// формируем вектор с высотами и дистанциями
	std::vector < std::vector < double >> coordinates = CreateVectorDistanceHeght(output_path);

	input_parameters_s iparam = CreateInputStruct(coordinates);
	output_parameters_s oparam = CreateOutputStruture(&iparam, output_path, posA, posB);

	output_parameters_s oparam_copy = oparam;	// чтобы не сломать выходные данные

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
	std::string result_str = "Максимальный угол закрытия:\t" + max_angle + "\n"
		+ "Минимальный угол закрытия:\t" + min_angle;
	return result_str;
}