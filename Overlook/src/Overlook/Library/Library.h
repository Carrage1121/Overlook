#pragma once 

#include "Overlook/Core/PublicSingleton.h"

#include <unordered_map>

namespace Overlook
{
    template <template <typename> typename Derived, typename LibType>
    class LibraryBase : public PublicSingleton<Derived<LibType>>
    {
    public:
        void Add(const std::string& name, const Ref<LibType>& mem)
        {
            OL_CORE_ASSERT(mLibrary.find(name) == mLibrary.end() && "Already have this member in Library!");
            mLibrary[name] = mem;
        }
        void Set(const std::string& name, const Ref<LibType>& mem)
        {
            OL_CORE_ASSERT(mLibrary.find(name) != mLibrary.end() && "Can't find this member in Library!");
            mLibrary[name] = mem;
        }
        [[nodiscard]] Ref<LibType> Get(const std::string& name)
        {
            OL_CORE_ASSERT(mLibrary.find(name) != mLibrary.end() && "Can't find this member in Library!");
            return mLibrary[name];
        }

    protected:
        std::unordered_map<std::string, Ref<LibType>> mLibrary;
    };

    template <typename LibType>
    class Library : public LibraryBase<Library, LibType>
    {
    public:
        Library();
    };
}