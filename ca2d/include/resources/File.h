#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace ca2d
{
	class File
	{
	public:

        /* Create this file object without binding it to a specific file */
        File();

        /* Create this file object and bind it to a file */
        File(const char* filename);

        /* Change the file this object is bound to */
		bool load(const char* filename);

        /* Reset this file object's binding */
		void unload();

        /* Get the contents of the file */
		std::string getContents() const;

        /* Check if this file exists */
        bool exists() const;

        /* Check if a file exists */
		static bool exists(const char* filename);

    private:

        /* The filename of the currently bound file */
        std::string mFilename;

	};

    /* Get the contents of the file */
    inline std::string File::getContents() const
    {
        // Read file into stringstream
        std::ifstream inFile(mFilename);

        if (inFile.good())
        {
            std::stringstream ss;

            ss << inFile.rdbuf();

            return ss.str();
        }

        return "";
    }
}