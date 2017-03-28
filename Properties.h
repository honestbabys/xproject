#ifndef _COMMON_PROPERTIES_H
#define _COMMON_PROPERTIES_H

#include <iostream>
#include <string>
#include <map>

class CProperties
{
public:
	CProperties(const std::string fileName);
	virtual ~CProperties();
	CProperties(const CProperties& copy); //copy constructor
	CProperties& operator =(const CProperties& copy); //assagin constructor
	void loadProperties();
	void printProperties();
	std::string getValue(const std::string& sectionName, const std::string& key);
	std::string getValue(const std::string& sectionName, const std::string& key, const std::string& defaultContent);
	int getSectionCount();
	std::map<std::string, std::string>* getSectionUnit(const std::string& sectionName); 
private:
	std::string _strFileName;
	const static int MAX_LINE = 256;
	std::map<std::string, std::map<std::string, std::string> > _mapSection;
};
#endif // !_COMMON_PROPERTIES_H

