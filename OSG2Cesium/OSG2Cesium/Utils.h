#pragma once
#include <string>
#include <vector>
class Utils
{
public: 
	Utils();
	~Utils();
	//�г��������ļ���
	static std::vector<std::string> findSubdirs(std::string dir);
	//�ļ�·���ָ�
	static void splitFilepath(std::string filepath, std::string& dir, std::string& name, std::string& ext);
};

