#include"RedactTextFile.h"
#include<cmath>
#include<algorithm>

//#pragma once

#define PI 3.14159265  

struct input_parameters_s
{
	double distance_between_station;
	std::vector<double> distances_to_blocks;
	double height_station;
	std::vector<double> heights_blocks;
};

struct output_parameters_s
{
	std::vector<double> curvature_earth;
	std::vector<double> height_visible;
	std::vector<double> dheight;
	std::vector<double> closing_angle;
};

class CalcParam {
public:
	CalcParam(const char* path, char* posA, char* posB);
	std::string PrintAngles();
private:
	input_parameters_s iparam_m;
	output_parameters_s oparam_m;
	std::vector<std::vector<double>> CreateVectorDistanceHeght(std::string& path);
	void CreateInputStruct(std::vector<std::vector<double>>& coordinates);
	void CreateOutputStruct(std::string& path, char* posA, char* posB);
};

//
//input_parameters_s CreateInputStruct(std::vector<std::vector<double>> &coordinates);
//output_parameters_s CreateOutputStruture(input_parameters_s* iparam, std::string& path,
//	char* posA, char* posB);
//std::vector<std::vector<double>> CreateVectorDistanceHeght(std::string& path);
//std::string Run(const char* path, char* posA, char* posB);