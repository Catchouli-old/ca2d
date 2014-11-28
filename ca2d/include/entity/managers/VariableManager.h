#pragma once

#include <map>
#include <string>
#include <memory>
#include <typeindex>

namespace ca2d
{
    
    /** A variable type map - values are stored behind shared_ptrs
        to provide type erasure and cleanup. */
    typedef std::map<std::string, std::shared_ptr<void>> VariableMap;

    /** A key-value map for generic variables. This is (mostly) a header-only class
        due to the use of templates and stl containers. */
    class VariableManager
    {
    public:

        /** Construct the variable manager */
        VariableManager();

        /** Set the value of a variable */
        template <typename T>
        void setValue(const char* key, const T& value);

        /** Set the value of a variable */
        template <typename T, typename... Args>
        void constructValue(const char* key, Args... args);

        /** Remove a value from the store */
        template <typename T>
        void unsetValue(const char* key);

        /** Get a pointer to a value */
        template <typename T>
        T* getValue(const char* key);

        /** Get a pointer to a value */
        template <typename T>
        const T* getValue(const char* key) const;

    private:

        /** A map to the variable maps */
        std::map<std::type_index, VariableMap> mTypeMap;

    };

    /** Construct the variable manager */
    inline VariableManager::VariableManager()
    {

    }

    /** Set the value of a variable */
    template <typename T>
    void VariableManager::setValue(const char* key, const T& value)
    {
        // Get the map for this type
        VariableMap& variableMap = mTypeMap[typeid(T)];

        // Copy construct the value and insert a unique_ptr to it
        variableMap[key] = std::shared_ptr<T>(new T(value));
    }

    /** Set the value of a variable */
    template <typename T, typename... Args>
    void VariableManager::constructValue(const char* key, Args... args)
    {
        // Get the map for this type
        VariableMap& variableMap = mTypeMap[typeid(T)];

        // Copy construct the value and insert a unique_ptr to it
        variableMap[key] = std::make_shared<T>(args...);
    }

    /** Remove a value from the store */
    template <typename T>
    void VariableManager::unsetValue(const char* key)
    {
        // Get the map for this type
        VariableMap& variableMap = mTypeMap[typeid(T)];

        // Insert a nullptr instead of actually removing anything
        variableMap[key] = nullptr;
    }

    /** Get a pointer to a value. In the case that the value is not
        defined, nullptr is returned */
    template <typename T>
    T* VariableManager::getValue(const char* key)
    {
        T* ptr = nullptr;

        // Get the map for this type
        VariableMap& variableMap = mTypeMap[typeid(T)];

        // If map contains this key, get the 
        if (variableMap.find(key) != variableMap.end())
            ptr = static_cast<T*>(variableMap.at(key).get());

        return ptr;
    }

    /** Get a pointer to a value. In the case that the value is not
        defined, nullptr is returned */
    template <typename T>
    const T* VariableManager::getValue(const char* key) const
    {
        const T* ptr = nullptr;

        // Get the map for this type
        // Check it exists first since we can't use map::operator[] in the const version
        if (mTypeMap.find(typeid(T)) != mTypeMap.end())
        {
            const VariableMap& variableMap = mTypeMap.at(typeid(T));

            // If map contains this key, get the 
            if (variableMap.find(key) != variableMap.end())
                ptr = static_cast<T*>(variableMap.at(key).get());
        }

        return ptr;
    }

}