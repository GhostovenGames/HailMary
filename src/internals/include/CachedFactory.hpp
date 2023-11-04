#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

/**
 * @brief Cache template class.
 *
 * @tparam CachedType Type of the object being cached.
 * @tparam loadFunction Function used to load the object to memory.
 * @tparam HashType Type of the class used to hash objects, by default string.
 */
template <class CachedType, class HashType = std::string> class CachedFactory {

  private:
    static std::unordered_map<HashType, std::unique_ptr<CachedType>> cache;

  public:
    /**
     * @brief Get an object from the cache.
     *
     * Get the an object value from the cache, if the object
     * using the loadFunction, if the object value is not in
     * the cache, cache it with the hash.
     *
     * @return CachedType
     */
    static const CachedType &get(HashType hash) {
        if (CachedFactory<CachedType, HashType>::cache.contains(hash)) {
            return *CachedFactory<CachedType, HashType>::cache.at(hash);
        }
        // Otherwise get the value first
        std::unique_ptr<CachedType> object = CachedType::load(hash);
        const CachedType &ret = *object;
        CachedFactory<CachedType, HashType>::cache.insert_or_assign(
            hash, std::move(object));
        return ret;
    }
};

template <class CachedType, class HashType>
std::unordered_map<HashType, std::unique_ptr<CachedType>>
    CachedFactory<CachedType, HashType>::cache;
