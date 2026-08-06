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

#ifndef CERYS_REGISTRY_9875HUSDO3435HSD234598H23598OHSEU_H
#define CERYS_REGISTRY_9875HUSDO3435HSD234598H23598OHSEU_H

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "defines.h"

namespace cerys::core::base {
template <typename ID>
class Registry {
public:
    static Registry& instance() {
        static Registry registry;
        return registry;
    }

    ID registerName(const std::string_view name) {
        const auto [it, inserted] = mNameToID.emplace(
            std::string{name},
            static_cast<ID>(mNames.size()));
        if (inserted) {
            mNames.emplace_back(it->first);
        }
        return it->second;
    }

    std::string const& getName(ID id) const {
        return mNames.at(static_cast<std::size_t>(id));
    }

    ID getID(const std::string_view name) const {
        return mNameToID.at(std::string{name});
    }

private:
    std::vector<std::string> mNames;
    std::unordered_map<std::string, ID> mNameToID;
};
}

#endif // CERYS_REGISTRY_9875HUSDO3435HSD234598H23598OHSEU_H