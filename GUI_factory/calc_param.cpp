#include "calc_param.h"

/*
* 1. ����������� ���� ����� � �����
* 2. ��������� ������� ����� �������
* 3. �� ������ ������� ������ ����������� <vector> � ������� � ����������
* 4. ����������� ��������� � ������� ��� �������
* 5. ����������� ��������� � ��������� ������� ������� ����������� � ���� ���� � �������� ����� �� ��� � � ����� � �������� �������
*/

input_parameters_s CreateInputStruct(std::vector<std::vector<double>>& coordinates) {
	input_parameters_s param;
	std::vector<double> heigths;
	std::vector<double> distances;
	// ������� ���������� ����� ��������� (��)
	param.distance_between_station = coordinates.at(coordinates.size() - 1).at(0) - coordinates.at(0).at(0);
	// ������� ������ ������� (�)
	param.height_station = coordinates.at(0).at(1);
	// ������ � ���������� ������� (�)
	for (const std::vector<double>& v : coordinates) {
		if (v == coordinates.at(0) || v == coordinates.at(coordinates.size() - 1))
		{
			continue;
		}
		heigths.push_back(v.at(1));		// ��������� � ������ � �������� �������
		distances.push_back(v.at(0));	// ��������� � ������ � ������������ �������
	}
	param.heights_blocks = heigths;
	param.distances_to_blocks = distances;
	return param;
}

output_parameters_s CreateOutputStruture(input_parameters_s* iparam, std::string& path,
	char* posA, char* posB) {
	output_parameters_s oparam;
	std::ofstream fout(path, std::ios_base::trunc | std::ios_base::out); // ��������� ���� ��� ������ �������������� �������� ���
	fout << CreateString(posA) << " - " << CreateString(posB) << "\n";
	CellSettings(fout, myWORD, strlen("�������� �� �������� �����\t"));
	fout << "�������� �� �������� �����";
	CellSettings(fout, myWORD, strlen("�������� �� �������� �����\t"));
	fout << "������� ������";
	CellSettings(fout, myWORD, strlen("�������� �� �������� �����\t"));
	fout << "������� �����";
	CellSettings(fout, myWORD, strlen("�������� �� �������� �����\t"));
	fout << "���� ��������\n";
	for (int i = 0; i < iparam->distances_to_blocks.size(); i++)
	{
		oparam.curvature_earth.push_back(pow(iparam->distances_to_blocks.at(i), 2) / 12.7); // ������� �������� �� �������� ����� (�)
		CellSettings(fout, myNUMBER, strlen("�������� �� �������� �����\t"));
		fout << oparam.curvature_earth.at(i);
		oparam.height_visible.push_back(iparam->heights_blocks.at(i) - 
			oparam.curvature_earth.at(i)); // ������� ������� ������ (�)
		CellSettings(fout, myNUMBER, strlen("�������� �� �������� �����\t"));
		fout << oparam.height_visible.at(i);
		oparam.dheight.push_back(oparam.height_visible.at(i) - iparam->height_station); // ������� ������� ����� (�)
		CellSettings(fout, myNUMBER, strlen("�������� �� �������� �����\t"));
		fout << oparam.dheight.at(i);
		oparam.closing_angle.push_back(atan(oparam.dheight.at(i) / 
			(iparam->distances_to_blocks.at(i) * 1000)) * 180 / PI);					// ������� ���� �������� (�)
		CellSettings(fout, myNUMBER, strlen("�������� �� �������� �����\t"));
		fout << oparam.closing_angle.at(i) << std::endl;
	}
	fout.close();
	return oparam;
}

// ������� ������ ���������� - ����
std::vector<std::vector<double>> CreateVectorDistanceHeght(std::string& path) {
	std::vector<std::vector<double>> coordinates;
	std::ifstream fin_string(path);
	std::ifstream fin_double(path);
	std::string data_string;
	std::vector<double> data_buff(2);				// ���� ����������-������
	int i = 0;
	int j = 0;
	while (data_string != "endl")
	{
		fin_double >> data_buff[0];		// ������
		fin_double >> data_buff[1];		// �������
		coordinates.push_back(data_buff);
		getline(fin_string, data_string, '\n');
	}
	fin_string.close();
	fin_double.close();
	coordinates.pop_back();
	return coordinates;
}

std::string Run(const char* path, char* posA, char* posB) {
	// �������� ���������� ���� � ����� ������ ��� ���� ����� ��� ������������� � �������� ����
	int i = 0;
	std::string s;
	while (*(path + i)) {
		s += *(path + i++);
	}

	// ��������� �������� ����
	std::string output_path = RedactFile(s);

	// ��������� ������ � �������� � �����������
	std::vector < std::vector < double >> coordinates = CreateVectorDistanceHeght(output_path);

	input_parameters_s iparam = CreateInputStruct(coordinates);
	output_parameters_s oparam = CreateOutputStruture(&iparam, output_path, posA, posB);

	output_parameters_s oparam_copy = oparam;	// ����� �� ������� �������� ������

	std::sort(oparam_copy.closing_angle.begin(), oparam_copy.closing_angle.end());

	// ��������� ��������� �� ������� � ���� ��� ������ ���������� ������ ������
	if (oparam_copy.closing_angle.empty() ||
		oparam_copy.curvature_earth.empty() ||
		oparam_copy.dheight.empty() ||
		oparam_copy.height_visible.empty() ) {
		return "";
	}
	std::string min_angle = std::to_string(oparam_copy.closing_angle[0]);
	std::string max_angle = std::to_string(oparam_copy.closing_angle[oparam_copy.closing_angle.size() - 1]);
	
	// ��� ������ � ���� � ������������� � ������������ ������ ��������
	std::string result_str = "������������ ���� ��������:\t" + max_angle + "\n"
		+ "����������� ���� ��������:\t" + min_angle;
	return result_str;
}