#include "resources/File.h"

namespace ca2d
{

    /* Create this file object without binding it to a specific file */
    File::File()
    {

    }

    /* Create this file object and bind it to a file */
    File::File(const char* filename)
    {
        load(filename);
    }

    /* Change the file this object is bound to */
    bool File::load(const char* filename)
    {
        if (exists(filename))
        {
            mFilename = filename;

            return true;
        }

        return false;
    }

    /* Reset this file object's binding */
    void File::unload()
    {
        mFilename = "";
    }

    /* Check if this file exists */
    bool File::exists() const
    {
        return std::ifstream(mFilename).good();
    }

    /* Check if a file exists */
    bool File::exists(const char* filename)
    {
        return std::ifstream(filename).good();
    }
}