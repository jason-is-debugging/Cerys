//  Copyright (c) 2026-2026 Contributors of Cerys(https://github.com/jason-is-debugging/Cerys)
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//       https://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//
//  Contributors:
//  Jason Shen (jason.shen.gm@gmail.com) (https://github.com/jason-is-debugging)
//
#ifndef CERYS_LITERALLIST_C224B4552B744372B7AB07287C80FA29_H
#define CERYS_LITERALLIST_C224B4552B744372B7AB07287C80FA29_H

#include <initializer_list>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace cerys {

template <typename T>
class LiteralList {
public:
    using List = std::vector<LiteralList>;
    using Storage = std::variant<T, List>;

private:
    Storage m_data;

public:
    // Empty list: {}
    LiteralList() : m_data(List{}) {}

    // Leaf: LiteralList<int> x{42};
    // ReSharper disable once CppNonExplicitConvertingConstructor
    LiteralList(T value) : m_data(std::move(value)) {}

    // Initializer list of values: LiteralList<int> x{{1, 2, 3}};
    LiteralList(std::initializer_list<T> init) : m_data(List{}) {
        for (const auto& item : init) {
            std::get<List>(m_data).emplace_back(item);
        }
    }

    // Nested initializer lists: LiteralList<int> x{{1}, {2}};
    // This handles the case where each element is itself an initializer_list
    LiteralList(std::initializer_list<std::initializer_list<T>> init) : m_data(List{}) {
        for (const auto& inner : init) {
            std::get<List>(m_data).emplace_back(inner);
        }
    }

    // Programmatic list construction
    // ReSharper disable once CppNonExplicitConvertingConstructor
    LiteralList(List list) : m_data(std::move(list)) {}

    [[nodiscard]] bool isLeaf() const noexcept {
        return std::holds_alternative<T>(m_data);
    }

    [[nodiscard]] bool isList() const noexcept {
        return std::holds_alternative<List>(m_data);
    }

    const T& leaf() const {
        return std::get<T>(m_data);
    }

    T& leaf() {
        return std::get<T>(m_data);
    }

    const List& children() const {
        return std::get<List>(m_data);
    }

    List& children() {
        return std::get<List>(m_data);
    }
};
}

#endif //CERYS_LITERALLIST_C224B4552B744372B7AB07287C80FA29_H
