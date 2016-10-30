#ifndef _TEXT_ASSET_H_
#define _TEXT_ASSET_H_

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <Trackable.h>

class TextAsset : public Trackable
{
public:
	TextAsset();
	~TextAsset();

	size_t read(const std::string& filename);
	size_t write(const std::string& filename);

	void display();

private:
	std::stringstream m_stream;
};

#endif // !_TEXT_ASSET_H_
