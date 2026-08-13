#ifndef CERYS_DATATYPEREGISTER_7A3905547A154708BF3C499251365D4A_H
#define CERYS_DATATYPEREGISTER_7A3905547A154708BF3C499251365D4A_H

#include <string_view>

#include "base/Registry.h"
#include "defines.h"

namespace cerys::core::base {
using DatatypeRegistry = Registry<DataTypeID>;

inline constexpr std::string_view Int8Name{"Int8"};
inline constexpr std::string_view Int16Name{"Int16"};
inline constexpr std::string_view Int32Name{"Int32"};
inline constexpr std::string_view Int64Name{"Int64"};
inline constexpr std::string_view UInt8Name{"UInt8"};
inline constexpr std::string_view UInt16Name{"UInt16"};
inline constexpr std::string_view UInt32Name{"UInt32"};
inline constexpr std::string_view UInt64Name{"UInt64"};
inline constexpr std::string_view Float32Name{"Float32"};
inline constexpr std::string_view Float64Name{"Float64"};

inline const DataTypeID Int8ID = DatatypeRegistry::instance().registerName(Int8Name);
inline const DataTypeID Int16ID = DatatypeRegistry::instance().
    registerName(Int16Name);
inline const DataTypeID Int32ID = DatatypeRegistry::instance().
    registerName(Int32Name);
inline const DataTypeID Int64ID = DatatypeRegistry::instance().
    registerName(Int64Name);
inline const DataTypeID UInt8ID = DatatypeRegistry::instance().
    registerName(UInt8Name);
inline const DataTypeID UInt16ID = DatatypeRegistry::instance().
    registerName(UInt16Name);
inline const DataTypeID UInt32ID = DatatypeRegistry::instance().
    registerName(UInt32Name);
inline const DataTypeID UInt64ID = DatatypeRegistry::instance().
    registerName(UInt64Name);
inline const DataTypeID Float32ID = DatatypeRegistry::instance().
    registerName(Float32Name);
inline const DataTypeID Float64ID = DatatypeRegistry::instance().
    registerName(Float64Name);

constexpr DataTypeID NullDataTypeID = std::numeric_limits<DataTypeID>::max();

inline std::string getDatatypeName(const DataTypeID id) noexcept {
    return DatatypeRegistry::instance().getName(id);
}
}

#endif // CERYS_DATATYPEREGISTER_7A3905547A154708BF3C499251365D4A_H