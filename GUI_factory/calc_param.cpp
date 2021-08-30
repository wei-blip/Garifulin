#include "calc_param.h"

/*
* 1. ��������� ������� ����� �������
* 2. �� ������ ������� ������ ����������� <vector> � ������� � ����������
* 3. ����������� ��������� � ������� ��� �������
* 4. ����������� ��������� � ��������� ������� ������� ����������� � ���� ���� � �������� ����� �� ��� � � ����� � �������� �������
*/

void CalcParam::CreateInputStruct(std::vector<std::vector<double>>& coordinates) {
	std::vector<double> heigths;
	std::vector<double> distances;
	// ������� ���������� ����� ��������� (��)
	iparam_m.distance_between_station = coordinates.at(coordinates.size() - 1).at(0) - coordinates.at(0).at(0);
	// ������� ������ ������� (�)
	iparam_m.height_station = coordinates.at(0).at(1);
	// ������ � ���������� ������� (�)
	for (const std::vector<double>& v : coordinates) {
		if (v == coordinates.at(0) || v == coordinates.at(coordinates.size() - 1))
		{
			continue;
		}
		heigths.push_back(v.at(1));		// ��������� � ������ � �������� �������
		distances.push_back(v.at(0));	// ��������� � ������ � ������������ �������
	}
	iparam_m.heights_blocks = heigths;
	iparam_m.distances_to_blocks = distances;
}

void CalcParam::CreateOutputStruct(std::string& path, char* posA, char* posB) {
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
	for (int i = 0; i < iparam_m.distances_to_blocks.size(); i++)
	{
		oparam_m.curvature_earth.push_back(pow(iparam_m.distances_to_blocks.at(i), 2) / 12.7); // ������� �������� �� �������� ����� (�)
		CellSettings(fout, myNUMBER, strlen("�������� �� �������� �����\t"));
		fout << oparam_m.curvature_earth.at(i);
		oparam_m.height_visible.push_back(iparam_m.heights_blocks.at(i) -
			oparam_m.curvature_earth.at(i)); // ������� ������� ������ (�)
		CellSettings(fout, myNUMBER, strlen("�������� �� �������� �����\t"));
		fout << oparam_m.height_visible.at(i);
		oparam_m.dheight.push_back(oparam_m.height_visible.at(i) - iparam_m.height_station); // ������� ������� ����� (�)
		CellSettings(fout, myNUMBER, strlen("�������� �� �������� �����\t"));
		fout << oparam_m.dheight.at(i);
		oparam_m.closing_angle.push_back(atan(oparam_m.dheight.at(i) /
			(iparam_m.distances_to_blocks.at(i) * 1000)) * 180 / PI);					// ������� ���� �������� (�)
		CellSettings(fout, myNUMBER, strlen("�������� �� �������� �����\t"));
		fout << oparam_m.closing_angle.at(i) << std::endl;
	}
	fout.close();
}

// ������� ������ ���������� - ����
std::vector<std::vector<double>> CalcParam::CreateVectorDistanceHeght(std::string& path) {
	std::vector<std::vector<double>> coordinates;
	std::ifstream fin_vector(path);
	std::ifstream fin_string(path);
	std::string s;
	std::vector<double> data_buff(2);				// ���� ����������-������
	while ( !fin_string.eof() )
	{
		fin_vector >> data_buff[0];		// ������
		fin_vector >> data_buff[1];		// �������
		coordinates.push_back(data_buff);
		getline(fin_string, s, '\n');
	}
	fin_vector.close();
	fin_string.close();
	coordinates.pop_back();
	return coordinates;
}

// ��������� ��������� � �������� � ��������� �������, ��������� �������� ���� ������������ �������
CalcParam::CalcParam(const char* path, char* posA, char* posB) {
	// �������� ���������� ���� � ����� ������ ��� ���� ����� ��� ������������� � �������� ����
	std::string ipath = CreateString(path);

	RedactFile NewOutputPath(ipath);
	// ��������� �������� ����
	std::string output_path = NewOutputPath.Run();

	// ��������� ������ � �������� � �����������
	std::vector < std::vector < double >> coordinates = CreateVectorDistanceHeght(output_path);

	CreateInputStruct(coordinates);					// �������� iparam
	CreateOutputStruct(output_path, posA, posB);	// �������� oparam
}

// ��������� ������ ���������� ������� ����� ��������� �� �����
std::string CalcParam::PrintAngles() {
	output_parameters_s oparam_copy = oparam_m;		// ����� �� ������� �������� ������
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
	std::string result_str =  "������������ ���� ��������:\t" + max_angle + "\n"
							+ "����������� ���� ��������:\t" + min_angle;
	return result_str;
}