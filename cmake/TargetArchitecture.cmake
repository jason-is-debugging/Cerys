# Target architecture configuration module
# Applies architecture-specific compile definitions to targets

function(apply_architecture_to_target target_name)
    # Define architecture macros via compile definitions
    if (CERYS_ARCH_X86_64)
        target_compile_definitions(${target_name} PUBLIC
            CERYS_ARCH_X86_64=1
            CERYS_ARCH_IS_X86_FAMILY=1
            CERYS_ARCH_BITS=${CERYS_ARCH_BITS}
            CERYS_ARCH_NAME="${CERYS_ARCH_NAME}"
        )
    elseif (CERYS_ARCH_X86_32)
        target_compile_definitions(${target_name} PUBLIC
            CERYS_ARCH_X86_32=1
            CERYS_ARCH_IS_X86_FAMILY=1
            CERYS_ARCH_BITS=${CERYS_ARCH_BITS}
            CERYS_ARCH_NAME="${CERYS_ARCH_NAME}"
        )
    elseif (CERYS_ARCH_ARM64)
        target_compile_definitions(${target_name} PUBLIC
            CERYS_ARCH_ARM64=1
            CERYS_ARCH_BITS=${CERYS_ARCH_BITS}
            CERYS_ARCH_NAME="${CERYS_ARCH_NAME}"
        )
    elseif (CERYS_ARCH_ARM32)
        target_compile_definitions(${target_name} PUBLIC
            CERYS_ARCH_ARM32=1
            CERYS_ARCH_BITS=${CERYS_ARCH_BITS}
            CERYS_ARCH_NAME="${CERYS_ARCH_NAME}"
        )
    elseif (CERYS_ARCH_PPC64)
        target_compile_definitions(${target_name} PUBLIC
            CERYS_ARCH_PPC64=1
            CERYS_ARCH_BITS=${CERYS_ARCH_BITS}
            CERYS_ARCH_NAME="${CERYS_ARCH_NAME}"
        )
    elseif (CERYS_ARCH_RISCV64)
        target_compile_definitions(${target_name} PUBLIC
            CERYS_ARCH_RISCV64=1
            CERYS_ARCH_BITS=${CERYS_ARCH_BITS}
            CERYS_ARCH_NAME="${CERYS_ARCH_NAME}"
        )
    elseif (CERYS_ARCH_UNKNOWN)
        target_compile_definitions(${target_name} PUBLIC CERYS_ARCH_UNKNOWN=1)
    endif ()
endfunction()
