

#ifndef CERYS_IDGENERATOR_CCBD7FA66B874ADB8481B44AB0A7C0CB_H
#define CERYS_IDGENERATOR_CCBD7FA66B874ADB8481B44AB0A7C0CB_H
#include <atomic>

namespace cerys::core::utils {
template<typename T>
class IdGenerator {
    public:
    static T generateId() {
        const T id = m_id.load();
        atomic_fetch_add(&m_id, 1);
        return id;
    }
private:
    static std::atomic<T> m_id = 0;
};
}

#endif //CERYS_IDGENERATOR_CCBD7FA66B874ADB8481B44AB0A7C0CB_H
