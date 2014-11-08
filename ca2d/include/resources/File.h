#pragma once

#include <string>
#include <fstream>
#include <sstream>

namespace rend
{
	class File
	{
	public:
        File();
        File(const char* filename);
        File(std::string filename);

		bool load(const char* filename);
		void unload();

		bool isLoaded();

		std::string getContents() const;

		static bool exists(const char* filename);

    private:
        bool mIsLoaded;
        std::string mFilename;
	};

    inline File::File()
        : mIsLoaded(false)
    {

    }

    inline File::File(const char* filename)
        : mIsLoaded(false)
    {
        load(filename);
    }

    inline File::File(std::string filename)
        : mIsLoaded(false)
    {
        load(filename.c_str());
    }

    inline bool File::load(const char* filename)
    {
        if (exists(filename))
        {
            mIsLoaded = true;
            mFilename = filename;

            return true;
        }

        return false;
    }

    inline void File::unload()
    {
        mIsLoaded = false;
        mFilename = "";
    }

    inline bool File::isLoaded()
    {
        if (mIsLoaded)
        {
            if (exists(mFilename.c_str()))
                mIsLoaded = true;

            return mIsLoaded;
        }

        return false;
    }

    inline bool File::exists(const char* filename)
    {
        return std::ifstream(filename).good();
    }

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