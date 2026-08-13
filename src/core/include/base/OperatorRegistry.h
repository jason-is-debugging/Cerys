#ifndef CERYS_OPERATORREGISTER_4984779273484CE0B8546FD40929C648_H
#define CERYS_OPERATORREGISTER_4984779273484CE0B8546FD40929C648_H

#include <string_view>

#include "base/Registry.h"
#include "defines.h"

namespace cerys::core::base {
using OperatorRegistry = Registry<OperatorID>;

inline constexpr std::string_view AddOperatorName{"add"};
inline constexpr std::string_view SubtractOperatorName{"subtract"};
inline constexpr std::string_view MultiplyOperatorName{"multiply"};
inline constexpr std::string_view DivideOperatorName{"divide"};
inline constexpr std::string_view MatMulOperatorName{"matmul"};
inline constexpr std::string_view ConvolutionOperatorName{"convolution"};
inline constexpr std::string_view LinearOperatorName{"linear"};
inline constexpr std::string_view ReLUOperatorName{"relu"};
inline constexpr std::string_view SigmoidOperatorName{"sigmoid"};
inline constexpr std::string_view TanhOperatorName{"tanh"};
inline constexpr std::string_view SoftmaxOperatorName{"softmax"};
inline constexpr std::string_view MaxPoolOperatorName{"max_pool"};
inline constexpr std::string_view AveragePoolOperatorName{"average_pool"};
inline constexpr std::string_view BatchNormOperatorName{"batch_norm"};
inline constexpr std::string_view LayerNormOperatorName{"layer_norm"};
inline constexpr std::string_view DropoutOperatorName{"dropout"};
inline constexpr std::string_view EmbeddingOperatorName{"embedding"};
inline constexpr std::string_view ReshapeOperatorName{"reshape"};
inline constexpr std::string_view TransposeOperatorName{"transpose"};
inline constexpr std::string_view ConcatenateOperatorName{"concatenate"};

inline const OperatorID AddOperatorID = OperatorRegistry::instance().registerName(
    AddOperatorName);
inline const OperatorID SubtractOperatorID = OperatorRegistry::instance().
    registerName(SubtractOperatorName);
inline const OperatorID MultiplyOperatorID = OperatorRegistry::instance().
    registerName(MultiplyOperatorName);
inline const OperatorID DivideOperatorID = OperatorRegistry::instance().registerName(
    DivideOperatorName);
inline const OperatorID MatMulOperatorID = OperatorRegistry::instance().registerName(
    MatMulOperatorName);
inline const OperatorID ConvolutionOperatorID = OperatorRegistry::instance().
    registerName(ConvolutionOperatorName);
inline const OperatorID LinearOperatorID = OperatorRegistry::instance().registerName(
    LinearOperatorName);
inline const OperatorID ReLUOperatorID = OperatorRegistry::instance().registerName(
    ReLUOperatorName);
inline const OperatorID SigmoidOperatorID = OperatorRegistry::instance().
    registerName(SigmoidOperatorName);
inline const OperatorID TanhOperatorID = OperatorRegistry::instance().registerName(
    TanhOperatorName);
inline const OperatorID SoftmaxOperatorID = OperatorRegistry::instance().
    registerName(SoftmaxOperatorName);
inline const OperatorID MaxPoolOperatorID = OperatorRegistry::instance().
    registerName(MaxPoolOperatorName);
inline const OperatorID AveragePoolOperatorID = OperatorRegistry::instance().
    registerName(AveragePoolOperatorName);
inline const OperatorID BatchNormOperatorID = OperatorRegistry::instance().
    registerName(BatchNormOperatorName);
inline const OperatorID LayerNormOperatorID = OperatorRegistry::instance().
    registerName(LayerNormOperatorName);
inline const OperatorID DropoutOperatorID = OperatorRegistry::instance().
    registerName(DropoutOperatorName);
inline const OperatorID EmbeddingOperatorID = OperatorRegistry::instance().
    registerName(EmbeddingOperatorName);
inline const OperatorID ReshapeOperatorID = OperatorRegistry::instance().
    registerName(ReshapeOperatorName);
inline const OperatorID TransposeOperatorID = OperatorRegistry::instance().
    registerName(TransposeOperatorName);
inline const OperatorID ConcatenateOperatorID = OperatorRegistry::instance().
    registerName(ConcatenateOperatorName);

constexpr OperatorID NullOperatorID = std::numeric_limits<OperatorID>::max();

inline std::string getOperatorName(const OperatorID id) noexcept {
    return OperatorRegistry::instance().getName(id);
}
}

#endif // CERYS_OPERATORREGISTER_4984779273484CE0B8546FD40929C648_H