# Architecture detection module
# Detects target architecture and sets appropriate macros

# Allow override of target architecture
set(CERYS_TARGET_ARCH "" CACHE STRING
        "Override target architecture (e.g. aarch64, x86_64). Empty = use CMAKE_SYSTEM_PROCESSOR.")

set(_arch_to_use "${CMAKE_SYSTEM_PROCESSOR}")
if (CERYS_TARGET_ARCH)
    set(_arch_to_use "${CERYS_TARGET_ARCH}")
endif ()

# Determine bitness
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(CERYS_ARCH_BITS 64)
elseif (CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(CERYS_ARCH_BITS 32)
else ()
    set(CERYS_ARCH_BITS 0)
endif ()

# Detect architecture
string(TOLOWER "${_arch_to_use}" _processor_lower)

if (_processor_lower MATCHES "^(amd64|x86_64|x64)$")
    set(CERYS_ARCH_X86_64 1)
    set(CERYS_ARCH_IS_X86_FAMILY 1)
    set(CERYS_ARCH_NAME "x86-64")
elseif (_processor_lower MATCHES "^(i[3-6]86|x86|i86pc)$")
    set(CERYS_ARCH_X86_32 1)
    set(CERYS_ARCH_IS_X86_FAMILY 1)
    set(CERYS_ARCH_NAME "x86")
elseif (_processor_lower MATCHES "^(aarch64|arm64|armv8)$")
    set(CERYS_ARCH_ARM64 1)
    set(CERYS_ARCH_NAME "arm64")
elseif (_processor_lower MATCHES "^(arm|armv7|armv6|armv5)$")
    set(CERYS_ARCH_ARM32 1)
    set(CERYS_ARCH_NAME "arm32")
elseif (_processor_lower MATCHES "^(ppc64|powerpc64)$")
    set(CERYS_ARCH_PPC64 1)
    set(CERYS_ARCH_NAME "ppc64")
elseif (_processor_lower MATCHES "^(riscv64|rv64)$")
    set(CERYS_ARCH_RISCV64 1)
    set(CERYS_ARCH_NAME "riscv64")
else ()
    message(WARNING "Unknown architecture: ${_arch_to_use}")
    set(CERYS_ARCH_UNKNOWN 1)
    set(CERYS_ARCH_NAME "unknown")
endif ()

# Export architecture variables for parent scope
# Only set PARENT_SCOPE if we're in a function scope (not top-level)
if(CMAKE_CURRENT_FUNCTION_LIST_DIR)
    set(CERYS_ARCH_BITS ${CERYS_ARCH_BITS} PARENT_SCOPE)
    set(CERYS_ARCH_NAME ${CERYS_ARCH_NAME} PARENT_SCOPE)
    set(CERYS_ARCH_X86_64 ${CERYS_ARCH_X86_64} PARENT_SCOPE)
    set(CERYS_ARCH_X86_32 ${CERYS_ARCH_X86_32} PARENT_SCOPE)
    set(CERYS_ARCH_ARM64 ${CERYS_ARCH_ARM64} PARENT_SCOPE)
    set(CERYS_ARCH_ARM32 ${CERYS_ARCH_ARM32} PARENT_SCOPE)
    set(CERYS_ARCH_PPC64 ${CERYS_ARCH_PPC64} PARENT_SCOPE)
    set(CERYS_ARCH_RISCV64 ${CERYS_ARCH_RISCV64} PARENT_SCOPE)
    set(CERYS_ARCH_UNKNOWN ${CERYS_ARCH_UNKNOWN} PARENT_SCOPE)
    set(CERYS_ARCH_IS_X86_FAMILY ${CERYS_ARCH_IS_X86_FAMILY} PARENT_SCOPE)
endif()
