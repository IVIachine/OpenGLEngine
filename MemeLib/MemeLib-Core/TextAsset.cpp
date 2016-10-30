#include "TextAsset.h"

TextAsset::TextAsset()
{
}

TextAsset::~TextAsset()
{
}

size_t TextAsset::read(const std::string & filename)
{
	m_stream.clear();

	std::ifstream	file(filename);
	size_t			linesRead = 0;
	std::string		line = "";

	while (file.good())
	{
		std::getline(file, line);
		m_stream << line << "\n";
		linesRead++;
	}

	file.close();

	return linesRead;
}

size_t TextAsset::write(const std::string & filename)
{
	std::ofstream	file(filename);
	size_t			linesWritten = 0;
	std::string		line = "";

	while (m_stream.good())
	{
		std::getline(m_stream, line);
		file << line << "\n";
		linesWritten++;
	}

	file.close();

	return linesWritten;
}


void TextAsset::display()
{
	for (size_t i = 0; m_stream.good(); i++)
	{
		std::string line;
		std::getline(m_stream, line);

		std::cout
			<< "" << i << "| " << line << "\n";
	}
}
